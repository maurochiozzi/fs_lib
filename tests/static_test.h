#ifndef STATIC_TEST
#define STATIC_TEST

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../device/device.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../minunit/minunit.h"

static char *static_device_beacon_survey() {
    const int buffer_size = 2;
    const int sample_size = 20;
    const int sample_rate = 40;

    // Define and initialize device with its sensors
    Device device;

    const int amount_of_magnetic_sensors = 1;
    MagneticSensor *sensors;
    Coordinate sensors_device_position[] = {
        [0] = {.x = -0.5, .y = -0.2886751345948, .z = 0},
        [1] = {.x = +0.0, .y = +0.5773502691869, .z = 0},
        [2] = {.x = -0.5, .y = +0.2886751345948, .z = 0}};

    const int sensors_i2c_address[] = {0xE1, 0xE2, 0xE3};

    sensors = (MagneticSensor *)malloc(sizeof(MagneticSensor) * amount_of_magnetic_sensors);

    for (int index = 0; index < amount_of_magnetic_sensors; index++) {
        sensors[index].device_position = sensors_device_position[index];

        initMagneticSensor(&sensors[index],
                           sample_size, buffer_size,
                           sensors_i2c_address[index]);
    }

    initDevice(&device, sensors, amount_of_magnetic_sensors);

    mu_assert("error, beacon survey - device initialization",
              isDeviceInitialized(&device) == 1);

    // Define and initialize environment with its beacons. No edges will be used
    // in this moment
    Environment environment;
    Environment mocked_environment;

    const int amount_of_beacons = 4;
    Beacon *beacons;
    Beacon *mocked_beacons;
    const float beacons_source_magnetic_moment = 6.999 * pow(10, -8);
    const float beacons_source_frequency[] = {2, 4, 6, 8};  // {36, 40, 80, 52};

    Coordinate mocked_beacons_positions[] = {
        [0] = {.x = -2.0, .y = -1.0, .z = 0},
        [1] = {.x = -1.5, .y = +1.5, .z = 0},
        [2] = {.x = +2.5, .y = +0.5, .z = 0},
        [3] = {.x = +1.5, .y = -1.5, .z = 0}};

    const int amount_of_edges = 10;
    Coordinate *edges;

    beacons = (Beacon *)malloc(sizeof(Beacon) * amount_of_beacons);
    mocked_beacons = (Beacon *)malloc(sizeof(Beacon) * amount_of_beacons);

    for (int index = 0; index < amount_of_beacons; index++) {
        initBeacon(&beacons[index],
                   beacons_source_magnetic_moment,
                   beacons_source_frequency[index],
                   sample_rate, sample_size);

        initBeacon(&mocked_beacons[index],
                   beacons_source_magnetic_moment,
                   beacons_source_frequency[index],
                   sample_rate, sample_size);

        mocked_beacons[index].magnetic_field_source.position = mocked_beacons_positions[index];
    }

    initEnvironment(&environment, beacons, edges, amount_of_beacons, amount_of_edges);
    initEnvironment(&mocked_environment, mocked_beacons, edges, amount_of_beacons, amount_of_edges);

    mu_assert("error, beacon survey - environment initialization",
              isEnvironmentInitialized(&environment) == 1);

    // start surveying beacons

    MagneticSensor *sensor;
    float environment_magnetic_field_intensity;

    float delta_time = 1.0 / sample_rate;
    float time_slice = 0.0;

    for (int index = 0; index < 1 * sample_size; index++) {
        for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensors; sensor_index++) {
            sensor = &device.magnetic_sensors[sensor_index];

            environment_magnetic_field_intensity =
                mockEnvironmentMagneticField(&mocked_environment, &sensor->device_position, time_slice);

            addSampleMagneticSignal(sensor, environment_magnetic_field_intensity);
        }

        time_slice += delta_time;
    }

    // estimateMagneticBeaconSourcePosition(&device, &environment);

    Coordinate *first_beacon_position = &beacons[0].magnetic_field_source.position;

    free(sensors);
    free(beacons);

    return 0;
}

static char *all_static_tests() {
    mu_run_test(static_device_beacon_survey);

    return 0;
}

#endif