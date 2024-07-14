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

    if(tensor->matrices != NULL)
        for(uint32_t i = 0; i < tensor->dimensions; i++)
            if(tensor->matrices[i] != NULL)
                c3e_matrix_free(tensor->matrices[i]);

    if(tensor->data != NULL)
        c3e_vector_free(tensor->data);
}

c3e_tensor* c3e_tensor_add(c3e_tensor* left, c3e_tensor* right) {
    assert(left != NULL);
    assert(right != NULL);
    
    assert(left->dimensions == right->dimensions);
    assert(left->dimension_size == right->dimension_size);

    c3e_matrix* matrices[left->dimensions];
    for(uint32_t i = 0; i < left->dimensions; i++) {
        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }

        matrices[i] = c3e_matrix_add(left->matrices[i], right->matrices[i]);
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
        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }

        matrices[i] = c3e_matrix_sub(left->matrices[i], right->matrices[i]);
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
        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }

        matrices[i] = c3e_matrix_mul(left->matrices[i], right->matrices[i]);
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
        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }

        matrices[i] = c3e_matrix_div(left->matrices[i], right->matrices[i]);
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
        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }

        matrices[i] = c3e_matrix_scale(tensor->matrices[i], x);
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
    assert(x != 0);

    c3e_matrix* matrices[tensor->dimensions];
    for(uint32_t i = 0; i < tensor->dimensions; i++) {
        if(matrices[i] == NULL) {
            for(uint32_t j = 0; j < i; j++)
                c3e_matrix_free(matrices[j]);

            return NULL;
        }

        matrices[i] = c3e_matrix_exp(tensor->matrices[i]);
    }

    c3e_vector* exp_data = c3e_vector_exp(tensor->data);
    if(exp_data == NULL) {
        for(uint32_t i = 0; i < tensor->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(tensor->dimension_size, tensor->dimensions, matrices, exp_data);
}