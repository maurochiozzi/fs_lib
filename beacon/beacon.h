#ifndef BEACON_H
#define BEACON_H

#include "../space/space.h"

typedef struct Beacon {
    float frequency;
    float magnetic_moment_rms;

    Coordinate position;

    int survey_status;  // 0 will be undiscovered and 1 discovered

} Beacon;

void initBeacon(Beacon *beacon);

#endif