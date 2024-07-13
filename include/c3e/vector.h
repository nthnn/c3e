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

#ifndef C3E_VECTOR_H
#define C3E_VECTOR_H

#include <c3e/commons.h>
#include <stdlib.h>

c3e_vector* c3e_vector_init(size_t size);
void c3e_vector_free(c3e_vector* vector);

c3e_number c3e_vector_length(c3e_matrix* matrix, int col);
c3e_number c3e_vector_get(c3e_vector* vector, size_t index);
void c3e_vector_set(c3e_vector* vector, size_t index, c3e_number value);
void c3e_vector_set_elements(c3e_vector* vector, c3e_number* values);

c3e_vector* c3e_vector_add(c3e_vector* vector, c3e_vector* subject);
c3e_vector* c3e_vector_sub(c3e_vector* vector, c3e_vector* subject);
c3e_vector* c3e_vector_mul(c3e_vector* vector, c3e_vector* subject);
c3e_vector* c3e_vector_div(c3e_vector* vector, c3e_vector* subject);
c3e_vector* c3e_vector_exp(c3e_vector* vector);
c3e_vector* c3e_vector_scale(c3e_vector* vector, int x);

c3e_number c3e_vector_sum(c3e_vector* vector);
c3e_number c3e_vector_norm(c3e_vector* vector);
c3e_number c3e_vector_angle(c3e_vector* vector, c3e_vector* subject);
c3e_number c3e_vector_cross(c3e_vector* vector, c3e_vector* subject);
c3e_number c3e_vector_projection(c3e_vector* vector, c3e_vector* subject);

c3e_number c3e_vector_dot(c3e_vector* vector, c3e_vector* subject);
c3e_number c3e_vector_dot_cols(
    c3e_matrix* matrix,
    int col1,
    c3e_matrix* subject,
    int col2
);

c3e_vector* c3e_vector_normalize(c3e_vector* vector);
c3e_vector* c3e_vector_transform(c3e_vector* vector, c3e_matrix* matrix);
c3e_vector* c3e_vector_copy(c3e_vector* vector);

c3e_vector* c3e_vector_zeros(size_t size);
c3e_vector* c3e_vector_ones(size_t size);

c3e_vector* c3e_vector_random(size_t size, int seed);
c3e_vector* c3e_vector_random_bound(
    size_t size, int seed,
    c3e_number min, c3e_number max
);

bool c3e_vector_equal(c3e_vector* vector, c3e_vector* subject);
bool c3e_vector_all_close(c3e_vector* vector, c3e_vector* subject);

#endif