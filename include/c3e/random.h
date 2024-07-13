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

#ifndef C3E_RANDOM_H
#define C3E_RANDOM_H

#include <c3e/commons.h>

c3e_number c3e_random();
c3e_number c3e_random_pseudo();
c3e_number c3e_random_bound(c3e_number min, c3e_number max);

#endif