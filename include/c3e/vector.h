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
 * @file vector.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Vector operations and utilities for the C3E library.
 *
 * This file provides functions for creating and manipulating vectors. Operations include initialization,
 * modification, arithmetic operations, and various vector-specific calculations.
 */
#ifndef C3E_VECTOR_H
#define C3E_VECTOR_H

#include <c3e/commons.h>

#include <stdlib.h>

/**
 * @brief Initializes a vector with a specified size.
 *
 * Allocates memory for a vector with the given size and initializes its elements to zero.
 *
 * @param size The number of elements in the vector.
 * @return A pointer to the newly initialized vector.
 */
c3e_vector* c3e_vector_init(size_t size);

/**
 * @brief Creates a new `c3e_vector` instance with the specified size and data.
 *
 * This function allocates memory for a new `c3e_vector` and initializes it with
 * the provided size and data. The `data` array should contain `size` elements
 * that are copied into the newly created vector's data array.
 *
 * @param size The number of elements in the vector.
 * @param data Pointer to an array of `c3e_number` containing the initial values
 *             for the vector. The data is copied into the new vector.
 * @return Pointer to the newly created `c3e_vector` structure, or `NULL` if memory
 *         allocation fails.
 */
c3e_vector* c3e_vector_create(size_t size, c3e_number* data);

/**
 * @brief Frees the memory allocated for a vector.
 *
 * Releases the memory occupied by the vector and its elements.
 *
 * @param vector A pointer to the vector to be freed.
 */
void c3e_vector_free(c3e_vector* vector);

/**
 * @brief Computes the length of a column vector extracted from a matrix.
 *
 * Calculates the Euclidean norm (length) of a column vector from a matrix.
 *
 * @param matrix The matrix from which the column vector is extracted.
 * @param col The index of the column to be used as the vector.
 * @return The length of the column vector.
 */
c3e_number c3e_vector_length(c3e_matrix* matrix, int col);

/**
 * @brief Retrieves an element from the vector at a specified index.
 *
 * @param vector A pointer to the vector.
 * @param index The index of the element to retrieve.
 * @return The value of the element at the specified index.
 */
c3e_number c3e_vector_get(c3e_vector* vector, size_t index);

/**
 * @brief Sets the value of an element in the vector at a specified index.
 *
 * @param vector A pointer to the vector.
 * @param index The index of the element to set.
 * @param value The value to be assigned to the element at the specified index.
 */
void c3e_vector_set(c3e_vector* vector, size_t index, c3e_number value);

/**
 * @brief Sets multiple elements in the vector with specified values.
 *
 * @param vector A pointer to the vector.
 * @param values An array of values to set in the vector.
 */
void c3e_vector_set_elements(c3e_vector* vector, c3e_number* values);

/**
 * @brief Adds two vectors element-wise.
 *
 * @param vector A pointer to the first vector.
 * @param subject A pointer to the second vector.
 * @return A pointer to the resulting vector after addition.
 */
c3e_vector* c3e_vector_add(c3e_vector* vector, c3e_vector* subject);

/**
 * @brief Subtracts one vector from another element-wise.
 *
 * @param vector A pointer to the first vector.
 * @param subject A pointer to the second vector to be subtracted.
 * @return A pointer to the resulting vector after subtraction.
 */
c3e_vector* c3e_vector_sub(c3e_vector* vector, c3e_vector* subject);

/**
 * @brief Multiplies two vectors element-wise.
 *
 * @param vector A pointer to the first vector.
 * @param subject A pointer to the second vector.
 * @return A pointer to the resulting vector after multiplication.
 */
c3e_vector* c3e_vector_mul(c3e_vector* vector, c3e_vector* subject);

/**
 * @brief Divides one vector by another element-wise.
 *
 * @param vector A pointer to the numerator vector.
 * @param subject A pointer to the denominator vector.
 * @return A pointer to the resulting vector after division.
 */
c3e_vector* c3e_vector_div(c3e_vector* vector, c3e_vector* subject);

/**
 * @brief Computes the element-wise exponential of a vector.
 *
 * @param vector A pointer to the vector.
 * @return A pointer to the resulting vector with exponential values.
 */
c3e_vector* c3e_vector_exp(c3e_vector* vector);

/**
 * @brief Scales the elements of a vector by a specified factor.
 *
 * @param vector A pointer to the vector.
 * @param x The scaling factor.
 * @return A pointer to the resulting scaled vector.
 */
c3e_vector* c3e_vector_scale(c3e_vector* vector, int x);

