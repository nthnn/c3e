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
#include <c3e/random.h>
#include <c3e/svd.h>
#include <c3e/trigo.h>
#include <c3e/vector.h>

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

static inline void c3e_swap_number(c3e_number* a, c3e_number* b) {
    c3e_number temp = *a;
    *a = *b;
    *b = temp;
}

static inline int c3e_parition(c3e_number arr[], int low, int high) {
    c3e_number pivot = arr[high];
    int i = (low - 1);

    for(int j = low; j <= high - 1; j++)
        if(arr[j] <= pivot) {
            i++;
            c3e_swap_number(&arr[i], &arr[j]);
        }

    c3e_swap_number(&arr[i+1], &arr[high]);
    return (i + 1);
}

static inline void c3e_quick_sort(c3e_number arr[], int low, int high) {
    if(low < high) {
        int pi = c3e_parition(arr, low, high);

        c3e_quick_sort(arr, low , pi-1);
        c3e_quick_sort(arr, pi+1, high);
    }
}

c3e_matrix* c3e_matrix_init(int rows, int cols) {
    c3e_matrix* matrix = (c3e_matrix*) malloc(sizeof(c3e_matrix));
    if(matrix == NULL)
        return NULL;

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (c3e_number*) calloc(rows * cols, sizeof(c3e_number));

    if(matrix->data == NULL) {
        free(matrix);
        return NULL;
    }

    return matrix;
}

void c3e_matrix_free(c3e_matrix* matrix) {
    free(matrix->data);
    free(matrix);
}

void c3e_matrix_set_elements(c3e_matrix* matrix, c3e_number* values) {
    for(int i = 0; i < matrix->rows * matrix->cols; i++)
        matrix->data[i] = values[i];
}

void c3e_matrix_fill(c3e_matrix* matrix, c3e_number value) {
    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(matrix, i, j) = value;
}

c3e_number c3e_matrix_get_at(c3e_matrix* matrix, int row, int col) {
    return MATRIX_ELEM_AT(matrix, row, col);
}

int c3e_matrix_size(c3e_matrix* matrix) {
    return matrix->rows * matrix->cols;
}

c3e_matrix* c3e_matrix_ones(int rows, int cols) {
    c3e_matrix* out = c3e_matrix_init(rows, cols);

    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) = 1.0;

    return out;
}

c3e_matrix* c3e_matrix_ones_like(c3e_matrix* matrix) {
    return c3e_matrix_ones(matrix->rows, matrix->cols);
}

c3e_matrix* c3e_matrix_zeros(int rows, int cols) {
    c3e_matrix* out = c3e_matrix_init(rows, cols);
    memset(out->data, 0, (rows * cols) * sizeof(c3e_number)); 

    return out;
}

c3e_matrix* c3e_matrix_zeros_like(c3e_matrix* matrix) {
    return c3e_matrix_zeros(matrix->rows, matrix->cols);
}

c3e_matrix* c3e_matrix_full(int rows, int cols, c3e_number value) {
    c3e_matrix* out = c3e_matrix_init(rows, cols);

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            MATRIX_ELEM_AT(out, i, j) = value;

    return out;
}

c3e_matrix* c3e_matrix_full_like(c3e_matrix* matrix, c3e_number value) {
    return c3e_matrix_full(matrix->rows, matrix->cols, value);
}

c3e_matrix* c3e_matrix_identity(int side) {
    c3e_matrix* out = c3e_matrix_zeros(side, side);

    for(
        int i = 0, j = 0;
        i < out->rows && j < out->cols;
        i++, j++
    ) MATRIX_ELEM_AT(out, i, j) = 1.0; 

    return out;
}

c3e_matrix* c3e_matrix_random(int rows, int cols, int seed) {
    #ifndef __linux__
    if(seed != 0)
        srand(seed);
    #endif

    int size = rows * cols;
    c3e_matrix* matrix = c3e_matrix_init(rows, cols);
    c3e_number* rand_array = (c3e_number*) malloc(sizeof(c3e_number) * size);

    for(int i = 0; i < size; i++)
        rand_array[i] =
            c3e_random() /
            (c3e_number) RAND_MAX;

    c3e_matrix_set_elements(matrix, rand_array);
    return matrix;
}

c3e_matrix* c3e_matrix_random_bound(
    int rows, int cols, int seed,
    c3e_number min, c3e_number max
) {
    #ifndef __linux__
    if(seed != 0)
        srand(seed);
    #endif

    int size = rows * cols;
    c3e_matrix* matrix = c3e_matrix_init(rows, cols);
    c3e_number* rand_array = (c3e_number*) malloc(sizeof(c3e_number) * size);

    for(int i = 0; i < size; i++)
        rand_array[i] =
            c3e_random_bound(min, max) /
            (c3e_number) RAND_MAX;

    c3e_matrix_set_elements(matrix, rand_array);
    return matrix;
}

c3e_matrix* c3e_matrix_copy(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    c3e_matrix_set_elements(out, matrix->data);

    return out;
}

