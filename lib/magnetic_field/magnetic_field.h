/**
 * @file magnetic_field.h
 * @brief Header file for magnetic field related operations.
 */

#ifndef MAGNETIC_FIELD_H
#define MAGNETIC_FIELD_H

#include "../space/space.h"

/**
 * @struct MagneticFieldSource
 * @brief Represents a magnetic field source, including magnetic moment, frequency, position, and initialization status.
 */
typedef struct MagneticFieldSource {
    float magnetic_moment_rms;  ///< Root-mean-square value of the magnetic moment.
    float frequency;            ///< Frequency of the magnetic field source.
    Coordinate position;        ///< Position of the magnetic field source.
    float check_prd;            ///< Check period.
    float check_sum;            ///< Check sum.
    int initialized;            ///< Initialization status (0 for not initialized, 1 for initialized).
} MagneticFieldSource;

/**
 * @brief Initializes a magnetic field source with the given magnetic moment and frequency.
 * @param source Pointer to the MagneticFieldSource object to be initialized.
 * @param magnetic_moment_rms Root-mean-square value of the magnetic moment.
 * @param frequency Frequency of the magnetic field source.
 */
void initMagneticFieldSource(MagneticFieldSource *source, float magnetic_moment_rms, float frequency);

/**
 * @brief Determines whether the given magnetic field source is initialized.
 * @param source Pointer to the MagneticFieldSource object to be checked.
 * @return 1 if the source is initialized, 0 otherwise.
 */
int isMagneticFieldSourceInitialized(MagneticFieldSource *source);

/**
 * @brief Computes the magnetic field intensity at a given target point due to a magnetic field source.
 * @param source Pointer to the MagneticFieldSource object representing the magnetic field source.
 * @param target Pointer to the Coordinate object representing the target point.
 * @return The magnetic field intensity at the target point.
 */
float getMagneticIntensityFromSource(MagneticFieldSource *source, Coordinate *target);

/**
 * @brief Computes the distance between a magnetic field source and a target point, given the magnetic field intensity at the target point.
 * @param source Pointer to the MagneticFieldSource object representing the magnetic field source.
 * @param intensity The magnetic field intensity at the target point.
 * @return The distance between the source and the target point.
 */
float getMagneticSourceDistanceByIntensity(MagneticFieldSource *source, float intensity);

#endif
