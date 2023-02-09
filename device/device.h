#ifndef DEVICE_H
#define DEVICE_H

#include "../space/space.h"

typedef struct
{
    Coordinate position;
    Vector heading;
} Device;

void initDevice(Device *device);
void updatePosition(Device *device, Coordinate position, Vector heading);

#endif