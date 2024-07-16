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

#include <c3e.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_vector(const char* name, c3e_vector* vector) {
    printf("%s: [\r\n", name);

    for(int i = 0, k = 0; i < vector->size; i++) {
        if(k == 3) {
            printf("\r\n");
            k = 0;
        }

        if(k == 0)
            printf("  ");

        printf("%0.2f ", vector->data[i]);
        k++;
    }

    printf("\r\n]\r\n\r\n");
}

void print_matrix(const char* name, c3e_matrix* matrix) {
    printf("%s: [", name);

    for(int i = 0; i < matrix->rows; i++) {
        printf("\r\n  ");

        for(int j = 0; j < matrix->cols; j++)
            printf("%0.2f ", c3e_matrix_get_at(matrix, i, j));
    }

    printf("\r\n]\r\n\r\n");
}

void print_tensor(const char* name, c3e_tensor* tensor) {
    printf("%s: \r\n", name);

    printf("  - Data: [\r\n");
    for(int i = 0, k = 0; i < tensor->data->size; i++) {
        if(k == 3) {
            printf("\r\n");
            k = 0;
        }

        if(k == 0)
            printf("    ");

        printf("%0.2f ", tensor->data->data[i]);
        k++;
    }
    printf("\r\n  ]\r\n\r\n");

    printf("  - Matrices:\r\n");
    for(uint32_t k = 0; k < tensor->dimensions; k++) {
        printf("  (%d): [", k);

        c3e_matrix* mtx = tensor->matrices[k];
        for(int i = 0; i < mtx->rows; i++) {
            printf("\r\n    ");

            for(int j = 0; j < mtx->cols; j++)
                printf("%0.2f ", c3e_matrix_get_at(mtx, i, j));
        }

        printf("\r\n  ]\r\n");
    }

    printf("\r\n");
}

void test_vector() {
    size_t size = 6;

    c3e_vector* vector1 = c3e_vector_init(size);
    c3e_vector* vector2 = c3e_vector_init(size);

    for(size_t i = 0; i < size; i++) {
        c3e_vector_set(vector1, i, (c3e_number)i + 1);
        c3e_vector_set(vector2, i, (c3e_number)(i + 1) * 2);
    }

    print_vector("Vector 1", vector1);
    print_vector("Vector 2", vector2);

    c3e_vector* result = c3e_vector_add(vector1, vector2);
    print_vector("Addition", result);
    c3e_vector_free(result);

    result = c3e_vector_sub(vector1, vector2);
    print_vector("Subtraction", result);
    c3e_vector_free(result);

    result = c3e_vector_mul(vector1, vector2);
    print_vector("Multiplication", result);
    c3e_vector_free(result);

    result = c3e_vector_div(vector1, vector2);
    print_vector("Division", result);
    c3e_vector_free(result);

    result = c3e_vector_exp(vector1);
    print_vector("Exponentiation", result);
    c3e_vector_free(result);

    result = c3e_vector_scale(vector1, 2);
    print_vector("Scaling by 2", result);
    c3e_vector_free(result);

    printf("Sum of elements in Vector 1: %f\r\n", c3e_vector_sum(vector1));
    printf("Norm of Vector 1: %f\r\n", c3e_vector_norm(vector1));
    printf("Angle between V1 and V2: %f\r\n", c3e_vector_angle(vector1, vector2));
    printf("Cross product of V1 and V2: %f\r\n", c3e_vector_cross(vector1, vector2));
    printf("Projection of Vector 1 on Vector 2: %f\r\n", c3e_vector_projection(vector1, vector2));
    printf("Dot product of Vector 1 and Vector 2: %f\r\n", c3e_vector_dot(vector1, vector2));

    c3e_number matrix1_data[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23,
        24, 25
    }, matrix2_data[] = {
        25, 24, 23, 22, 21, 20, 19,
        18, 17, 16, 15, 14, 13, 12,
        11, 10, 9, 8, 7, 6, 5, 4, 3,
        2, 1
    };

    c3e_matrix matrix1 = {5, 5, matrix1_data}, matrix2 = {5, 5, matrix2_data};
    printf(
        "Dot product of col 0 from M1 and M2: %f\r\n\r\n",
        c3e_vector_dot_cols(&matrix1, 0, &matrix2, 0)
    );

    result = c3e_vector_normalize(vector1);
    print_vector("Normalization of Vector 1", result);
    c3e_vector_free(result);

    c3e_number matrix_data[] = {1, 2, 3, 4, 5, 6};
    c3e_matrix matrix = {1, 6, matrix_data};

    result = c3e_vector_transform(vector1, &matrix);
    print_vector("Transform V1 with matrix", result);
    c3e_vector_free(result);

    result = c3e_vector_zeros(size);
    print_vector("Zeros vector", result);
    c3e_vector_free(result);

    result = c3e_vector_ones(size);
    print_vector("Ones vector", result);
    c3e_vector_free(result);

    result = c3e_vector_random(size, c3e_random());
    print_vector("Random Vector", result);
    c3e_vector_free(result);

    result = c3e_vector_random_bound(size, c3e_random(), 0.0, 1.0);
    print_vector("Random Vector with Bounds (0.0 - 1.0)", result);
    c3e_vector_free(result);

    result = c3e_vector_copy(vector1);
    print_vector("Copy of Vector 1", result);
    c3e_vector_free(result);

    printf("V1 and V2 are equal: %s\n", c3e_vector_equals(vector1, vector2) ? "yes" : "no");
    printf("V1 and V2 are all close: %s\n", c3e_vector_all_close(vector1, vector2) ? "yes" : "no");

    c3e_vector_free(vector1);
    c3e_vector_free(vector2);
}

