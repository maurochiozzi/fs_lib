#include "magnetic_field.h"

#include <stdio.h>
#include <stdlib.h>

#include "../environment/environment.h"
#include "../space/space.h"
#include "math.h"

void initMagneticFieldSource(MagneticFieldSource *source, float magnetic_moment_rms, float frequency) {
    source->initialized = 0;

    source->check_sum = 0;
    source->check_prd = 1;

    if (magnetic_moment_rms <= 0 || frequency < 0) return;

    source->magnetic_moment_rms = magnetic_moment_rms;
    source->frequency = frequency;

    source->initialized = 1;

    // Calculate check sum and product
    source->check_sum += source->initialized;
    source->check_sum += source->magnetic_moment_rms;
    source->check_sum += source->frequency;

    source->check_prd *= source->initialized;
    source->check_prd *= source->magnetic_moment_rms;
    source->check_prd *= source->frequency;
}

int isMagneticFieldSourceInitialized(MagneticFieldSource *source) {
    float check_sum = 0;
    float check_prd = 1;

    check_sum += source->initialized;
    check_sum += source->magnetic_moment_rms;
    check_sum += source->frequency;

    check_prd *= source->initialized;
    check_prd *= source->magnetic_moment_rms;
    check_prd *= source->frequency;

    return check_sum == source->check_sum && check_prd == source->check_prd;
}

float getMagneticIntensityFromSource(MagneticFieldSource *source, Coordinate *reference) {
    float distance = euclideanDistance2(&source->position, reference);

    float intensity = source->magnetic_moment_rms / (distance * distance * distance) * 1000000;

    return intensity;
}

float getMagneticSourceDistanceByIntensity(MagneticFieldSource *source, float intensity) {
    float distance = cbrt(source->magnetic_moment_rms /
                          intensity * 1000000);

    return distance;
}
