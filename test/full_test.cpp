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

void print_vector(c3e_vector* vector) {
    printf("[\r\n");

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

void print_matrix(c3e_matrix* matrix) {
    printf("[");

    for(int i = 0; i < matrix->rows; i++) {
        printf("\r\n  ");

        for(int j = 0; j < matrix->cols; j++)
            printf("%0.2f ", c3e_matrix_get_at(matrix, i, j));
    }

    printf("\r\n]\r\n\r\n");
}

void test_vector() {
    size_t size = 6;

    c3e_vector* vector1 = c3e_vector_init(size);
    c3e_vector* vector2 = c3e_vector_init(size);

    for(size_t i = 0; i < size; i++) {
        c3e_vector_set(vector1, i, (c3e_number)i + 1);
        c3e_vector_set(vector2, i, (c3e_number)(i + 1) * 2);
    }

    printf("Vector 1: ");
    print_vector(vector1);

    printf("Vector 2: ");
    print_vector(vector2);

    c3e_vector* result = c3e_vector_add(vector1, vector2);
    printf("Addition: ");
    print_vector(result);
    c3e_vector_free(result);

    result = c3e_vector_sub(vector1, vector2);
    printf("Subtraction: ");
    print_vector(result);
    c3e_vector_free(result);

    result = c3e_vector_mul(vector1, vector2);
    printf("Multiplication: ");
    print_vector(result);
    c3e_vector_free(result);

    result = c3e_vector_div(vector1, vector2);
    printf("Division: ");
    print_vector(result);
    c3e_vector_free(result);

    result = c3e_vector_exp(vector1);
    printf("Exponentiation: ");
    print_vector(result);
    c3e_vector_free(result);

    result = c3e_vector_scale(vector1, 2);
    printf("Scaling by 2: ");
    print_vector(result);
    c3e_vector_free(result);

    c3e_number sum = c3e_vector_sum(vector1);
    printf("Sum of elements in Vector 1: %f\r\n", sum);

    c3e_number norm = c3e_vector_norm(vector1);
    printf("Norm of Vector 1: %f\r\n", norm);

    c3e_number angle = c3e_vector_angle(vector1, vector2);
    printf("Angle between Vector 1 and Vector 2: %f\r\n", angle);

    c3e_number cross = c3e_vector_cross(vector1, vector2);
    printf("Cross product of Vector 1 and Vector 2: %f\r\n", cross);

    c3e_number projection = c3e_vector_projection(vector1, vector2);
    printf("Projection of Vector 1 on Vector 2: %f\r\n", projection);

    c3e_number dot = c3e_vector_dot(vector1, vector2);
    printf("Dot product of Vector 1 and Vector 2: %f\r\n", dot);

    c3e_number matrix1_data[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23,
        24, 25
    };
    c3e_number matrix2_data[] = {
        25, 24, 23, 22, 21, 20, 19,
        18, 17, 16, 15, 14, 13, 12,
        11, 10, 9, 8, 7, 6, 5, 4, 3,
        2, 1
    };
    
    c3e_matrix matrix1 = {5, 5, matrix1_data};
    c3e_matrix matrix2 = {5, 5, matrix2_data};

    c3e_number dot_cols = c3e_vector_dot_cols(&matrix1, 0, &matrix2, 0);
    printf("Dot product of columns 0 from matrix1 and matrix2: %f\r\n\r\n", dot_cols);

    result = c3e_vector_normalize(vector1);
    printf("Normalization of Vector 1: ");
    print_vector(result);
    c3e_vector_free(result);

    c3e_number matrix_data[] = {1, 2, 3, 4, 5, 6};
    c3e_matrix matrix = {1, 6, matrix_data};

    result = c3e_vector_transform(vector1, &matrix);
    printf("Transformation of Vector 1 with matrix: ");
    print_vector(result);
    c3e_vector_free(result);

    result = c3e_vector_zeros(size);
    printf("Zeros vector: ");
    print_vector(result);
    c3e_vector_free(result);

    result = c3e_vector_ones(size);
    printf("Ones vector: ");
    print_vector(result);
    c3e_vector_free(result);

    srand(time(NULL));
    result = c3e_vector_random(size, rand());
    printf("Random vector: ");
    print_vector(result);
    c3e_vector_free(result);

    result = c3e_vector_copy(vector1);
    printf("Copy of Vector 1: ");
    print_vector(result);
    c3e_vector_free(result);

    bool equal = c3e_vector_equal(vector1, vector2);
    printf("Vector 1 and Vector 2 are equal: %s\n", equal ? "true" : "false");

    bool all_close = c3e_vector_all_close(vector1, vector2);
    printf("Vector 1 and Vector 2 are all close: %s\n", all_close ? "true" : "false");

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
    c3e_number values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    c3e_matrix_set_elements(matrix, values);

    printf("Original Matrix:\n");
    print_matrix(matrix);

    c3e_matrix* transpose_matrix = c3e_matrix_transpose(matrix);
    printf("\nTransposed Matrix:\n");
    print_matrix(transpose_matrix);
    c3e_matrix_free(transpose_matrix);

    c3e_matrix* matrix2 = c3e_matrix_init(3, 3);
    c3e_number values2[] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    c3e_matrix_set_elements(matrix2, values2);

    c3e_matrix* sum_matrix = c3e_matrix_add(matrix, matrix2);
    printf("\nSum Matrix:\n");
    print_matrix(sum_matrix);
    c3e_matrix_free(sum_matrix);

    c3e_matrix* mul_matrix = c3e_matrix_dot(matrix, matrix2);
    printf("\nMultiplied Matrix:\n");
    print_matrix(mul_matrix);
    c3e_matrix_free(mul_matrix);

    c3e_matrix* identity_matrix = c3e_matrix_identity(3);
    c3e_matrix* inverse_matrix = c3e_matrix_inverse(identity_matrix);

    printf("\nInverse of Identity Matrix:\n");
    print_matrix(inverse_matrix);
    c3e_matrix_free(identity_matrix);
    c3e_matrix_free(inverse_matrix);

    c3e_number determinant = c3e_matrix_determinant(matrix);
    printf("\nDeterminant of the Matrix: %.2f\n", determinant);

    c3e_matrix_free(matrix);
    c3e_matrix_free(matrix2);
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

    return 0;
}
