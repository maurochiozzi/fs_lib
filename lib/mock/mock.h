#ifndef MOCK_H
#define MOCK_H

#include <stdint.h>

#include "../device/device.h"
#include "../environment/environment.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../space/space.h"

float mockMagneticSourceint32_tensityFromSource(
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
    Environment *environment, Coordinate *reference,
    MagneticSensorCharacteristic *sensor_characteristic,
    float timestamp, int32_t with_error);

float mockMagneticSourceint32_tensityFromSourceWithErrors(
    MagneticFieldSource *source, Coordinate *reference,
    MagneticSensorCharacteristic *sensor_characteristic, float timestamp);

void mockBeaconSurveyRun(
    Device *device,
    Environment *environment,
    Environment *mocked_environment,
    int32_t sample_rate, int32_t sample_size, int32_t with_error);

void mockMagneticFieldSampleRun(
    Device *device, Vector device_velocity, float heading,
    Coordinate *final_device_position, Vector *device_position_offset,
    Environment *environment, int32_t sample_rate, int32_t sample_size, int32_t with_error);

#endif