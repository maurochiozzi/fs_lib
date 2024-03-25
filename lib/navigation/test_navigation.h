/**
 * @file test_navigation.h
 * @brief This file contains the unit tests for the navigation module.
 */

#ifndef NAVIGATION_TEST
#define NAVIGATION_TEST

#include <math.h>
#include <stdio.h>

#include "../minunit/minunit.h"
#include "../space/space.h"
#include "navigation.h"

/**
 * @brief Test for the function `calculatePositionByTrilateration` with three references.
 *
 * This test checks if the `calculatePositionByTrilateration` function calculates the position correctly
 * using three references.
 */
static char *test_calculate_position_by_trilateration_three_references() {
    Segment segments[3];
    Coordinate position_estimated = {0};

    // beacons at (0,0), (4,4) and (8,0) with location at (4,2)

    segments[0].reference.x = 0;
    segments[0].reference.y = 0;
    segments[0].reference.z = 0;
    segments[0].magnitude = sqrt(4 * 4 + 2 * 2);

    segments[1].reference.x = 4;
    segments[1].reference.y = 4;
    segments[1].reference.z = 0;
    segments[1].magnitude = sqrt(0 * 0 + 2 * 2);

    segments[2].reference.x = 8;
    segments[2].reference.y = 0;
    segments[2].reference.z = 0;
    segments[2].magnitude = sqrt(4 * 4 + 2 * 2);

    calculatePositionByTrilateration(segments, &position_estimated, 3);

    mu_assert("error, trilateration test 01",
              position_estimated.x == 4.0 &&
                  position_estimated.y == 2.0 &&
                  position_estimated.z == 0.0);

    // beacons at (2,2), (4,6) and (6,0) with location at (2,4)

    segments[0].reference.x = 2;
    segments[0].reference.y = 2;
    segments[0].reference.z = 0;
    segments[0].magnitude = sqrt(0 * 0 + 2 * 2);

    segments[1].reference.x = 6;
    segments[1].reference.y = 4;
    segments[1].reference.z = 0;
    segments[1].magnitude = sqrt(4 * 4 + 0 * 0);

    segments[2].reference.x = 6;
    segments[2].reference.y = 0;
    segments[2].reference.z = 0;
    segments[2].magnitude = sqrt(4 * 4 + 4 * 4);

    calculatePositionByTrilateration(segments, &position_estimated, 3);

    mu_assert("error, trilateration test 02",
              position_estimated.x == 2.0 &&
                  position_estimated.y == 4.0 &&
                  position_estimated.z == 0.0);

    return 0;
}

/**
 * @brief Runs all navigation module unit tests.
 */
static char *navigation_all_tests() {
    mu_run_test(test_calculate_position_by_trilateration_three_references);

    return 0;
}

#endif
