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
#include <c3e/matrix_tuple.h>
#include <c3e/svd.h>
#include <c3e/vector.h>

c3e_svd c3e_svd_init(c3e_matrix* matrix) {
    int x = matrix->rows, y = matrix->cols;
    c3e_matrix_tuple left_sg, right_sg;

    c3e_matrix* left = c3e_matrix_identity(x);
    c3e_matrix* right = c3e_matrix_identity(y);
    c3e_matrix* singular = c3e_matrix_copy(matrix);

    for(int i = 0; i < 100; i++) {
        left_sg = c3e_matrix_qr_decomp(singular);
        singular = left_sg.b;
        left = c3e_matrix_mul(left, left_sg.a);

        right_sg = c3e_matrix_qr_decomp(c3e_matrix_transpose(singular));
        singular = c3e_matrix_transpose(right_sg.b);
        right = c3e_matrix_mul(right, right_sg.a);

        if(c3e_vector_all_close(
            c3e_matrix_diagonal(singular, 0),
            c3e_vector_zeros(singular->rows)
        )) break;
    }

    c3e_vector* sigma = c3e_matrix_diagonal(singular, 0);

    c3e_matrix_free(singular);
    c3e_matrix_tuple_free(left_sg);
    c3e_matrix_tuple_free(right_sg);

    c3e_svd svd;
    svd.singular = sigma;
    svd.left = left;
    svd.right = c3e_matrix_transpose(right);

    return svd;
}

void c3e_svd_free(c3e_svd svd) {
    c3e_matrix_free(svd.left);
    c3e_matrix_free(svd.right);
    c3e_vector_free(svd.singular);
}