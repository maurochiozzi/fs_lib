/**
 * @file test_magnetic_field.h
 * @brief This file contains unit tests for the magnetic_field module.
 */

#ifndef TEST_MAGNETIC_FIELD
#define TEST_MAGNETIC_FIELD

#include <stdio.h>

#include "../minunit/minunit.h"
#include "magnetic_field.h"

/**
 * @brief Test for magnetic field source initialization
 *
 * This function tests whether a magnetic field source has been correctly initialized
 * by the initMagneticFieldSource function.
 *
 * @return NULL if the test passes, otherwise an error message.
 */
static char *test_magnetic_field_source_initialized() {
    MagneticFieldSource source = {0};

    initMagneticFieldSource(&source, 0.2, 30);

    mu_assert("error, magnetic field source initialization",
              isMagneticFieldSourceInitialized(&source) == 1);

    return 0;
}

/**
 * @brief Test for magnetic field source not initialized
 *
 * This function tests whether a magnetic field source has been correctly not initialized
 * by the isMagneticFieldSourceInitialized function.
 *
 * @return NULL if the test passes, otherwise an error message.
 */
static char *test_magnetic_field_source_not_initialized() {
    MagneticFieldSource source = {0};

    mu_assert("error, magnetic field source initialization misinterpreting",
              isMagneticFieldSourceInitialized(&source) == 0);

    return 0;
}

/**
 * @brief Run all magnetic field tests
 *
 * This function runs all magnetic field tests.
 *
 * @return NULL if all tests pass, otherwise an error message.
 */
static char *magnetic_field_all_tests() {
    mu_run_test(test_magnetic_field_source_not_initialized);
    mu_run_test(test_magnetic_field_source_initialized);

    return 0;
}

#endif
