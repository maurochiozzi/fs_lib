#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "../beacon/beacon.h"
#include "../space/space.h"

typedef struct
{
    // Will define environment boundaries
    int amount_of_edges;
    Coordinate *edges;

    int amount_of_beacons;
    Beacon *beacons;

    int check_prd;
    int check_sum;

    int initialized;

} Environment;

void initEnvironment(Environment *environment, Beacon *beacons,
                     Coordinate *edges, int amount_of_beacons, int amount_of_edges);

int isEnvironmentInitialized(Environment *environment);

int isPointInsideEnvironment(Environment *environment, Coordinate *point);

float mockEnvironmentMagneticField(Environment *environment, Coordinate *reference, float timestamp);

#endif