/**
 * @file magnetic_sensor.h
 * @brief Contains the definition of the MagneticSensor struct and related functions.
 */

#ifndef MAGNETIC_SENSOR_H
#define MAGNETIC_SENSOR_H

#include "../beacon/beacon.h"
#include "../indexer/indexer.h"
#include "../space/space.h"
#include "../spectrum/spectrum.h"

#define MAGNETIC_SENSOR_INITIALIZATION_CHECK_SUM 6

/**
 * @brief A struct that represents a magnetic sensor.
 */
typedef struct MagneticSensor {
    int address; /**< The address of the sensor. */

    /**
     * @brief The position of the sensor inside the device.
     */
    Coordinate device_position;

    /**
     * @brief The position of the sensor in relation to the beacons.
     */
    Coordinate local_position;

    int amount_of_buffers; /**< The number of buffers. */
    int sample_size;       /**< The size of each sample. */
    float *samples;        /**< An array of samples. */

    Spectrum spectrum; /**< A spectrum object. */
    Indexer indexer;   /**< An indexer object. */

    int initialized; /**< Whether the sensor has been initialized or not. */

} MagneticSensor;

/**
 * @brief Initializes a magnetic sensor.
 *
 * @param sensor A pointer to the magnetic sensor to initialize.
 * @param sample_size The size of each sample.
 * @param amount_of_buffers The number of buffers.
 * @param i2c The I2C interface to use.
 */
void initMagneticSensor(MagneticSensor *sensor,
                        unsigned int sample_size,
                        unsigned int amount_of_buffers,
                        int i2c);

/**
 * @brief Checks if a magnetic sensor has been initialized.
 *
 * @param sensor A pointer to the magnetic sensor to check.
 *
 * @return 1 if the sensor has been initialized, 0 otherwise.
 */
int isMagneticSensorInitialized(MagneticSensor *sensor);

/**
 * @brief Samples the magnetic signal from a magnetic sensor.
 *
 * @param sensor The magnetic sensor to sample.
 *
 * @return A Vector representing the magnetic signal.
 */
Vector sampleMagneticSignal(MagneticSensor sensor);

/**
 * @brief Adds a sample to a magnetic sensor's sample buffer.
 *
 * @param sensor A pointer to the magnetic sensor to add the sample to.
 * @param magnetic_sample The magnetic sample to add.
 *
 * @return 1 if the sample was added successfully, 0 otherwise.
 */
int addSampleMagneticSignal(MagneticSensor *sensor, float magnetic_sample);

/**
 * @brief Updates the spectrum of a magnetic sensor.
 *
 * @param sensor A pointer to the magnetic sensor to update the spectrum of.
 * @param sample The sample to update the spectrum with.
 */
void updateSpectrum(MagneticSensor *sensor, const float sample);

/**
 * @brief Gets the magnetic signal strength of a magnetic sensor with respect to a beacon.
 *
 * @param sensor A pointer to the magnetic sensor.
 * @param beacon A pointer to the beacon.
 *
 * @return The magnetic signal strength.
 */
float getMagneticSignalStrength(MagneticSensor *sensor, Beacon *beacon);

/**
 * @brief Calculates the distance between a magnetic sensor and a beacon.
 *
 * @param sensor A pointer to the magnetic sensor.
 * @param beacon A pointer to the beacon.
 *
 * @return The distance between the sensor and the beacon.
 */
float calculateDistanceFromBeacon(MagneticSensor *sensor, Beacon *beacon);

/**
 * @brief Resets a magnetic sensor's sample buffer.
 *
 * @param sensor A pointer to the magnetic sensor to reset.
 */
void resetSampleCache(MagneticSensor *sensor);

#endif
