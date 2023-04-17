#include "mock.h"

#include <math.h>

#include "../beacon/beacon.h"
#include "../environment/environment.h"
#include "../magnetic_field/magnetic_field.h"
#include "../space/space.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Calculates the intensity of the magnetic field from a single magnetic field source.
 *
 * @param source The magnetic field source.
 * @param reference The reference coordinate.
 * @param timestamp The timestamp.
 * @return The intensity of the magnetic field.
 */
float mockMagneticSourceIntensityFromSource(MagneticFieldSource *source, Coordinate *reference, float timestamp) {
    float intensity = getMagneticIntensityFromSource(source, reference);

    return intensity * cos(2 * M_PI * source->frequency * timestamp);
}

/**
 * @brief Calculates the total magnetic field intensity at a given reference coordinate and timestamp.
 *
 * @param environment The environment containing magnetic field sources.
 * @param reference The reference coordinate.
 * @param timestamp The timestamp.
 * @return The total magnetic field intensity.
 */
float mockEnvironmentMagneticField(Environment *environment, Coordinate *reference, float timestamp) {
    float environment_magnetic_field_intensity = 0;

    Beacon *beacons = environment->beacons;

    for (int beacon_index = 0; beacon_index < environment->amount_of_beacons; beacon_index++) {
        environment_magnetic_field_intensity += mockMagneticSourceIntensityFromSource(
            &beacons[beacon_index].magnetic_field_source, reference, timestamp);
    }

    return environment_magnetic_field_intensity;
}