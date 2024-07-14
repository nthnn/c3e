#include <c3e/matrix.h>
#include <c3e/tensor.h>
#include <c3e/vector.h>
#include <assert.h>
#include <stdlib.h>

c3e_tensor* c3e_tensor_init(
    size_t dimension_size,
    uint32_t dimensions,
    c3e_matrix** matrices,
    c3e_vector* data
) {
    assert(dimension_size);
    assert(dimensions != 0);

    assert(matrices != NULL);

    assert(data != NULL);
    assert(data->size == dimension_size);

    c3e_tensor* tensor = (c3e_tensor*)
        malloc(sizeof(c3e_tensor));
    if(tensor == NULL)
        return NULL;

    tensor->dimensions = dimensions;
    tensor->dimension_size = dimension_size;
    tensor->data = data;

    tensor->matrices = (c3e_matrix**)malloc(dimensions * sizeof(c3e_matrix*));
    if(tensor->matrices == NULL) {
        free(tensor);
        return NULL;
    }

    for(uint32_t i = 0; i < dimensions; i++) {
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

        matrices[i] = c3e_matrix_add(
            left->matrices[i],
            right->matrices[i]
        );
    }

    c3e_vector* sum_data = c3e_vector_add(
        left->data,
        right->data
    );
    if(sum_data == NULL) {
        for(uint32_t i = 0; i < left->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(
        left->dimension_size,
        left->dimensions,
        matrices,
        sum_data
    );
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

        matrices[i] = c3e_matrix_sub(
            left->matrices[i],
            right->matrices[i]
        );
    }

    c3e_vector* sum_data = c3e_vector_sub(
        left->data,
        right->data
    );
    if(sum_data == NULL) {
        for(uint32_t i = 0; i < left->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(
        left->dimension_size,
        left->dimensions,
        matrices,
        sum_data
    );
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

        matrices[i] = c3e_matrix_mul(
            left->matrices[i],
            right->matrices[i]
        );
    }

    c3e_vector* sum_data = c3e_vector_mul(
        left->data,
        right->data
    );
    if(sum_data == NULL) {
        for(uint32_t i = 0; i < left->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(
        left->dimension_size,
        left->dimensions,
        matrices,
        sum_data
    );
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

        matrices[i] = c3e_matrix_div(
            left->matrices[i],
            right->matrices[i]
        );
    }

    c3e_vector* sum_data = c3e_vector_div(
        left->data,
        right->data
    );
    if(sum_data == NULL) {
        for(uint32_t i = 0; i < left->dimensions; i++)
            c3e_matrix_free(matrices[i]);

        return NULL;
    }

    return c3e_tensor_init(
        left->dimension_size,
        left->dimensions,
        matrices,
        sum_data
    );
}