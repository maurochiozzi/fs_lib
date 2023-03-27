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

    Baseline *baseline;

    MagneticSensor *magnetic_sensors;
    int amount_of_magnetic_sensors;

    int baseline_configured;

    int check_prd;
    int check_sum;

    int initialized;

} Device;

void initDevice(Device *device, MagneticSensor *magnetic_sensors, int amount_of_magnetic_sensors);

void setBaseline(Device *Device, Baseline *baseline);

int isDeviceInitialized(Device *device);

void updatePosition(Device *device, Coordinate position, Vector heading);
void updateDevicePosition(Device *device, Environment *environment);

void getCoordinates(Device *device, Environment *environment, int reference);

void estimateDevicePosition(Device *device, Environment *environment);

#endif