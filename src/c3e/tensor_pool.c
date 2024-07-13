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

#include <c3e/tensor_pool.h>
#include <assert.h>
#include <stdlib.h>

c3e_tensor_pool* c3e_tensor_pool_create(size_t size) {
    assert(size);

    c3e_tensor_pool* pool = (c3e_tensor_pool*)
        malloc(sizeof(c3e_tensor_pool));
    if(pool == NULL)
        return NULL;

    pool->memory = 0;
    pool->allocs = 0;
    pool->size = size;
    pool->data = malloc(pool->size);

    if(pool->data == NULL) {
        free(pool);
        return NULL;
    }

    return pool;
}

void* c3e_tensor_pool_alloc(
    c3e_tensor_pool* pool,
    size_t size,
    uint32_t *id
) {
    assert(pool);
    assert(size);

    size = (size + 8 - 1) & ~7;
    if(pool->memory + size > pool->size)
        return NULL;

    void* ptr = pool->data + pool->memory;
    pool->memory += size;

    if(id != NULL)
        *id = ++pool->allocs;

    return ptr;
}

void c3e_tensor_pool_reset(c3e_tensor_pool* pool) {
    assert(pool);
    assert(pool->data);

    pool->memory = 0;
    pool->allocs = 0;
}

void c3e_tensor_pool_free(c3e_tensor_pool* pool) {
    if(pool) {
        c3e_tensor_pool_reset(pool);

        free(pool->data);
        free(pool);
    }
}