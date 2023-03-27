#ifndef TEST_BEACON
#define TEST_BEACON

#include <stdio.h>
#include <stdlib.h>

#include "../minunit/minunit.h"
#include "beacon.h"

static char *test_beacon_initialization() {
    Beacon beacon = {0};

    initBeacon(&beacon, 0.2, 30, 220, 110);

    mu_assert("error, beacon initialization",
              isBeaconInitialized(&beacon) == 1);

    return 0;
}

static char *test_beacon_not_initialized() {
    Beacon beacon = {0};

    mu_assert("error, beacon initialization misinterpreting",
              isBeaconInitialized(&beacon) == 0);

    return 0;
}

static char *beacon_all_tests() {
    mu_run_test(test_beacon_not_initialized);
    mu_run_test(test_beacon_initialization);

    return 0;
}

#endif