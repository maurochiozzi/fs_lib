#ifndef TEST_ENVIRONMENT
#define TEST_ENVIRONMENT

#include <stdio.h>
#include <stdlib.h>

#include "../beacon/beacon.h"
#include "../minunit/minunit.h"
#include "environment.h"

static char *test_environment_initialization() {
    Environment environment = {0};

    int amount_of_beacons = 3;
    Beacon *beacons;

    int amount_of_edges = 10;
    Coordinate *edges;

    beacons = (Beacon *)malloc(sizeof(Beacon) * amount_of_beacons);

    for (int index = 0; index < amount_of_beacons; index++) {
        initBeacon(&beacons[index], 0.1, 55.0, 220, 110);
    }

    initEnvironment(&environment, beacons, edges, amount_of_beacons, amount_of_edges);

    mu_assert("error, environment initialization",
              isEnvironmentInitialized(&environment) == 1);

    free(beacons);

    return 0;
}

static char *test_environment_not_initialized() {
    Environment environment = {0};

    mu_assert("error, environment initialization misinterpreting",
              isEnvironmentInitialized(&environment) == 0);

    return 0;
}

static char *environment_all_tests() {
    mu_run_test(test_environment_not_initialized);
    mu_run_test(test_environment_initialization);

    return 0;
}

#endif