#include <c3e/matrix.h>
#include <c3e/tensor.h>
#include <c3e/vector.h>
#include <assert.h>
#include <stdlib.h>

c3e_tensor* c3e_tensor_init(size_t dsize, uint32_t dims, c3e_matrix** matrices, c3e_vector* data) {
    assert(dsize);
    assert(dims != 0);

    assert(matrices != NULL);

    assert(data != NULL);
    assert(data->size == dsize);

    c3e_tensor* tensor = (c3e_tensor*) malloc(sizeof(c3e_tensor));
    if(tensor == NULL)
        return NULL;

    tensor->dimensions = dims;
    tensor->dimension_size = dsize;
    tensor->data = data;

    tensor->matrices = (c3e_matrix**)malloc(dims * sizeof(c3e_matrix*));
    if(tensor->matrices == NULL) {
        free(tensor);
        return NULL;
    }

    for(uint32_t i = 0; i < dims; i++) {
        tensor->matrices[i] = matrices[i];

        if(tensor->matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                free(tensor->matrices[j]);

            free(tensor->matrices);
            free(tensor);

            return NULL;
        }
    }

    return tensor;
}

void c3e_tensor_free(c3e_tensor* tensor) {
    assert(tensor != NULL);

    if(tensor->matrices != NULL) {
        for(uint32_t i = 0; i < tensor->dimensions; i++)
            if(tensor->matrices[i] != NULL)
                c3e_matrix_free(tensor->matrices[i]);
        
        free(tensor->matrices);
    }

    if(tensor->data != NULL)
        c3e_vector_free(tensor->data);
    free(tensor);
}

