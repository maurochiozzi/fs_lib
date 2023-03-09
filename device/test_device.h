#ifndef TEST_DEVICE
#define TEST_DEVICE

#include <stdio.h>

#include "../minunit/minunit.h"
#include "device.h"

static char *test_device_ready() {
    Device device;

    initDevice(&device, 3);

    Coordinate *position = &device.position;
    Vector *heading = &device.heading;

    mu_assert("error, device initialization",
              isDeviceInitialized(&device));

    return 0;
}

static char *test_device_not_ready() {
    Device device;

    mu_assert("error, device initialization misinterpreting",
              isDeviceInitialized(&device) == 0);

    return 0;
}

static char *test_device_without_sensors() {
    Device device;

    initDevice(&device, 0);

    mu_assert("error, device initialization misinterpreting",
              isDeviceInitialized(&device) == 0);

    return 0;
}

static char *device_all_tests() {
    mu_run_test(test_device_ready);
    mu_run_test(test_device_not_ready);
    mu_run_test(test_device_without_sensors);

    return 0;
}

#endif