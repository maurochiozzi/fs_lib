#ifndef MAGNETIC_SENSOR_H
#define MAGNETIC_SENSOR_H

#include "../beacon/beacon.h"
#include "../indexer/indexer.h"
#include "../space/space.h"
#include "../spectrum/spectrum.h"

#define MAGNETIC_SENSOR_INITIALIZATION_CHECK_SUM 6

typedef struct MagneticSensor {
    int address;

    // Position of the sensor inside of the device
    Coordinate device_position;

    // Position of the sensor in respect of the beacons
    Coordinate local_position;

    int amount_of_buffers;
    int sample_size;
    float *samples;

    Spectrum spectrum;

    Indexer indexer;

    int initialized;

} MagneticSensor;

void initMagneticSensor(MagneticSensor *sensor,
                        unsigned int sample_size,
                        unsigned int amount_of_buffers,
                        int i2c);

int isMagneticSensorInitialized(MagneticSensor *sensor);

Vector sampleMagneticSignal(MagneticSensor sensor);

int addSampleMagneticSignal(MagneticSensor *sensor, Vector vector);

float getMagneticSignalStrength(MagneticSensor sensor, Beacon beacon);

float calculateDistanceFromBeacon(MagneticSensor sensor, Beacon beacon);

void resetSampleCache(MagneticSensor *sensor);

#endif