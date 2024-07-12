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

#include <c3e/matrix.h>
#include <c3e/trigo.h>
#include <c3e/vector.h>

#include <assert.h>
#include <math.h>
#include <stdlib.h>

c3e_vector* c3e_vector_init(size_t size) {
    c3e_vector* vector = (c3e_vector*) malloc(sizeof(c3e_vector));
    vector->size = size;
    vector->data = (c3e_number*) calloc(size, sizeof(c3e_number));

    return vector;
}

void c3e_vector_free(c3e_vector* vector) {
    free(vector->data);
    free(vector);
}

c3e_number c3e_vector_length(c3e_matrix* matrix, int col) {
    c3e_number sum = 0.0;

    for(int i = 0; i < matrix->rows; i++)
        sum += MATRIX_ELEM_AT(matrix, i, col) *
            MATRIX_ELEM_AT(matrix, i, col);

    return sqrt(sum);
}

c3e_number c3e_vector_get(c3e_vector* vector, size_t index) {
    if(index >= vector->size)
        return 0.0;

    return vector->data[index];
}

void c3e_vector_set(c3e_vector* vector, size_t index, c3e_number value) {
    if(index >= vector->size)
        return;

    vector->data[index] = value;
}

void c3e_vector_set_elements(c3e_vector* vector, c3e_number* values) {
    for(int i = 0; i < vector->size; i++)
        vector->data[i] = values[i];
}

c3e_vector* c3e_vector_add(c3e_vector* vector, c3e_vector* subject) {
    assert(vector->size == subject->size);

    c3e_vector* out = c3e_vector_init(vector->size);
    for(int i = 0; i < out->size; i++)
        out->data[i] = (vector->data[i] + subject->data[i]);

    return out;
}

c3e_vector* c3e_vector_sub(c3e_vector* vector, c3e_vector* subject) {
    assert(vector->size == subject->size);

    c3e_vector* out = c3e_vector_init(vector->size);
    for(int i = 0; i < out->size; i++)
        out->data[i] = (vector->data[i] - subject->data[i]);

    return out;
}

c3e_vector* c3e_vector_mul(c3e_vector* vector, c3e_vector* subject){
    assert(vector->size == subject->size);

    c3e_vector* out = c3e_vector_init(vector->size);
    for(int i = 0; i < vector->size; i++)
        out->data[i] = vector->data[i] * subject->data[i];

    return out;
}

c3e_vector* c3e_vector_div(c3e_vector* vector, c3e_vector* subject){
    assert(vector->size == subject->size);

    c3e_vector* out = c3e_vector_init(vector->size);
    for(int i = 0; i < vector->size; i++)
        out->data[i] = vector->data[i] / subject->data[i];

    return out;
}

c3e_vector* c3e_vector_exp(c3e_vector* vector) {
    c3e_vector* out = c3e_vector_copy(vector);

    for(int i = 0; i < vector->size; i++)
        out->data[i] = exp(vector->data[i]);

    return out;
}

c3e_vector* c3e_vector_scale(c3e_vector* vector, int x) {
    c3e_vector* out = c3e_vector_init(vector->size);

    for(int i = 0; i < out->size; i++)
        out->data[i] = vector->data[i] * x;

    return out;
}

c3e_number c3e_vector_sum(c3e_vector* vector) {
    c3e_number sum = 0.0;

    for(int i = 0; i < vector->size; i++)
        sum += vector->data[i];

    return sum;
}

c3e_number c3e_vector_norm(c3e_vector* vector) {
    c3e_number out = 0.0;

    for(int i = 0; i < vector->size; i++)
        out += vector->data[i] * vector->data[i];

    return sqrt(out);
}

c3e_number c3e_vector_angle(c3e_vector* vector, c3e_vector* subject) {
    c3e_number vec = c3e_vector_norm(vector),
        sub = c3e_vector_norm(subject),
        product = c3e_vector_dot(vector, subject);

    return acos(product / (vec * sub));
}

c3e_number c3e_vector_cross(c3e_vector* vector, c3e_vector* subject) {
    return (c3e_vector_norm(vector) * c3e_vector_norm(subject)) *
        sin(c3e_radian_degrees(c3e_vector_angle(vector, subject)));
}

c3e_number c3e_vector_projection(c3e_vector* vector, c3e_vector* subject) {
    return c3e_vector_dot(vector, subject) /
        c3e_vector_norm(subject);
}

c3e_number c3e_vector_dot(c3e_vector* vector, c3e_vector* subject) {
    assert(vector->size == subject->size);

    c3e_number out = 0.0;
    for(int i = 0; i < vector->size; i++)
        out += vector->data[i] * subject->data[i];

    return out;
}

c3e_number c3e_vector_dot_cols(
    c3e_matrix* matrix,
    int col1,
    c3e_matrix* subject,
    int col2
) {
    c3e_number dot = 0;

    for(int i = 0; i < matrix->rows; i++)
        dot += MATRIX_ELEM_AT(matrix, i, col1) *
            MATRIX_ELEM_AT(subject, i, col2);

    return dot;
}

c3e_vector* c3e_vector_normalize(c3e_vector* vector) {
    c3e_vector* out = c3e_vector_init(vector->size);
    c3e_number norm = c3e_vector_norm(vector);

    for(int i = 0; i < vector->size; i++)
        out->data[i] = (vector->data[i] / norm);

    return out;
}

c3e_vector* c3e_vector_transform(c3e_vector* vector, c3e_matrix* matrix) {
    assert(matrix->cols == vector->size);

    c3e_vector* out = c3e_vector_zeros(matrix->rows);
    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            out->data[i] +=
                MATRIX_ELEM_AT(matrix, i, j) *
                vector->data[j];

    return out;
}

c3e_vector* c3e_vector_zeros(size_t size) {
    c3e_vector* out = c3e_vector_init(size);

    for(int i = 0; i < size; i++)
        out->data[i] = 0.0;

    return out;
}

c3e_vector* c3e_vector_ones(size_t size) {
    c3e_vector* out = c3e_vector_init(size);

    for(int i = 0; i < size; i++)
        out->data[i] = 1.0;

    return out;
}

c3e_vector* c3e_vector_random(size_t size, int seed) {
    if(seed != 0)
        srand(seed);

    c3e_vector* out = c3e_vector_init(size);
    for(int i = 0; i < size; i++)
        out->data[i] = (c3e_number) rand() / (c3e_number) RAND_MAX;

    return out;
}

c3e_vector* c3e_vector_copy(c3e_vector* vector) {
    c3e_vector* out = c3e_vector_init(vector->size);
    for(int i = 0; i < vector->size; i++)
        out->data[i] = vector->data[i];

    return out;
}

bool c3e_vector_equal(c3e_vector* vector, c3e_vector* subject) {
    if(vector->size != subject->size)
        return false;

    for(int i = 0; i < vector->size; i++)
        if(vector->data[i] != subject->data[i])
            return false;

    return true;
}

bool c3e_vector_all_close(c3e_vector* vector, c3e_vector* subject) {
    if(vector->size != subject->size)
        return false;

    for(int i = 0; i < vector->size; i++)
        if(fabs(vector->data[i] - subject->data[i]) >
            (1e-08 + 1e-05 * fabs(subject->data[i])))
            return false;

    return true;
}