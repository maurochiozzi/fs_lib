#ifndef TEST_MAGNETIC_FIELD
#define TEST_MAGNETIC_FIELD

#include <stdio.h>

#include "../minunit/minunit.h"
#include "magnetic_field.h"

static char *test_magnetic_field_source_initialized() {
    MagneticFieldSource source;

    initMagneticFieldSource(&source, 0.2, 30);

    mu_assert("error, magnetic field source initialization",
              isMagneticFieldSourceInitialized(&source) == 1);

    return 0;
}

static char *test_magnetic_field_source_not_initialized() {
    MagneticFieldSource source;

    mu_assert("error, magnetic field source initialization misinterpreting",
              isMagneticFieldSourceInitialized(&source) == 0);

    return 0;
}

static char *magnetic_field_all_tests() {
    mu_run_test(test_magnetic_field_source_not_initialized);
    mu_run_test(test_magnetic_field_source_initialized);

    return 0;
}

#endif