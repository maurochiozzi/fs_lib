#ifndef STATIC_TEST
#define STATIC_TEST

#include <stdio.h>
#include <stdlib.h>

#include "../device/device.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../minunit/minunit.h"

static char *static_device_beacon_survey() {
    const int buffer_size = 2;
    const int sample_size = 110;
    const int sample_rate = 220;

    // Define and initialize device with its sensors
    Device device;

    const int amount_of_magnetic_sensors = 3;
    MagneticSensor *sensors;
    Coordinate sensors_device_position[] = {
        [0] = {.x = 0, .y = 0, .z = 0},
        [1] = {.x = 0, .y = 0, .z = 0},
        [2] = {.x = 0, .y = 0, .z = 0}};

    const int sensors_i2c_address[] = {0xE1, 0xE2, 0xE3};

    sensors = (MagneticSensor *)malloc(sizeof(MagneticSensor) * amount_of_magnetic_sensors);

    for (int index = 0; index < amount_of_magnetic_sensors; index++) {
        sensors[index].device_position = sensors_device_position[index];

        initMagneticSensor(&sensors[index],
                           sample_rate, buffer_size,
                           sensors_i2c_address[index]);
    }

    initDevice(&device, sensors, amount_of_magnetic_sensors);

    mu_assert("error, beacon survey - device initialization",
              isDeviceInitialized(&device) == 1);

    // Define and initialize environment with its beacons. No edges will be used
    // in this moment
    Environment environment;

    const int amount_of_beacons = 3;
    Beacon *beacons;
    const float beacons_source_magnetic_moment[] = {.2, .05, .1};
    const float beacons_source_frequency[] = {35, 45, 80};

    const int amount_of_edges = 10;
    Coordinate *edges;

    beacons = (Beacon *)malloc(sizeof(Beacon) * amount_of_beacons);

    for (int index = 0; index < amount_of_beacons; index++) {
        initBeacon(&beacons[index],
                   beacons_source_magnetic_moment[index],
                   beacons_source_frequency[index],
                   sample_rate, sample_size);
    }

    initEnvironment(&environment, beacons, edges, amount_of_beacons, amount_of_edges);

    mu_assert("error, beacon survey - environment initialization",
              isEnvironmentInitialized(&environment) == 1);

    // start surveying beacons

    free(sensors);
    free(beacons);

    return 0;
}

static char *all_static_tests() {
    mu_run_test(static_device_beacon_survey);

    return 0;
}

#endif