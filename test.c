#include <stdio.h>

#include "beacon/test_beacon.h"
#include "device/test_device.h"
#include "indexer/test_indexer.h"
#include "magnetic_field/test_magnetic_field.h"
#include "magnetic_sensor/test_magnetic_sensor.h"
#include "minunit/minunit.h"
#include "spectrum/test_spectrum.h"

int tests_run = 0;

static char *all_tests() {
    mu_run_all_sub_tests(spectrum_all_tests);
    mu_run_all_sub_tests(indexer_all_tests);
    mu_run_all_sub_tests(magnetic_sensor_all_tests);
    mu_run_all_sub_tests(device_all_tests);
    mu_run_all_sub_tests(magnetic_field_all_tests);
    mu_run_all_sub_tests(beacon_all_tests);

    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();

    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}