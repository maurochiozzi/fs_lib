#ifndef TEST_DEVICE
#define TEST_DEVICE

#include <stdio.h>
#include <stdlib.h>

#include "../magnetic_sensor/magnetic_sensor.h"
#include "../minunit/minunit.h"
#include "device.h"

/**
 * @brief Tests the initialization of a device with magnetic sensors.
 *
 * @return char* - Returns NULL if test passes, or an error message if it fails.
 */
static char *test_device_initialization() {
    Device device = {0};

    const int amount_of_magnetic_sensors = 3;
    MagneticSensor *sensors;

    const int sensors_i2c_address[] = {0xE1, 0xE2, 0xE3};
    const int sensors_i2c_interface[] = {0xE1, 0xE2, 0xE3};

    sensors = (MagneticSensor *)malloc(sizeof(MagneticSensor) * amount_of_magnetic_sensors);

    for (int index = 0; index < amount_of_magnetic_sensors; index++) {
        initMagneticSensor(&sensors[index], 110, 2, sensors_i2c_address[index],
                           sensors_i2c_interface[index]);
    }

    initDevice(&device, sensors, amount_of_magnetic_sensors);

    mu_assert("error, device initialization",
              isDeviceInitialized(&device) == 1);

    // Reset global variables and free variables
    phases_initialized = 0;
    amount_of_phases = 0;

    free(phases);

    for (int i = 0; i < amount_of_magnetic_sensors; i++) {
        free(sensors[i].samples);
    }

    free(sensors);

    return 0;
}

/**
 * @brief Tests that a device is not initialized if it has not been properly initialized.
 *
 * @return char* - Returns NULL if test passes, or an error message if it fails.
 */
static char *test_device_not_initialized() {
    Device device = {0};

    mu_assert("error, device initialization misinterpreting",
              isDeviceInitialized(&device) == 0);

    return 0;
}

/**
 * @brief Runs all the tests for the device.
 *
 * @return char* - Returns NULL if all tests pass, or an error message if any of the tests fail.
 */
static char *device_all_tests() {
    mu_run_test(test_device_not_initialized);
    mu_run_test(test_device_initialization);

    return 0;
}

#endif
