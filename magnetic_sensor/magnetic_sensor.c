#include "magnetic_sensor.h"

#include "../space/space.h"

void initSensor(MagneticSensor sensor, int i2c) {
    // init sensor buffer
    sensor.samples = (float*)malloc(sizeof(float) * 2 * sensor.sample_size);

    // init sensor connection
}

int addSample(MagneticSensor sensor, Vector vector) {
    sensor.samples[sensor.sample_index] = norm(vector);

    return incrementSampleIndex(sensor);
}

int incrementSampleIndex(MagneticSensor sensor) {
    sensor.sample_index = (sensor.sample_index + 1) % 2 * sensor.sample_size;

    int increment_buffer = sensor.sample_index % sensor.sample_size;

    if (increment_buffer == 0) {
        mutexSampleCache(sensor);
    }

    return increment_buffer;
}

void mutexSampleCache(MagneticSensor sensor) {
    sensor.buffer_index = (sensor.buffer_index + 1) % 2;
}

/**
 * This function will reset the cache of the previous filled cache.
 */
void resetSampleCache(MagneticSensor sensor) {
    const int previous_cache_index = (sensor.buffer_index + 1) % 2;

    for (int index = sensor.buffer_index * sensor.sample_size;
         index < (sensor.buffer_index + 1) * sensor.sample_size; index++) {
        sensor.samples[index] = 0.0;
    }
}
