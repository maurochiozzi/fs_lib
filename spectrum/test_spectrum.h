#ifndef TEST_SPECTRUM
#define TEST_SPECTRUM

#include <stdio.h>

#include "../minunit/minunit.h"
#include "spectrum.h"

static char *test_spectrum_initialized() {
    Spectrum spectrum;

    initSpectrum(&spectrum, 110, 2);

    mu_assert("error, spectrum initialization",
              isSpectrumInitialized(&spectrum) == 1);

    return 0;
}

static char *test_spectrum_not_initialized() {
    Spectrum spectrum;

    mu_assert("error, spectrum initialization misinterpreting",
              isSpectrumInitialized(&spectrum) == 0);

    return 0;
}

static char *spectrum_all_tests() {
    mu_run_test(test_spectrum_not_initialized);
    mu_run_test(test_spectrum_initialized);

    return 0;
}

#endif