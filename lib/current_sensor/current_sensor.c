/**
 * @file current_sensor.c
 * @brief Contains functions for interacting with a current sensor.
 */

#include "current_sensor.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../indexer/indexer.h"
#include "../space/space.h"
#include "../spectrum/spectrum.h"

/**
 * @brief Initializes a CurrentSensor struct with the given parameters.
 *
 * @param sensor A pointer to the CurrentSensor struct to initialize.
 * @param sample_size The size of each sample buffer.
 * @param amount_of_buffers The number of sample buffers.
 * @param i2c_address The I2C address of the current sensor.
 */
void initCurrentSensor(CurrentSensor *sensor,
                       short int sample_size,
                       short int amount_of_buffers,
                       short int i2c_address,
                       short int i2c_interface) {
    sensor->initialized = 0;
    sensor->address = -1;

    if (sample_size <= 10 || amount_of_buffers < 1 || i2c_address < 0) return;

    sensor->sample_size = sample_size;
    sensor->amount_of_buffers = amount_of_buffers;
    sensor->address = i2c_address;
    sensor->interface = i2c_interface;

    initIndexer(&sensor->indexer, sample_size, amount_of_buffers);
    initSpectrum(&sensor->spectrum, sample_size, amount_of_buffers);

    // init sensor buffer
    sensor->samples = (float *)malloc(sizeof(float) * amount_of_buffers * sample_size);
    sensor->indexer.sample_size = sample_size;

    // init sensor connection
    sensor->initialized = 1;
}

/**
 * @brief Checks if the given CurrentSensor is initialized.
 *
 * @param sensor A pointer to the CurrentSensor to check.
 *
 * @return 1 if the sensor is initialized, 0 otherwise.
 */
int isCurrentSensorInitialized(CurrentSensor *sensor) {
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

    return check_sum == CURRENT_SENSOR_INITIALIZATION_CHECK_SUM;
}

/**
 * @brief Samples the current signal from the given CurrentSensor.
 *
 * @param sensor The CurrentSensor to sample from.
 *
 * @return A Vector struct representing the sampled current signal.
 */
// TODO
float sampleCurrentSignal(CurrentSensor sensor) {
    return 0.0;
}

/**
 * @brief Adds a sample to the given CurrentSensor's sample buffer.
 *
 * @param sensor A pointer to the CurrentSensor to add the sample to.
 * @param sample The sample to add.
 *
 * @return 1 if the sample was added successfully, 0 otherwise.
 */
int addSampleCurrent(CurrentSensor *sensor, float sample) {
    int indexer = sensor->indexer.buffer * sensor->indexer.sample_size + sensor->indexer.sample;

    sensor->samples[indexer] = sample;

    updateCurrentSpectrum(sensor, sample);

    return incrementIndex(&sensor->indexer);
}

/**
 * @brief Gets the current intensity of the given sensor and beacon.
 *
 * @param sensor The current sensor to use.
 * @param beacon The beacon to measure the current intensity.
 *
 * @return The current signal strength.
 */
float getCurrentIntensity(CurrentSensor *sensor, Beacon *beacon) {
    return getSpectrumWindowIntensity(&sensor->spectrum, beacon->spectrum_window,
                                      &sensor->indexer);
}

/**
 * @brief Updates the spectrum of the given sensor with the provided sample.
 * @param sensor The current sensor to update the spectrum of.
 * @param sample The sample to use to update the spectrum.
 */
void updateCurrentSpectrum(CurrentSensor *sensor, const float sample) {
    Spectrum *spectrum = &sensor->spectrum;
    Indexer *indexer = &sensor->indexer;

    float complex phase;

    for (int i = 0; i < indexer->sample + 1; i++) {
        phase = phases[indexer->sample * indexer->sample_size + i];

        spectrum->samples[indexer->buffer * indexer->sample_size + i] +=
            spectrum->double_per_sample_size * (sample * (phase));
    }

    for (int i = 0; i < indexer->sample; i++) {
        phase = phases[indexer->sample * indexer->sample_size + i];

        spectrum->samples[indexer->buffer * indexer->sample_size + indexer->sample] +=
            spectrum->double_per_sample_size * (sensor->samples[indexer->buffer * indexer->sample_size + i] * (phase));
    }
}

/**
 * @brief Resets the cache of the previous filled cache.
 * @param sensor The current sensor to reset the cache of.
 */
void resetCurrentSampleCache(CurrentSensor *sensor) {
    Indexer *indexer = &sensor->indexer;

    const int previous_cache_index = (indexer->buffer + 1) %
                                     sensor->amount_of_buffers;

    for (int signal_index = indexer->buffer * sensor->sample_size;
         signal_index < (indexer->buffer + 1) * sensor->sample_size; signal_index++) {
        sensor->samples[signal_index] = 0.0;
    }
}
