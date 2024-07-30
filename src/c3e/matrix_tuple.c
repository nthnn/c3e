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

#include <c3e/assert.h>
#include <c3e/matrix.h>
#include <c3e/matrix_tuple.h>
#include <c3e/vector.h>

c3e_matrix_tuple c3e_matrix_qr_decomp(c3e_matrix* matrix) {
    c3e_assert(matrix->rows == matrix->cols);
    c3e_assert(c3e_matrix_determinant(matrix) != 0.0);

    c3e_matrix* original = c3e_matrix_copy(matrix);
    c3e_matrix* orthogonal = c3e_matrix_zeros(matrix->rows, matrix->cols);
    c3e_matrix* uppertri = c3e_matrix_zeros(matrix->rows, matrix->cols);

    for(int i = 0; i < original->cols; i++) {
        c3e_matrix_col_copy(original, i, orthogonal, i);

        for(int j = 0; j < i; j++) {
            c3e_number r = c3e_vector_dot_cols(orthogonal, i, orthogonal, j); 

            MATRIX_ELEM(uppertri, j, i) = r;
            c3e_matrix_col_sub(orthogonal, i, orthogonal, j, r);
        }

        c3e_number norm = c3e_vector_length(orthogonal, i);
        MATRIX_ELEM(uppertri, i, i) = norm;
        c3e_matrix_col_div(orthogonal, i, norm);
    }

    c3e_matrix_tuple tuple;
    tuple.a = orthogonal;
    tuple.b = uppertri;

    c3e_matrix_free(original);
    return tuple;
}

c3e_matrix_tuple c3e_matrix_lu_decomp(c3e_matrix* orig) {
    c3e_assert(orig->rows == orig->cols);

    int n = orig->rows;
    c3e_matrix* lower = c3e_matrix_init(n, n);
    c3e_matrix* upper = c3e_matrix_init(n, n);

    for(int i = 0; i < n; i++) {
        for(int k = 0; k < n; k++) {
            c3e_number sum = 0.0;

            for(int j = 0; j < i; j++)
                sum += MATRIX_ELEM(lower, i, j) * MATRIX_ELEM(upper, j, k);
            MATRIX_ELEM(upper, i, k) = MATRIX_ELEM(orig, i, k) - sum;
        }

        for(int k = i + 1; k < n; k++) {
            c3e_number sum = 0.0;

            for(int j = 0; j < i; j++)
                sum += MATRIX_ELEM(lower, k, j) * MATRIX_ELEM(upper, j, i);
            MATRIX_ELEM(lower, k, i) = (MATRIX_ELEM(orig, k, i) - sum) / MATRIX_ELEM(upper, i, i);
        }

        MATRIX_ELEM(lower, i, i) = 1.0;
    }

    c3e_matrix_tuple tuple;
    tuple.a = lower;
    tuple.b = upper;

    return tuple;
}

void c3e_matrix_tuple_free(c3e_matrix_tuple tuple) {
    c3e_matrix_free(tuple.a);
    c3e_matrix_free(tuple.b);
}