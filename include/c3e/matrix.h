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

/**
 * @file c3e/matrix.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Matrix operations for the Complex Compute Core Engine (C3E) framework.
 *
 * This file contains the definitions and functions for working with matrices 
 * in the C3E framework. It includes functions for matrix initialization, 
 * manipulation, and various matrix operations.
 */
#ifndef C3E_MATRIX_H
#define C3E_MATRIX_H

#include <c3e/commons.h>

/**
 * @def MATRIX_ELEM(matrix, row, col)
 * @brief Macro to access a matrix element.
 *
 * This macro provides a convenient way to access an element in a matrix 
 * given its row and column indices.
 *
 * @param matrix Pointer to the matrix structure.
 * @param row Row index of the element.
 * @param col Column index of the element.
 * @return Value at the specified row and column in the matrix.
 */
#define MATRIX_ELEM(matrix, row, col) \
    (matrix)->data[(row) * (matrix)->cols + (col)]

/**
 * @brief Initializes a matrix with the given number of rows and columns.
 *
 * Allocates memory and initializes a matrix structure with the specified 
 * dimensions. The matrix data is not initialized.
 *
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 * @return Pointer to the initialized matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_init(int rows, int cols);

/**
 * @brief Frees the memory allocated for a matrix.
 *
 * Deallocates the memory associated with the matrix structure and its data.
 *
 * @param matrix Pointer to the matrix to be freed.
 */
void c3e_matrix_free(c3e_matrix* matrix);

/**
 * @brief Sets the elements of a matrix to the given values.
 *
 * Populates the matrix with values provided in an array.
 *
 * @param matrix Pointer to the matrix.
 * @param values Array of values to set in the matrix.
 */
void c3e_matrix_set_elements(c3e_matrix* matrix, c3e_number* values);

/**
 * @brief Fills a matrix with a specified value.
 *
 * Sets all elements of the matrix to the given value.
 *
 * @param matrix Pointer to the matrix.
 * @param value Value to set for all elements in the matrix.
 */
void c3e_matrix_fill(c3e_matrix* matrix, c3e_number value);

/**
 * @brief Retrieves an element from the matrix at a specific position.
 *
 * @param matrix Pointer to the matrix.
 * @param row Row index of the desired element.
 * @param col Column index of the desired element.
 * @return The value at the specified position.
 */
c3e_number c3e_matrix_get_at(c3e_matrix* matrix, int row, int col);

/**
 * @brief Computes the total number of elements in a matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The total number of elements in the matrix.
 */
int c3e_matrix_size(c3e_matrix* matrix);

/**
 * @brief Creates a matrix with all elements set to one.
 *
 * Initializes a matrix with the specified number of rows and columns, 
 * and sets all elements to one.
 *
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 * @return Pointer to the newly created matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_ones(int rows, int cols);

/**
 * @brief Creates a matrix of ones with the same shape as another matrix.
 *
 * @param matrix Pointer to the reference matrix.
 * @return Pointer to the new matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_ones_like(c3e_matrix* matrix);

/**
 * @brief Creates a matrix with all elements set to zero.
 *
 * Initializes a matrix with the specified number of rows and columns, 
 * and sets all elements to zero.
 *
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 * @return Pointer to the newly created matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_zeros(int rows, int cols);

/**
 * @brief Creates a matrix of zeros with the same shape as another matrix.
 *
 * @param matrix Pointer to the reference matrix.
 * @return Pointer to the new matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_zeros_like(c3e_matrix* matrix);

/**
 * @brief Creates a matrix with all elements set to a specified value.
 *
 * Initializes a matrix with the specified number of rows and columns, 
 * and sets all elements to the provided value.
 *
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 * @param value The value to set for all elements in the matrix.
 * @return Pointer to the newly created matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_full(int rows, int cols, c3e_number value);

/**
 * @brief Creates a matrix with the same shape as another matrix and fills it with a specified value.
 *
 * @param matrix Pointer to the reference matrix.
 * @param value The value to set for all elements in the new matrix.
 * @return Pointer to the new matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_full_like(c3e_matrix* matrix, c3e_number value);

/**
 * @brief Creates an identity matrix of a given size.
 *
 * An identity matrix is a square matrix with ones on the diagonal and zeros elsewhere.
 *
 * @param side The number of rows and columns (must be equal) in the identity matrix.
 * @return Pointer to the newly created identity matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_identity(int side);

/**
 * @brief Creates a matrix with random values.
 *
 * Initializes a matrix with random values. The randomness is controlled by a seed.
 *
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 * @param seed Seed for the random number generator.
 * @return Pointer to the newly created matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_random(int rows, int cols, int seed);

/**
 * @brief Creates a matrix with random values within a specified range.
 *
 * Initializes a matrix with random values within the given bounds [min, max].
 * The randomness is controlled by a seed.
 *
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 * @param seed Seed for the random number generator.
 * @param min Minimum value for the random numbers.
 * @param max Maximum value for the random numbers.
 * @return Pointer to the newly created matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_random_bound(int rows, int cols, int seed, c3e_number min, c3e_number max);

/**
 * @brief Creates a copy of a matrix.
 *
 * Allocates memory and copies the contents of the source matrix into a new matrix.
 *
 * @param matrix Pointer to the matrix to copy.
 * @return Pointer to the newly created copy of the matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_copy(c3e_matrix* matrix);

/**
 * @brief Appends one matrix to another along a specified axis.
 *
 * Combines two matrices by appending the second matrix to the first along the specified axis.
 * Axis 0 appends rows, and axis 1 appends columns.
 *
 * @param matrix Pointer to the matrix to append to.
 * @param subject Pointer to the matrix to append.
 * @param axis Axis along which to append the matrices (0 for rows, 1 for columns).
 * @return Pointer to the newly created combined matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_append(c3e_matrix* matrix, c3e_matrix* subject, int axis);

/**
 * @brief Adds two matrices element-wise.
 *
 * Computes the element-wise sum of two matrices of the same dimensions.
 *
 * @param matrix Pointer to the first matrix.
 * @param subject Pointer to the second matrix.
 * @return Pointer to the resulting matrix after addition, or NULL on failure.
 */
