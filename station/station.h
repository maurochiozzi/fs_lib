#ifndef STATION_H
#define STATION_H

#include "../beacon/beacon.h"

int requestStationNumberOfBeacons();

void requestBeaconsInformation(Beacon* beacon, int number_of_beacons);

#endif