c3e_matrix* c3e_matrix_append(c3e_matrix* matrix, c3e_matrix* subject, int axis) {
    if(axis == 0) {
        assert(matrix->rows == subject->rows);

        c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols + subject->cols);
        for(int i = 0; i < matrix->rows; i++)
            for(int j = 0; j < matrix->cols; j++)
                MATRIX_ELEM_AT(out, i, j) =
                    MATRIX_ELEM_AT(matrix, i, j);

        for(int i = 0; i < subject->rows; i++)
            for(int j = 0; j < subject->cols; j++)
                MATRIX_ELEM_AT(out, i, j + matrix->rows) =
                    MATRIX_ELEM_AT(subject, i, j);

        return out;
    }
    else if(axis == 1) {
        assert(matrix->cols == subject->cols);

        c3e_matrix* out = c3e_matrix_init(matrix->rows + subject->rows, matrix->cols);
        for(int i = 0; i < matrix->rows; i++)
            for(int j = 0; j < matrix->cols; j++)
                MATRIX_ELEM_AT(out, i, j) =
                    MATRIX_ELEM_AT(matrix, i, j);

        for(int i = 0; i < subject->rows; i++)
            for(int j = 0; j < subject->cols; j++)
                MATRIX_ELEM_AT(
                    out, i,
                    (j + (matrix->rows * matrix->cols))
                ) = MATRIX_ELEM_AT(subject, i, j);

        return out;
    }

    return c3e_matrix_zeros(matrix->rows, matrix->cols);
}

c3e_matrix* c3e_matrix_add(c3e_matrix* matrix, c3e_matrix* subject) {
    int rows = (matrix->rows > subject->rows) ?
        matrix->rows : subject->rows;
    int cols = (matrix->cols > subject->cols) ?
        matrix->cols : subject->cols;

    assert(
        matrix->rows == subject->rows ||
        matrix->rows == 1 ||
        subject->rows == 1
    );

    assert(
        matrix->cols == subject->cols ||
        matrix->cols == 1 ||
        subject->cols == 1
    );

    c3e_matrix* out = c3e_matrix_init(rows, cols);
    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                MATRIX_ELEM_AT(
                    matrix,
                    (matrix->rows == 1) ? 0 : i,
                    (matrix->cols == 1) ? 0 : j
                ) +
                MATRIX_ELEM_AT(
                    subject,
                    (subject->rows == 1) ? 0 : i,
                    (subject->cols == 1) ? 0 : j
                );

    return out;
}

c3e_matrix* c3e_matrix_sub(c3e_matrix* matrix, c3e_matrix* subject) {
    int rows = (matrix->rows > subject->rows) ?
        matrix->rows : subject->rows;
    int cols = (matrix->cols > subject->cols) ?
        matrix->cols : subject->cols;

    assert(
        matrix->rows == subject->rows ||
        matrix->rows == 1 ||
        subject->rows == 1
    );

    assert(
        matrix->cols == subject->cols ||
        matrix->cols == 1 ||
        subject->cols == 1
    );

    c3e_matrix* out = c3e_matrix_init(rows, cols);
    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                MATRIX_ELEM_AT(
                    matrix,
                    (matrix->rows == 1) ? 0 : i,
                    (matrix->cols == 1) ? 0 : j
                ) -
                MATRIX_ELEM_AT(
                    subject,
                    (subject->rows == 1) ? 0 : i,
                    (subject->cols == 1) ? 0 : j
                );

    return out;
}

c3e_matrix* c3e_matrix_mul(c3e_matrix* matrix, c3e_matrix* subject) {
    assert(matrix->cols == subject->rows);

    c3e_matrix* out = c3e_matrix_init(matrix->rows, subject->cols);
    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < subject->cols; j++) {
            c3e_number sum = 0.0;
            for(int k = 0; k < matrix->cols; k++)
                sum += MATRIX_ELEM_AT(matrix, i, k) *
                    MATRIX_ELEM_AT(subject, k, j);

            MATRIX_ELEM_AT(out, i, j) = sum;
        }

    return out;
}

c3e_matrix* c3e_matrix_div(c3e_matrix* matrix, c3e_matrix* subject) {
    assert(matrix->cols == subject->rows);

    c3e_matrix* out = c3e_matrix_init(matrix->rows, subject->cols);
    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < subject->cols; j++) {
            c3e_number sum = 0.0;
            for(int k = 0; k < matrix->cols; k++)
                sum += MATRIX_ELEM_AT(matrix, i, k) /
                    MATRIX_ELEM_AT(subject, k, j);

            MATRIX_ELEM_AT(out, i, j) = sum;
        }

    return out;
}

c3e_matrix* c3e_matrix_dot(c3e_matrix* matrix, c3e_matrix* subject) {
    assert(
        matrix->rows == subject->rows &&
        matrix->cols == subject->cols
    );

    c3e_matrix* out = c3e_matrix_copy(matrix);
    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) *= MATRIX_ELEM_AT(subject, i, j);

    return out;
}

c3e_matrix* c3e_matrix_scale(c3e_matrix* matrix, int x) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                MATRIX_ELEM_AT(matrix, i, j) * x;

    return out;
}

c3e_matrix* c3e_matrix_transpose(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->cols, matrix->rows);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, j, i) =
                MATRIX_ELEM_AT(matrix, i, j);

    return out;
}

c3e_matrix* c3e_matrix_slice(
    c3e_matrix* matrix,
    int from_rows,
    int to_rows,
    int from_cols,
    int to_cols
) {
    assert(from_rows >= 0 &&
        from_cols >= 0 &&
        to_rows <= matrix->rows &&
        to_cols <= matrix->cols
    );

    c3e_matrix* out = c3e_matrix_init(
        to_rows - from_rows,
        to_cols - from_cols
    );

    for(int i = from_rows, x = 0; (i < to_rows && x < out->rows); i++, x++)
        for(int j = from_cols, y = 0; (j < to_cols && y < out->cols); j++, y++)
            MATRIX_ELEM_AT(out, x, y) =
                MATRIX_ELEM_AT(matrix, i, j);

    return out;
}

