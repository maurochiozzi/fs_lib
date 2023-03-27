#include "beacon.h"

#include <stdio.h>
#include <stdlib.h>

#include "../space/space.h"

void initBeacon(Beacon *beacon,
                float magnetic_moment_rms, float frequency,
                int sample_rate, int sample_size) {
    beacon->initialized = 0;

    if (sample_rate <= 0 || sample_size <= 0) return;

    beacon->check_sum = 0;
    beacon->check_prd = 1;

    initMagneticFieldSource(&beacon->magnetic_field_source, magnetic_moment_rms, frequency);

    beacon->spectrum_window = beacon->magnetic_field_source.frequency / (sample_rate / sample_size);
    beacon->survey_status = 0;

    beacon->initialized = 1;

    // Calculate check sum and product
    beacon->check_sum += beacon->initialized;
    beacon->check_sum += beacon->spectrum_window;
    beacon->check_sum += beacon->magnetic_field_source.frequency;

    beacon->check_prd *= beacon->initialized;
    beacon->check_prd *= beacon->spectrum_window;
    beacon->check_prd *= beacon->magnetic_field_source.frequency;
}

int isBeaconInitialized(Beacon *beacon) {
    if (beacon && beacon->initialized == 0) return 0;

    float check_sum = 0;
    float check_prd = 1;

    check_sum += beacon->initialized;
    check_sum += beacon->spectrum_window;
    check_sum += beacon->magnetic_field_source.frequency;

    check_prd *= beacon->initialized;
    check_prd *= beacon->spectrum_window;
    check_prd *= beacon->magnetic_field_source.frequency;

    return check_sum == beacon->check_sum && check_prd == beacon->check_prd;
}