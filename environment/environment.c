#include "environment.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <math.h>
#include <stdio.h>

#include "../beacon/beacon.h"
#include "../magnetic_field/magnetic_field.h"
#include "../space/space.h"

void initEnvironment(Environment *environment, Beacon *beacons,
                     Coordinate *edges, int amount_of_beacons, int amount_of_edges) {
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

int isEnvironmentInitialized(Environment *environment) {
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
    for (int index = 0; index < environment->amount_of_beacons; index++) {
        if (isBeaconInitialized(&environment->beacons[index]) == 0) {
            // If at least one beacon is wrongly initialized, environment is not ready

            return 0;
        }
    }

    return 1;
}

int isPointInsideEnvironment(Environment *environment, Coordinate *point) {
    return 0;
}

float mockMagneticSourceIntensityFromSource(MagneticFieldSource *source, Coordinate *reference, float time_slice) {
    float intensity = getMagneticIntensityFromSource(source, reference);

    return intensity * cos(2 * M_PI * source->frequency * time_slice);
}

float mockEnvironmentMagneticField(Environment *environment, Coordinate *reference, float time_slice) {
    float environment_magnetic_field_intensity = 0;

    Beacon *beacons = environment->beacons;

    for (int beacon_index = 0; beacon_index < environment->amount_of_beacons; beacon_index++) {
        environment_magnetic_field_intensity += mockMagneticSourceIntensityFromSource(
            &beacons[beacon_index].magnetic_field_source, reference, time_slice);
    }

    return environment_magnetic_field_intensity;
}