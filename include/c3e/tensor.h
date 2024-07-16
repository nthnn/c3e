#ifndef C3E_TENSOR_H
#define C3E_TENSOR_H

#include <c3e/commons.h>

c3e_tensor* c3e_tensor_init(size_t dsize, uint32_t dims, c3e_matrix** matrices, c3e_vector* data);
void c3e_tensor_free(c3e_tensor* tensor);

c3e_tensor* c3e_tensor_add(c3e_tensor* left, c3e_tensor* right);
c3e_tensor* c3e_tensor_sub(c3e_tensor* left, c3e_tensor* right);
c3e_tensor* c3e_tensor_mul(c3e_tensor* left, c3e_tensor* right);
c3e_tensor* c3e_tensor_div(c3e_tensor* left, c3e_tensor* right);
c3e_tensor* c3e_tensor_scale(c3e_tensor* tensor, int x);
c3e_tensor* c3e_tensor_exp(c3e_tensor* tensor);

c3e_tensor* c3e_tensor_normalize(c3e_tensor* tensor);
c3e_tensor* c3e_tensor_copy(c3e_tensor* tensor);

c3e_tensor* c3e_tensor_zeros(size_t dsize, uint32_t dims, int rows, int cols);
c3e_tensor* c3e_tensor_ones(size_t dsize, uint32_t dims, int rows, int cols);
c3e_tensor* c3e_tensor_fill(size_t dsize, uint32_t dims, int rows, int cols, c3e_number value);

c3e_tensor* c3e_tensor_random(size_t dsize, uint32_t dims, int rows, int cols, int seed);
c3e_tensor* c3e_tensor_random_bound(size_t dsize, uint32_t dims, int rows, int cols, int seed, c3e_number min, c3e_number max);

#endif