#include <stdio.h>

#include "beacon.h"
#include "body.h"
#include "space.h"

#define PREVIOUS_POSITIONS_SIZE 10

Body body;
Body previous_positions[PREVIOUS_POSITIONS_SIZE];

// stores beacons frequency, magnetic moment and location
#define MAX_REACHABLE_BEACONS 5

Beacon beacons[MAX_REACHABLE_BEACONS];

// An array of nodes will define a environment boundary
#define MAX_ENVIRONMENT_NODES 4

Coordinate *environment;

// stores magnetic space samples
#define MAGNETIC_space_SAMPLE_SIZE ;

short magnetic_space_sample_index;
Vector **magnetic_space_samples;

int init();
int init_body();
int init_beacons();
int init_environments();

int init_sensors();

int fetch_data(Beacon *beacons, Coordinate *environment);

int fetch_beacons_data(Beacon *beacons);
int fetch_environment_boundaries(Coordinate *environment);

int survey_beacons(Beacon *beacons, Coordinate *environment);

int acquire_body_position();

int main() {
    init();

    fetch_data(&beacons, &environment);

    survey_beacons(&beacons, &environment);

    acquire_body_position();

    return 0;
}

int init() {
    init_body();
    init_beacons();
    init_environments();
    init_sensors();
}

int init_body() {
    return 0;
}

int init_beacons() {
    return 0;
}

int init_environments() {
    return 0;
}

int init_sensors() {
    return 0;
}

int fetch_data(Beacon *beacons, Coordinate *environment) {
    // fetch beacon informations (frequency and magnetic moment) from station
    fetch_beacons_data(&beacons);

    // fetch environment boundaries from station
    fetch_environment_boundaries(&environment);

    return 0;
}

int fetch_beacons_data(Beacon *beacons) {
    return 0;
}

int fetch_environment_boundaries(Coordinate *environment) {
    return 0;
}

int survey_beacons(Beacon *beacons, Coordinate *environment) {
    return 0;
}

int acquire_body_position() {
    while (1) {
        while (magnetic_space_sample_index < MAGNETIC_space_SAMPLE_SIZE) {
            sample_magnetic_space(&magnetic_space_samples, magnetic_space_sample_index);

            update_magnetic_space_spectrum(&magnetic_space_samples);
        }

        estimate_position();

        send_position();
    }

    return 0;
}