void test_svd() {
    c3e_matrix* matrix = c3e_matrix_init(3, 3);
    c3e_number values[] = {
        14, 0, 0,
        21, 175, 0,
        -14, -70, 35
    };
    c3e_matrix_set_elements(matrix, values);

    c3e_svd svd = c3e_svd_init(matrix);
    printf("SVD result:\r\n");

    printf("  - Left (U) matrix:\r\n");
    for(int i = 0; i < svd.left->rows; i++) {
        printf("\t");

        for(int j = 0; j < svd.left->cols; j++)
            printf("%.2f ", c3e_matrix_get_at(svd.left, i, j));
        printf("\r\n");
    }

    printf("  - Right (V) matrix:\r\n");
    for(int i = 0; i < svd.right->rows; i++) {
        printf("\t");

        for(int j = 0; j < svd.right->cols; j++)
            printf("%.2f ", c3e_matrix_get_at(svd.right, i, j));
        printf("\n");
    }

    printf("  - Singular (S) values:\r\n\t");
    for(int i = 0; i < svd.singular->size; i++)
        printf("%.2f ", c3e_vector_get(svd.singular, i));
    printf("\r\n");

    c3e_svd_free(svd);
    c3e_matrix_free(matrix);
}

void test_matrix() {
    c3e_matrix* matrix = c3e_matrix_init(3, 3);
    c3e_number values[] = {
        14, 0, 0,
        21, 175, 0,
        -14, -70, 35
    };

    c3e_matrix_set_elements(matrix, values);
    print_matrix("Original Matrix", matrix);

    c3e_matrix* ones_matrix = c3e_matrix_ones(3, 3);
    print_matrix("Ones Matrix", ones_matrix);
    c3e_matrix_free(ones_matrix);

    c3e_matrix* zeros_matrix = c3e_matrix_zeros(3, 3);
    print_matrix("Zeros Matrix", zeros_matrix);
    c3e_matrix_free(zeros_matrix);

    c3e_matrix* full_matrix = c3e_matrix_full(3, 3, 5.0);
    print_matrix("Full Matrix (5.0)", full_matrix);
    c3e_matrix_free(full_matrix);

    c3e_matrix* identity_matrix = c3e_matrix_identity(3);
    print_matrix("Identity Matrix", identity_matrix);

    c3e_matrix* copied_matrix = c3e_matrix_copy(matrix);
    print_matrix("Copied Matrix", copied_matrix);

    c3e_matrix* sum_matrix = c3e_matrix_add(matrix, copied_matrix);
    print_matrix("Sum Matrix", sum_matrix);

    c3e_matrix* sub_matrix = c3e_matrix_sub(matrix, copied_matrix);
    print_matrix("Subtracted Matrix", sub_matrix);

    c3e_matrix_free(sum_matrix);
    c3e_matrix_free(sub_matrix);
    c3e_matrix_free(copied_matrix);

    c3e_matrix* mul_matrix = c3e_matrix_dot(matrix, identity_matrix);
    print_matrix("Multiplied Matrix", mul_matrix);
    c3e_matrix_free(mul_matrix);

    c3e_matrix* scaled_matrix = c3e_matrix_scale(matrix, 2.0);
    print_matrix("Scaled Matrix (x2)", scaled_matrix);
    c3e_matrix_free(scaled_matrix);

    c3e_matrix* transposed_matrix = c3e_matrix_transpose(matrix);
    print_matrix("Transposed Matrix", transposed_matrix);
    c3e_matrix_free(transposed_matrix);

    c3e_matrix* inverse_matrix = c3e_matrix_inverse(matrix);
    print_matrix("Inverse of Identity Matrix", inverse_matrix);
    c3e_matrix_free(inverse_matrix);

    c3e_number trace = c3e_matrix_trace(matrix);
    printf("Trace of Matrix: %.2f\r\n", trace);

    c3e_number determinant = c3e_matrix_determinant(matrix);
    printf("Determinant of Identity: %.2f\r\n", determinant);

    c3e_number frobenius_norm = c3e_matrix_frobenius(matrix);
    printf("Frobenius Norm: %.2f\r\n", frobenius_norm);

    c3e_number l1_norm = c3e_matrix_l1_norm(matrix);
    printf("L1 Norm: %.2f\r\n", l1_norm);

    c3e_number infinity_norm = c3e_matrix_infinity_norm(matrix);
    printf("Infinity Norm: %.2f\r\n\r\n", infinity_norm);

    c3e_matrix* qr_matrix = c3e_matrix_qr_algo(matrix);
    print_matrix("QR Decomposition Matrix", qr_matrix);
    c3e_matrix_free(qr_matrix);

    c3e_matrix* cholesky_matrix = c3e_matrix_cholesky_decomp(identity_matrix);
    print_matrix("Cholesky Decomposition of Identity", cholesky_matrix);

    c3e_matrix_free(cholesky_matrix);
    c3e_matrix_free(identity_matrix);

    int rank = c3e_matrix_rank(matrix);
    printf("Rank of Matrix: %d\n", rank);

    int pivot = c3e_matrix_find_pivot(matrix, 1, 1);
    printf("Pivot of Matrix at (1, 1): %d\n", pivot);

    c3e_matrix_add_row(matrix, 0, 1, 1.0);
    print_matrix("Matrix after Adding R0 to R1", matrix);

    c3e_matrix_swap_rows(matrix, 0, 2);
    print_matrix("Matrix after Swapping R0 and R2", matrix);

    c3e_matrix_multiply_row(matrix, 1, 2.0);
    print_matrix("Matrix after Multiplying R1 by 2", matrix);

    c3e_matrix* slice = c3e_matrix_slice(matrix, 0, 2, 0, 2);
    print_matrix("Sliced Matrix (0:2, 0:2)", slice);
    c3e_matrix_free(slice);

    c3e_matrix* reshaped = c3e_matrix_reshape(matrix, 1, 9);
    print_matrix("Reshaped Matrix (1x9)", reshaped);
    c3e_matrix_free(reshaped);

    c3e_matrix* normalized = c3e_matrix_normalize(matrix);
    print_matrix("Normalized Matrix", normalized);
    c3e_matrix_free(normalized);

    c3e_vector* diagonal =
        c3e_matrix_diagonal(matrix, 0);
    print_vector("Diagonal of Matrix", diagonal);

    c3e_matrix* from_vector = c3e_matrix_from_vec(diagonal);
    print_matrix("Matrix from Vector", from_vector);

    c3e_vector_free(diagonal);
    c3e_matrix_free(from_vector);

    c3e_vector* eigenvalues = c3e_matrix_eigenvalues(matrix);
    print_vector("Eigenvalues of Identity", eigenvalues);
    c3e_vector_free(eigenvalues);

    c3e_matrix* eigenvectors = c3e_matrix_eigenvec(matrix);
    print_matrix("Eigenvectors of Identity Matrix", eigenvectors);
    c3e_matrix_free(eigenvectors);

    c3e_matrix* log_matrix = c3e_matrix_log(matrix);
    print_matrix("Logarithm of Matrix", log_matrix);
    c3e_matrix_free(log_matrix);

    c3e_matrix* log10_matrix = c3e_matrix_log10(matrix);
    print_matrix("Log10 of Matrix", log10_matrix);
    c3e_matrix_free(log10_matrix);

    c3e_matrix* log1p_matrix = c3e_matrix_log1p(matrix);
    print_matrix("Log1p of Matrix", log1p_matrix);
    c3e_matrix_free(log1p_matrix);

    c3e_matrix* sqrt_matrix = c3e_matrix_sqrt(matrix);
    print_matrix("Square Root of Identity", sqrt_matrix);
    c3e_matrix_free(sqrt_matrix);

    c3e_matrix* rsqrt_matrix = c3e_matrix_rsqrt(matrix);
    print_matrix("Reciprocal Square Root of Identity", rsqrt_matrix);
    c3e_matrix_free(rsqrt_matrix);

    c3e_matrix* exp_matrix = c3e_matrix_exp(matrix);
    print_matrix("Exponential of Identity", exp_matrix);
    c3e_matrix_free(exp_matrix);

    c3e_matrix* log_cumsum_exp_matrix = c3e_matrix_log_cumsum_exp(matrix);
    print_matrix("Log Cumsum Exp of Identity Matrix", log_cumsum_exp_matrix);
    c3e_matrix_free(log_cumsum_exp_matrix);

    c3e_matrix_sort(matrix);
    print_matrix("Sorted Matrix", matrix);

    c3e_matrix* repeated_matrix = c3e_matrix_repeat(matrix, 2, 2);
    print_matrix("Repeated Matrix (2x2)", repeated_matrix);
    c3e_matrix_free(repeated_matrix);

    c3e_matrix* cumsum_matrix = c3e_matrix_cum_sum(matrix);
    print_matrix("Cumulative Sum of Matrix", cumsum_matrix);
    c3e_matrix_free(cumsum_matrix);

    c3e_matrix* cumprod_matrix = c3e_matrix_cum_product(matrix);
    print_matrix("Cumulative Product of Matrix", cumprod_matrix);
    c3e_matrix_free(cumprod_matrix);

    printf("All close: %s\r\n", c3e_matrix_all_close(matrix, copied_matrix) ? "yes" : "no");
    c3e_matrix_free(matrix);
}

