#include "mock.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "../beacon/beacon.h"
#include "../device/device.h"
#include "../environment/environment.h"
#include "../magnetic_field/magnetic_field.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../noise/noise.h"
#include "../space/space.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Calculates the int32_tensity of the magnetic field from a single magnetic field source.
 *
 * @param source The magnetic field source.
 * @param reference The reference coordinate.
 * @param timestamp The timestamp.
 * @return The int32_tensity of the magnetic field.
 */
float mockMagneticSourceint32_tensityFromSource(MagneticFieldSource *source, Coordinate *reference, float timestamp) {
    float int32_tensity = getMagneticint32_tensityFromSource(source, reference);

    return int32_tensity * cos(2 * M_PI * source->frequency * timestamp);
}

float mockMagneticSourceint32_tensityFromSourceWithErrors(
    MagneticFieldSource *source, Coordinate *reference,
    MagneticSensorCharacteristic *sensor_characteristic, float timestamp) {
    float upper_value = sensor_characteristic->range.upper;
    float int32_tensity;

    int32_tensity = mockMagneticSourceint32_tensityFromSource(source, reference, timestamp);

    // add error to it
    int32_tensity += unsigned_noise() * sensor_characteristic->noise_amplitude * sensor_characteristic->resolution;

    // check overflow
    if (int32_tensity > upper_value) {
        if (sensor_characteristic->overflow_mode == 0) {
            int32_tensity = upper_value;
        } else {
            float scale_factor = (int32_tensity / upper_value);

            int32_tensity = (scale_factor - (int32_t)scale_factor) * upper_value;
        }
    }

    // correct it with resolution
    int32_tensity = ((int32_t)(int32_tensity / sensor_characteristic->resolution)) * sensor_characteristic->resolution;

    return int32_tensity;
}

/**
 * @brief Calculates the total magnetic field int32_tensity at a given reference coordinate and timestamp.
 *
 * @param environment The environment containing magnetic field sources.
 * @param reference The reference coordinate.
 * @param timestamp The timestamp.
 * @return The total magnetic field int32_tensity.
 */
float mockEnvironmentMagneticField(Environment *environment, Coordinate *reference,
                                   MagneticSensorCharacteristic *sensor_characteristic,
                                   float timestamp, int32_t with_error) {
    float environment_magnetic_field_int32_tensity = 0;

    Beacon *beacons = environment->beacons;

    if (with_error == 0) {
        for (int32_t beacon_index = 0; beacon_index < environment->amount_of_beacons; beacon_index++) {
            environment_magnetic_field_int32_tensity += mockMagneticSourceint32_tensityFromSource(
                &beacons[beacon_index].magnetic_field_source, reference, timestamp);
        }
    } else {
        for (int32_t beacon_index = 0; beacon_index < environment->amount_of_beacons; beacon_index++) {
            environment_magnetic_field_int32_tensity += mockMagneticSourceint32_tensityFromSourceWithErrors(
                &beacons[beacon_index].magnetic_field_source, reference, sensor_characteristic, timestamp);
        }
    }

    return environment_magnetic_field_int32_tensity;
}

void mockBeaconSurveyRun(
    Device *device,
    Environment *environment,
    Environment *mocked_environment,
    int32_t sample_rate, int32_t sample_size, int32_t with_errors) {
    MagneticSensor *sensor;

    const int32_t amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;
    double environment_magnetic_field_int32_tensity;

    float delta_time = 1.0 / sample_rate;
    float timestamp = 0.0;

    for (int32_t index = 0; index < 1 * sample_size; index++) {
        for (int32_t sensor_index = 0; sensor_index < amount_of_magnetic_sensors; sensor_index++) {
            sensor = &device->magnetic_sensors[sensor_index];

            environment_magnetic_field_int32_tensity =
                mockEnvironmentMagneticField(mocked_environment, &sensor->device_position,
                                             &sensor->characteristic, timestamp, with_errors);

            addSampleMagneticSignal(sensor, environment_magnetic_field_int32_tensity);
        }

        timestamp += delta_time;
    }
}

void mockMagneticFieldSampleRun(
    Device *device, Vector device_velocity, float heading,
    Coordinate *final_device_position, Vector *device_position_offset,
    Environment *environment, int32_t sample_rate, int32_t sample_size, int32_t with_error) {
    MagneticSensor *sensor;
    Coordinate mocked_sensor_position = {0};

    const int32_t amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;
    double environment_magnetic_field_int32_tensity;

    float delta_time = 1.0 / sample_rate;
    float timestamp = 0.0;

    // Start sampling environment magnetic field
    for (int32_t index = 0; index < 1 * sample_size; index++) {
        // update mocked device offset from its original position
        device_position_offset->x += device_velocity.x * delta_time;
        device_position_offset->y += device_velocity.y * delta_time;
        device_position_offset->z += device_velocity.z * delta_time;

        for (int32_t sensor_index = 0; sensor_index < amount_of_magnetic_sensors; sensor_index++) {
            sensor = &device->magnetic_sensors[sensor_index];

            mocked_sensor_position = sensor->device_position;

            rotate2d(&sensor->device_position, heading, &mocked_sensor_position);

            translate(&mocked_sensor_position, device_position_offset,
                      &mocked_sensor_position);

            environment_magnetic_field_int32_tensity =
                mockEnvironmentMagneticField(
                    environment,
                    &mocked_sensor_position,
                    &sensor->characteristic,
                    timestamp, with_error);

            addSampleMagneticSignal(sensor, environment_magnetic_field_int32_tensity);
        }

        timestamp += delta_time;
    }

    // update mocked device final position
    final_device_position->x = device_position_offset->x;
    final_device_position->y = device_position_offset->y;
    final_device_position->z = device_position_offset->z;
}
