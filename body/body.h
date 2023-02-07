#ifndef BODY_H
#define BODY_H

#include "field.h"

typedef struct
{
    Coordinate position;
    Vector heading;
} Body;

void initBody(Body *body);
void updatePosition(Body *body, Coordinate position, Vector heading);

#endif