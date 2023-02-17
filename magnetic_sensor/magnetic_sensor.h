#ifndef MAGNETIC_SENSOR_H
#define MAGNETIC_SENSOR_H

#include "../beacon/beacon.h"
#include "../indexer/indexer.h"
#include "../space/space.h"
#include "../spectrum/spectrum.h"

typedef struct MagneticSensor {
    int address;

    // Position of the sensor inside of the device
    Coordinate device_position;

    // Position of the sensor in respect of the beacons
    Coordinate local_position;

    int sample_size;
    float *samples;

    Spectrum spectrum;

    Indexer indexer;

} MagneticSensor;

void initMagneticSensor(MagneticSensor sensor, int i2c);

Vector sampleMagneticSignal(MagneticSensor sensor);

int addSampleMagneticSignal(MagneticSensor sensor, Vector vector);

float getMagneticSignalStrength(MagneticSensor sensor, Beacon beacon);

float getDistanceFromSensor(MagneticSensor sensor, Beacon beacon);

void resetSampleCache(MagneticSensor sensor);

#endif