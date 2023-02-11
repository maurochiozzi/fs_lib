#ifndef MAGNETIC_SENSOR_H
#define MAGNETIC_SENSOR_H

#include "../indexer/indexer.h"
#include "../space/space.h"

typedef struct
{
    int address;

    // Position of the sensor inside of the device
    Coordinate device_position;

    // Position of the sensor in respect of the beacons
    Coordinate local_position;

    int sample_size;
    float *samples;

    Indexer indexer;

} MagneticSensor;

void initMagneticSensor(MagneticSensor sensor, int i2c);

int addSample(MagneticSensor sensor, Vector vector);

void resetSampleCache(MagneticSensor sensor);

#endif