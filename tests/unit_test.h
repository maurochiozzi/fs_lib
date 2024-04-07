/**
 * @file unit_test.h
 * @brief Header file for running all unit tests.
 */
#ifndef UNIT_TEST
#define UNIT_TEST

#include "../lib/beacon/test_beacon.h"
#include "../lib/current_sensor/test_current_sensor.h"
#include "../lib/device/test_device.h"
#include "../lib/environment/test_environment.h"
#include "../lib/indexer/test_indexer.h"
#include "../lib/magnetic_field/test_magnetic_field.h"
#include "../lib/magnetic_sensor/test_magnetic_sensor.h"
#include "../lib/minunit/minunit.h"
#include "../lib/navigation/test_navigation.h"
#include "../lib/spectrum/test_spectrum.h"

/**
 * @brief Runs all unit tests for the entire project.
 *
 * This function runs all unit tests for the entire project, including all subsystems.
 *
 * @return A character pointer to the result of the test suite.
 */
static char *all_unit_tests() {
    mu_run_all_sub_tests(spectrum_all_tests);
    mu_run_all_sub_tests(indexer_all_tests);
    mu_run_all_sub_tests(magnetic_sensor_all_tests);
    mu_run_all_sub_tests(device_all_tests);
    mu_run_all_sub_tests(magnetic_field_all_tests);
    mu_run_all_sub_tests(current_sensor_all_tests);
    mu_run_all_sub_tests(beacon_all_tests);
    mu_run_all_sub_tests(environment_all_tests);
    mu_run_all_sub_tests(navigation_all_tests);

    return 0;
}

#endif