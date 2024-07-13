#ifndef C3E_TENSOR_H
#define C3E_TENSOR_H

#include <c3e/commons.h>

c3e_tensor* c3e_tensor_init(
    size_t dimension_size,
    uint32_t dimensions,
    c3e_matrix** matrices,
    c3e_vector* data
);

void c3e_tensor_free(c3e_tensor* tensor);

c3e_tensor* c3e_tensor_add(c3e_tensor* left, c3e_tensor* right);
c3e_tensor* c3e_tensor_sub(c3e_tensor* left, c3e_tensor* right);
c3e_tensor* c3e_tensor_mul(c3e_tensor* left, c3e_tensor* right);
c3e_tensor* c3e_tensor_div(c3e_tensor* left, c3e_tensor* right);
c3e_tensor* c3e_tensor_scale(c3e_tensor* tensor, int x);
c3e_tensor* c3e_tensor_exp(c3e_tensor* tensor);

#endif