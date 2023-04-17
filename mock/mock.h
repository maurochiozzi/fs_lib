#ifndef MOCK_H
#define MOCK_H

#include "../device/device.h"
#include "../environment/environment.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../space/space.h"

float mockMagneticSourceIntensityFromSource(
    MagneticFieldSource *source,
    Coordinate *reference, float timestamp);

/**
 * @brief Mocks a magnetic field in an environment given a Coordinate reference
 * and a timestamp.
 *
 * @param environment The Environment to calculate the magnetic field for.
 * @param reference The Coordinate that will be used to calculate the magnetic field.
 * @param timestamp The timestamp that will be used to calculate the magnetic field.
 *
 * @return Returns the calculated magnetic field in the environment.
 */
float mockEnvironmentMagneticField(
    Environment *environment,
    Coordinate *reference, float timestamp);

void mockBeaconSurveyRun(
    Device *device,
    Environment *environment,
    Environment *mocked_environment,
    int sample_rate, int sample_size);

void mockMagneticFieldSampleRun(
    Device *device, Vector device_velocity, float heading,
    Environment *environment, Coordinate *mocked_device_position,
    int sample_rate, int sample_size);

#endif