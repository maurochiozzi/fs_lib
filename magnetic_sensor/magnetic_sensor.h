#ifndef MAGNETIC_SENSOR_H
#define MAGNETIC_SENSOR_H

#include "../beacon/beacon.h"
#include "../indexer/indexer.h"
#include "../space/space.h"
#include "../spectrum/spectrum.h"

typedef struct
{
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

typedef struct
{
    Coordinate reference;
    Coordinate destination;

    float intensity;
} MagneticSignalStrength;

enum Reference { BEACON,
                 SENSOR };

void initMagneticSensor(MagneticSensor sensor, int i2c);

int addSample(MagneticSensor sensor, Vector vector);

void getMagneticSignalStrength(MagneticSensor sensor,
                               Beacon *beacons,
                               MagneticSignalStrength *magnetic_signal_strength,
                               int amount_of_beacons,
                               int reference);

void resetSampleCache(MagneticSensor sensor);

#endif