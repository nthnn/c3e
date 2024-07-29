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
 * @file commons.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Common data structures and type definitions for the C3E library.
 *
 * This file contains the basic type definitions and structures used throughout the C3E library,
 * including vectors, matrices, and tensors. It also defines common numerical constants and types.
 */

#ifndef C3E_COMMONS_H
#define C3E_COMMONS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef PI
/**
 * @def PI
 * @brief The mathematical constant π (pi), approximated to 15 decimal places.
 */
#define PI 3.14159265358979323846
#endif

#ifndef C3E_32BIT_NUMBER
/**
 * @typedef c3e_number
 * @brief A type representing a numerical value in C3E. Defaults to double precision.
 *
 * This type is used for representing numerical values in vectors, matrices, and other data structures.
 * It can be defined as float by defining C3E_32BIT_NUMBER during compilation.
 */
typedef double c3e_number;
#else
typedef float  c3e_number;
#endif

/**
 * @struct c3e_vector
 * @brief Represents a mathematical vector.
 *
 * This structure is used to store a vector, which is a one-dimensional array of numerical values.
 * The vector includes a size attribute indicating the number of elements and a pointer to the data.
 */
typedef struct {
    uint32_t size;      ///< The number of elements in the vector.
    c3e_number* data;   ///< Pointer to the data array containing vector elements.
} c3e_vector;

/**
 * @struct c3e_matrix
 * @brief Represents a mathematical matrix.
 *
 * This structure is used to store a matrix, which is a two-dimensional array of numerical values.
 * The matrix includes attributes for the number of rows and columns, and a pointer to the data.
 */
typedef struct {
    uint32_t rows;      ///< The number of rows in the matrix.
    uint32_t cols;      ///< The number of columns in the matrix.
    c3e_number* data;   ///< Pointer to the data array containing matrix elements.
} c3e_matrix;

/**
 * @struct c3e_matrix_tuple
 * @brief A structure representing a tuple of two matrices.
 *
 * This structure is typically used in operations where pairs of matrices are needed, such as matrix multiplication.
 */
typedef struct {
    c3e_matrix* a;      ///< Pointer to the first matrix in the tuple.
    c3e_matrix* b;      ///< Pointer to the second matrix in the tuple.
} c3e_matrix_tuple;

/**
 * @struct c3e_svd
 * @brief Represents the Singular Value Decomposition (SVD) of a matrix.
 *
 * This structure stores the components of an SVD: the left singular vectors, the right singular vectors,
 * and the singular values.
 */
typedef struct {
    c3e_matrix* left;       ///< Matrix containing the left singular vectors.
    c3e_matrix* right;      ///< Matrix containing the right singular vectors.
    c3e_vector* singular;   ///< Vector containing the singular values.
} c3e_svd;

/**
 * @struct c3e_tensor
 * @brief Represents a tensor, a multi-dimensional array of numerical values.
 *
 * This structure is used to store tensors, which generalize vectors and matrices to higher dimensions.
 * It includes attributes for the number of dimensions, the size of each dimension, and pointers to the data.
 */
typedef struct {
    uint32_t dimensions;    ///< The number of dimensions in the tensor.
    size_t dimension_size;  ///< The size of each dimension.

    c3e_matrix** matrices;  ///< Pointer to an array of matrices representing the tensor data.
    c3e_vector* data;       ///< Pointer to a vector containing the tensor data.
} c3e_tensor;

#endif /* C3E_COMMONS_H */