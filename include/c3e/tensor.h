#ifndef C3E_TENSOR_H
#define C3E_TENSOR_H

#include <c3e/commons.h>

c3e_tensor* c3e_tensor_init(
    size_t dimension_size,
    uint32_t* dimensions,
    c3e_vector* data
);

void c3e_tensor_free(c3e_tensor* tensor);

#endif