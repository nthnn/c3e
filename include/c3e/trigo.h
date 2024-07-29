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
 * @file trigo.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Trigonometric and special functions for the C3E library.
 *
 * This file provides functions for performing trigonometric calculations and special mathematical functions.
 * These include conversions between radians and degrees, as well as Gamma and logarithmic Gamma functions, and many more.
 */
#ifndef C3E_TRIGO_H
#define C3E_TRIGO_H

#include <c3e/commons.h>

/**
 * @brief Converts an angle from radians to degrees.
 *
 * This function converts a given angle in radians to its equivalent in degrees.
 *
 * @param x The angle in radians to be converted.
 * @return The equivalent angle in degrees.
 */
c3e_number c3e_radian_degrees(c3e_number x);

/**
 * @brief Computes the Gamma function of a given number.
 *
 * This function calculates the Gamma function of a number, which is a generalization of the factorial function.
 * For positive integers, it returns the factorial of (x-1). For other values, it provides an approximation
 * based on the Gamma function definition.
 *
 * @param x The value for which the Gamma function is to be computed.
 * @return The Gamma function of the input value.
 */
c3e_number c3e_gamma(c3e_number x);

/**
 * @brief Computes the logarithm of the Gamma function (log-Gamma) of a given number.
 *
 * This function calculates the natural logarithm of the Gamma function for a given input. The log-Gamma function
 * is useful in various statistical computations, especially in contexts where logarithmic scales are employed.
 *
 * @param x The value for which the log-Gamma function is to be computed.
 * @return The natural logarithm of the Gamma function of the input value.
 */
c3e_number c3e_log_gamma(c3e_number x);

#endif /* C3E_TRIGO_H */