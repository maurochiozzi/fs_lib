#ifndef BEACON_H
#define BEACON_H

#include "../space/space.h"

typedef struct Beacon {
    float magnetic_moment_rms;

    float frequency;
    int spectrum_window;

    Coordinate position;

    float accuracy;
    int survey_status;  // 0 will be undiscovered and 1 discovered

} Beacon;

void initBeacon(Beacon beacon);

#endif