void matrix_col_copy(
    c3e_matrix* matrix,
    int col,
    c3e_matrix* dst,
    int dst_col
) {
    for(int i = 0; i < matrix->rows; i++)
        MATRIX_ELEM_AT(dst, i, dst_col) =
            MATRIX_ELEM_AT(matrix, i, col);
}

void matrix_col_subtract(
    c3e_matrix* matrix,
    int col,
    c3e_matrix* dst,
    int dst_col,
    c3e_number scalar
) {
    for(int i = 0; i < matrix->rows; i++)
        MATRIX_ELEM_AT(matrix, i, col) -=
            scalar * MATRIX_ELEM_AT(dst, i, dst_col);
}

void matrix_col_divide(c3e_matrix* matrix, int col, c3e_number scalar) {
    for(int i = 0; i < matrix->rows; i++)
        MATRIX_ELEM_AT(matrix, i, col) /= scalar;
}

c3e_number c3e_matrix_trace(c3e_matrix* matrix) {
    assert(matrix->rows == matrix->cols);

    c3e_number out = 0.0;
    for(int i = 0; i < (matrix->rows * matrix->cols);) {
        out += matrix->data[i];
        i += matrix->rows + 1;
    }

    return out;
}

c3e_number c3e_matrix_determinant(c3e_matrix* matrix) {
    assert(matrix->rows == matrix->cols);

    c3e_number out = 0.0;
    int n = matrix->rows;

    if(n == 1)
        out = matrix->data[0];
    else if(n == 2)
        out = (matrix->data[0] * matrix->data[3]) - (matrix->data[1] * matrix->data[2]);
    else for(int i = 0; i < n; i++) {
        int sub_row = 0, sub_col = 0;
        c3e_matrix* submatrix = c3e_matrix_init(n-1, n-1);

        for(int j = 1; j < n; j++)
            if(j != 0)
                for(int k = 0; k < n; k++)
                    if(k != i) {
                        MATRIX_ELEM_AT(submatrix, sub_row, sub_col) =
                            MATRIX_ELEM_AT(matrix, j, k);

                        sub_col++;
                        if(sub_col == n-1) {
                            sub_col = 0;
                            sub_row++;
                        }
                    }

        out += (i % 2 == 0 ? 1 : -1) *
            matrix->data[i] *
            c3e_matrix_determinant(submatrix);
        c3e_matrix_free(submatrix);
    }

    return out;
}

c3e_number c3e_matrix_log_determ(c3e_matrix* matrix) {
    return log(c3e_matrix_determinant(matrix));
}

c3e_number c3e_matrix_frobenius(c3e_matrix* matrix) {
    c3e_number out = 0.0;

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            out += MATRIX_ELEM_AT(matrix, i, j) *
                MATRIX_ELEM_AT(matrix, i, j);

    return sqrt(out);
}

c3e_number c3e_matrix_l1_norm(c3e_matrix* matrix) {
    c3e_number out = 0.0;

    for(int i = 0; i < matrix->rows; i++) {
        c3e_number col_sum = 0.0;

        for(int j = 0; j < matrix->cols; j++)
            col_sum += fabs(MATRIX_ELEM_AT(matrix, j, i));

        if(col_sum > out)
            out = col_sum;
    }

    return out;
}

c3e_number c3e_matrix_infinity_norm(c3e_matrix* matrix) {
    c3e_number out = 0.0;

    for(int i = 0; i < matrix->rows; i++) {
        c3e_number row_sum = 0.0;

        for(int j = 0; j < matrix->cols; j++)
            row_sum += fabs(MATRIX_ELEM_AT(matrix, i, j));

        if(row_sum > out)
            out = row_sum;
    }

    return out; 
}

void c3e_matrix_add_row(c3e_matrix* matrix, int row1, int row2, c3e_number scalar) {
    for(int j = 0; j < matrix->cols; j++)
        MATRIX_ELEM_AT(matrix, row1, j) +=
            scalar * MATRIX_ELEM_AT(matrix, row2, j);
}

void c3e_matrix_swap_rows(c3e_matrix* matrix, int row1, int row2) {
    if(row1 == row2) 
        return;

    for(int i = 0; i < matrix->cols; i++) {
        c3e_number x = matrix->data[row1 * matrix->cols + i];

        MATRIX_ELEM_AT(matrix, row1, i) =
            MATRIX_ELEM_AT(matrix, row2, i);
        MATRIX_ELEM_AT(matrix, row2, i) = x;
    }
}

void c3e_matrix_multiply_row(c3e_matrix* matrix, int row, c3e_number x) {
    for(int j = 0; j < matrix->cols; j++)
        MATRIX_ELEM_AT(matrix, row, j) *= x;
}

c3e_matrix* c3e_matrix_normalize(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    c3e_number fnorm = c3e_matrix_frobenius(matrix);

    if(fnorm > 0.0)
        for(int i = 0; i < matrix->rows; i++)
            for(int j = 0; j < matrix->cols; j++)
                MATRIX_ELEM_AT(out, i, j) =
                    MATRIX_ELEM_AT(matrix, i, j) / fnorm;

    return out;
}

c3e_matrix* c3e_matrix_row_echelon(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_copy(matrix);
    int lead = 0,
        rows = out->rows,
        cols = out->cols;

    while(lead < rows && lead < cols) {
        int pivot = c3e_matrix_find_pivot(out, lead, lead);

        if(pivot == -1) {
            lead++;
            continue;
        }

        c3e_matrix_swap_rows(out, lead, pivot);
        c3e_matrix_multiply_row(out, lead, 1.0 / MATRIX_ELEM_AT(out, lead, lead));

        for(int i = 0; i < rows; i++)
            if(i != lead)
                c3e_matrix_add_row(out, i, lead, -MATRIX_ELEM_AT(out, i, lead));

        lead++;
    }

    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            if(MATRIX_ELEM_AT(out, i, j) == -0.0)
                MATRIX_ELEM_AT(out, i, j) = 0.0;
    return out;
}


