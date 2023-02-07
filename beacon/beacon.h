#ifndef BEACON_H
#define BEACON_H

#include "../space/space.h"

typedef struct Beacon {
    Coordinate position;

    float frequency;
    float magnetic_moment_rms;
} Beacon;

void initBeacon(Beacon *beacon);

#endif