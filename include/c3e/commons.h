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

#ifndef C3E_COMMONS_H
#define C3E_COMMONS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

#ifndef C3E_32BIT_NUMBER
typedef double c3e_number;
#else
typedef float  c3e_number;
#endif

typedef struct {
    uint32_t size;
    c3e_number* data;
} c3e_vector;

typedef struct {
    uint32_t rows;
    uint32_t cols;
    c3e_number* data;
} c3e_matrix;

typedef struct {
    c3e_matrix* a;
    c3e_matrix* b;
} c3e_matrix_tuple;

typedef struct {
    c3e_matrix* left;
    c3e_matrix* right;
    c3e_vector* singular;
} c3e_svd;

typedef struct {
    uint32_t dimensions;
    size_t dimension_size;

    c3e_matrix** matrices;
    c3e_vector* data;
} c3e_tensor;

#endif