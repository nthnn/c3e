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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

c3e_number c3e_random() {
    int urandom = open("/dev/urandom", O_RDONLY);

    if(urandom == -1) {
        srand(time(NULL));
        return c3e_random_pseudo();
    }

    uint32_t rand_num;
    ssize_t bytes_read = read(urandom, &rand_num, sizeof(rand_num));

    close(urandom);
    if(bytes_read != sizeof(rand_num)) {
        srand(time(NULL));
        return c3e_random_pseudo();
    }

    srand(rand_num);
    return c3e_random_pseudo();
}

c3e_number c3e_random_pseudo() {
    return (c3e_number) rand();
}

c3e_number c3e_random_bound(c3e_number min, c3e_number max) {
    assert(min < max);
    return min + (max - min) * c3e_random();
}