c3e_tensor* c3e_tensor_add(c3e_tensor* left, c3e_tensor* right) {
    assert(left != NULL);
    assert(right != NULL);
    
    assert(left->dimensions == right->dimensions);
    assert(left->dimension_size == right->dimension_size);

    c3e_matrix* matrices[left->dimensions];
    for(uint32_t i = 0; i < left->dimensions; i++) {
        matrices[i] = c3e_matrix_add(left->matrices[i], right->matrices[i]);

        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }
    }

    c3e_vector* sum_data = c3e_vector_add(left->data, right->data);
    if(sum_data == NULL) {
        for(uint32_t i = 0; i < left->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(left->dimension_size, left->dimensions, matrices, sum_data);
}

c3e_tensor* c3e_tensor_sub(c3e_tensor* left, c3e_tensor* right) {
    assert(left != NULL);
    assert(right != NULL);

    assert(left->dimensions == right->dimensions);
    assert(left->dimension_size == right->dimension_size);

    c3e_matrix* matrices[left->dimensions];
    for(uint32_t i = 0; i < left->dimensions; i++) {
        matrices[i] = c3e_matrix_sub(left->matrices[i], right->matrices[i]);

        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }
    }

    c3e_vector* sub_data = c3e_vector_sub(left->data, right->data);
    if(sub_data == NULL) {
        for(uint32_t i = 0; i < left->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(left->dimension_size, left->dimensions, matrices, sub_data);
}

c3e_tensor* c3e_tensor_mul(c3e_tensor* left, c3e_tensor* right) {
    assert(left != NULL);
    assert(right != NULL);

    assert(left->dimensions == right->dimensions);
    assert(left->dimension_size == right->dimension_size);

    c3e_matrix* matrices[left->dimensions];
    for(uint32_t i = 0; i < left->dimensions; i++) {
        matrices[i] = c3e_matrix_mul(left->matrices[i], right->matrices[i]);

        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }
    }

    c3e_vector* mul_data = c3e_vector_mul(left->data, right->data);
    if(mul_data == NULL) {
        for(uint32_t i = 0; i < left->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(left->dimension_size, left->dimensions, matrices, mul_data);
}

c3e_tensor* c3e_tensor_div(c3e_tensor* left, c3e_tensor* right) {
    assert(left != NULL);
    assert(right != NULL);

    assert(left->dimensions == right->dimensions);
    assert(left->dimension_size == right->dimension_size);

    c3e_matrix* matrices[left->dimensions];
    for(uint32_t i = 0; i < left->dimensions; i++) {
        matrices[i] = c3e_matrix_div(left->matrices[i], right->matrices[i]);

        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }
    }

    c3e_vector* div_data = c3e_vector_div(left->data, right->data);
    if(div_data == NULL) {
        for(uint32_t i = 0; i < left->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(left->dimension_size, left->dimensions, matrices, div_data);
}

c3e_tensor* c3e_tensor_scale(c3e_tensor* tensor, int x) {
    assert(tensor != NULL);
    assert(x != 0);

    c3e_matrix* matrices[tensor->dimensions];
    for(uint32_t i = 0; i < tensor->dimensions; i++) {
        matrices[i] = c3e_matrix_scale(tensor->matrices[i], x);

        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }
    }

    c3e_vector* scaled_data = c3e_vector_scale(tensor->data, x);
    if(scaled_data == NULL) {
        for(uint32_t i = 0; i < tensor->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(tensor->dimension_size, tensor->dimensions, matrices, scaled_data);
}

c3e_tensor* c3e_tensor_exp(c3e_tensor* tensor) {
    assert(tensor != NULL);

    c3e_matrix* matrices[tensor->dimensions];
    for(uint32_t i = 0; i < tensor->dimensions; i++) {
        matrices[i] = c3e_matrix_exp(tensor->matrices[i]);

        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }
    }

    c3e_vector* exp_data = c3e_vector_exp(tensor->data);
    if(exp_data == NULL) {
        for(uint32_t i = 0; i < tensor->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(tensor->dimension_size, tensor->dimensions, matrices, exp_data);
}

c3e_tensor* c3e_tensor_normalize(c3e_tensor* tensor) {
    assert(tensor != NULL);

    c3e_matrix* matrices[tensor->dimensions];
    for(uint32_t i = 0; i < tensor->dimensions; i++) {
        matrices[i] = c3e_matrix_normalize(tensor->matrices[i]);

        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }
    }

    c3e_vector* exp_data = c3e_vector_normalize(tensor->data);
    if(exp_data == NULL) {
        for(uint32_t i = 0; i < tensor->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(tensor->dimension_size, tensor->dimensions, matrices, exp_data);
}

c3e_tensor* c3e_tensor_copy(c3e_tensor* tensor) {
    assert(tensor != NULL);

    c3e_matrix* matrices[tensor->dimensions];
    for(uint32_t i = 0; i < tensor->dimensions; i++) {
        matrices[i] = c3e_matrix_copy(tensor->matrices[i]);

        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }
    }

    c3e_vector* exp_data = c3e_vector_copy(tensor->data);
    if(exp_data == NULL) {
        for(uint32_t i = 0; i < tensor->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(tensor->dimension_size, tensor->dimensions, matrices, exp_data);
}

c3e_tensor* c3e_tensor_zeros(size_t dsize, uint32_t dims, int rows, int cols) {
    assert(dsize != rows * cols);

    c3e_matrix* matrices[dims];
    for(uint32_t i = 0; i < dims; i++)
        matrices[i] = c3e_matrix_zeros(rows, cols);

    return c3e_tensor_init(dsize, dims, matrices, c3e_vector_zeros(dsize));
}

c3e_tensor* c3e_tensor_ones(size_t dsize, uint32_t dims, int rows, int cols) {
    assert(dsize != rows * cols);

    c3e_matrix* matrices[dims];
    for(uint32_t i = 0; i < dims; i++)
        matrices[i] = c3e_matrix_ones(rows, cols);

    return c3e_tensor_init(dsize, dims, matrices, c3e_vector_ones(dsize));
}

c3e_tensor* c3e_tensor_fill(size_t dsize, uint32_t dims, int rows, int cols, c3e_number values) {
    assert(dsize != rows * cols);

    c3e_matrix* matrices[dims];
    for(uint32_t i = 0; i < dims; i++) {
        matrices[i] = c3e_matrix_init(rows, cols);
        c3e_matrix_fill(matrices[i], values);
    }

    return c3e_tensor_init(dsize, dims, matrices, c3e_vector_zeros(dsize));
}

c3e_tensor* c3e_tensor_random(size_t dsize, uint32_t dims, int rows, int cols, int seed) {
    assert(dsize != rows * cols);

    c3e_matrix* matrices[dims];
    for(uint32_t i = 0; i < dims; i++)
        matrices[i] = c3e_matrix_random(rows, cols, seed);

    return c3e_tensor_init(dsize, dims, matrices, c3e_vector_random(dsize, seed));
}

c3e_tensor* c3e_tensor_random_bound(size_t dsize, uint32_t dims, int rows, int cols, int seed, c3e_number min, c3e_number max) {
    assert(dsize != rows * cols);

    c3e_matrix* matrices[dims];
    for(uint32_t i = 0; i < dims; i++)
        matrices[i] = c3e_matrix_random_bound(rows, cols, seed, min, max);

    return c3e_tensor_init(dsize, dims, matrices, c3e_vector_random_bound(dsize, seed, min, max));
}

bool c3e_tensor_equals(c3e_tensor* tensor, c3e_tensor* subject) {
    bool equals = false;

    for(uint32_t i = 0; i < tensor->dimension_size; i++)
        equals = equals && c3e_matrix_equals(tensor->matrices[i], subject->matrices[i]);

    equals = equals && c3e_vector_equals(tensor->data, subject->data);
    return equals;
}

bool c3e_tensor_all_close(c3e_tensor* tensor, c3e_tensor* subject) {
    bool all_close = false;

    for(uint32_t i = 0; i < tensor->dimension_size; i++)
        all_close = all_close && c3e_matrix_all_close(tensor->matrices[i], subject->matrices[i]);

    all_close = all_close && c3e_vector_all_close(tensor->data, subject->data);
    return all_close;
}
