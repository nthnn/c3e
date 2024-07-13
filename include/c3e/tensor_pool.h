/*
 * Copyright 2024 Nathanne Isip
 * 
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the
 *    above copyright notice, this list of conditions
 *    and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the
 *    above copyright notice, this list of conditions
 *    and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 */

#ifndef C3E_TENSOR_H
#define C3E_TENSOR_H

#include <c3e/commons.h>
#include <stdlib.h>

c3e_tensor_pool* c3e_tensor_pool_create(size_t size);
void* c3e_tensor_pool_alloc(
    c3e_tensor_pool* pool,
    size_t size,
    uint32_t *id
);

void c3e_tensor_pool_reset(c3e_tensor_pool* pool);
void c3e_tensor_pool_free(c3e_tensor_pool* pool);

#endif