c3e_matrix* c3e_matrix_inverse(c3e_matrix* matrix) {
    assert(matrix->rows == matrix->cols);
    assert(c3e_matrix_determinant(matrix) != 0.0);

    int n = matrix->rows;

    c3e_matrix* eye = c3e_matrix_identity(n);
    c3e_matrix* aug = c3e_matrix_append(matrix, eye, 0);
    c3e_matrix* echelon = c3e_matrix_row_echelon(aug);
    c3e_matrix* inv = c3e_matrix_init(n, n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            MATRIX_ELEM_AT(inv, i, j) =
                echelon->data[i * (2*n) + n + j];

    c3e_matrix_free(echelon);
    c3e_matrix_free(aug);
    c3e_matrix_free(eye);

    return inv;
}

c3e_matrix* c3e_matrix_qr_algo(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_copy(matrix);

    c3e_matrix_tuple qr;
    for(int i = 0; i < 500; i++) {
        qr = c3e_matrix_qr_decomp(out);
        out = c3e_matrix_mul(qr.b, qr.a);

        if(c3e_matrix_max(
            c3e_matrix_abs(c3e_matrix_tril(out, -1))
        ) < 1e-10)
            break;
    }

    return out;
}

c3e_matrix* c3e_matrix_cholesky_decomp(c3e_matrix* matrix) {
    assert(c3e_matrix_all_close(
        matrix,
        c3e_matrix_transpose(matrix)
    ));

    c3e_matrix* lower = c3e_matrix_zeros(matrix->rows, matrix->cols);
    for(int i = 0; i < matrix->rows; i++) {
        for(int j = 0; j <= i; j++) {
            c3e_number sum = 0.0;

            for(int k = 0; k < j; k++)
                sum += MATRIX_ELEM_AT(lower, i, k) *
                    MATRIX_ELEM_AT(lower, j, k);

            if(i == j)
                MATRIX_ELEM_AT(lower, i, j) =
                    sqrt(MATRIX_ELEM_AT(matrix, i, j) - sum);
            else MATRIX_ELEM_AT(lower, i, j) =
                (1.0 / MATRIX_ELEM_AT(lower, j, j) *
                    (MATRIX_ELEM_AT(matrix, i, j) - sum)); 
        }
    }

    return lower;
}

int c3e_matrix_rank(c3e_matrix* matrix) {
    c3e_matrix* rem;
    int non_zero_row_count = 0;

    if(matrix->rows == matrix->cols && c3e_matrix_determinant(matrix) != 0)
        return matrix->rows;
    else if(matrix->rows == matrix->cols && c3e_matrix_determinant(matrix) == 0) {
        rem = c3e_matrix_row_echelon(matrix);
        non_zero_row_count = c3e_matrix_non_zero_rows(rem);

        c3e_matrix_free(rem);
    }
    else {
        rem = c3e_matrix_row_echelon(matrix);
        non_zero_row_count = c3e_matrix_non_zero_rows(rem);

        c3e_matrix_free(rem);
    }

    return non_zero_row_count;
}

int c3e_matrix_non_zero_rows(c3e_matrix* matrix) {
    int count = 0;

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            if(matrix->data[i * matrix->cols + j] == 0)
                continue;
            else if(MATRIX_ELEM_AT(matrix, i, j) != 0 &&
                (i * matrix->cols + j + 1) % matrix->cols == 0)
                count++;

    return count;
}

int c3e_matrix_find_pivot(c3e_matrix* matrix, int col, int row) {
    for(int i = row; i < matrix->rows; i++)
        if(fabs(MATRIX_ELEM_AT(matrix, i, col)) > 1e-10)
            return i;

    return -1;
}

c3e_matrix* c3e_matrix_tril(c3e_matrix* matrix, int diag) {
    assert(matrix->rows == matrix->cols);

    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            if(j <= i - diag)
                MATRIX_ELEM_AT(out, i, j) =
                    MATRIX_ELEM_AT(matrix, i, j);
            else MATRIX_ELEM_AT(out, i, j) = 0.0;

    return out;
}

c3e_matrix* c3e_matrix_triu(c3e_matrix* matrix, int diag) {
    assert(matrix->rows == matrix->cols);

    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            if(j >= i + diag)
                MATRIX_ELEM_AT(out, i, j) =
                    MATRIX_ELEM_AT(matrix, i, j);
            else MATRIX_ELEM_AT(out, i, j) = 0.0;

    return out;
}

c3e_vector* c3e_matrix_diagonal(c3e_matrix* matrix, int k) {
    assert(matrix->rows == matrix->cols);
    assert(abs(k) < matrix->rows);

    c3e_vector* out = c3e_vector_init(matrix->rows - abs(k));
    if(k >= 0)
        for(int i = 0; i < (matrix->rows - abs(k)); i++)
            out->data[i] =
                MATRIX_ELEM_AT(matrix, i, i + abs(k));
    else if(k < 0)
        for(int i = 0; i < (matrix->rows - abs(k)); i++)
            out->data[i] =
                MATRIX_ELEM_AT(matrix, i + abs(k), i);

    return out;
}

c3e_number c3e_matrix_sum(c3e_matrix* matrix) {
    c3e_number sum = 0.0;
    for(int i = 0; i < matrix->rows * matrix->cols; i++)
        sum += matrix->data[i];

    return sum;
}

c3e_number c3e_matrix_max(c3e_matrix* matrix) {
    c3e_number max_val = -INFINITY;

    for(int i = 0; i < matrix->rows * matrix->cols; i++)
        if(matrix->data[i] > max_val)
            max_val = matrix->data[i];

    return max_val;
}

c3e_number c3e_matrix_min(c3e_matrix* matrix) {
    c3e_number min_val = INFINITY;
    
    for(int i = 0; i < matrix->rows * matrix->cols; i++)
        if(matrix->data[i] < min_val)
            min_val = matrix->data[i];

    return min_val;
}

c3e_number c3e_matrix_mean(c3e_matrix* matrix) {
    int num_el = matrix->rows * matrix->cols;
    c3e_number out = 0.0;

    for(int i = 0; i < num_el; i++)
        out += matrix->data[i];
    return out / num_el;
}

c3e_number c3e_matrix_std(c3e_matrix* matrix) {
    c3e_number out = 0.0,
        mean = c3e_matrix_mean(matrix);
    int num_el = matrix->rows * matrix->cols;

    for(int i = 0; i < num_el; i++)
        out += (matrix->data[i] - mean) *
            (matrix->data[i] - mean);

    return sqrt(out / num_el);
}

c3e_matrix* c3e_matrix_min_vals(c3e_matrix* matrix, int dim) {
    c3e_number min = INFINITY;

    if(dim == 0) {
        c3e_matrix* out = c3e_matrix_init(matrix->rows, 1);

        for(int i = 0; i < matrix->rows; i++) {
            for(int j = 0; j < matrix->cols; j++)
                if(MATRIX_ELEM_AT(matrix, i, j) < min)
                    min = MATRIX_ELEM_AT(matrix, i, j); 

            out->data[i] = min;
            min = INFINITY;
        }

        return out;
    }
    else if(dim == 1) {
        c3e_matrix* out = c3e_matrix_init(1, matrix->cols);

        for(int j = 0; j < matrix->cols; j++) {
            for(int i = 0; i < matrix->rows; i++)
                if(MATRIX_ELEM_AT(matrix, i, j) < min)
                    min = MATRIX_ELEM_AT(matrix, i, j);

            out->data[j] = min;
            min = INFINITY;
        }

        return out;
    }

    return NULL;
}

c3e_matrix* c3e_matrix_max_values(c3e_matrix* matrix, int dim) {
    c3e_number max = -INFINITY;

    if(dim == 0) {
        c3e_matrix* out = c3e_matrix_init(matrix->rows, 1);

        for(int i = 0; i < matrix->rows; i++) {
            for(int j = 0; j < matrix->cols; j++)
                if(MATRIX_ELEM_AT(matrix, i, j) > max)
                    max = MATRIX_ELEM_AT(matrix, i, j);

            out->data[i] = max;
            max = -INFINITY;
        }

        return out;
    }
    else if(dim == 1) {
        c3e_matrix* out = c3e_matrix_init(1, matrix->cols);

        for(int j = 0; j < matrix->cols; j++) {
            for(int i = 0; i < matrix->rows; i++)
                if(MATRIX_ELEM_AT(matrix, i, j) > max)
                    max = MATRIX_ELEM_AT(matrix, i, j);

            out->data[j] = max;
            max = -INFINITY;
        }

        return out;
    }
    
    return NULL;
}

c3e_matrix* c3e_matrix_sum_vals(c3e_matrix* matrix, int dim) {
    c3e_number sum = 0.0;

    if(dim == 0) {
        c3e_matrix* out = c3e_matrix_init(matrix->rows, 1);

        for(int i = 0; i <  matrix->rows; i++) {
            for(int j = 0; j < matrix->cols; j++)
                sum += MATRIX_ELEM_AT(matrix, i, j);

            out->data[i] = sum;
            sum = 0.0;
        }

        return out;
    }
    else if(dim == 1) {
        c3e_matrix* out = c3e_matrix_init(1, matrix->cols);

        for(int j = 0; j < matrix->cols; j++) {
            for(int i = 0; i < matrix->rows; i++)
                sum += MATRIX_ELEM_AT(matrix, i, j);

            out->data[j] = sum;
            sum = 0.0;
        }

        return out;
    }

    return NULL;
}

c3e_matrix* c3e_matrix_mean_vals(c3e_matrix* matrix, int dim) {
    int row = matrix->cols,
        col = matrix->rows;

    if(dim == 0) {
        c3e_matrix* out = c3e_matrix_init(matrix->rows, 1);
        c3e_number sum = 0.0;

        for(int i = 0; i < matrix->rows; i++) {
            for(int j = 0; j < matrix->cols; j++)
                sum += MATRIX_ELEM_AT(matrix, i, j); 

            out->data[i] = sum / row;
            sum = 0.0;
        }

        return out;
    }
    else if(dim == 1) {
        c3e_matrix* out = c3e_matrix_init(1, matrix->cols);
        c3e_number sum = 0.0;

        for(int j = 0; j < matrix->cols; j++) {
            for(int i = 0; i < matrix->rows; i++)
                sum += MATRIX_ELEM_AT(matrix, i, j);

            out->data[j] = sum / col;
            sum = 0.0;
        }

        return out;
    }

    return NULL;
}

c3e_matrix* c3e_matrix_std_vals(c3e_matrix* matrix, int dim) {
    int row = matrix->cols,
        col = matrix->rows;

    if(dim == 0) {
        c3e_matrix* out = c3e_matrix_init(matrix->rows, 1);
        c3e_number sum = 0.0;

        for(int i = 0; i < matrix->rows; i++) {
            for(int j = 0; j < matrix->cols; j++)
                sum += MATRIX_ELEM_AT(matrix, i, j) *
                    MATRIX_ELEM_AT(matrix, i, j);

            out->data[i] = sqrt(row / row);
            sum = 0.0;
        }

        return out;
    }
    else if(dim == 1) {
        c3e_matrix* out = c3e_matrix_init(1, matrix->cols);
        c3e_number sum = 0.0;

        for(int j = 0; j < matrix->cols; j++) {
            for(int i = 0; i < matrix->rows; i++)
                sum += MATRIX_ELEM_AT(matrix, i, j) *
                    MATRIX_ELEM_AT(matrix, i, j);

            out->data[j] = sqrt(sum / col);
            sum = 0.0;
        }

        return out;
    }

    return NULL;
}

bool c3e_matrix_all_close(c3e_matrix* matrix, c3e_matrix* subject) {
    if(matrix->rows != subject->rows ||
        matrix->cols != subject->cols)
        return false;

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            if(fabs(MATRIX_ELEM_AT(matrix, i, j) -
                MATRIX_ELEM_AT(subject, i, j)) >
                (1e-08 + 1e-05 * fabs(MATRIX_ELEM_AT(subject, i, j)))
            ) return false;

    return true;
}

c3e_matrix* c3e_matrix_from_vec(c3e_vector* vector) {
    c3e_matrix* out = c3e_matrix_init(1, vector->size);

    for(int i = 0; i < vector->size; i++)
        out->data[i] = vector->data[i];

    return out;
}

c3e_matrix* c3e_matrix_eigenvec(c3e_matrix* matrix) {
    c3e_matrix* eig = c3e_matrix_init(matrix->rows, matrix->cols);
    c3e_vector* eigenvalues = c3e_matrix_eigenvalues(matrix);

    c3e_matrix* eigenvector = NULL;
    c3e_matrix* original = NULL;
    c3e_svd svd;

    for(int i = 0; i < eigenvalues->size; i++) {
        original = c3e_matrix_sub(
            matrix,
            c3e_matrix_scalar_mul(
                c3e_matrix_identity(matrix->rows),
                eigenvalues->data[i]
            )
        );
        svd = c3e_svd_init(original);
        eigenvector = c3e_matrix_slice(
            svd.right, 2,
            matrix->rows, 0, 3
        );

        c3e_number norm = c3e_matrix_frobenius(eigenvector);
        for(int j = 0; j < matrix->rows; j++)
            MATRIX_ELEM_AT(eig, j, i) = eigenvector->data[j] / norm;
    }

    if(eigenvector != NULL)
        c3e_matrix_free(eigenvector);

    if(original != NULL)
        c3e_matrix_free(original);

    if(eigenvalues != NULL)
        c3e_vector_free(eigenvalues);

    c3e_svd_free(svd);
    return eig;
}

c3e_vector* c3e_matrix_eigenvalues(c3e_matrix* matrix) {
    c3e_vector* out = c3e_vector_init(matrix->rows);
    c3e_matrix* decomp = c3e_matrix_qr_algo(matrix);

    for(int i = 0; i < out->size; i++)
        out->data[i] = MATRIX_ELEM_AT(decomp, i, i);

    c3e_matrix_free(decomp);
    return out;
}

c3e_matrix* c3e_matrix_vec_mul(c3e_matrix* matrix, c3e_vector* vector) {
    assert(matrix->cols == vector->size);

    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                MATRIX_ELEM_AT(matrix, i, j) *
                vector->data[j];

    return out;
}

c3e_matrix* c3e_matrix_scalar_add(c3e_matrix* matrix, c3e_number x) {
    c3e_matrix* out = c3e_matrix_copy(matrix);

    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) += x;

    return out;
}

