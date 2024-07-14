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

#ifndef C3E_MATRIX_H
#define C3E_MATRIX_H

#include <c3e/commons.h>

#define MATRIX_ELEM(matrix, row, col) \
    (matrix)->data[(row) * (matrix)->cols + (col)]

c3e_matrix* c3e_matrix_init(int rows, int cols);
void c3e_matrix_free(c3e_matrix* matrix);
void c3e_matrix_set_elements(c3e_matrix* matrix, c3e_number* values);
void c3e_matrix_fill(c3e_matrix* matrix, c3e_number value);

c3e_number c3e_matrix_get_at(c3e_matrix* matrix, int row, int col);
int c3e_matrix_size(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_ones(int rows, int cols);
c3e_matrix* c3e_matrix_ones_like(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_zeros(int rows, int cols);
c3e_matrix* c3e_matrix_zeros_like(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_full(int rows, int cols, c3e_number value);
c3e_matrix* c3e_matrix_full_like(c3e_matrix* matrix, c3e_number value);

c3e_matrix* c3e_matrix_identity(int side);
c3e_matrix* c3e_matrix_random(int rows, int cols, int seed);
c3e_matrix* c3e_matrix_random_bound(int rows, int cols, int seed, c3e_number min, c3e_number max);

c3e_matrix* c3e_matrix_copy(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_append(c3e_matrix* matrix, c3e_matrix* subject, int axis);

c3e_matrix* c3e_matrix_add(c3e_matrix* matrix, c3e_matrix* subject);
c3e_matrix* c3e_matrix_sub(c3e_matrix* matrix, c3e_matrix* subject);
c3e_matrix* c3e_matrix_mul(c3e_matrix* matrix, c3e_matrix* subject);
c3e_matrix* c3e_matrix_div(c3e_matrix* matrix, c3e_matrix* subject);
c3e_matrix* c3e_matrix_dot(c3e_matrix* matrix, c3e_matrix* subject);

c3e_matrix* c3e_matrix_scale(c3e_matrix* matrix, int x);
c3e_matrix* c3e_matrix_transpose(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_slice(c3e_matrix* matrix, int frows, int trows, int fcols, int tcols);
void c3e_matrix_col_copy(c3e_matrix* matrix, int col, c3e_matrix* dst, int dst_col);

void c3e_matrix_col_sub(c3e_matrix* matrix, int col, c3e_matrix* dst, int dcol, c3e_number scalar);
void c3e_matrix_col_div(c3e_matrix* matrix, int col, c3e_number scalar);

c3e_number c3e_matrix_trace(c3e_matrix* matrix);
c3e_number c3e_matrix_determinant(c3e_matrix* matrix);
c3e_number c3e_matrix_log_determ(c3e_matrix* matrix);
c3e_number c3e_matrix_frobenius(c3e_matrix* matrix);
c3e_number c3e_matrix_l1_norm(c3e_matrix* matrix);
c3e_number c3e_matrix_infinity_norm(c3e_matrix* matrix);

void c3e_matrix_add_row(c3e_matrix* matrix, int row1, int row2, c3e_number scalar);
void c3e_matrix_swap_rows(c3e_matrix* matrix, int row1, int row2);
void c3e_matrix_multiply_row(c3e_matrix* matrix, int row1, c3e_number scalar);

c3e_matrix* c3e_matrix_normalize(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_row_echelon(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_inverse(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_qr_algo(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_cholesky_decomp(c3e_matrix* matrix);

int c3e_matrix_rank(c3e_matrix* matrix);
int c3e_matrix_non_zero_rows(c3e_matrix* matrix);
int c3e_matrix_find_pivot(c3e_matrix* matrix, int col, int row);

c3e_matrix* c3e_matrix_tril(c3e_matrix* matrix, int diag);
c3e_matrix* c3e_matrix_triu(c3e_matrix* matrix, int diag);
c3e_vector* c3e_matrix_diagonal(c3e_matrix* matrix, int k);

c3e_number c3e_matrix_sum(c3e_matrix* matrix);
c3e_number c3e_matrix_max(c3e_matrix* matrix);
c3e_number c3e_matrix_min(c3e_matrix* matrix);
c3e_number c3e_matrix_mean(c3e_matrix* matrix);
c3e_number c3e_matrix_std(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_min_vals(c3e_matrix* matrix, int dim);
c3e_matrix* c3e_matrix_max_values(c3e_matrix* matrix, int dim);
c3e_matrix* c3e_matrix_sum_vals(c3e_matrix* matrix, int dim);
c3e_matrix* c3e_matrix_mean_vals(c3e_matrix* matrix, int dim);
c3e_matrix* c3e_matrix_std_vals(c3e_matrix* matrix, int dim);

bool c3e_matrix_all_close(c3e_matrix* matrix, c3e_matrix* subject);

c3e_matrix* c3e_matrix_from_vec(c3e_vector* vector);
c3e_matrix* c3e_matrix_eigenvec(c3e_matrix* matrix);
c3e_vector* c3e_matrix_eigenvalues(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_vec_mul(c3e_matrix* matrix, c3e_vector* vector);

c3e_matrix* c3e_matrix_scalar_add(c3e_matrix* matrix, c3e_number x);
c3e_matrix* c3e_matrix_scalar_sub(c3e_matrix* matrix, c3e_number x);
c3e_matrix* c3e_matrix_scalar_mul(c3e_matrix* matrix, c3e_number x);
c3e_matrix* c3e_matrix_scalar_div(c3e_matrix* matrix, c3e_number x);

c3e_matrix* c3e_matrix_flatten(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_reshape(c3e_matrix* matrix, int rows, int cols);
c3e_matrix* c3e_matrix_clip(c3e_matrix* matrix, c3e_number min, c3e_number max);

c3e_matrix* c3e_matrix_arc_sin(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_arc_sinh(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_sin(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_sinh(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_arc_cos(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_arc_cosh(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_cos(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_cosh(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_arc_tan(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_arc_tanh(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_tan(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_tanh(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_abs(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_fabs(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_a_range(c3e_number start, c3e_number end, c3e_number step);

c3e_matrix* c3e_matrix_cum_sum(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_cum_product(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_log(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_log10(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_log2(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_log1p(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_reciproc(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_pow(c3e_matrix* matrix, c3e_number exp);
c3e_number c3e_matrix_product(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_rsqrt(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_sqrt(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_lerp(c3e_matrix* matrix, c3e_matrix* subject, c3e_number weight);

c3e_matrix* c3e_matrix_neg(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_sign(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_equals(c3e_matrix* matrix, c3e_matrix* subject);
c3e_matrix* c3e_matrix_less_than(c3e_matrix* matrix, c3e_matrix* subject);
c3e_matrix* c3e_matrix_less_than_eq(c3e_matrix* matrix, c3e_matrix* subject);
c3e_matrix* c3e_matrix_greater_than(c3e_matrix* matrix, c3e_matrix* subject);
c3e_matrix* c3e_matrix_greater_than_eq(c3e_matrix* matrix, c3e_matrix* subject);
c3e_matrix* c3e_matrix_exp(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_log_cumsum_exp(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_log_gamma(c3e_matrix* matrix);

void c3e_matrix_sort(c3e_matrix* matrix);
void c3e_matrix_resize(c3e_matrix* matrix, int rows, int cols);
void c3e_matrix_resize_as(c3e_matrix* matrix, c3e_matrix* subject);

c3e_matrix* c3e_matrix_get(c3e_matrix* matrix, c3e_matrix* subject);
c3e_matrix* c3e_matrix_repeat(c3e_matrix* matrix, int rrows, int rcols);
c3e_matrix* c3e_matrix_solve(c3e_matrix* matrix, c3e_matrix* subject);

int c3e_matrix_arg_min(c3e_matrix* matrix);
int c3e_matrix_arg_max(c3e_matrix* matrix);

c3e_matrix* c3e_matrix_arg_sort(c3e_matrix* matrix);
c3e_matrix* c3e_matrix_arg_min_vals(c3e_matrix* matrix, int dim);
c3e_matrix* c3e_matrix_arg_max_vals(c3e_matrix* matrix, int dim);

#endif