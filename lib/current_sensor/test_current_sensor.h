/**
 * @file test_current_sensor.h
 * @brief Unit tests for current_sensor.h
 */

#ifndef TEST_CURRENT_SENSOR
#define TEST_CURRENT_SENSOR

#include <stdint.h>
#include <stdio.h>

#include "../minunit/minunit.h"
#include "../spectrum/spectrum.h"
#include "current_sensor.h"

/**
 * @brief Unit test to check if a CurrentSensor struct is initialized correctly
 *
 * @return char* NULL if the test passes, error message otherwise
 */
static char *test_current_sensor_initialized() {
    CurrentSensor sensor = {0};

    initCurrentSensor(&sensor, 110, 2, 0xE2, 2);

    mu_assert("error, sensor initialization",
              isCurrentSensorInitialized(&sensor) == 1);

    // Reset global variables and free variables
    phases_initialized = 0;
    amount_of_phases = 0;

    free(phases);
    free(sensor.samples);

    return 0;
}

/**
 * @brief Unit test to check if a CurrentSensor struct is not initialized
 *
 * @return char* NULL if the test passes, error message otherwise
 */
static char *test_current_sensor_not_initialized() {
    CurrentSensor sensor = {0};

    mu_assert("error, sensor initialization misint32_terpreting",
              isCurrentSensorInitialized(&sensor) == 0);

    return 0;
}

/**
 * @brief Run all current sensor unit tests
 *
 * @return char* NULL if all tests pass, error message otherwise
 */
static char *current_sensor_all_tests() {
    mu_run_test(test_current_sensor_not_initialized);
    mu_run_test(test_current_sensor_initialized);

    return 0;
}

#endif
