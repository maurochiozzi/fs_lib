#include <stdio.h>
#include <stdlib.h>

#include "beacon/beacon.h"
#include "body/body.h"
#include "space/space.h"

#define PREVIOUS_POSITIONS_SIZE 10

Body body;
Body *previous_positions;
int previous_position_index;

// stores beacons frequency, magnetic moment and location
#define MAX_REACHABLE_BEACONS 5

Beacon *beacons;

// An array of nodes will define a environment boundary
#define MAX_ENVIRONMENT_NODES 4

Coordinate *environment;

// stores magnetic space samples
#define MAGNETIC_INTENSITY_SAMPLE_SIZE ;

int magnetic_intensity_samples;
Vector **magnetic_intensity_samples;

int init();
int initPreviousPositionArray();
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
    printf("Initializing...\n");

    initBody(&body);

    printf("Body position (%.2f, %.2f, %.2f)\n", body.heading.x, body.heading.y, body.heading.z);

    initPreviousPositionArray();
    initBeacons();
    initEnvironments();
    initSensors();

    return 0;
}

int initPreviousPositionArray() {
    previous_position_index = 0;

    previous_positions = (Body *)malloc(PREVIOUS_POSITIONS_SIZE);

    return 0;
}

int initBeacons() {
    beacons = (Beacon *)malloc(MAX_REACHABLE_BEACONS);

    return 0;
}

int initEnvironments() {
    environment = (Coordinate *)malloc(MAX_ENVIRONMENT_NODES);

    return 0;
}

int initSensors() {
    return 0;
}

int fetchData(Beacon *beacons, Coordinate *environment) {
    printf("Fetching data...\n");

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
    printf("Surveying beacons...\n");

    return 0;
}

int acquireBodyPosition() {
    printf("Acquiring position...\n");

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
