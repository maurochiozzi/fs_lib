/**
 * @file current_sensor.h
 * @brief Contains the definition of the CurrentSensor struct and related functions.
 */

#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

#include "../beacon/beacon.h"
#include "../indexer/indexer.h"
#include "../space/space.h"
#include "../spectrum/spectrum.h"

#define CURRENT_SENSOR_INITIALIZATION_CHECK_SUM 6

typedef struct CurrentSensorCharacteristic {
    FloatRange range;
    float resolution;
    float noise_amplitude;

} CurrentSensorCharacteristic;

/**
 * @brief A struct that represents a current sensor.
 */
typedef struct CurrentSensor {
    short int address; /**< The address of the sensor. */
    short int interface;

    short int amount_of_buffers; /**< The number of buffers. */
    short int sample_size;       /**< The size of each sample. */
    float *samples;              /**< An array of samples. */

    Spectrum spectrum; /**< A spectrum object. */
    Indexer indexer;   /**< An indexer object. */

    // This is a optional information so it will not be inside the init
    CurrentSensorCharacteristic characteristic;

    short int initialized; /**< Whether the sensor has been initialized or not. */

} CurrentSensor;

/**
 * @brief Initializes a current sensor.
 *
 * @param sensor A pointer to the current sensor to initialize.
 * @param sample_size The size of each sample.
 * @param amount_of_buffers The number of buffers.
 * @param i2c The I2C interface to use.
 */
void initCurrentSensor(CurrentSensor *sensor,
                       short int sample_size,
                       short int amount_of_buffers,
                       short int i2c_address,
                       short int i2c_interface);

/**
 * @brief Checks if a current sensor has been initialized.
 *
 * @param sensor A pointer to the current sensor to check.
 *
 * @return 1 if the sensor has been initialized, 0 otherwise.
 */
int isCurrentSensorInitialized(CurrentSensor *sensor);

/**
 * @brief Samples the current  from a current sensor.
 *
 * @param sensor The current sensor to sample.
 *
 * @return A Vector representing the current .
 */
float sampleCurrent(CurrentSensor sensor);

/**
 * @brief Adds a sample to a current sensor's sample buffer.
 *
 * @param sensor A pointer to the current sensor to add the sample to.
 * @param current_sample The current sample to add.
 *
 * @return 1 if the sample was added successfully, 0 otherwise.
 */
int addSampleCurrent(CurrentSensor *sensor, float current_sample);

/**
 * @brief Updates the spectrum of a current sensor.
 *
 * @param sensor A pointer to the current sensor to update the spectrum of.
 * @param sample The sample to update the spectrum with.
 */
void updateCurrentSpectrum(CurrentSensor *sensor, const float sample);

/**
 * @brief Gets the current signal strength of a current sensor with respect to a beacon.
 *
 * @param sensor A pointer to the current sensor.
 * @param beacon A pointer to the beacon.
 *
 * @return The current signal strength.
 */
float getCurrentIntensity(CurrentSensor *sensor, Beacon *beacon);

/**
 * @brief Resets a current sensor's sample buffer.
 *
 * @param sensor A pointer to the current sensor to reset.
 */
void resetCurrentSampleCache(CurrentSensor *sensor);

#endif
