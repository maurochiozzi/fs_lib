/**
 * @file beacon.h
 *
 * @brief Header file for the Beacon struct and associated functions.
 */

#ifndef BEACON_H
#define BEACON_H

#ifndef TRUNCATION
#define TRUNCATION 1000.0
#endif

#include <stdint.h>

#include "../magnetic_field/magnetic_field.h"
#include "../space/space.h"

/**
 * @brief Check sum used to verify that a Beacon has been properly initialized.
 */
#define BEACON_INITIALIZATION_CHECK_SUM 3

/**
 * @brief Struct representing a beacon.
 */
typedef struct Beacon {
    /**
     * @brief Source of the magnetic field emitted by the beacon.
     */
    MagneticFieldSource magnetic_field_source;

    /**
     * @brief Size of the spectrum window used to analyze the magnetic field.
     */
    int8_t spectrum_window;

    /**
     * @brief Level of precision required for detecting the beacon.
     */
    // TODO what is this?
    // float precision;

    /**
     * @brief Status of the beacon survey: 0 for undiscovered, 1 for discovered.
     */
    int8_t survey_status;

    /**
     * @brief Checksum period used to verify that a Beacon has been properly initialized.
     */
    int8_t check_prd;

    /**
     * @brief Checksum value used to verify that a Beacon has been properly initialized.
     */
    int8_t check_sum;

    /**
     * @brief Flag indicating whether the Beacon has been properly initialized.
     */
    int8_t initialized;
} Beacon;

/**
 * @brief Initializes a Beacon with the given parameters.
 *
 * @param beacon pointer to the Beacon struct to be initialized.
 * @param magnetic_moment_rms RMS value of the magnetic moment.
 * @param frequency Frequency of the magnetic field.
 * @param sample_rate Sampling rate of the magnetic field.
 * @param sample_size Number of samples to be taken.
 */
void initBeacon(Beacon *beacon, float magnetic_moment_rms, float frequency,
                int32_t sample_rate, int32_t sample_size);

/**
 * @brief Checks whether a Beacon has been properly initialized.
 *
 * @param beacon pointer to the Beacon struct to be checked.
 *
 * @return 1 if the Beacon has been properly initialized, 0 otherwise.
 */
int32_t isBeaconInitialized(Beacon *beacon);

#endif