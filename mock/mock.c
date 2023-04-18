#include "mock.h"

#include <math.h>
#include <stdlib.h>

#include "../beacon/beacon.h"
#include "../device/device.h"
#include "../environment/environment.h"
#include "../magnetic_field/magnetic_field.h"
#include "../magnetic_sensor/magnetic_sensor.h"
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

void mockBeaconSurveyRun(
    Device *device,
    Environment *environment,
    Environment *mocked_environment,
    int sample_rate, int sample_size) {
    MagneticSensor *sensor;

    const int amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;
    double environment_magnetic_field_intensity;

    float delta_time = 1.0 / sample_rate;
    float timestamp = 0.0;

    for (int index = 0; index < 1 * sample_size; index++) {
        for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensors; sensor_index++) {
            sensor = &device->magnetic_sensors[sensor_index];

            environment_magnetic_field_intensity =
                mockEnvironmentMagneticField(mocked_environment, &sensor->device_position, timestamp);

            addSampleMagneticSignal(sensor, environment_magnetic_field_intensity);
        }

        timestamp += delta_time;
    }
}

void mockMagneticFieldSampleRun(
    Device *device, Vector device_velocity, float heading,
    Coordinate *final_device_position, Vector *device_position_offset,
    Environment *environment, int sample_rate, int sample_size) {
    MagneticSensor *sensor;
    Coordinate mocked_sensor_position = {0};

    const int amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;
    double environment_magnetic_field_intensity;

    float delta_time = 1.0 / sample_rate;
    float timestamp = 0.0;

    // Start sampling environment magnetic field
    for (int index = 0; index < 1 * sample_size; index++) {
        // update mocked device offset from its original position
        device_position_offset->x += device_velocity.x * delta_time;
        device_position_offset->y += device_velocity.y * delta_time;
        device_position_offset->z += device_velocity.z * delta_time;

        for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensors; sensor_index++) {
            sensor = &device->magnetic_sensors[sensor_index];

            mocked_sensor_position = sensor->device_position;

            rotate2d(&sensor->device_position, heading, &mocked_sensor_position);

            translate(&mocked_sensor_position, device_position_offset,
                      &mocked_sensor_position);

            environment_magnetic_field_intensity =
                mockEnvironmentMagneticField(
                    environment,
                    &mocked_sensor_position,
                    timestamp);

            addSampleMagneticSignal(sensor, environment_magnetic_field_intensity);
        }

        timestamp += delta_time;
    }

    // update mocked device final position
    final_device_position->x = device_position_offset->x;
    final_device_position->y = device_position_offset->y;
    final_device_position->z = device_position_offset->z;
}
