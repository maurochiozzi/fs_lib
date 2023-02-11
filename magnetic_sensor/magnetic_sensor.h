#ifndef MAGNETIC_SENSOR_H
#define MAGNETIC_SENSOR_H

#include "../space/space.h"

typedef struct
{
    int address;

    // Position of the sensor inside of the device
    Coordinate position;

    int sample_size;
    float **samples;

    int sample_index;
    int sample_cache;

} MagneticSensor;

void initSensor(MagneticSensor sensor, int i2c);

int addSample(MagneticSensor sensor, Vector vector);
int incrementSampleIndex(MagneticSensor sensor);
void mutexSampleCache(MagneticSensor sensor);
void resetSampleCache(MagneticSensor sensor);

#endif