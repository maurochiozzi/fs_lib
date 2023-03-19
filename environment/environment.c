#include "environment.h"

#include "../beacon/beacon.h"
#include "../space/space.h"

void initEnvironment(Environment *environment, Beacon *beacons,
                     Coordinate *edges, int amount_of_beacons, int amount_of_edges) {
    environment->initialized = 0;

    if (amount_of_edges <= 0 || amount_of_beacons <= 0) return;

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

int isEnvironmentInitialized(Environment *environment) {
    if (environment->initialized == 0) return 0;

    // Check if all beacons sensors are correctly initialized
    for (int index = 0; index < environment->amount_of_beacons; index++) {
        if (isBeaconInitialized(&environment->beacons[index]) == 0) {
            // If at least one beacon is wrongly initialized, environment is not ready

            return 0;
        }
    }

    float check_sum = 0;
    float check_prd = 1;

    check_sum += environment->initialized;
    check_sum += environment->amount_of_edges;
    check_sum += environment->amount_of_beacons;

    check_prd *= environment->initialized;
    check_prd *= environment->amount_of_beacons;
    check_prd *= environment->amount_of_edges;

    return check_sum == environment->check_sum && check_prd == environment->check_prd;
}

int isPointInsideEnvironment(Environment *environment, Coordinate *point) {
    return 0;
}