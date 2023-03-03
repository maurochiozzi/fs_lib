#ifndef DEVICE_H
#define DEVICE_H

#include "../beacon/beacon.h"
#include "../environment/environment.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../space/space.h"

typedef struct
{
    Coordinate position;
    Vector heading;

    MagneticSensor *magnetic_sensors;
    int amount_of_magnetic_sensors;

} Device;

void initDevice(Device *device);

void updatePosition(Device *device, Coordinate position, Vector heading);

void getCoordinates(Device *device, Environment *environment, int reference);

void estimateDevicePosition(Device *device, Environment *environment);

#endif