/**
 * @brief Computes the sum of all elements in a vector.
 *
 * @param vector A pointer to the vector.
 * @return The sum of all elements in the vector.
 */
c3e_number c3e_vector_sum(c3e_vector* vector);

/**
 * @brief Computes the Euclidean norm (magnitude) of a vector.
 *
 * @param vector A pointer to the vector.
 * @return The Euclidean norm of the vector.
 */
c3e_number c3e_vector_norm(c3e_vector* vector);

/**
 * @brief Calculates the angle between two vectors.
 *
 * @param vector A pointer to the first vector.
 * @param subject A pointer to the second vector.
 * @return The angle between the two vectors in radians.
 */
c3e_number c3e_vector_angle(c3e_vector* vector, c3e_vector* subject);

/**
 * @brief Computes the cross product of two vectors.
 *
 * Only valid for 3-dimensional vectors.
 *
 * @param vector A pointer to the first vector.
 * @param subject A pointer to the second vector.
 * @return The cross product of the two vectors.
 */
c3e_number c3e_vector_cross(c3e_vector* vector, c3e_vector* subject);

/**
 * @brief Computes the projection of one vector onto another.
 *
 * @param vector A pointer to the vector to be projected.
 * @param subject A pointer to the vector onto which projection is done.
 * @return The scalar projection of the vector onto the subject vector.
 */
c3e_number c3e_vector_projection(c3e_vector* vector, c3e_vector* subject);

/**
 * @brief Computes the dot product of two vectors.
 *
 * @param vector A pointer to the first vector.
 * @param subject A pointer to the second vector.
 * @return The dot product of the two vectors.
 */
c3e_number c3e_vector_dot(c3e_vector* vector, c3e_vector* subject);

/**
 * @brief Computes the dot product of two columns in matrices.
 *
 * @param matrix A pointer to the first matrix.
 * @param col1 The index of the column in the first matrix.
 * @param subject A pointer to the second matrix.
 * @param col2 The index of the column in the second matrix.
 * @return The dot product of the two specified columns.
 */
c3e_number c3e_vector_dot_cols(c3e_matrix* matrix, int col1, c3e_matrix* subject, int col2);

/**
 * @brief Normalizes a vector to unit length.
 *
 * @param vector A pointer to the vector to be normalized.
 * @return A pointer to the resulting unit vector.
 */
c3e_vector* c3e_vector_normalize(c3e_vector* vector);

/**
 * @brief Transforms a vector by multiplying it with a matrix.
 *
 * @param vector A pointer to the vector.
 * @param matrix A pointer to the matrix used for transformation.
 * @return A pointer to the resulting transformed vector.
 */
c3e_vector* c3e_vector_transform(c3e_vector* vector, c3e_matrix* matrix);

/**
 * @brief Creates a copy of a vector.
 *
 * @param vector A pointer to the vector to be copied.
 * @return A pointer to the newly created copy of the vector.
 */
c3e_vector* c3e_vector_copy(c3e_vector* vector);

/**
 * @brief Creates a vector of zeros.
 *
 * @param size The number of elements in the vector.
 * @return A pointer to the newly created vector with all elements set to zero.
 */
c3e_vector* c3e_vector_zeros(size_t size);

/**
 * @brief Creates a vector of ones.
 *
 * @param size The number of elements in the vector.
 * @return A pointer to the newly created vector with all elements set to one.
 */
c3e_vector* c3e_vector_ones(size_t size);

/**
 * @brief Creates a vector filled with a specific value.
 *
 * @param size The number of elements in the vector.
 * @param values The value to fill each element of the vector.
 * @return A pointer to the newly created vector with all elements set to the specified value.
 */
c3e_vector* c3e_vector_fill(size_t size, c3e_number values);

/**
 * @brief Creates a vector with random values.
 *
 * @param size The number of elements in the vector.
 * @param seed The seed value for the random number generator.
 * @return A pointer to the newly created vector with random values.
 */
c3e_vector* c3e_vector_random(size_t size, int seed);

/**
 * @brief Creates a vector with random values within a specified range.
 *
 * @param size The number of elements in the vector.
 * @param seed The seed value for the random number generator.
 * @param min The minimum value in the range.
 * @param max The maximum value in the range.
 * @return A pointer to the newly created vector with random values within the specified range.
 */
c3e_vector* c3e_vector_random_bound(size_t size, int seed, c3e_number min, c3e_number max);

