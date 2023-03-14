#include "magnetic_sensor.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../indexer/indexer.h"
#include "../space/space.h"
#include "../spectrum/spectrum.h"

void initMagneticSensor(MagneticSensor *sensor,
                        unsigned int sample_size,
                        unsigned int amount_of_buffers,
                        int i2c_address) {
    sensor->initialized = 0;
    sensor->address = -1;

    if (sample_size <= 10 || amount_of_buffers < 1 || i2c_address < 0) return;

    sensor->sample_size = sample_size;
    sensor->amount_of_buffers = amount_of_buffers;
    sensor->address = i2c_address;

    initIndexer(&sensor->indexer, sample_size, amount_of_buffers);
    initSpectrum(&sensor->spectrum, sample_size, amount_of_buffers);

    // init sensor buffer
    sensor->samples = (float *)malloc(sizeof(float) * amount_of_buffers * sensor->sample_size);
    sensor->indexer.sample_size = sensor->sample_size;

    // init sensor connection

    sensor->initialized = 1;
}

int isMagneticSensorInitialized(MagneticSensor *sensor) {
    int check_sum = 0;

    if (sensor->initialized == 1) {
        check_sum++;
    }

    if (sensor->address > 0) {
        check_sum++;
    }

    if (sensor->sample_size > 0) {
        check_sum++;
    }

    if (sensor->amount_of_buffers > 0) {
        check_sum++;
    }

    if (isIndexerInitialized(&sensor->indexer) == 1) {
        check_sum++;
    }

    if (isSpectrumInitialized(&sensor->spectrum) == 1) {
        check_sum++;
    }

    return check_sum == MAGNETIC_SENSOR_INITIALIZATION_CHECK_SUM;
}

Vector sampleMagneticSignal(MagneticSensor sensor) {
    Vector vector = {.x = 0.0, .y = 0.0, .z = 0.0};

    return vector;
}

int addSampleMagneticSignal(MagneticSensor *sensor, Vector vector) {
    const float sample = norm(vector);

    sensor->samples[sensor->indexer.sample] = sample;

    updateSpectrum(&sensor->spectrum, sample, sensor->samples, &sensor->indexer);

    return incrementIndex(&sensor->indexer);
}

float getMagneticSignalStrength(MagneticSensor *sensor, Beacon *beacon) {
    return getSpectrumWindowIntensity(&sensor->spectrum, beacon->spectrum_window,
                                      &sensor->indexer);
}

float calculateDistanceFromBeacon(MagneticSensor *sensor, Beacon *beacon) {
    float magnetic_signal_strength = getMagneticSignalStrength(sensor, beacon);

    float distance = cbrt(beacon->magnetic_field_source.magnetic_moment_rms /
                          magnetic_signal_strength * 1000000);

    return distance;
}

/**
 * This function will reset the cache of the previous filled cache.
 */
void resetSampleCache(MagneticSensor *sensor) {
    Indexer *indexer = &sensor->indexer;

    const int previous_cache_index = (indexer->buffer + 1) %
                                     sensor->amount_of_buffers;

    for (int index = indexer->buffer * sensor->sample_size;
         index < (indexer->buffer + 1) * sensor->sample_size; index++) {
        sensor->samples[index] = 0.0;
    }
}