c3e_matrix* c3e_matrix_scalar_sub(c3e_matrix* matrix, c3e_number x) {
    c3e_matrix* out = c3e_matrix_copy(matrix);

    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) -= x;

    return out;
}

c3e_matrix* c3e_matrix_scalar_mul(c3e_matrix* matrix, c3e_number x) {
    c3e_matrix* out = c3e_matrix_copy(matrix);

    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) *= x;

    return out;
}

c3e_matrix* c3e_matrix_scalar_div(c3e_matrix* matrix, c3e_number x) {
    c3e_matrix* out = c3e_matrix_copy(matrix);

    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) /= x;

    return out;
}

c3e_matrix* c3e_matrix_flatten(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(1, matrix->rows * matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                MATRIX_ELEM_AT(matrix, i, j);

    return out;
}

c3e_matrix* c3e_matrix_reshape(c3e_matrix* matrix, int rows, int cols) {
    assert(matrix->rows * matrix->cols == rows * cols);

    c3e_matrix* out = c3e_matrix_init(rows, cols);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            MATRIX_ELEM_AT(out, i, j) = MATRIX_ELEM_AT(matrix, i, j);

    return out;
}

c3e_matrix* c3e_matrix_clip(c3e_matrix* matrix, c3e_number min, c3e_number max) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    
    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            if(MATRIX_ELEM_AT(matrix, i, j) < min)
                MATRIX_ELEM_AT(out, i, j) = min;
            else if(MATRIX_ELEM_AT(matrix, i, j) > max)
                MATRIX_ELEM_AT(out, i, j) = max;
            else MATRIX_ELEM_AT(out, i, j) =
                MATRIX_ELEM_AT(matrix, i, j);

    return out;
}

