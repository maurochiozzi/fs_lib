/**
 * @file station.h
 * @brief Header file containing declarations for functions related to a station.
 */

#ifndef STATION_H
#define STATION_H

#include <stdint.h>

#include "../beacon/beacon.h"

/**
 * @brief Requests the number of beacons from a station.
 *
 * This function requests the number of beacons from a station.
 *
 * @return The number of beacons.
 */
int32_t requestStationNumberOfBeacons();

/**
 * @brief Requests information about the beacons from a station.
 *
 * This function requests information about the beacons from a station.
 *
 * @param beacon A pointer to the array of beacons to store the information.
 * @param number_of_beacons The number of beacons to request information about.
 */
void requestBeaconsInformation(Beacon* beacon, int32_t number_of_beacons);

#endif
