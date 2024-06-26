/**
 * @file magnetic_sensor.c
 * @brief Contains functions for int32_teracting with a magnetic sensor.
 */

#include "magnetic_sensor.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../indexer/indexer.h"
#include "../magnetic_field/magnetic_field.h"
#include "../space/space.h"
#include "../spectrum/spectrum.h"

/**
 * @brief Initializes a MagneticSensor struct with the given parameters.
 *
 * @param sensor A pointer to the MagneticSensor struct to initialize.
 * @param sample_size The size of each sample buffer.
 * @param amount_of_buffers The number of sample buffers.
 * @param i2c_address The I2C address of the magnetic sensor.
 */
void initMagneticSensor(MagneticSensor *sensor,
                        uint32_t sample_size,
                        uint32_t amount_of_buffers,
                        int32_t i2c_address,
                        int32_t i2c_int32_terface) {
    sensor->initialized = 0;
    sensor->address = -1;

    if (sample_size <= 10 || amount_of_buffers < 1 || i2c_address < 0) return;

    sensor->sample_size = sample_size;
    sensor->amount_of_buffers = amount_of_buffers;
    sensor->address = i2c_address;
    sensor->int32_terface = i2c_int32_terface;

    initIndexer(&sensor->indexer, sample_size, amount_of_buffers);
    initSpectrum(&sensor->spectrum, sample_size, amount_of_buffers);

    // init sensor buffer
    sensor->samples = (float *)malloc(sizeof(float) * amount_of_buffers * sample_size);
    sensor->indexer.sample_size = sample_size;

    // init sensor connection
    sensor->initialized = 1;
}

/**
 * @brief Checks if the given MagneticSensor is initialized.
 *
 * @param sensor A pointer to the MagneticSensor to check.
 *
 * @return 1 if the sensor is initialized, 0 otherwise.
 */
int32_t isMagneticSensorInitialized(MagneticSensor *sensor) {
    int32_t check_sum = 0;

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

/**
 * @brief Samples the magnetic signal from the given MagneticSensor.
 *
 * @param sensor The MagneticSensor to sample from.
 *
 * @return A Vector struct representing the sampled magnetic signal.
 */
// TODO
Vector sampleMagneticSignal(MagneticSensor sensor) {
    Vector vector = {.x = 0.0, .y = 0.0, .z = 0.0};

    return vector;
}

/**
 * @brief Adds a sample to the given MagneticSensor's sample buffer.
 *
 * @param sensor A pointer to the MagneticSensor to add the sample to.
 * @param sample The sample to add.
 *
 * @return 1 if the sample was added successfully, 0 otherwise.
 */
int32_t addSampleMagneticSignal(MagneticSensor *sensor, float sample) {
    int32_t indexer = sensor->indexer.buffer * sensor->indexer.sample_size + sensor->indexer.sample;

    sensor->samples[indexer] = sample;

    updateSpectrum(sensor, sample);

    return incrementIndex(&sensor->indexer);
}

/**
 * @brief Gets the magnetic signal strength from the given sensor and beacon.
 * @param sensor The magnetic sensor to use.
 * @param beacon The beacon to measure the magnetic signal strength from.
 * @return The magnetic signal strength.
 */
float getMagneticSignalStrength(MagneticSensor *sensor, Beacon *beacon) {
    return getSpectrumWindowint32_tensity(&sensor->spectrum, beacon->spectrum_window,
                                          &sensor->indexer);
}

/**
 * @brief Calculates the distance between the given sensor and beacon.
 * @param sensor The magnetic sensor to use.
 * @param beacon The beacon to calculate the distance to.
 * @return The calculated distance.
 */
float calculateDistanceFromBeacon(MagneticSensor *sensor, Beacon *beacon) {
    float magnetic_signal_strength;
    float distance;

    magnetic_signal_strength = getMagneticSignalStrength(sensor, beacon);

    distance = getMagneticSourceDistanceByint32_tensity(
        &beacon->magnetic_field_source,
        magnetic_signal_strength);

    return distance;
}

/**
 * @brief Updates the spectrum of the given sensor with the provided sample.
 * @param sensor The magnetic sensor to update the spectrum of.
 * @param sample The sample to use to update the spectrum.
 */
void updateSpectrum(MagneticSensor *sensor, const float sample) {
    Spectrum *spectrum = &sensor->spectrum;
    Indexer *indexer = &sensor->indexer;

    float complex phase;

    for (int32_t i = 0; i < indexer->sample + 1; i++) {
        phase = phases[indexer->sample * indexer->sample_size + i];

        spectrum->samples[indexer->buffer * indexer->sample_size + i] +=
            spectrum->double_per_sample_size * (sample * (phase));
    }

    for (int32_t i = 0; i < indexer->sample; i++) {
        phase = phases[indexer->sample * indexer->sample_size + i];

        spectrum->samples[indexer->buffer * indexer->sample_size + indexer->sample] +=
            spectrum->double_per_sample_size * (sensor->samples[indexer->buffer * indexer->sample_size + i] * (phase));
    }
}

/**
 * @brief Resets the cache of the previous filled cache.
 * @param sensor The magnetic sensor to reset the cache of.
 */
void resetSampleCache(MagneticSensor *sensor) {
    Indexer *indexer = &sensor->indexer;

    for (int32_t index = indexer->buffer * sensor->sample_size;
         index < (indexer->buffer + 1) * sensor->sample_size; index++) {
        sensor->samples[index] = 0.0;
    }
}
