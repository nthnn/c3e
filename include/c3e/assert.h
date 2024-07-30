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
 * @file c3e/assert.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Header file for custom assertion handling functions.
 *
 * This header file provides functions for custom assertion handling in the C3E library.
 * It allows setting up custom assertion handlers, removing them, and checking if a
 * handler is currently set.
 */
#ifndef C3E_ASSERT_H
#define C3E_ASSERT_H

#include <stdbool.h>

/**
 * @brief Evaluates an assertion and triggers a custom handler if the condition is false.
 *
 * This function evaluates the given condition and triggers the custom assertion handler
 * if the condition evaluates to `false`. If no custom handler is set, the default behavior
 * is to print an assertion message and terminate the program.
 *
 * @param condition The condition to evaluate. If this condition evaluates to `false`, 
 *                  the assertion fails and the custom handler (if set) will be triggered.
 */
void c3e_assert(bool condition);

/**
 * @brief Sets a custom assertion handler.
 *
 * This function sets a custom handler function that will be called when an assertion fails.
 * The handler function should accept two parameters: a filename and a line number where the
 * assertion failed.
 *
 * @param event A pointer to the custom handler function. This function will be called when
 *              an assertion fails. The handler function should have the signature:
 *              void handler(const char* filename, int line).
 *
 * @see c3e_assert
 */
void c3e_assert_handler(void (*event)(const char* filename, int line));

/**
 * @brief Removes the currently set custom assertion handler.
 *
 * This function removes the custom assertion handler that was previously set using
 * `c3e_assert_handler()`. After calling this function, assertions will use the default
 * behavior, which is to terminate the program.
 */
void c3e_assert_remove_handle();

/**
 * @brief Checks if a custom assertion handler is currently set.
 *
 * This function checks whether a custom assertion handler has been set using
 * `c3e_assert_handler()`.
 *
 * @return `true` if a custom assertion handler is currently set, `false` otherwise.
 */
bool c3e_assert_has_handler();

#endif /* C3E_ASSERT_H */