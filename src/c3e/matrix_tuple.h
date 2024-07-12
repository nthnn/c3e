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

#ifndef C3E_MATRIX_TUPLE_H
#define C3E_MATRIX_TUPLE_H

#include <c3e/commons.h>

c3e_matrix_tuple c3e_matrix_qr_decomp(c3e_matrix* matrix);
c3e_matrix_tuple c3e_matrix_lu_decomp(c3e_matrix* original);

void c3e_matrix_tuple_free(c3e_matrix_tuple tuple);

#endif