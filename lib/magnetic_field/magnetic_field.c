/**
 * @file magnetic_field.c
 * @brief Implementation file for the MagneticFieldSource struct and related functions.
 */

#include "magnetic_field.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../environment/environment.h"
#include "../space/space.h"
#include "math.h"

#ifndef M_QUARTER_PI
#define M_QUARTER_PI 0.0795774715459
#endif

/**
 * @brief Initializes a MagneticFieldSource object.
 *
 * @param source A pointer to the MagneticFieldSource object to be initialized.
 * @param magnetic_moment_rms The RMS magnetic moment of the source.
 * @param frequency The frequency of the magnetic field.
 */
void initMagneticFieldSource(MagneticFieldSource *source, float magnetic_moment_rms, float frequency) {
    source->initialized = 0;

    source->check_sum = 0;
    source->check_prd = 1;

    if (magnetic_moment_rms <= 0 || frequency < 0) return;

    source->magnetic_moment_rms = magnetic_moment_rms;
    source->frequency = frequency;

    source->initialized = 1;

    // Calculate check sum and product
    source->check_sum += source->initialized;
    source->check_sum += source->magnetic_moment_rms;
    source->check_sum += source->frequency;

    source->check_prd *= source->initialized;
    source->check_prd *= source->magnetic_moment_rms;
    source->check_prd *= source->frequency;
}

/**
 * @brief Checks whether a MagneticFieldSource object has been initialized properly.
 *
 * @param source A pointer to the MagneticFieldSource object to be checked.
 *
 * @return 1 if the object has been initialized correctly, 0 otherwise.
 */
int32_t isMagneticFieldSourceInitialized(MagneticFieldSource *source) {
    float check_sum = 0;
    float check_prd = 1;

    check_sum += source->initialized;
    check_sum += source->magnetic_moment_rms;
    check_sum += source->frequency;

    check_prd *= source->initialized;
    check_prd *= source->magnetic_moment_rms;
    check_prd *= source->frequency;

    return check_sum == source->check_sum && check_prd > 0 && check_prd == source->check_prd;
}

/**
 * @brief Calculates the magnetic field int32_tensity at a given reference point.
 *
 * @param source A pointer to the MagneticFieldSource object representing the magnetic field source.
 * @param reference A pointer to the Coordinate object representing the reference point.
 *
 * @return The magnetic field int32_tensity at the reference point.
 */
float getMagneticint32_tensityFromSource(MagneticFieldSource *source, Coordinate *reference) {
    float distance = euclideanDistance2(&source->position, reference);

    float int32_tensity = M_QUARTER_PI * source->magnetic_moment_rms / (distance * distance * distance) * 10000;

    return int32_tensity;
}

/**
 * @brief Calculates the distance from the magnetic field source required to generate a specified int32_tensity.
 *
 * @param source A pointer to the MagneticFieldSource object representing the magnetic field source.
 * @param int32_tensity The specified int32_tensity.
 *
 * @return The distance from the source required to generate the specified int32_tensity.
 */
float getMagneticSourceDistanceByint32_tensity(MagneticFieldSource *source, float int32_tensity) {
    float distance = cbrt(M_QUARTER_PI * source->magnetic_moment_rms / int32_tensity * 10000);

    return distance;
}
