#include "magnetic_sensor.h"

#include "../space/space.h"

void initSensor(MagneticSensor sensor, int i2c) {
    // pass
}

int addSample(MagneticSensor sensor, Vector vector) {
    sensor.samples[sensor.sample_cache][sensor.sample_index] = norm(vector);

    return incrementSampleIndex(sensor);
}

int incrementSampleIndex(MagneticSensor sensor) {
    sensor.sample_index = (sensor.sample_index + 1) % sensor.sample_size;

    if (sensor.sample_index == 0) {
        mutexSampleCache(sensor);
    }

    return sensor.sample_index != 0;
}

void mutexSampleCache(MagneticSensor sensor) {
    sensor.sample_cache = (sensor.sample_cache + 1) % 2;
}

/**
 * This function will reset the cache of the previous filled cache.
 */
void resetSampleCache(MagneticSensor sensor) {
    const int previous_cache_index = (sensor.sample_cache + 1) % 2;

    for (int index = 0; index < sensor.sample_size; index++) {
        sensor.samples[previous_cache_index][index] = 0.0;
    }
}
