/**
 * @file test_magnetic_sensor.h
 * @brief Unit tests for magnetic_sensor.h
 */

#ifndef TEST_MAGNETIC_SENSOR
#define TEST_MAGNETIC_SENSOR

#include <stdio.h>

#include "../minunit/minunit.h"
#include "magnetic_sensor.h"

/**
 * @brief Unit test to check if a MagneticSensor struct is initialized correctly
 *
 * @return char* NULL if the test passes, error message otherwise
 */
static char *test_magnetic_sensor_initialized() {
    MagneticSensor sensor = {0};

    initMagneticSensor(&sensor, 110, 2, 0xE2, 2);

    mu_assert("error, sensor initialization",
              isMagneticSensorInitialized(&sensor) == 1);

    // Reset global variables and free variables
    phases_initialized = 0;
    amount_of_phases = 0;

    free(phases);
    free(sensor.samples);

    return 0;
}

/**
 * @brief Unit test to check if a MagneticSensor struct is not initialized
 *
 * @return char* NULL if the test passes, error message otherwise
 */
static char *test_magnetic_sensor_not_initialized() {
    MagneticSensor sensor = {0};

    mu_assert("error, sensor initialization misinterpreting",
              isMagneticSensorInitialized(&sensor) == 0);

    return 0;
}

/**
 * @brief Run all magnetic sensor unit tests
 *
 * @return char* NULL if all tests pass, error message otherwise
 */
static char *magnetic_sensor_all_tests() {
    mu_run_test(test_magnetic_sensor_not_initialized);
    mu_run_test(test_magnetic_sensor_initialized);

    return 0;
}

#endif
