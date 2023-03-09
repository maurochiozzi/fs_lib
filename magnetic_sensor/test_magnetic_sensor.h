#ifndef TEST_MAGNETIC_SENSOR
#define TEST_MAGNETIC_SENSOR

#include <stdio.h>

#include "../minunit/minunit.h"
#include "magnetic_sensor.h"

static char *test_magnetic_sensor_ready() {
    MagneticSensor sensor;

    initMagneticSensor(&sensor, 110, 2, 0xE2);

    mu_assert("error, sensor initialization",
              isMagneticSensorInitialized(&sensor) == 1);

    return 0;
}

static char *test_magnetic_sensor_not_ready() {
    MagneticSensor sensor;

    mu_assert("error, sensor initialization misinterpreting",
              isMagneticSensorInitialized(&sensor) != 0);

    return 0;
}

static char *magnetic_sensor_all_tests() {
    mu_run_test(test_magnetic_sensor_ready);
    mu_run_test(test_magnetic_sensor_not_ready);

    return 0;
}

#endif