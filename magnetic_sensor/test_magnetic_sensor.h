#ifndef TEST_MAGNETIC_SENSOR
#define TEST_MAGNETIC_SENSOR

#include <stdio.h>

#include "../minunit/minunit.h"
#include "magnetic_sensor.h"

static char *test_magnetic_sensor_initialized() {
    MagneticSensor sensor = {0};

    initMagneticSensor(&sensor, 110, 2, 0xE2);

    mu_assert("error, sensor initialization",
              isMagneticSensorInitialized(&sensor) == 1);

    // Reset global variables and free variables
    angles_initialized = 0;
    amount_of_angles = 0;

    free(angles);
    free(sensor.samples);

    return 0;
}

static char *test_magnetic_sensor_not_initialized() {
    MagneticSensor sensor = {0};

    mu_assert("error, sensor initialization misinterpreting",
              isMagneticSensorInitialized(&sensor) == 0);

    return 0;
}

static char *magnetic_sensor_all_tests() {
    mu_run_test(test_magnetic_sensor_not_initialized);
    mu_run_test(test_magnetic_sensor_initialized);

    return 0;
}

#endif