/**
 * @brief Compares two vectors for equality.
 *
 * Determines if two vectors have identical elements.
 *
 * @param vector A pointer to the first vector.
 * @param subject A pointer to the second vector.
 * @return True if the vectors are equal, false otherwise.
 */
bool c3e_vector_equals(c3e_vector* vector, c3e_vector* subject);

/**
 * @brief Checks if all elements of one vector are close to another vector's elements within a tolerance.
 *
 * Useful for comparing vectors in numerical computations where exact equality is not feasible.
 *
 * @param vector A pointer to the first vector.
 * @param subject A pointer to the second vector.
 * @return True if all elements are within tolerance, false otherwise.
 */
bool c3e_vector_all_close(c3e_vector* vector, c3e_vector* subject);

/**
 * @brief Computes the arc sine of each element in the vector.
 * 
 * This function applies the arc sine function (inverse of sine) to each element of the input vector.
 * The resulting vector contains the arc sine values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the arc sine function will be applied.
 * @return Pointer to a new vector containing the arc sine values of the input vector elements.
 */
c3e_vector* c3e_vector_arc_sin(c3e_vector* vector);

/**
 * @brief Computes the arc hyperbolic sine of each element in the vector.
 * 
 * This function applies the arc hyperbolic sine function (inverse of hyperbolic sine) to each element of the input vector.
 * The resulting vector contains the arc hyperbolic sine values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the arc hyperbolic sine function will be applied.
 * @return Pointer to a new vector containing the arc hyperbolic sine values of the input vector elements.
 */
c3e_vector* c3e_vector_arc_sinh(c3e_vector* vector);

/**
 * @brief Computes the sine of each element in the vector.
 * 
 * This function applies the sine function to each element of the input vector.
 * The resulting vector contains the sine values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the sine function will be applied.
 * @return Pointer to a new vector containing the sine values of the input vector elements.
 */
c3e_vector* c3e_vector_sin(c3e_vector* vector);

/**
 * @brief Computes the hyperbolic sine of each element in the vector.
 * 
 * This function applies the hyperbolic sine function to each element of the input vector.
 * The resulting vector contains the hyperbolic sine values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the hyperbolic sine function will be applied.
 * @return Pointer to a new vector containing the hyperbolic sine values of the input vector elements.
 */
c3e_vector* c3e_vector_sinh(c3e_vector* vector);

/**
 * @brief Computes the arc cosine of each element in the vector.
 * 
 * This function applies the arc cosine function (inverse of cosine) to each element of the input vector.
 * The resulting vector contains the arc cosine values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the arc cosine function will be applied.
 * @return Pointer to a new vector containing the arc cosine values of the input vector elements.
 */
c3e_vector* c3e_vector_arc_cos(c3e_vector* vector);

/**
 * @brief Computes the arc hyperbolic cosine of each element in the vector.
 * 
 * This function applies the arc hyperbolic cosine function (inverse of hyperbolic cosine) to each element of the input vector.
 * The resulting vector contains the arc hyperbolic cosine values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the arc hyperbolic cosine function will be applied.
 * @return Pointer to a new vector containing the arc hyperbolic cosine values of the input vector elements.
 */
c3e_vector* c3e_vector_arc_cosh(c3e_vector* vector);

/**
 * @brief Computes the cosine of each element in the vector.
 * 
 * This function applies the cosine function to each element of the input vector.
 * The resulting vector contains the cosine values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the cosine function will be applied.
 * @return Pointer to a new vector containing the cosine values of the input vector elements.
 */
c3e_vector* c3e_vector_cos(c3e_vector* vector);

/**
 * @brief Computes the hyperbolic cosine of each element in the vector.
 * 
 * This function applies the hyperbolic cosine function to each element of the input vector.
 * The resulting vector contains the hyperbolic cosine values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the hyperbolic cosine function will be applied.
 * @return Pointer to a new vector containing the hyperbolic cosine values of the input vector elements.
 */
c3e_vector* c3e_vector_cosh(c3e_vector* vector);

/**
 * @brief Computes the arc tangent of each element in the vector.
 * 
 * This function applies the arc tangent function (inverse of tangent) to each element of the input vector.
 * The resulting vector contains the arc tangent values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the arc tangent function will be applied.
 * @return Pointer to a new vector containing the arc tangent values of the input vector elements.
 */
c3e_vector* c3e_vector_arc_tan(c3e_vector* vector);

