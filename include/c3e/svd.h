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
 * @file svd.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Functions for Singular Value Decomposition (SVD) in the C3E library.
 *
 * This file provides functions for performing Singular Value Decomposition (SVD) on matrices within
 * the C3E library. SVD is a matrix factorization technique used in various applications including
 * dimensionality reduction, data compression, and numerical stability.
 */
#ifndef C3E_SVD_H
#define C3E_SVD_H

#include <c3e/commons.h>

/**
 * @brief Initializes and computes the Singular Value Decomposition (SVD) of a matrix.
 *
 * This function performs SVD on the given matrix and returns the decomposition components, which include
 * the left singular vectors, right singular vectors, and the singular values.
 *
 * @param matrix Pointer to the matrix to be decomposed.
 * @return A `c3e_svd` structure containing the results of the SVD computation, including:
 *         - `left`: Matrix containing the left singular vectors.
 *         - `right`: Matrix containing the right singular vectors.
 *         - `singular`: Vector containing the singular values.
 */
c3e_svd c3e_svd_init(c3e_matrix* matrix);

/**
 * @brief Frees the resources associated with an SVD decomposition.
 *
 * This function deallocates memory used by the `c3e_svd` structure, which includes freeing memory for
 * the left singular vectors, right singular vectors, and singular values.
 *
 * @param svd The `c3e_svd` structure to be freed.
 */
void c3e_svd_free(c3e_svd svd);

#endif /* C3E_SVD_H */
