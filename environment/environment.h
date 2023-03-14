#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "../beacon/beacon.h"
#include "../space/space.h"

typedef struct
{
    // Will define environment boundaries
    Coordinate *edges;

    Beacon *beacons;

    int amount_of_beacons;

} Environment;

int isPointInsideEnvironment(Environment environment, Coordinate point);

#endif