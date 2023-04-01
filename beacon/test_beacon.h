/**
 * @file test_beacon.c
 * @brief This file contains the unit tests for the beacon.h and beacon.c files.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../minunit/minunit.h"  // Unit testing framework
#include "beacon.h"              // Code being tested

/**
 * @brief Tests that a Beacon can be initialized correctly
 *
 * @return char* Returns 0 if the test passes, an error message otherwise
 */
static char *test_beacon_initialization() {
    Beacon beacon = {0};

    initBeacon(&beacon, 0.2, 30, 220, 110);

    // Check that the Beacon is initialized correctly
    mu_assert("error, beacon initialization",
              isBeaconInitialized(&beacon) == 1);

    return 0;
}

/**
 * @brief Tests that an uninitialized Beacon is detected correctly
 *
 * @return char* Returns 0 if the test passes, an error message otherwise
 */
static char *test_beacon_not_initialized() {
    Beacon beacon = {0};

    // Check that the uninitialized Beacon is detected correctly
    mu_assert("error, beacon initialization misinterpreting",
              isBeaconInitialized(&beacon) == 0);

    return 0;
}

/**
 * @brief Runs all of the Beacon unit tests
 *
 * @return char* Returns 0 if all of the tests pass, an error message otherwise
 */
static char *beacon_all_tests() {
    mu_run_test(test_beacon_not_initialized);
    mu_run_test(test_beacon_initialization);

    return 0;
}

/**
 * @brief Defines a compile-time constant to indicate that the TEST_BEACON header has been included
 */
#ifndef TEST_BEACON
#define TEST_BEACON

#endif