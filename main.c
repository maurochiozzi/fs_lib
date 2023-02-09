#include <stdio.h>
#include <stdlib.h>

#include "beacon/beacon.h"
#include "device/device.h"
#include "space/space.h"
#include "station/station.h"

#define PREVIOUS_POSITIONS_SIZE 10

Device device;
Device *previous_positions;
int previous_position_index;

// stores beacons frequency, magnetic moment and location
int amount_of_beacons_available;

Beacon *beacons;

// An array of nodes will define a environment boundary
#define MAX_ENVIRONMENT_NODES 3

Coordinate *environment;

// stores magnetic space samples
#define MAGNETIC_INTENSITY_SAMPLE_SIZE ;

int magnetic_intensity_index;
Vector **magnetic_intensity_samples;

int init();
int initPreviousPositionArray(Device *previous_positions);
int initBeacons(Beacon *beacons);
int initEnvironments(Coordinate *environment);

int initSensors();

int surveyBeacons(Beacon *beacons, Coordinate *environment);

int acquireDevicePosition();

int main(void) {
    init();

    surveyBeacons(beacons, environment);

    acquireDevicePosition();

    return 0;
}

int init() {
    printf("Initializing...\n");

    initDevice(&device);
    initPreviousPositionArray(previous_positions);

    initBeacons(beacons);
    initEnvironments(environment);
    initSensors();

    return 0;
}

int initPreviousPositionArray(Device *previous_positions) {
    previous_position_index = 0;

    previous_positions = (Device *)malloc(PREVIOUS_POSITIONS_SIZE * sizeof(Device));

    // its not required to init it with positions at zero

    return 0;
}

int initBeacons(Beacon *beacons) {
    amount_of_beacons_available = requestStationNumberOfBeacons();

    beacons = (Beacon *)malloc(amount_of_beacons_available * sizeof(Beacon));

    for (int index = 0; index < amount_of_beacons_available; index++) {
        initBeacon(&beacons[index]);
    }

    requestBeaconsInformation(beacons, amount_of_beacons_available);

    return 0;
}

int initEnvironments(Coordinate *environment) {
    environment = (Coordinate *)malloc(MAX_ENVIRONMENT_NODES * sizeof(Coordinate));

    return 0;
}

int initSensors() {
    return 0;
}

int surveyBeacons(Beacon *beacons, Coordinate *environment) {
    printf("Surveying beacons...\n");

    return 0;
}

int acquireDevicePosition() {
    printf("Acquiring position...\n");

    char buf[] = "0.100;0.8foo40;0.030;;;;0.460;0.760bar;-0.090trash";
    char *err, *p = buf;
    double val;
    while (*p) {
        val = strtod(p, &err);
        if (p == err)
            p++;
        else if ((err == NULL) || (*err == 0)) {
            printf("Value: %f\n", val);
            break;
        } else {
            printf("Value: %f\n", val);
            p = err + 1;
        }
    }
    return 0;

    while (1) {
        // while (magnetic_instensity_samples < MAGNETIC_SAMPLE_SIZE) {
        //     sample_magnetic_space(&magnetic_space_samples, magnetic_instensity_samples);

        //     update_magnetic_space_spectrum(&magnetic_space_samples);
        // }

        // estimate_position();

        // send_position();
    }

    return 0;
}
