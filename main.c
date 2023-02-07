#include <stdio.h>

#include "beacon.h"
#include "body.h"
#include "space.h"

#define PREVIOUS_POSITIONS_SIZE 10

Body body;
Body previous_positions[PREVIOUS_POSITIONS_SIZE];

// stores beacons frequency, magnetic moment and location
#define MAX_REACHABLE_BEACONS 10

Beacon beacons[MAX_REACHABLE_BEACONS];

// An array of nodes will define a environment boundary
#define MAX_ENVIRONMENT_NODES

Coordinate *environment;

// stores magnetic space samples
#define MAGNETIC_space_SAMPLE_SIZE ;

short magnetic_space_sample_index;
Vector **magnetic_space_samples;

int init_variables();
int init_sensors();
int fetch_beacons_data(Beacon *beacons);
int fetch_environment_boundaries(Coordinate *environment);

int survey_beacons(Beacon *beacons, Coordinate *environment);

int main() {
    init_variables();

    init_sensors();

    // fetch beacon informations (frequency and magnetic moment) from station
    fetch_beacons_data(&beacons);

    // fetch environment boundaries from station
    fetch_environment_boundaries(&environment);

    // locate beacons (at least two)
    survey_beacons(&beacons, &environment);

    // --- loop

    while (1) {
        while (magnetic_space_sample_index < MAGNETIC_space_SAMPLE_SIZE) {
            sample_magnetic_space(&magnetic_space_samples, magnetic_space_sample_index);

            update_magnetic_space_spectrum(&magnetic_space_samples);
        }

        estimate_position();

        send_position();
    }

    // sample data, append to fourier array

    // calculate positions

    // send positions to station

    return 0;
}

int init_variables() {
    return 0;
}

int init_sensors() {
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
