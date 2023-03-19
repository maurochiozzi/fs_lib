#ifndef TEST_DEVICE
#define TEST_DEVICE

#include <stdio.h>
#include <stdlib.h>

#include "../magnetic_sensor/magnetic_sensor.h"
#include "../minunit/minunit.h"
#include "device.h"

static char *test_device_initialization() {
    Device device;

    const int amount_of_magnetic_sensors = 3;
    MagneticSensor *sensors;

    const int sensors_i2c[] = {0xE1, 0xE2, 0xE3};

    sensors = (MagneticSensor *)malloc(sizeof(MagneticSensor) * amount_of_magnetic_sensors);

    for (int index = 0; index < amount_of_magnetic_sensors; index++) {
        initMagneticSensor(&sensors[index], 110, 2, sensors_i2c[index]);
    }

    initDevice(&device, sensors, amount_of_magnetic_sensors);

    mu_assert("error, device initialization",
              isDeviceInitialized(&device) == 1);

    return 0;
}

static char *test_device_not_initialized() {
    Device device;

    mu_assert("error, device initialization misinterpreting",
              isDeviceInitialized(&device) == 0);

    return 0;
}

static char *device_all_tests() {
    mu_run_test(test_device_not_initialized);
    mu_run_test(test_device_initialization);

    return 0;
}

#endif