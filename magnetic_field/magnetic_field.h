#ifndef MAGNETIC_FIELD_H
#define MAGNETIC_FIELD_H

#include "../space/space.h"

typedef struct MagneticFieldSource {
    float magnetic_moment_rms;
    float frequency;

    Coordinate position;

    float check_prd;
    float check_sum;

    int initialized;
} MagneticFieldSource;

void initMagneticFieldSource(MagneticFieldSource *source, float magnetic_moment_rms, float frequency);
int isMagneticFieldSourceInitialized(MagneticFieldSource *source);
float getMagneticIntensityFromSource(MagneticFieldSource *source, Coordinate *target);
float getMagneticSourceDistanceByIntensity(MagneticFieldSource *source, float intensity);

#endif