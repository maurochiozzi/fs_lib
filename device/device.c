#include "../space/space.h"
#include "device.h"

void initDevice(Device *device) {
    setCoordinate(&device->position, 0.0, 0.0, 0.0);
    setVector(&device->heading, 0.0, 0.0, 0.0);
}

void updatePosition(Device *device, Coordinate position, Vector heading) {
    device->position = position;
    device->heading = heading;
}