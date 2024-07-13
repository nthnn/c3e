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

#include <c3e/random.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

c3e_number c3e_random() {
    c3e_number rand_num;

    #ifdef __linux__
    FILE *urandom = fopen("/dev/urandom", "rb");
    if(urandom == NULL)
        return (c3e_number) rand();

    if(!fread(&rand_num, sizeof(rand_num), 1, urandom))
        return (c3e_number) rand();

    fclose(urandom);
    #else
    rand_num = (c3e_number) rand();
    #endif

    return rand_num;
}

c3e_number c3e_random_bound(c3e_number min, c3e_number max) {
    assert(min < max);

    return min + (max - min) *
        (c3e_random() / (RAND_MAX + 1.0));
}