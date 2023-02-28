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

    MagneticSensor *sensors;
    int amount_of_sensors;

} Device;

enum Reference { BEACON,
                 SENSOR };

void initDevice(Device *device);

void updatePosition(Device *device, Coordinate position, Vector heading);

void getCoordinates(Device *device, Environment *environment, int reference);

Coordinate estimateDevicePosition(Device *device, Environment *environment);

#endif