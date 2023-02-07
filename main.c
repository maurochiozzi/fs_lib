#include <math.h>
#include <stdio.h>

#include "beacon/beacon.h"
#include "body/body.h"
#include "space/space.h"

#define PREVIOUS_POSITIONS_SIZE 10

Body body;
Body previous_positions[PREVIOUS_POSITIONS_SIZE];

// stores beacons frequency, magnetic moment and location
#define MAX_REACHABLE_BEACONS 5

Beacon *beacons;

// An array of nodes will define a environment boundary
#define MAX_ENVIRONMENT_NODES 4

Coordinate *environment;

// stores magnetic space samples
#define MAGNETIC_space_SAMPLE_SIZE ;

short magnetic_space_sample_index;
Vector **magnetic_space_samples;

int init();
int initBeacons();
int initEnvironments();

int initSensors();

int fetchData(Beacon *beacons, Coordinate *environment);

int fetchBeaconsData(Beacon *beacons);
int fetchEnvironmentBoundaries(Coordinate *environment);

int surveyBeacons(Beacon *beacons, Coordinate *environment);

int acquireBodyPosition();

int main(void) {
    init();

    fetchData(beacons, environment);

    surveyBeacons(beacons, environment);

    acquireBodyPosition();

    return 0;
}

int init() {
    initBody(&body);
    initBeacons();
    initEnvironments();
    initSensors();

    return 0;
}

int initBeacons() {
    return 0;
}

int initEnvironments() {
    return 0;
}

int initSensors() {
    return 0;
}

int fetchData(Beacon *beacons, Coordinate *environment) {
    // fetch beacon informations (frequency and magnetic moment) from station
    fetchBeaconsData(beacons);

    // fetch environment boundaries from station
    fetchEnvironmentBoundaries(environment);

    return 0;
}

int fetchBeaconsData(Beacon *beacons) {
    return 0;
}

int fetchEnvironmentBoundaries(Coordinate *environment) {
    return 0;
}

int surveyBeacons(Beacon *beacons, Coordinate *environment) {
    return 0;
}

int acquireBodyPosition() {
    while (1) {
        // while (magnetic_space_sample_index < MAGNETIC_space_SAMPLE_SIZE) {
        //     sample_magnetic_space(&magnetic_space_samples, magnetic_space_sample_index);

        //     update_magnetic_space_spectrum(&magnetic_space_samples);
        // }

        // estimate_position();

        // send_position();
    }

    return 0;
}