c3e_matrix* c3e_matrix_add(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Subtracts one matrix from another element-wise.
 *
 * Computes the element-wise difference of two matrices of the same dimensions.
 *
 * @param matrix Pointer to the matrix to subtract from.
 * @param subject Pointer to the matrix to subtract.
 * @return Pointer to the resulting matrix after subtraction, or NULL on failure.
 */
c3e_matrix* c3e_matrix_sub(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Multiplies two matrices element-wise.
 *
 * Computes the element-wise product of two matrices of the same dimensions.
 *
 * @param matrix Pointer to the first matrix.
 * @param subject Pointer to the second matrix.
 * @return Pointer to the resulting matrix after multiplication, or NULL on failure.
 */
c3e_matrix* c3e_matrix_mul(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Divides one matrix by another element-wise.
 *
 * Computes the element-wise quotient of two matrices of the same dimensions.
 *
 * @param matrix Pointer to the matrix to divide.
 * @param subject Pointer to the matrix to divide by.
 * @return Pointer to the resulting matrix after division, or NULL on failure.
 */
c3e_matrix* c3e_matrix_div(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Computes the dot product of two matrices.
 *
 * Computes the matrix product (dot product) of two matrices.
 *
 * @param matrix Pointer to the first matrix.
 * @param subject Pointer to the second matrix.
 * @return Pointer to the resulting matrix after dot product, or NULL on failure.
 */
c3e_matrix* c3e_matrix_dot(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Scales the elements of a matrix by a scalar value.
 *
 * Multiplies each element of the matrix by the given scalar value.
 *
 * @param matrix Pointer to the matrix to be scaled.
 * @param x The scalar value to multiply with.
 * @return Pointer to the scaled matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_scale(c3e_matrix* matrix, int x);

/**
 * @brief Transposes a matrix.
 *
 * Swaps the rows and columns of the matrix, effectively rotating it by 90 degrees.
 *
 * @param matrix Pointer to the matrix to transpose.
 * @return Pointer to the transposed matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_transpose(c3e_matrix* matrix);

/**
 * @brief Slices a sub-matrix from a matrix.
 *
 * Extracts a sub-matrix from the original matrix, defined by the range of rows 
 * and columns specified.
 *
 * @param matrix Pointer to the original matrix.
 * @param frows Starting row index (inclusive).
 * @param trows Ending row index (exclusive).
 * @param fcols Starting column index (inclusive).
 * @param tcols Ending column index (exclusive).
 * @return Pointer to the sliced matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_slice(c3e_matrix* matrix, int frows, int trows, int fcols, int tcols);

/**
 * @brief Copies a column from one matrix to another.
 *
 * Copies the elements from a specified column in the source matrix to a specified 
 * column in the destination matrix.
 *
 * @param matrix Pointer to the source matrix.
 * @param col Column index in the source matrix to copy.
 * @param dst Pointer to the destination matrix.
 * @param dst_col Column index in the destination matrix where the column is to be copied.
 */
void c3e_matrix_col_copy(c3e_matrix* matrix, int col, c3e_matrix* dst, int dst_col);

/**
 * @brief Subtracts a scalar value from a column of a matrix.
 *
 * Subtracts a scalar value from each element in the specified column of the matrix 
 * and stores the result in another matrix.
 *
 * @param matrix Pointer to the source matrix.
 * @param col Column index in the source matrix.
 * @param dst Pointer to the destination matrix.
 * @param dcol Column index in the destination matrix where the result is stored.
 * @param scalar The scalar value to subtract.
 */
void c3e_matrix_col_sub(c3e_matrix* matrix, int col, c3e_matrix* dst, int dcol, c3e_number scalar);

/**
 * @brief Divides a column of a matrix by a scalar value.
 *
 * Divides each element in the specified column of the matrix by the given scalar value.
 *
 * @param matrix Pointer to the matrix.
 * @param col Column index in the matrix.
 * @param scalar The scalar value to divide by.
 */
void c3e_matrix_col_div(c3e_matrix* matrix, int col, c3e_number scalar);

/**
 * @brief Computes the trace of a matrix.
 *
 * The trace is the sum of the diagonal elements of a square matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The trace of the matrix.
 */
c3e_number c3e_matrix_trace(c3e_matrix* matrix);

/**
 * @brief Computes the determinant of a matrix.
 *
 * The determinant is a scalar value that is a function of a square matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The determinant of the matrix.
 */
c3e_number c3e_matrix_determinant(c3e_matrix* matrix);

/**
 * @brief Computes the logarithm of the determinant of a matrix.
 *
 * Computes the natural logarithm of the absolute value of the determinant of a matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The logarithm of the determinant.
 */
c3e_number c3e_matrix_log_determ(c3e_matrix* matrix);

/**
 * @brief Computes the Frobenius norm of a matrix.
 *
 * The Frobenius norm is the square root of the sum of the absolute squares of the matrix elements.
 *
 * @param matrix Pointer to the matrix.
 * @return The Frobenius norm of the matrix.
 */
c3e_number c3e_matrix_frobenius(c3e_matrix* matrix);

/**
 * @brief Computes the L1 norm of a matrix.
 *
 * The L1 norm is the sum of the absolute values of the matrix elements.
 *
 * @param matrix Pointer to the matrix.
 * @return The L1 norm of the matrix.
 */
c3e_number c3e_matrix_l1_norm(c3e_matrix* matrix);

/**
 * @brief Computes the infinity norm of a matrix.
 *
 * The infinity norm is the maximum absolute row sum of the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The infinity norm of the matrix.
 */
c3e_number c3e_matrix_infinity_norm(c3e_matrix* matrix);

/**
 * @brief Extracts a row from the given matrix and returns it as a c3e_vector.
 *
 * This function creates a new vector that contains the elements of the specified row
 * from the given matrix. The row index is zero-based, so the first row is index 0.
 *
 * @param matrix Pointer to the c3e_matrix from which to extract the row.
 * @param row The zero-based index of the row to extract.
 * @return Pointer to a new c3e_vector containing the elements of the specified row, or NULL if the row index is out of bounds.
 */
c3e_vector* c3e_matrix_get_row(c3e_matrix* matrix, int row);

/**
 * @brief Adds a scaled row to another row in a matrix.
 *
 * Adds a scalar multiple of one row to another row within the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @param row1 Index of the row to be modified.
 * @param row2 Index of the row to be scaled and added.
 * @param scalar Scalar value to multiply row2 by before adding to row1.
 */
void c3e_matrix_add_row(c3e_matrix* matrix, int row1, int row2, c3e_number scalar);

/**
 * @brief Swaps two rows in a matrix.
 *
 * Interchanges the contents of two rows in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @param row1 Index of the first row.
 * @param row2 Index of the second row.
 */
void c3e_matrix_swap_rows(c3e_matrix* matrix, int row1, int row2);

/**
 * @brief Multiplies a row in a matrix by a scalar value.
 *
 * Scales the elements of a specified row by a scalar value.
 *
 * @param matrix Pointer to the matrix.
 * @param row1 Index of the row to be multiplied.
 * @param scalar The scalar value to multiply with.
 */
void c3e_matrix_multiply_row(c3e_matrix* matrix, int row1, c3e_number scalar);

/**
 * @brief Normalizes the elements of a matrix.
 *
 * Adjusts the matrix elements such that they lie within a certain range, typically [0, 1].
 *
 * @param matrix Pointer to the matrix to be normalized.
 * @return Pointer to the normalized matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_normalize(c3e_matrix* matrix);

/**
 * @brief Converts a matrix to its row echelon form.
 *
 * Transforms the matrix to row echelon form using Gaussian elimination.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the matrix in row echelon form, or NULL on failure.
 */
c3e_matrix* c3e_matrix_row_echelon(c3e_matrix* matrix);

/**
 * @brief Computes the inverse of a matrix.
 *
 * Calculates the inverse of the matrix if it exists.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the inverted matrix, or NULL if the matrix is singular.
 */
c3e_matrix* c3e_matrix_inverse(c3e_matrix* matrix);

/**
 * @brief Computes the QR decomposition of a matrix.
 *
 * Decomposes the matrix into an orthogonal matrix Q and an upper triangular matrix R.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to a matrix containing Q and R, or NULL on failure.
 */
c3e_matrix* c3e_matrix_qr_algo(c3e_matrix* matrix);

/**
 * @brief Performs Cholesky decomposition on a matrix.
 *
 * Decomposes the matrix into a lower triangular matrix L such that L*L^T = A.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the lower triangular matrix L, or NULL on failure.
 */
c3e_matrix* c3e_matrix_cholesky_decomp(c3e_matrix* matrix);

/**
 * @brief Determines the rank of a matrix.
 *
 * The rank is the maximum number of linearly independent rows or columns in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The rank of the matrix.
 */
int c3e_matrix_rank(c3e_matrix* matrix);

/**
 * @brief Counts the number of non-zero rows in a matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The number of non-zero rows.
 */
int c3e_matrix_non_zero_rows(c3e_matrix* matrix);

/**
 * @brief Finds the pivot element in a specified column starting from a given row.
 *
 * Identifies the pivot element in the matrix for Gaussian elimination.
 *
 * @param matrix Pointer to the matrix.
 * @param col Column index to search for the pivot.
 * @param row Starting row index for the search.
 * @return The row index of the pivot element, or -1 if no pivot is found.
 */
int c3e_matrix_find_pivot(c3e_matrix* matrix, int col, int row);

/**
 * @brief Extracts the lower triangular part of a matrix.
 *
 * The lower triangular part includes the diagonal and the elements below it.
 *
 * @param matrix Pointer to the matrix.
 * @param diag Diagonal offset (0 for main diagonal, positive for above, negative for below).
 * @return Pointer to the lower triangular matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_tril(c3e_matrix* matrix, int diag);

/**
 * @brief Extracts the upper triangular part of a matrix.
 *
 * The upper triangular part includes the diagonal and the elements above it.
 *
 * @param matrix Pointer to the matrix.
 * @param diag Diagonal offset (0 for main diagonal, positive for above, negative for below).
 * @return Pointer to the upper triangular matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_triu(c3e_matrix* matrix, int diag);

/**
 * @brief Extracts the diagonal elements of a matrix.
 *
 * Returns a vector containing the elements on the specified diagonal.
 *
 * @param matrix Pointer to the matrix.
 * @param k Diagonal offset (0 for main diagonal, positive for above, negative for below).
 * @return Pointer to the vector containing the diagonal elements, or NULL on failure.
 */
c3e_vector* c3e_matrix_diagonal(c3e_matrix* matrix, int k);

/**
 * @brief Sums all elements of a matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The sum of all elements in the matrix.
 */
c3e_number c3e_matrix_sum(c3e_matrix* matrix);

/**
 * @brief Finds the maximum element in a matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The maximum element in the matrix.
 */
c3e_number c3e_matrix_max(c3e_matrix* matrix);

/**
 * @brief Finds the minimum element in a matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The minimum element in the matrix.
 */
c3e_number c3e_matrix_min(c3e_matrix* matrix);

/**
 * @brief Computes the mean of all elements in a matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The mean of the matrix elements.
 */
c3e_number c3e_matrix_mean(c3e_matrix* matrix);

/**
 * @brief Computes the standard deviation of all elements in a matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return The standard deviation of the matrix elements.
 */
c3e_number c3e_matrix_std(c3e_matrix* matrix);

/**
 * @brief Finds the minimum values along a specified dimension.
 *
 * @param matrix Pointer to the matrix.
 * @param dim Dimension along which to find minimum values (0 for rows, 1 for columns).
 * @return Pointer to a matrix or vector containing the minimum values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_min_vals(c3e_matrix* matrix, int dim);

/**
 * @brief Finds the maximum values along a specified dimension.
 *
 * @param matrix Pointer to the matrix.
 * @param dim Dimension along which to find maximum values (0 for rows, 1 for columns).
 * @return Pointer to a matrix or vector containing the maximum values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_max_values(c3e_matrix* matrix, int dim);

/**
 * @brief Computes the sum of elements along a specified dimension.
 *
 * @param matrix Pointer to the matrix.
 * @param dim Dimension along which to sum elements (0 for rows, 1 for columns).
 * @return Pointer to a matrix or vector containing the sum of elements, or NULL on failure.
 */
c3e_matrix* c3e_matrix_sum_vals(c3e_matrix* matrix, int dim);

/**
 * @brief Computes the mean of elements along a specified dimension.
 *
 * @param matrix Pointer to the matrix.
 * @param dim Dimension along which to compute the mean (0 for rows, 1 for columns).
 * @return Pointer to a matrix or vector containing the mean of elements, or NULL on failure.
 */
c3e_matrix* c3e_matrix_mean_vals(c3e_matrix* matrix, int dim);

/**
 * @brief Computes the standard deviation of elements along a specified dimension.
 *
 * @param matrix Pointer to the matrix.
 * @param dim Dimension along which to compute the standard deviation (0 for rows, 1 for columns).
 * @return Pointer to a matrix or vector containing the standard deviation, or NULL on failure.
 */
c3e_matrix* c3e_matrix_std_vals(c3e_matrix* matrix, int dim);

/**
 * @brief Checks if all elements in two matrices are close within a tolerance.
 *
 * Compares each element in the given matrices to see if they are close in value
 * within a certain tolerance, indicating similarity between the matrices.
 *
 * @param matrix Pointer to the first matrix.
 * @param subject Pointer to the second matrix to compare with.
 * @return `true` if all elements are close, `false` otherwise.
 */
bool c3e_matrix_all_close(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Converts a vector to a matrix.
 *
 * Transforms a vector into a single-column matrix, with each element of the vector
 * becoming a row in the resulting matrix.
 *
 * @param vector Pointer to the vector to convert.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_from_vec(c3e_vector* vector);

/**
 * @brief Computes the eigenvectors of a matrix.
 *
 * Calculates the eigenvectors of a square matrix, which are vectors that describe
 * the directions along which the matrix acts by stretching.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to a matrix whose columns are the eigenvectors, or NULL on failure.
 */
c3e_matrix* c3e_matrix_eigenvec(c3e_matrix* matrix);

/**
 * @brief Computes the eigenvalues of a matrix.
 *
 * Calculates the eigenvalues of a square matrix, which are scalars representing the
 * factor by which the eigenvectors are scaled during transformation.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to a vector containing the eigenvalues, or NULL on failure.
 */
c3e_vector* c3e_matrix_eigenvalues(c3e_matrix* matrix);

/**
 * @brief Multiplies a matrix by a vector.
 *
 * Performs matrix-vector multiplication, resulting in a new vector.
 *
 * @param matrix Pointer to the matrix.
 * @param vector Pointer to the vector to multiply.
 * @return Pointer to the resulting vector, or NULL on failure.
 */
c3e_matrix* c3e_matrix_vec_mul(c3e_matrix* matrix, c3e_vector* vector);

/**
 * @brief Adds a scalar to each element of a matrix.
 *
 * @param matrix Pointer to the matrix.
 * @param x The scalar value to add.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_scalar_add(c3e_matrix* matrix, c3e_number x);

/**
 * @brief Subtracts a scalar from each element of a matrix.
 *
 * @param matrix Pointer to the matrix.
 * @param x The scalar value to subtract.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_scalar_sub(c3e_matrix* matrix, c3e_number x);

/**
 * @brief Multiplies each element of a matrix by a scalar.
 *
 * @param matrix Pointer to the matrix.
 * @param x The scalar value to multiply with.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_scalar_mul(c3e_matrix* matrix, c3e_number x);

/**
 * @brief Divides each element of a matrix by a scalar.
 *
 * @param matrix Pointer to the matrix.
 * @param x The scalar value to divide by.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_scalar_div(c3e_matrix* matrix, c3e_number x);

/**
 * @brief Flattens a matrix into a single-row matrix.
 *
 * Converts the matrix into a one-dimensional representation, stacking rows sequentially.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the flattened matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_flatten(c3e_matrix* matrix);

/**
 * @brief Reshapes a matrix to the specified dimensions.
 *
 * Changes the dimensions of the matrix to the given number of rows and columns.
 *
 * @param matrix Pointer to the matrix.
 * @param rows Number of rows for the new shape.
 * @param cols Number of columns for the new shape.
 * @return Pointer to the reshaped matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_reshape(c3e_matrix* matrix, int rows, int cols);

/**
 * @brief Clips the values of a matrix to be within a specified range.
 *
 * Limits the values in the matrix such that they do not exceed the specified minimum
 * and maximum bounds.
 *
 * @param matrix Pointer to the matrix.
 * @param min Minimum value to clip to.
 * @param max Maximum value to clip to.
 * @return Pointer to the clipped matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_clip(c3e_matrix* matrix, c3e_number min, c3e_number max);

/**
 * @brief Computes the inverse sine (arcsine) of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the arcsine values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_arc_sin(c3e_matrix* matrix);

/**
 * @brief Computes the inverse hyperbolic sine (arcsinh) of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the arcsinh values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_arc_sinh(c3e_matrix* matrix);

/**
 * @brief Computes the sine of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the sine values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_sin(c3e_matrix* matrix);

/**
 * @brief Computes the hyperbolic sine (sinh) of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the sinh values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_sinh(c3e_matrix* matrix);

/**
 * @brief Computes the inverse cosine (arccos) of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the arccos values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_arc_cos(c3e_matrix* matrix);

/**
 * @brief Computes the inverse hyperbolic cosine (arccosh) of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the arccosh values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_arc_cosh(c3e_matrix* matrix);

/**
 * @brief Computes the cosine of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the cosine values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_cos(c3e_matrix* matrix);

/**
 * @brief Computes the hyperbolic cosine (cosh) of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the cosh values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_cosh(c3e_matrix* matrix);

/**
 * @brief Computes the inverse tangent (arctan) of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the arctan values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_arc_tan(c3e_matrix* matrix);

/**
 * @brief Computes the inverse hyperbolic tangent (arctanh) of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the arctanh values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_arc_tanh(c3e_matrix* matrix);

/**
 * @brief Computes the tangent of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the tangent values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_tan(c3e_matrix* matrix);

/**
 * @brief Computes the hyperbolic tangent (tanh) of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the tanh values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_tanh(c3e_matrix* matrix);

/**
 * @brief Computes the absolute value of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with the absolute values, or NULL on failure.
 */
c3e_matrix* c3e_matrix_abs(c3e_matrix* matrix);

/**
 * @brief Creates a matrix with values within a specified range.
 *
 * Generates a matrix with elements starting from `start`, incrementing by `step`, up to but not including `end`.
 *
 * @param start The starting value of the sequence.
 * @param end The end value of the sequence (exclusive).
 * @param step The increment value.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_a_range(c3e_number start, c3e_number end, c3e_number step);

/**
 * @brief Computes the cumulative sum of matrix elements along a specified axis.
 *
 * This function calculates the cumulative sum of the elements in the matrix along
 * the specified axis, either row-wise or column-wise.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with cumulative sums, or NULL on failure.
 */
c3e_matrix* c3e_matrix_cum_sum(c3e_matrix* matrix);

/**
 * @brief Computes the cumulative product of matrix elements along a specified axis.
 *
 * This function calculates the cumulative product of the elements in the matrix along
 * the specified axis, either row-wise or column-wise.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix with cumulative products, or NULL on failure.
 */
c3e_matrix* c3e_matrix_cum_product(c3e_matrix* matrix);

/**
 * @brief Applies the natural logarithm to each element in the matrix.
 *
 * This function computes the natural logarithm (base e) of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_log(c3e_matrix* matrix);

/**
 * @brief Applies the base-10 logarithm to each element in the matrix.
 *
 * This function computes the logarithm base 10 of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_log10(c3e_matrix* matrix);

/**
 * @brief Applies the base-2 logarithm to each element in the matrix.
 *
 * This function computes the logarithm base 2 of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_log2(c3e_matrix* matrix);

/**
 * @brief Applies the natural logarithm of one plus the element to each element in the matrix.
 *
 * This function computes `log(1 + x)` for each element `x` in the matrix, which is useful
 * for computing logarithms of values near zero.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_log1p(c3e_matrix* matrix);

/**
 * @brief Computes the reciprocal of each element in the matrix.
 *
 * This function calculates the reciprocal (1/x) of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_reciproc(c3e_matrix* matrix);

/**
 * @brief Raises each element in the matrix to a specified power.
 *
 * This function computes the result of raising each element in the matrix to the power of `exp`.
 *
 * @param matrix Pointer to the matrix.
 * @param exp The exponent to raise each element to.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_pow(c3e_matrix* matrix, c3e_number exp);

/**
 * @brief Computes the product of all elements in the matrix.
 *
 * This function calculates the product of all elements in the matrix, which can be useful
 * for various mathematical and statistical applications.
 *
 * @param matrix Pointer to the matrix.
 * @return The product of all matrix elements.
 */
c3e_number c3e_matrix_product(c3e_matrix* matrix);

/**
 * @brief Computes the reciprocal square root of each element in the matrix.
 *
 * This function calculates the reciprocal of the square root of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_rsqrt(c3e_matrix* matrix);

/**
 * @brief Computes the square root of each element in the matrix.
 *
 * This function calculates the square root of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_sqrt(c3e_matrix* matrix);

/**
 * @brief Performs linear interpolation between two matrices.
 *
 * This function computes a weighted sum of two matrices, `matrix` and `subject`, based on
 * the specified `weight`.
 *
 * @param matrix Pointer to the first matrix.
 * @param subject Pointer to the second matrix.
 * @param weight The interpolation weight, ranging from 0 (all from `matrix`) to 1 (all from `subject`).
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_lerp(c3e_matrix* matrix, c3e_matrix* subject, c3e_number weight);

/**
 * @brief Negates each element in the matrix.
 *
 * This function computes the negative of each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_neg(c3e_matrix* matrix);

/**
 * @brief Computes the sign of each element in the matrix.
 *
 * This function calculates the sign of each element, returning 1 for positive, -1 for negative,
 * and 0 for zero values.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_sign(c3e_matrix* matrix);

/**
 * @brief Checks for element-wise equality between two matrices.
 *
 * This function returns a matrix where each element is 1 if the corresponding elements
 * of `matrix` and `subject` are equal, and 0 otherwise.
 *
 * @param matrix Pointer to the first matrix.
 * @param subject Pointer to the second matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_equals(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Checks for element-wise less-than comparison between two matrices.
 *
 * This function returns a matrix where each element is 1 if the corresponding element of `matrix`
 * is less than that of `subject`, and 0 otherwise.
 *
 * @param matrix Pointer to the first matrix.
 * @param subject Pointer to the second matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_less_than(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Checks for element-wise less-than-or-equal comparison between two matrices.
 *
 * This function returns a matrix where each element is 1 if the corresponding element of `matrix`
 * is less than or equal to that of `subject`, and 0 otherwise.
 *
 * @param matrix Pointer to the first matrix.
 * @param subject Pointer to the second matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_less_than_eq(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Checks for element-wise greater-than comparison between two matrices.
 *
 * This function returns a matrix where each element is 1 if the corresponding element of `matrix`
 * is greater than that of `subject`, and 0 otherwise.
 *
 * @param matrix Pointer to the first matrix.
 * @param subject Pointer to the second matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_greater_than(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Checks for element-wise greater-than-or-equal comparison between two matrices.
 *
 * This function returns a matrix where each element is 1 if the corresponding element of `matrix`
 * is greater than or equal to that of `subject`, and 0 otherwise.
 *
 * @param matrix Pointer to the first matrix.
 * @param subject Pointer to the second matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_greater_than_eq(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Computes the exponential of each element in the matrix.
 *
 * This function calculates the exponential of each element, i.e., `e` raised to the power of the element.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_exp(c3e_matrix* matrix);

/**
 * @brief Computes the log-cumulative-sum-exp of each row of the matrix.
 *
 * This function calculates the log of the cumulative sum of the exponentials of the elements in each row.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_log_cumsum_exp(c3e_matrix* matrix);

/**
 * @brief Computes the logarithm of the Gamma function for each element in the matrix.
 *
 * This function calculates the log of the Gamma function, which generalizes the factorial function,
 * for each element in the matrix.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_log_gamma(c3e_matrix* matrix);

/**
 * @brief Sorts the elements of the matrix in ascending order.
 *
 * This function sorts all elements in the matrix in ascending order, modifying the matrix in place.
 * The sorting is performed in a row-major order.
 *
 * @param matrix Pointer to the matrix to be sorted.
 */
void c3e_matrix_sort(c3e_matrix* matrix);

/**
 * @brief Resizes the matrix to the specified dimensions.
 *
 * This function changes the dimensions of the matrix to `rows` by `cols`. If the new size is smaller,
 * the matrix elements will be truncated. If larger, the additional elements will be uninitialized.
 *
 * @param matrix Pointer to the matrix to be resized.
 * @param rows New number of rows.
 * @param cols New number of columns.
 */
void c3e_matrix_resize(c3e_matrix* matrix, int rows, int cols);

/**
 * @brief Resizes the matrix to match the dimensions of another matrix.
 *
 * This function resizes the matrix to have the same number of rows and columns as the `subject` matrix.
 * The matrix's content is not affected by this operation.
 *
 * @param matrix Pointer to the matrix to be resized.
 * @param subject Pointer to the matrix whose dimensions are used.
 */
void c3e_matrix_resize_as(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Extracts a submatrix from the given matrix.
 *
 * This function extracts elements from the `matrix` based on the indices provided in `subject`.
 * The `subject` matrix contains the row and column indices for the elements to be extracted.
 *
 * @param matrix Pointer to the source matrix.
 * @param subject Pointer to the matrix containing row and column indices.
 * @return Pointer to the resulting submatrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_get(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Repeats the matrix `rrows` times vertically and `rcols` times horizontally.
 *
 * This function creates a new matrix where the original matrix is tiled `rrows` times along the rows
 * and `rcols` times along the columns.
 *
 * @param matrix Pointer to the matrix to be repeated.
 * @param rrows Number of repetitions along rows.
 * @param rcols Number of repetitions along columns.
 * @return Pointer to the resulting repeated matrix, or NULL on failure.
 */
c3e_matrix* c3e_matrix_repeat(c3e_matrix* matrix, int rrows, int rcols);

/**
 * @brief Solves the linear system of equations represented by `matrix` and `subject`.
 *
 * This function solves the matrix equation `matrix * x = subject` for `x`. It assumes that `matrix` is a
 * square matrix and `subject` is a column vector.
 *
 * @param matrix Pointer to the coefficient matrix.
 * @param subject Pointer to the right-hand side matrix or vector.
 * @return Pointer to the solution matrix or vector, or NULL on failure.
 */
c3e_matrix* c3e_matrix_solve(c3e_matrix* matrix, c3e_matrix* subject);

/**
 * @brief Finds the index of the minimum element in the matrix.
 *
 * This function returns the index of the smallest element in the matrix. The index is computed as a
 * single integer where the row and column indices can be derived.
 *
 * @param matrix Pointer to the matrix.
 * @return Index of the minimum element.
 */
int c3e_matrix_arg_min(c3e_matrix* matrix);

/**
 * @brief Finds the index of the maximum element in the matrix.
 *
 * This function returns the index of the largest element in the matrix. The index is computed as a
 * single integer where the row and column indices can be derived.
 *
 * @param matrix Pointer to the matrix.
 * @return Index of the maximum element.
 */
int c3e_matrix_arg_max(c3e_matrix* matrix);

/**
 * @brief Returns the indices of the elements in ascending order.
 *
 * This function returns a matrix containing the indices of the elements sorted in ascending order.
 *
 * @param matrix Pointer to the matrix.
 * @return Pointer to the resulting matrix of sorted indices, or NULL on failure.
 */
c3e_matrix* c3e_matrix_arg_sort(c3e_matrix* matrix);

/**
 * @brief Finds the indices of the minimum values along a specified dimension.
 *
 * This function returns a matrix where each element represents the index of the minimum value along
 * the specified dimension (0 for rows, 1 for columns).
 *
 * @param matrix Pointer to the matrix.
 * @param dim The dimension along which to find minimum values (0 for rows, 1 for columns).
 * @return Pointer to the resulting matrix of indices, or NULL on failure.
 */
c3e_matrix* c3e_matrix_arg_min_vals(c3e_matrix* matrix, int dim);

/**
 * @brief Finds the indices of the maximum values along a specified dimension.
 *
 * This function returns a matrix where each element represents the index of the maximum value along
 * the specified dimension (0 for rows, 1 for columns).
 *
 * @param matrix Pointer to the matrix.
 * @param dim The dimension along which to find maximum values (0 for rows, 1 for columns).
 * @return Pointer to the resulting matrix of indices, or NULL on failure.
 */
c3e_matrix* c3e_matrix_arg_max_vals(c3e_matrix* matrix, int dim);

#endif /* C3E_MATRIX_H */