c3e_matrix* c3e_matrix_arc_sin(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                asin(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_arc_sinh(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                asinh(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_sin(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                sin(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_sinh(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                sinh(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_arc_cos(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                acos(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_arc_cosh(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                acosh(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_cos(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                cos(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_cosh(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                cosh(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_arc_tan(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                atan(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_arc_tanh(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                atanh(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_tan(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                tan(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_tanh(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                tanh(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_abs(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    
    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                fabs(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_fabs(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                fabs(MATRIX_ELEM_AT(out, i, j));

    return out;
}

c3e_matrix* c3e_matrix_a_range(c3e_number start, c3e_number end, c3e_number step) {
    int size = ceil((end - start) / step);
    c3e_matrix* out = c3e_matrix_init(1, size);

    c3e_number value = start;
    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++) {
            MATRIX_ELEM_AT(out, i, j) = value;
            value += step;
        }

    return out;
}

c3e_matrix* c3e_matrix_cum_sum(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    c3e_number sum = 0.0;

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++) {
            sum += MATRIX_ELEM_AT(matrix, i, j);
            MATRIX_ELEM_AT(out, i, j) = sum;
        }

    return out;
}

c3e_matrix* c3e_matrix_cum_product(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    c3e_number prod = 1.0;

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++) {
            prod *= MATRIX_ELEM_AT(matrix, i, j);
            MATRIX_ELEM_AT(out, i, j) = prod;
        }

    return out;
}

c3e_matrix* c3e_matrix_log(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                log(MATRIX_ELEM_AT(out, i, j));

    return out;
}

c3e_matrix* c3e_matrix_log10(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                log10(MATRIX_ELEM_AT(out, i, j));

    return out;
}

c3e_matrix* c3e_matrix_log2(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                log2(MATRIX_ELEM_AT(out, i, j));

    return out;
}

c3e_matrix* c3e_matrix_log1p(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                log1p(MATRIX_ELEM_AT(out, i, j));

    return out;
}

c3e_matrix* c3e_matrix_reciproc(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                (1 / MATRIX_ELEM_AT(out, i, j));

    return out;
}

c3e_matrix* c3e_matrix_pow(c3e_matrix* matrix, c3e_number exp) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) = pow(MATRIX_ELEM_AT(matrix, i, j), exp);

    return out;
}

c3e_number c3e_matrix_product(c3e_matrix* matrix) {
    c3e_number out = 1.0;

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            out *= MATRIX_ELEM_AT(matrix, i, j);

    return out;
}

c3e_matrix* c3e_matrix_rsqrt(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                (1 / sqrt(MATRIX_ELEM_AT(matrix, i, j)));

    return out;
}

c3e_matrix* c3e_matrix_sqrt(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                sqrt(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_lerp(c3e_matrix* matrix, c3e_matrix* subject, c3e_number weight) {
    assert(matrix->rows == subject->rows);
    assert(matrix->cols == subject->cols);

    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                MATRIX_ELEM_AT(matrix, i, j) + weight *
                (MATRIX_ELEM_AT(subject, i, j) -
                    MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_neg(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) *= -1;

    return out;
}

c3e_matrix* c3e_matrix_sign(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            if(MATRIX_ELEM_AT(matrix, i, j) < 0)
                MATRIX_ELEM_AT(out, i, j) = -1.0;
            else if(MATRIX_ELEM_AT(matrix, i, j) > 0)
                MATRIX_ELEM_AT(out, i, j) = 1.0;
            else MATRIX_ELEM_AT(out, i, j) = 0.0;

    return out;
}

c3e_matrix* c3e_matrix_equals(c3e_matrix* matrix, c3e_matrix* subject) {
    assert(matrix->rows == subject->rows);
    assert(matrix->cols == subject->cols);

    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) = (c3e_number)
                (MATRIX_ELEM_AT(matrix, i, j) ==
                    MATRIX_ELEM_AT(subject, i, j));

    return out;
}

c3e_matrix* c3e_matrix_less_than(c3e_matrix* matrix, c3e_matrix* subject) {
    assert(matrix->rows == subject->rows);
    assert(matrix->cols == subject->cols);

    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) = (c3e_number)
                (MATRIX_ELEM_AT(matrix, i, j) <
                    MATRIX_ELEM_AT(subject, i, j));

    return out;
}

c3e_matrix* c3e_matrix_less_than_eq(c3e_matrix* matrix, c3e_matrix* subject) {
    assert(matrix->rows == subject->rows);
    assert(matrix->cols == subject->cols);

    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) = (c3e_number)
                (MATRIX_ELEM_AT(matrix, i, j) <=
                    MATRIX_ELEM_AT(subject, i, j));

    return out;
}

c3e_matrix* c3e_matrix_greater_than(c3e_matrix* matrix, c3e_matrix* subject) {
    assert(matrix->rows == subject->rows);
    assert(matrix->cols == subject->cols);

    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) = (c3e_number)
                (MATRIX_ELEM_AT(matrix, i, j) > MATRIX_ELEM_AT(subject, i, j));

    return out;
}

c3e_matrix* c3e_matrix_greater_than_eq(c3e_matrix* matrix, c3e_matrix* subject) {
    assert(matrix->rows == subject->rows);
    assert(matrix->cols == subject->cols);

    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);
    for(int i = 0; i < out->rows; i++)
        for(int j = 0; j < out->cols; j++)
            MATRIX_ELEM_AT(out, i, j) = (c3e_number)
                (MATRIX_ELEM_AT(matrix, i, j) >= MATRIX_ELEM_AT(subject, i, j));

    return out;
}

c3e_matrix* c3e_matrix_exp(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                exp(MATRIX_ELEM_AT(matrix, i, j));

    return out;
}

c3e_matrix* c3e_matrix_log_cumsum_exp(c3e_matrix* matrix) {
    return c3e_matrix_log(c3e_matrix_cum_sum(c3e_matrix_exp(matrix)));
}

c3e_matrix* c3e_matrix_log_gamma(c3e_matrix* matrix) {
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++)
        for(int j = 0; j < matrix->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                log(c3e_gamma(MATRIX_ELEM_AT(matrix, i, j)));

    return out;
}

void c3e_matrix_sort(c3e_matrix* matrix) {
    int size = matrix->rows * matrix->cols;
    c3e_quick_sort(matrix->data, 0, size - 1);
}

void c3e_matrix_resize(c3e_matrix* matrix, int rows, int cols) {
    matrix->rows = rows;
    matrix->cols = cols;
}

void c3e_matrix_resize_as(c3e_matrix* matrix, c3e_matrix* subject) {
    matrix->rows = subject->rows;
    matrix->cols = subject->cols;
}

c3e_matrix* c3e_matrix_get(c3e_matrix* matrix, c3e_matrix* subject) {
    c3e_matrix* out = c3e_matrix_init(subject->rows, subject->cols);

    for(int i = 0; i < subject->rows; i++)
        for(int j = 0; j < subject->cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                matrix->data[(int) MATRIX_ELEM_AT(subject, i, j)];

    return out;
}

c3e_matrix* c3e_matrix_repeat(c3e_matrix* matrix, int rrows, int rcols) {
    int rows = matrix->rows * rrows;
    int cols = matrix->cols * rcols;

    c3e_matrix* out = c3e_matrix_init(rows, cols);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            MATRIX_ELEM_AT(out, i, j) =
                MATRIX_ELEM_AT(
                    matrix,
                    i % matrix->rows,
                    j % matrix->cols
                );

    return out;
}

c3e_matrix* c3e_matrix_solve(c3e_matrix* matrix, c3e_matrix* subject) {
    c3e_matrix* inv = c3e_matrix_inverse(matrix);
    c3e_matrix* out = c3e_matrix_mul(
        c3e_matrix_transpose(subject),
        inv
    );

    c3e_matrix_free(inv);
    return out;
}

int c3e_matrix_arg_min(c3e_matrix* matrix) {
    for(int i = 0; i < matrix->rows * matrix->cols; i++)
        if(matrix->data[i] == c3e_matrix_min(matrix))
            return i;

    return -1;
}

int c3e_matrix_arg_max(c3e_matrix* matrix) {
    for(int i = 0; i < matrix->rows * matrix->cols; i++)
        if(matrix->data[i] == c3e_matrix_max(matrix))
            return i;

    return -1;
}

c3e_matrix* c3e_matrix_arg_sort(c3e_matrix* matrix) {
    c3e_matrix* copy = c3e_matrix_copy(matrix);
    c3e_matrix* out = c3e_matrix_init(matrix->rows, matrix->cols);

    c3e_matrix_sort(matrix);
    for(int i = 0; i < matrix->rows * matrix->cols; i++)
        for(int j = 0; j < copy->rows * copy->cols; j++)
            if(matrix->data[i] == copy->data[j] && (out->data[i-1] != j))
                out->data[i] = j;

    c3e_matrix_free(copy);
    return out;
}

c3e_matrix* c3e_matrix_arg_min_vals(c3e_matrix* matrix, int dim) {
    assert(dim >= 0 && dim < 2);

    if(dim == 0) {
        c3e_matrix* out = c3e_matrix_init(matrix->rows, 1);
        c3e_matrix* min = c3e_matrix_min_vals(matrix, 0);

        for(int i = 0; i < matrix->rows; i++)
            for(int j = 0; j < matrix->cols; j++)
                if(min->data[i] == MATRIX_ELEM_AT(matrix, i, j))
                    out->data[i] = j;

        c3e_matrix_free(min);
        return out;
    }
    else if(dim == 1) {
        c3e_matrix* out = c3e_matrix_init(1, matrix->cols);
        c3e_matrix* min = c3e_matrix_min_vals(matrix, 1);

        for(int j = 0; j < matrix->cols; j++)
            for(int i = 0; i < matrix->rows; i++)
                if(min->data[j] == MATRIX_ELEM_AT(matrix, i, j))
                    out->data[j] = i;

        c3e_matrix_free(min);
        return out;
    }

    return NULL;
}

c3e_matrix* c3e_matrix_arg_max_vals(c3e_matrix* matrix, int dim) {
    assert(dim >= 0 && dim < 2);

    if(dim == 0) {
        c3e_matrix* out = c3e_matrix_init(matrix->rows, 1);
        c3e_matrix* max = c3e_matrix_max_values(matrix, 0);

        for(int i = 0; i < matrix->rows; i++)
            for(int j = 0; j < matrix->cols; j++)
                if(max->data[i] == MATRIX_ELEM_AT(matrix, i, j))
                    out->data[i] = j;

        c3e_matrix_free(max);
        return out;
    }
    else if(dim == 1) {
        c3e_matrix* out = c3e_matrix_init(1, matrix->cols);
        c3e_matrix* max = c3e_matrix_max_values(matrix, 1);

        for(int j = 0; j < matrix->cols; j++)
            for(int i = 0; i < matrix->rows; i++)
                if(max->data[j] == MATRIX_ELEM_AT(matrix, i, j))
                    out->data[j] = i;

        c3e_matrix_free(max);
        return out;
    }

    return NULL;
}