/**
 * @brief Computes the arc hyperbolic tangent of each element in the vector.
 * 
 * This function applies the arc hyperbolic tangent function (inverse of hyperbolic tangent) to each element of the input vector.
 * The resulting vector contains the arc hyperbolic tangent values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the arc hyperbolic tangent function will be applied.
 * @return Pointer to a new vector containing the arc hyperbolic tangent values of the input vector elements.
 */
c3e_vector* c3e_vector_arc_tanh(c3e_vector* vector);

/**
 * @brief Computes the tangent of each element in the vector.
 * 
 * This function applies the tangent function to each element of the input vector.
 * The resulting vector contains the tangent values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the tangent function will be applied.
 * @return Pointer to a new vector containing the tangent values of the input vector elements.
 */
c3e_vector* c3e_vector_tan(c3e_vector* vector);

/**
 * @brief Computes the hyperbolic tangent of each element in the vector.
 * 
 * This function applies the hyperbolic tangent function to each element of the input vector.
 * The resulting vector contains the hyperbolic tangent values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the hyperbolic tangent function will be applied.
 * @return Pointer to a new vector containing the hyperbolic tangent values of the input vector elements.
 */
c3e_vector* c3e_vector_tanh(c3e_vector* vector);

/**
 * @brief Computes the absolute value of each element in the vector.
 * 
 * This function applies the absolute value function to each element of the input vector.
 * The resulting vector contains the absolute values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the absolute value function will be applied.
 * @return Pointer to a new vector containing the absolute values of the input vector elements.
 */
c3e_vector* c3e_vector_abs(c3e_vector* vector);

/**
 * @brief Computes the natural logarithm of each element in the vector.
 * 
 * This function applies the natural logarithm function to each element of the input vector.
 * The resulting vector contains the natural logarithm values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the natural logarithm function will be applied.
 * @return Pointer to a new vector containing the natural logarithm values of the input vector elements.
 */
c3e_vector* c3e_vector_log(c3e_vector* vector);

/**
 * @brief Computes the base-10 logarithm of each element in the vector.
 * 
 * This function applies the base-10 logarithm function to each element of the input vector.
 * The resulting vector contains the base-10 logarithm values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the base-10 logarithm function will be applied.
 * @return Pointer to a new vector containing the base-10 logarithm values of the input vector elements.
 */
c3e_vector* c3e_vector_log10(c3e_vector* vector);

/**
 * @brief Computes the base-2 logarithm of each element in the vector.
 * 
 * This function applies the base-2 logarithm function to each element of the input vector.
 * The resulting vector contains the base-2 logarithm values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the base-2 logarithm function will be applied.
 * @return Pointer to a new vector containing the base-2 logarithm values of the input vector elements.
 */
c3e_vector* c3e_vector_log2(c3e_vector* vector);

/**
 * @brief Computes the natural logarithm of (1 + each element in the vector).
 * 
 * This function applies the natural logarithm function to (1 + each element) of the input vector.
 * The resulting vector contains the natural logarithm values of the modified elements.
 * 
 * @param vector Pointer to the input vector on which the natural logarithm of (1 + element) function will be applied.
 * @return Pointer to a new vector containing the natural logarithm values of the modified input vector elements.
 */
c3e_vector* c3e_vector_log1p(c3e_vector* vector);

/**
 * @brief Computes each element of the vector raised to the given power.
 * 
 * This function applies the power function to each element of the input vector, raising each element
 * to the specified exponent.
 * 
 * @param vector Pointer to the input vector on which the power function will be applied.
 * @param exp The exponent to which each element of the vector will be raised.
 * @return Pointer to a new vector containing the results of raising each element to the given power.
 */
c3e_vector* c3e_vector_pow(c3e_vector* vector, c3e_number exp);

/**
 * @brief Computes the reciprocal square root of each element in the vector.
 * 
 * This function applies the reciprocal square root function (1 / sqrt(x)) to each element of the input vector.
 * The resulting vector contains the reciprocal square root values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the reciprocal square root function will be applied.
 * @return Pointer to a new vector containing the reciprocal square root values of the input vector elements.
 */
c3e_vector* c3e_vector_rsqrt(c3e_vector* vector);

/**
 * @brief Computes the square root of each element in the vector.
 * 
 * This function applies the square root function to each element of the input vector.
 * The resulting vector contains the square root values of the original elements.
 * 
 * @param vector Pointer to the input vector on which the square root function will be applied.
 * @return Pointer to a new vector containing the square root values of the input vector elements.
 */
c3e_vector* c3e_vector_sqrt(c3e_vector* vector);

#endif /* C3E_VECTOR_H */