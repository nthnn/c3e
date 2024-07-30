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

#include <c3e/assert.h>

#include <stdio.h>
#include <stdlib.h>

static void (*assert_handler)(const char* filename, int line) = NULL;

void c3e_assert(bool condition) {
    if(!condition) {
        if(assert_handler)
            assert_handler(__FILE__, __LINE__);
        else {
            char message[256];
            snprintf(
                message, sizeof(message),
                "Assertion failed in file %s at line %d\n", __FILE__, __LINE__
            );

            perror(message);
            exit(EXIT_FAILURE);
        }
    }
}

void c3e_assert_handler(void (*handler)(const char* filename, int line)) {
    assert_handler = handler;
}

void c3e_assert_remove_handler() {
    assert_handler = NULL;
}

bool c3e_assert_has_handler() {
    return assert_handler != NULL;
}
