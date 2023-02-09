#include "station.h"

#include <stdio.h>

#include "../beacon/beacon.h"

int requestStationNumberOfBeacons() {
    return 5;
}

void requestBeaconsInformation(Beacon* beacons, int number_of_beacons) {
    const float beacons_data[5][2] = {
        {10.0, 0.5},
        {16.0, 0.2},
        {34.0, 0.1},
        {36.0, 0.2},
        {64.0, 0.3}};

    for (int index = 0; index < number_of_beacons; index++) {
        beacons[index].frequency = beacons_data[index][0];
        beacons[index].magnetic_moment_rms = beacons_data[index][1];
    }
}