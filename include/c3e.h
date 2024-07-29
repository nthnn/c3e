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
 * @file c3e.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Main header file for the Complex Compute Core Engine (C3E).
 *
 * This file includes all the necessary header files required for using the 
 * Complex Compute Core Engine (C3E). The C3E library provides advanced 
 * computational functionalities including matrix operations, tensor operations, 
 * random number generation, trigonometric calculations, and more. This file 
 * acts as the central include point for applications utilizing C3E.
 */
#ifndef C3E_H
#define C3E_H

#ifndef __linux__
#   error "Incompatible target architecture using C3E."
#endif

#include <c3e/commons.h>
#include <c3e/matrix.h>
#include <c3e/matrix_tuple.h>
#include <c3e/net.h>
#include <c3e/random.h>
#include <c3e/svd.h>
#include <c3e/tensor.h>
#include <c3e/trigo.h>
#include <c3e/vector.h>

#endif /* C3E_H */