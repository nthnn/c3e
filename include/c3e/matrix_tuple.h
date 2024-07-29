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
 * @file matrix_tuple.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Defines functions and structures for matrix tuple operations in C3E.
 *
 * This header file provides the declarations for functions related to matrix tuple operations,
 * including QR decomposition and LU decomposition. It also includes a function for freeing
 * matrix tuples.
 */
#ifndef C3E_MATRIX_TUPLE_H
#define C3E_MATRIX_TUPLE_H

#include <c3e/commons.h>

/**
 * @brief Computes the QR decomposition of a given matrix.
 *
 * This function decomposes a given matrix into a product of an orthogonal matrix (Q)
 * and an upper triangular matrix (R).
 *
 * @param matrix Pointer to the matrix to be decomposed.
 * @return A structure containing the matrices Q and R.
 */
c3e_matrix_tuple c3e_matrix_qr_decomp(c3e_matrix* matrix);

/**
 * @brief Computes the LU decomposition of a given matrix.
 *
 * This function decomposes a given matrix into a product of a lower triangular matrix (L)
 * and an upper triangular matrix (U). The input matrix should be a square matrix.
 *
 * @param original Pointer to the original matrix to be decomposed.
 * @return A structure containing the matrices L and U.
 */
c3e_matrix_tuple c3e_matrix_lu_decomp(c3e_matrix* original);

/**
 * @brief Frees the memory allocated for a matrix tuple.
 *
 * This function should be called to free the memory allocated for the matrices in the tuple
 * returned by the decomposition functions.
 *
 * @param tuple The matrix tuple to be freed.
 */
void c3e_matrix_tuple_free(c3e_matrix_tuple tuple);

#endif /* C3E_MATRIX_TUPLE_H */