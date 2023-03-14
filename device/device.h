#ifndef DEVICE_H
#define DEVICE_H

#include "../beacon/beacon.h"
#include "../environment/environment.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../space/space.h"

#define DEVICE_INITIALIZATION_CHECK_SUM 4
#define DEVICE_READY_CHECK_SUM 2

typedef struct
{
    Coordinate position;
    Vector heading;

    Baseline *baseline;

    MagneticSensor *magnetic_sensors;
    int amount_of_magnetic_sensors;

    int initialized;
    int magnetic_sensors_configured;
    int baseline_configured;
    int ready;

} Device;

void initDevice(Device *device, MagneticSensor *magnetic_sensors, int amount_of_magnetic_sensors);

void setBaseline(Device *Device, Baseline *baseline);

int isDeviceInitialized(Device *device);

int isDeviceReady(Device *device);

void updatePosition(Device *device, Coordinate position, Vector heading);

void getCoordinates(Device *device, Environment *environment, int reference);

void estimateDevicePosition(Device *device, Environment *environment);

#endif