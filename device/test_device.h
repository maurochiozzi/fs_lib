#ifndef TEST_DEVICE
#define TEST_DEVICE

#include <stdio.h>
#include <stdlib.h>

#include "../magnetic_sensor/magnetic_sensor.h"
#include "../minunit/minunit.h"
#include "device.h"

static char *test_device_initialization() {
    Device device;
    MagneticSensor *sensors;

    initDevice(&device, sensors, 3);

    mu_assert("error, device initialization",
              isDeviceInitialized(&device) == 1);

    return 0;
}

static char *test_device_not_initialization() {
    Device device;

    mu_assert("error, device initialization misinterpreting",
              isDeviceInitialized(&device) == 0);

    return 0;
}

static char *test_device_ready() {
    const int amount_of_magnetic_sensors = 3;

    Device device;
    MagneticSensor *sensors;
    const int sensors_i2c[] = {0xE1, 0xE2, 0xE3};

    sensors = (MagneticSensor *)malloc(sizeof(MagneticSensor) * amount_of_magnetic_sensors);

    initDevice(&device, sensors, amount_of_magnetic_sensors);

    for (int index = 0; index < device.amount_of_magnetic_sensors; index++) {
        initMagneticSensor(&device.magnetic_sensors[index], 110, 2, sensors_i2c[index]);
    }

    mu_assert("error, device ready",
              isDeviceReady(&device) == 1);

    return 0;
}

static char *test_device_not_ready() {
    const int amount_of_magnetic_sensors = 3;

    Device device;
    MagneticSensor *sensors;

    sensors = (MagneticSensor *)malloc(sizeof(MagneticSensor) * amount_of_magnetic_sensors);

    initDevice(&device, sensors, amount_of_magnetic_sensors);

    mu_assert("error, device not ready",
              isDeviceReady(&device) == 0);

    return 0;
}

static char *test_device_without_sensors() {
    Device device;

    MagneticSensor *sensors;

    initDevice(&device, sensors, 0);

    mu_assert("error, device without sensors",
              isDeviceInitialized(&device) != 0);

    return 0;
}

static char *device_all_tests() {
    mu_run_test(test_device_not_initialization);
    mu_run_test(test_device_initialization);
    mu_run_test(test_device_not_ready);
    mu_run_test(test_device_ready);
    mu_run_test(test_device_without_sensors);

    return 0;
}

#endif