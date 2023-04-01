/**
 * @file station.c
 * @brief Implementation of the functions for the station module.
 */

#include "station.h"

#include <stdio.h>

#include "../beacon/beacon.h"

/**
 * @brief Requests the number of beacons available.
 *
 * @return The number of beacons available.
 */
int requestStationNumberOfBeacons() {
    return 5;
}

/**
 * @brief Requests the information about the available beacons.
 *
 * @param beacons Array of Beacon structs where the information will be stored.
 * @param number_of_beacons The number of beacons available.
 */
void requestBeaconsInformation(Beacon* beacons, int number_of_beacons) {
    MagneticFieldSource* source;

    const float beacons_data[5][2] = {
        {10.0, 0.5},
        {16.0, 0.2},
        {34.0, 0.1},
        {36.0, 0.2},
        {64.0, 0.3}};

    for (int index = 0; index < number_of_beacons; index++) {
        source = &beacons[index].magnetic_field_source;

        source->frequency = beacons_data[index][0];
        source->magnetic_moment_rms = beacons_data[index][1];
    }
}
