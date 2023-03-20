#ifndef UNIT_TEST
#define UNIT_TEST

#include "../beacon/test_beacon.h"
#include "../device/test_device.h"
#include "../environment/test_environment.h"
#include "../indexer/test_indexer.h"
#include "../magnetic_field/test_magnetic_field.h"
#include "../magnetic_sensor/test_magnetic_sensor.h"
#include "../minunit/minunit.h"
#include "../navigation/test_navigation.h"
#include "../spectrum/test_spectrum.h"

static char *all_unit_tests() {
    mu_run_all_sub_tests(spectrum_all_tests);
    mu_run_all_sub_tests(indexer_all_tests);
    mu_run_all_sub_tests(magnetic_sensor_all_tests);
    mu_run_all_sub_tests(device_all_tests);
    mu_run_all_sub_tests(magnetic_field_all_tests);
    mu_run_all_sub_tests(beacon_all_tests);
    mu_run_all_sub_tests(environment_all_tests);
    mu_run_all_sub_tests(navigation_all_tests);

    return 0;
}

#endif