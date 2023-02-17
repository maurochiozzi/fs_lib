#include "magnetic_sensor.h"

#include <math.h>
#include <stdlib.h>

#include "../indexer/indexer.h"
#include "../space/space.h"
#include "../spectrum/spectrum.h"

void initMagneticSensor(MagneticSensor sensor, int i2c) {
    // init sensor buffer
    sensor.samples = (float *)malloc(sizeof(float) * 2 * sensor.sample_size);
    sensor.indexer.sample_size = sensor.sample_size;

    // init sensor connection
}

Vector sampleMagneticSignal(MagneticSensor sensor) {
    Vector vector = {.x = 0.0, .y = 0.0, .z = 0.0};

    return vector;
}

int addSampleMagneticSignal(MagneticSensor sensor, Vector vector) {
    const float sample = norm(vector);

    sensor.samples[sensor.indexer.sample] = sample;

    updateSpectrum(sensor.spectrum, sample, sensor.samples, sensor.indexer);

    return incrementIndex(sensor.indexer);
}

float getMagneticSignalStrength(MagneticSensor sensor, Beacon beacon) {
    return getIntensity(sensor.spectrum, beacon.spectrum_window,
                        sensor.indexer);
}

float getDistanceFromSensor(MagneticSensor sensor, Beacon beacon) {
    float magnetic_signal_strength = getMagneticSignalStrength(sensor, beacon);

    float distance = cbrt(beacon.magnetic_moment_rms / magnetic_signal_strength * 1000000);

    return distance;
}

/**
 * This function will reset the cache of the previous filled cache.
 */
void resetSampleCache(MagneticSensor sensor) {
    const int previous_cache_index = (sensor.indexer.buffer + 1) % 2;

    for (int index = sensor.indexer.buffer * sensor.sample_size;
         index < (sensor.indexer.buffer + 1) * sensor.sample_size; index++) {
        sensor.samples[index] = 0.0;
    }
}
