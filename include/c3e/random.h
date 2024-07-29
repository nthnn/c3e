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
 * @file random.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Random number generation utilities for the C3E library.
 *
 * This file provides functions for generating random numbers within the C3E library. It includes
 * utilities for generating random numbers with varying characteristics, including pseudorandom
 * values and numbers within a specified range.
 */
#ifndef C3E_RANDOM_H
#define C3E_RANDOM_H

#include <c3e/commons.h>

/**
 * @brief Generates a random number.
 *
 * This function produces a random floating-point number from `/dev/urandom`.
 * The number generated is uniformly distributed within this range.
 *
 * @return A random number in the range [0.0, 1.0).
 */
c3e_number c3e_random();

/**
 * @brief Generates a pseudorandom number.
 *
 * This function produces a pseudorandom floating-point number between 0.0 and 1.0. Unlike `c3e_random()`,
 * this function may use a different algorithm or seed for generating pseudorandom numbers, providing
 * a potentially different distribution or pattern of randomness.
 *
 * @return A pseudorandom number in the range [0.0, 1.0).
 */
c3e_number c3e_random_pseudo();

/**
 * @brief Generates a random number within a specified range.
 *
 * This function generates a random floating-point number
 * between `min` and `max`. The generated number is
 * uniformly distributed within the specified range.
 *
 * @param min The lower bound of the range (inclusive).
 * @param max The upper bound of the range (inclusive).
 * @return A random number within the range [min, max].
 */
c3e_number c3e_random_bound(c3e_number min, c3e_number max);

#endif /* C3E_RANDOM_H */