void test_tensor() {
    size_t dimension_size = 3;
    uint32_t dimensions = 2;

    c3e_vector* vector1 = c3e_vector_random(dimension_size, 0);
    c3e_matrix* matrices_t1[] = {
        c3e_matrix_random(dimension_size, dimension_size, 0),
        c3e_matrix_random(dimension_size, dimension_size, 0)
    };
    c3e_tensor* tensor1 = c3e_tensor_init(
        dimension_size,
        dimensions,
        matrices_t1,
        vector1
    );

    if(tensor1 == NULL) {
        printf("Error: Failed to create tensor1.\r\n");

        c3e_matrix_free(matrices_t1[0]);
        c3e_matrix_free(matrices_t1[1]);
        c3e_vector_free(vector1);

        return;
    }

    c3e_vector* vector2 = c3e_vector_random(dimension_size, 0);
    c3e_matrix* matrices_t2[] = {
        c3e_matrix_random(dimension_size, dimension_size, 0),
        c3e_matrix_random(dimension_size, dimension_size, 0)
    };
    c3e_tensor* tensor2 = c3e_tensor_init(
        dimension_size,
        dimensions,
        matrices_t2,
        vector2
    );

    if(tensor2 == NULL) {
        printf("Error: Failed to create tensor2.\r\n");

        c3e_tensor_free(tensor1);
        c3e_matrix_free(matrices_t2[0]);
        c3e_matrix_free(matrices_t2[1]);
        c3e_vector_free(vector2);

        return;
    }

    c3e_tensor* sum_tensor = c3e_tensor_add(tensor1, tensor2);
    if(sum_tensor == NULL) {
        printf("Error: Failed to add tensors.\r\n");
        return;
    }
    else print_tensor("Tensor Sum", sum_tensor);
    c3e_tensor_free(sum_tensor);

    c3e_tensor* diff_tensor = c3e_tensor_sub(tensor1, tensor2);
    if(diff_tensor == NULL) {
        printf("Error: Failed to subtract tensors.\r\n");
        return;
    }
    else print_tensor("Tensor Difference", diff_tensor);
    c3e_tensor_free(diff_tensor);

    c3e_tensor* factor_tensor = c3e_tensor_mul(tensor1, tensor2);
    if(factor_tensor == NULL) {
        printf("Error: Failed to multiply tensors.\r\n");
        return;
    }
    else print_tensor("Tensor Factor", factor_tensor);
    c3e_tensor_free(factor_tensor);

    c3e_tensor* quotient_tensor = c3e_tensor_div(tensor1, tensor2);
    if(quotient_tensor == NULL) {
        printf("Error: Failed to divide tensors.\r\n");
        return;
    }
    else print_tensor("Tensor Quotient", quotient_tensor);
    c3e_tensor_free(quotient_tensor);

    c3e_tensor_free(tensor1);
    c3e_tensor_free(tensor2);
}

int main() {
    printf("----------------Vector Tests----------------\r\n\r\n");
    test_vector();
    printf("\r\n");

    printf("------Single-Value Decomposition Tests------\r\n\r\n");
    test_svd();
    printf("\r\n");

    printf("----------------Matrix Tests----------------\r\n\r\n");
    test_matrix();
    printf("\r\n");

    printf("----------------Tensor Tests----------------\r\n\r\n");
    test_tensor();
    printf("\r\n");

    return 0;
}
