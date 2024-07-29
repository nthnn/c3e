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
 * @file tensor.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Functions for tensor operations in the C3E library.
 *
 * This file provides functions for creating, manipulating, and performing operations on tensors.
 * Tensors are multi-dimensional arrays of numerical values, generalizing vectors and matrices.
 * The provided functions include tensor initialization, arithmetic operations, and utilities.
 */
#ifndef C3E_TENSOR_H
#define C3E_TENSOR_H

#include <c3e/commons.h>

/**
 * @brief Initializes a tensor with given data and dimensions.
 *
 * This function creates a new tensor with the specified number of dimensions and size, initializing it
 * with provided matrices and vector data.
 *
 * @param dsize The size of the data vector.
 * @param dims The number of dimensions in the tensor.
 * @param matrices Array of matrices representing the tensor data.
 * @param data Pointer to a vector containing the tensor data.
 * @return A pointer to the newly created `c3e_tensor` structure.
 */
c3e_tensor* c3e_tensor_init(size_t dsize, uint32_t dims, c3e_matrix** matrices, c3e_vector* data);

/**
 * @brief Frees the resources associated with a tensor.
 *
 * This function deallocates memory used by the `c3e_tensor` structure, including memory for the matrices
 * and vector data.
 *
 * @param tensor Pointer to the `c3e_tensor` structure to be freed.
 */
void c3e_tensor_free(c3e_tensor* tensor);

/**
 * @brief Adds two tensors element-wise.
 *
 * This function performs element-wise addition of two tensors with the same dimensions.
 *
 * @param left Pointer to the first tensor.
 * @param right Pointer to the second tensor.
 * @return A pointer to a new `c3e_tensor` structure containing the result of the addition.
 */
c3e_tensor* c3e_tensor_add(c3e_tensor* left, c3e_tensor* right);

/**
 * @brief Subtracts one tensor from another element-wise.
 *
 * This function performs element-wise subtraction of two tensors with the same dimensions.
 *
 * @param left Pointer to the tensor to be subtracted from.
 * @param right Pointer to the tensor to subtract.
 * @return A pointer to a new `c3e_tensor` structure containing the result of the subtraction.
 */
c3e_tensor* c3e_tensor_sub(c3e_tensor* left, c3e_tensor* right);

/**
 * @brief Multiplies two tensors element-wise.
 *
 * This function performs element-wise multiplication of two tensors with the same dimensions.
 *
 * @param left Pointer to the first tensor.
 * @param right Pointer to the second tensor.
 * @return A pointer to a new `c3e_tensor` structure containing the result of the multiplication.
 */
c3e_tensor* c3e_tensor_mul(c3e_tensor* left, c3e_tensor* right);

/**
 * @brief Divides one tensor by another element-wise.
 *
 * This function performs element-wise division of two tensors with the same dimensions.
 *
 * @param left Pointer to the tensor to be divided.
 * @param right Pointer to the tensor to divide by.
 * @return A pointer to a new `c3e_tensor` structure containing the result of the division.
 */
c3e_tensor* c3e_tensor_div(c3e_tensor* left, c3e_tensor* right);

/**
 * @brief Scales the elements of a tensor by a scalar value.
 *
 * This function multiplies every element of the tensor by a specified scalar value.
 *
 * @param tensor Pointer to the tensor to be scaled.
 * @param x The scalar value by which to scale the tensor.
 * @return A pointer to a new `c3e_tensor` structure containing the scaled tensor.
 */
c3e_tensor* c3e_tensor_scale(c3e_tensor* tensor, int x);

/**
 * @brief Applies the exponential function to each element of a tensor.
 *
 * This function computes the exponential of every element in the tensor.
 *
 * @param tensor Pointer to the tensor to be transformed.
 * @return A pointer to a new `c3e_tensor` structure containing the exponential-transformed tensor.
 */
c3e_tensor* c3e_tensor_exp(c3e_tensor* tensor);

/**
 * @brief Normalizes the elements of a tensor.
 *
 * This function normalizes the tensor elements, typically scaling them to a specific range or unit length.
 *
 * @param tensor Pointer to the tensor to be normalized.
 * @return A pointer to a new `c3e_tensor` structure containing the normalized tensor.
 */
c3e_tensor* c3e_tensor_normalize(c3e_tensor* tensor);

