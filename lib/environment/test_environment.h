/**
 * @file test_environment.h
 * @brief Unit tests for the environment module
 */

#ifndef TEST_ENVIRONMENT
#define TEST_ENVIRONMENT

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../beacon/beacon.h"
#include "../minunit/minunit.h"
#include "environment.h"

/**
 * @brief Test environment initialization
 *
 * Test if the environment is properly initialized with the given parameters
 *
 * @return char* - NULL if the test passed, an error message otherwise
 */
static char *test_environment_initialization() {
    Environment environment = {0};

    int32_t amount_of_beacons = 3;
    Beacon *beacons;

    int32_t amount_of_edges = 10;
    Coordinate *edges;

    beacons = (Beacon *)malloc(sizeof(Beacon) * amount_of_beacons);

    for (int32_t index = 0; index < amount_of_beacons; index++) {
        initBeacon(&beacons[index], 0.1, 55.0, 220, 110);
    }

    initEnvironment(&environment, beacons, edges, amount_of_beacons, amount_of_edges);

    mu_assert("error, environment initialization",
              isEnvironmentInitialized(&environment) == 1);

    free(beacons);

    return 0;
}

/**
 * @brief Test environment not initialized
 *
 * Test if the environment is not initialized when its variables are set to 0
 *
 * @return char* - NULL if the test passed, an error message otherwise
 */
static char *test_environment_not_initialized() {
    Environment environment = {0};

    mu_assert("error, environment initialization misint32_terpreting",
              isEnvironmentInitialized(&environment) == 0);

    return 0;
}

/**
 * @brief Run all environment tests
 *
 * Run all unit tests for the environment module
 *
 * @return char* - NULL
 */
static char *environment_all_tests() {
    mu_run_test(test_environment_not_initialized);
    mu_run_test(test_environment_initialization);

    return 0;
}

#endif
