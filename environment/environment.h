#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "space.h"

typedef struct
{
    Coordinate *nodes;
} Environment;

int isPointInsideEnvironment(Environment environment, Coordinate point);

#endif