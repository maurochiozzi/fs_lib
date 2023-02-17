#ifndef DEVICE_H
#define DEVICE_H

#include "../beacon/beacon.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../space/space.h"

typedef struct
{
    Coordinate position;
    Vector heading;
} Device;

enum Reference { BEACON,
                 SENSOR };

void initDevice(Device *device);

void updatePosition(Device *device, Coordinate position, Vector heading);

void getCoordinates(Beacon *beacons, MagneticSensor *sensors,
                    const int amount_of_beacons,
                    const int amount_of_magnetic_sensor,
                    int reference, Coordinate *coordinates);

Coordinate getDevicePosition(Coordinate *coordinates, int available_points);

#endif