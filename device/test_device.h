#ifndef TEST_DEVICE
#define TEST_DEVICE

#include <stdio.h>

#include "../minunit/minunit.h"
#include "device.h"

static char *test_device_ready() {
    Device device;

    initDevice(&device);

    Coordinate *position = &device.position;
    Vector *heading = &device.heading;

    mu_assert("error, device initialization",
              isDeviceReady(&device));

    return 0;
}

static char *test_init_device_not_ready() {
    Device device;

    mu_assert("error, device initialization misinterpreting",
              isDeviceReady(&device) == 0);

    return 0;
}

static char *device_all_tests() {
    mu_run_test(test_device_ready);
    mu_run_test(test_init_device_not_ready);

    return 0;
}

#endif