/**
 * @file Beacon.c
 * @brief Implements the Beacon struct and functions for working with beacons.
 *
 * @see beacon.h
 */

#include "beacon.h"

#include <stdio.h>
#include <stdlib.h>

#include "../space/space.h"

/**
 * @brief Initializes a Beacon object with the provided parameters.
 *
 * @param beacon A pointer to the Beacon object to be initialized.
 * @param magnetic_moment_rms The magnetic moment RMS value of the Beacon.
 * @param frequency The frequency of the Beacon's magnetic field.
 * @param sample_rate The sample rate of the Beacon's magnetic field.
 * @param sample_size The sample size of the Beacon's magnetic field.
 *
 * This function initializes the Beacon object with the provided parameters,
 * and calculates the check sum and product used to verify the Beacon's initialization.
 */
void initBeacon(Beacon *beacon,
                float magnetic_moment_rms, float frequency,
                int sample_rate, int sample_size) {
    beacon->initialized = 0;

    // Return early if sample_rate or sample_size are invalid
    if (sample_rate <= 0 || sample_size <= 0) return;

    beacon->check_sum = 0;
    beacon->check_prd = 1;

    // Initialize the magnetic field source with the given parameters
    initMagneticFieldSource(&beacon->magnetic_field_source, magnetic_moment_rms, frequency);

    // Calculate the spectrum window based on the magnetic field source frequency and the given sample rate and size
    beacon->spectrum_window = (TRUNCATION * beacon->magnetic_field_source.frequency / (sample_rate / (float)sample_size)) / TRUNCATION;

    // Set the survey status to 0 (undiscovered)
    beacon->survey_status = 0;

    // Set the initialized flag to 1
    beacon->initialized = 1;

    // Calculate the check sum and product based on the initialized values
    beacon->check_sum += beacon->initialized;
    beacon->check_sum += beacon->spectrum_window;
    beacon->check_sum += beacon->magnetic_field_source.frequency;

    beacon->check_prd *= beacon->initialized;
    beacon->check_prd *= beacon->spectrum_window;
    beacon->check_prd *= beacon->magnetic_field_source.frequency;
}

/**
 * @brief Checks if a Beacon object has been properly initialized.
 *
 * @param beacon A pointer to the Beacon object to be checked.
 *
 * @return Returns 1 if the Beacon is properly initialized, 0 otherwise.
 *
 * This function checks if a Beacon object has been properly initialized by comparing
 * the calculated check sum and product to the stored values.
 */
int isBeaconInitialized(Beacon *beacon) {
    // Return 0 if the beacon is NULL or not initialized
    if (beacon && beacon->initialized == 0) return 0;

    // Calculate the check sum and product based on the current values
    float check_sum = 0;
    float check_prd = 1;

    check_sum += beacon->initialized;
    check_sum += beacon->spectrum_window;
    check_sum += beacon->magnetic_field_source.frequency;

    check_prd *= beacon->initialized;
    check_prd *= beacon->spectrum_window;
    check_prd *= beacon->magnetic_field_source.frequency;

    // Return true if the calculated check sum and product match the stored values
    return check_sum == beacon->check_sum && check_prd == beacon->check_prd;
}