/**
 * @brief Creates a copy of a tensor.
 *
 * This function duplicates the given tensor, creating a new tensor with the same data and dimensions.
 *
 * @param tensor Pointer to the tensor to be copied.
 * @return A pointer to a new `c3e_tensor` structure that is a copy of the original tensor.
 */
c3e_tensor* c3e_tensor_copy(c3e_tensor* tensor);

/**
 * @brief Creates a tensor filled with zeros.
 *
 * This function creates a tensor of specified dimensions and size, initialized with zeros.
 *
 * @param dsize The size of the data vector.
 * @param dims The number of dimensions in the tensor.
 * @param rows The number of rows in each matrix.
 * @param cols The number of columns in each matrix.
 * @return A pointer to the newly created `c3e_tensor` structure filled with zeros.
 */
c3e_tensor* c3e_tensor_zeros(size_t dsize, uint32_t dims, int rows, int cols);

/**
 * @brief Creates a tensor filled with ones.
 *
 * This function creates a tensor of specified dimensions and size, initialized with ones.
 *
 * @param dsize The size of the data vector.
 * @param dims The number of dimensions in the tensor.
 * @param rows The number of rows in each matrix.
 * @param cols The number of columns in each matrix.
 * @return A pointer to the newly created `c3e_tensor` structure filled with ones.
 */
c3e_tensor* c3e_tensor_ones(size_t dsize, uint32_t dims, int rows, int cols);

/**
 * @brief Creates a tensor filled with a specific value.
 *
 * This function creates a tensor of specified dimensions and size, initialized with a given value.
 *
 * @param dsize The size of the data vector.
 * @param dims The number of dimensions in the tensor.
 * @param rows The number of rows in each matrix.
 * @param cols The number of columns in each matrix.
 * @param value The value to fill the tensor with.
 * @return A pointer to the newly created `c3e_tensor` structure filled with the specified value.
 */
c3e_tensor* c3e_tensor_fill(size_t dsize, uint32_t dims, int rows, int cols, c3e_number value);

/**
 * @brief Creates a tensor with random values within a range.
 *
 * This function generates a tensor with random values within a specified range, using a given seed for randomness.
 *
 * @param dsize The size of the data vector.
 * @param dims The number of dimensions in the tensor.
 * @param rows The number of rows in each matrix.
 * @param cols The number of columns in each matrix.
 * @param seed The seed value for the random number generator.
 * @param min The minimum value of the random range.
 * @param max The maximum value of the random range.
 * @return A pointer to the newly created `c3e_tensor` structure filled with random values.
 */
c3e_tensor* c3e_tensor_random(size_t dsize, uint32_t dims, int rows, int cols, int seed);

/**
 * @brief Creates a tensor with random values within a specified range.
 *
 * This function generates a tensor with random values within a specified range, using a given seed for randomness.
 *
 * @param dsize The size of the data vector.
 * @param dims The number of dimensions in the tensor.
 * @param rows The number of rows in each matrix.
 * @param cols The number of columns in each matrix.
 * @param seed The seed value for the random number generator.
 * @param min The minimum value of the random range.
 * @param max The maximum value of the random range.
 * @return A pointer to the newly created `c3e_tensor` structure filled with random values within the specified range.
 */
c3e_tensor* c3e_tensor_random_bound(size_t dsize, uint32_t dims, int rows, int cols, int seed, c3e_number min, c3e_number max);

/**
 * @brief Checks if two tensors are equal.
 *
 * This function compares two tensors to determine if they are element-wise equal.
 *
 * @param tensor Pointer to the first tensor.
 * @param subject Pointer to the second tensor.
 * @return `true` if the tensors are equal; `false` otherwise.
 */
bool c3e_tensor_equals(c3e_tensor* tensor, c3e_tensor* subject);

/**
 * @brief Checks if two tensors are element-wise close within a tolerance.
 *
 * This function compares two tensors to determine if they are element-wise close within a specified tolerance.
 *
 * @param tensor Pointer to the first tensor.
 * @param subject Pointer to the second tensor.
 * @return `true` if the tensors are element-wise close; `false` otherwise.
 */
bool c3e_tensor_all_close(c3e_tensor* tensor, c3e_tensor* subject);

#endif /* C3E_TENSOR_H */