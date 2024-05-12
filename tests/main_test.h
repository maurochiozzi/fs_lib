#ifndef MAIN_TEST
#define MAIN_TEST

#include <stdint.h>
#include <stdio.h>

#include "../lib/minunit/minunit.h"
#include "dynamic_test.h"
#include "static_test.h"
#include "transmitter_test.h"
#include "unit_test.h"

int32_t tests_run = 0;

static char *all_tests() {
    mu_run_all_sub_tests(all_unit_tests);
    mu_run_all_sub_tests(all_static_tests);
    mu_run_all_sub_tests(all_dynamic_tests);
    mu_run_all_sub_tests(transmitter_dft);

    return 0;
}

int32_t main_test(int32_t argc, char **argv) {
    char *result = all_tests();

    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

#endif