/**
 * @file test_spectrum.h
 * @brief Unit tests for spectrum.c
 */

#ifndef TEST_SPECTRUM
#define TEST_SPECTRUM

#include <stdint.h>
#include <stdio.h>

#include "../minunit/minunit.h"
#include "spectrum.h"

/**
 * @brief Test whether a Spectrum struct is initialized or not.
 *
 * Initializes a Spectrum struct and checks if its initialization
 * status is correctly reported.
 *
 * @return NULL if test passes, an error message if it fails.
 */
static char *test_spectrum_initialized() {
    Spectrum spectrum = {0};

    initSpectrum(&spectrum, 110, 2);

    mu_assert("error, spectrum initialization",
              isSpectrumInitialized(&spectrum) == 1);

    // Reset global variables and free variables
    phases_initialized = 0;
    amount_of_phases = 0;

    free(phases);

    return 0;
}

/**
 * @brief Test whether a non-initialized Spectrum struct is correctly detected.
 *
 * Creates a zero-initialized Spectrum struct and checks if its initialization
 * status is correctly reported as not initialized.
 *
 * @return NULL if test passes, an error message if it fails.
 */
static char *test_spectrum_not_initialized() {
    Spectrum spectrum = {0};

    mu_assert("error, spectrum initialization misint32_terpreting",
              isSpectrumInitialized(&spectrum) == 0);

    return 0;
}

/**
 * @brief Run all tests related to the Spectrum struct.
 *
 * @return NULL if all tests pass, an error message if at least one test fails.
 */
static char *spectrum_all_tests() {
    mu_run_test(test_spectrum_not_initialized);
    mu_run_test(test_spectrum_initialized);

    return 0;
}

#endif
