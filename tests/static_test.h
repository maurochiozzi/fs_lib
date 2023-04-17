/**
 * @file static_test.h
 * @brief This file contains test cases for the static condition.
 *
 * This file contains test cases for the static condition. The tests
 * are designed to cover several features and functionalities of
 * the software.
 *
 */

#ifndef STATIC_TEST
#define STATIC_TEST

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../device/device.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../minunit/minunit.h"
#include "../mock/mock.h"
#include "../navigation/navigation.h"

/**
 * @brief Test case for the beacon survey feature.
 *
 * This function tests the functionality of the beacon survey feature.
 * The feature estimates the position of beacons using the magnetic field
 * intensity detected by a set of magnetic sensors mounted on a device. The
 * function creates a mocked environment with four beacons and a mocked device
 * with three magnetic sensors. The test generates magnetic field intensity
 * samples and uses them to estimate the position of each beacon. The estimated
 * positions are compared to the actual positions of the beacons to check if
 * the functionality works correctly.
 *
 * @return char* - Null if the test passed, an error message otherwise.
 */
static char *static_device_beacon_survey() {
    // Auxiliary variables to help during simulations
    MagneticSensor *sensor;
    float device_heading = 0.0;

    float environment_magnetic_field_intensity;

    const int amount_of_buffers = 2;
    const int sample_size = 110;
    const int sample_rate = 220;

    float delta_time = 1.0 / sample_rate;
    float timestamp = 0.0;

    const float error_check = 0.001;

    Coordinate mocked_device_position = {0};
    Coordinate mocked_sensor_position = {0};

    // Mocked environment will be used to mock beacons and get the magnetic
    // field intensity from them.
    Environment mocked_environment = {0};
    Beacon *mocked_beacons;

    Coordinate mocked_beacons_positions[] = {
        [0] = {.x = -2.0, .y = -1.0, .z = 0},
        [1] = {.x = -1.5, .y = +1.5, .z = 0},
        [2] = {.x = +2.5, .y = +0.5, .z = 0},
        [3] = {.x = +1.5, .y = -1.5, .z = 0}};

    // Define device and its sensors
    Device device = {0};
    Baseline baseline = {0};

    const int amount_of_magnetic_sensors = 3;
    MagneticSensor *device_sensors;

    Coordinate device_sensors_position[] = {
        [0] = {.x = -0.5, .y = -0.2886751345948, .z = 0},
        [1] = {.x = +0.0, .y = +0.5773502691869, .z = 0},
        [2] = {.x = +0.5, .y = -0.2886751345948, .z = 0}};

    const int sensors_i2c_address[] = {0xE1, 0xE2, 0xE3};

    // Define environment with its beacons. No edges will be used at this moment
    Environment environment = {0};

    const int amount_of_beacons = 4;
    Beacon *beacons;

    const float beacons_source_magnetic_moment = 6.999 * pow(10, -8);
    const float beacons_source_frequency[] = {36, 40, 80, 52};

    const int amount_of_edges = 10;
    Coordinate *edges;

    // Initialize sensors, devices, beacons and environment
    device_sensors = (MagneticSensor *)malloc(sizeof(MagneticSensor) * amount_of_magnetic_sensors);

    for (int index = 0; index < amount_of_magnetic_sensors; index++) {
        device_sensors[index].device_position = device_sensors_position[index];

        initMagneticSensor(&device_sensors[index],
                           sample_size, amount_of_buffers,
                           sensors_i2c_address[index]);
    }

    baseline.initial_point = &device_sensors[0].local_position;
    baseline.ending_point = &device_sensors[2].local_position;

    initDevice(&device, device_sensors, amount_of_magnetic_sensors);
    setBaseline(&device, &baseline);

    // Check if device was correctly initialized
    mu_assert("error, beacon survey - device initialization",
              isDeviceInitialized(&device) == 1);

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

    // Check if environment was correctly initialized
    mu_assert("error, beacon survey - environment initialization",
              isEnvironmentInitialized(&environment) == 1);

    // start surveying beacons
    mockBeaconSurveyRun(
        &device, &environment,
        &mocked_environment,
        sample_rate, sample_size);

    estimateMagneticBeaconSourcePosition(&device, &environment);

    // check beacons surveyed

    for (int index = 0; index < amount_of_beacons; index++) {
        mu_assert("beacon survey error",
                  calculatePositionError(&mocked_beacons[index].magnetic_field_source.position,
                                         &beacons[index].magnetic_field_source.position) < error_check);
    }

    // now update device position after move
    mocked_device_position.x = 2.4;
    mocked_device_position.y = 1.8;
    mocked_device_position.z = 0.0;

    // Start sampling environment magnetic field from the new position
    mockMagneticFieldSampleRun(
        &device, device_heading,
        &environment,
        &mocked_device_position,
        sample_rate, sample_size);

    // Update device position with sensors estimations
    updateDevicePosition(&device, &environment);

    mu_assert("device survey 01 error",
              calculatePositionError(&mocked_device_position,
                                     &device.position) < error_check);

    // now update device position after move
    mocked_device_position.x = 0.2;
    mocked_device_position.y = 1.2;
    mocked_device_position.z = 0.0;

    // Start sampling environment magnetic field from the new position
    mockMagneticFieldSampleRun(
        &device, device_heading,
        &environment,
        &mocked_device_position,
        sample_rate, sample_size);

    // Update device position with sensors estimations
    updateDevicePosition(&device, &environment);

    mu_assert("device survey 02 error",
              calculatePositionError(&mocked_device_position,
                                     &device.position) < error_check);

    // Rotate device position to check attitude and heading
    device_heading = 45;

    // Start sampling environment magnetic field from the new position
    mockMagneticFieldSampleRun(
        &device, device_heading,
        &environment,
        &mocked_device_position,
        sample_rate, sample_size);

    // Update device position with sensors estimations
    updateDevicePosition(&device, &environment);

    mu_assert("device survey 03 position error",
              calculatePositionError(&mocked_device_position,
                                     &device.position) < error_check);

    mu_assert("device survey 03 heading error",
              calculateError(device_heading,
                             device.heading) < error_check);

    // Reset global variables and free variables
    phases_initialized = 0;
    amount_of_phases = 0;

    free(phases);
    free(device_sensors);
    free(beacons);

    return 0;
}

/**
 * @brief Runs all static tests
 *
 * @return char* NULL
 */
static char *all_static_tests() {
    mu_run_test(static_device_beacon_survey);

    return 0;
}

#endif