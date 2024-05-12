/**
 * @file environment.c
 * @brief Functions for handling the environment.
 */

#include "environment.h"

#include <stdint.h>

#include "../beacon/beacon.h"
#include "../magnetic_field/magnetic_field.h"
#include "../space/space.h"

/**
 * @brief Initializes the environment with the given beacons and edges.
 *
 * @param environment pointer to the environment to be initialized.
 * @param beacons pointer to the array of beacons in the environment.
 * @param edges pointer to the array of edges in the environment.
 * @param amount_of_beacons The number of beacons in the environment.
 * @param amount_of_edges The number of edges in the environment.
 */
void initEnvironment(Environment *environment, Beacon *beacons,
                     Coordinate *edges, int32_t amount_of_beacons, int32_t amount_of_edges) {
    environment->initialized = 0;

    if (amount_of_edges <= 0 || amount_of_beacons <= 0) return;

    environment->check_sum = 0;
    environment->check_prd = 1;

    environment->amount_of_edges = amount_of_edges;
    environment->amount_of_beacons = amount_of_beacons;

    environment->edges = edges;
    environment->beacons = beacons;

    environment->initialized = 1;

    // Calculate check sum and product
    environment->check_sum += environment->initialized;
    environment->check_sum += environment->amount_of_edges;
    environment->check_sum += environment->amount_of_beacons;

    environment->check_prd *= environment->initialized;
    environment->check_prd *= environment->amount_of_beacons;
    environment->check_prd *= environment->amount_of_edges;
}

/**
 * @brief Determines if the environment is initialized and ready for use.
 *
 * @param environment pointer to the environment to be checked.
 * @return 1 if the environment is initialized, 0 otherwise.
 */
int32_t isEnvironmentInitialized(Environment *environment) {
    if (environment->initialized == 0) return 0;

    float check_sum = 0;
    float check_prd = 1;

    check_sum += environment->initialized;
    check_sum += environment->amount_of_edges;
    check_sum += environment->amount_of_beacons;

    check_prd *= environment->initialized;
    check_prd *= environment->amount_of_beacons;
    check_prd *= environment->amount_of_edges;

    if (!(check_sum == environment->check_sum && check_prd == environment->check_prd)) return 0;

    // Check if all beacons sensors are correctly initialized
    for (int32_t index = 0; index < environment->amount_of_beacons; index++) {
        if (isBeaconInitialized(&environment->beacons[index]) == 0) {
            // If at least one beacon is wrongly initialized, environment is not ready
            return 0;
        }
    }

    return 1;
}

/**
 * @brief Determines if the given point is inside the environment.
 *
 * @param environment pointer to the environment to be checked.
 * @param point pointer to the point to be checked.
 * @return 1 if the point is inside the environment, 0 otherwise.
 */
int32_t ispointInsideEnvironment(Environment *environment, Coordinate *point) {
    return 0;
}
