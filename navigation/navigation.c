/**
 * @file navigation.c
 * @brief Functions for estimating positions using trilateration
 */

#include "navigation.h"

#include <stdio.h>
#include <stdlib.h>

#include "../beacon/beacon.h"
#include "../device/device.h"
#include "../environment/environment.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../space/space.h"
#include "../spectrum/spectrum.h"

/**
 * @brief Estimates the position of the magnetic sensor on the device based on the detected magnetic fields.
 *
 * @param device Pointer to the device.
 * @param environment Pointer to the environment.
 */
void estimateMagneticSensorPosition(Device *device, Environment *environment) {
    const int amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;
    const int amount_of_beacons = environment->amount_of_beacons;

    Coordinate *device_position = &device->position;
    Coordinate *sensor_position;

    MagneticSensor *sensor;

    // Allocate memory for the segments matrix
    Segment *segments_matrix = (Segment *)malloc(sizeof(Segment) *
                                                 amount_of_magnetic_sensors *
                                                 amount_of_beacons);

    buildSegmentsMatrix(device, environment, segments_matrix, SENSOR);
    estimateMagneticSensorsPositions(device, environment, segments_matrix);

    for (int i = 0; i < device->amount_of_magnetic_sensors; i++) {
        sensor = &device->magnetic_sensors[i];

        // Clear the spectrum and indexer for the sensor
        clearPastSpectrum(&sensor->spectrum, &sensor->indexer);
    }

    // Free the segments matrix
    free(segments_matrix);

    // Indicate that the magnetic sensor position estimation is complete
    printf("Magnetic sensor position estimation complete.\n");
}

/**
 * @brief Estimates the position of the magnetic field source of the beacon based on the detected magnetic fields.
 *
 * @param device Pointer to the device.
 * @param environment Pointer to the environment.
 */
void estimateMagneticBeaconSourcePosition(Device *device, Environment *environment) {
    const int amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;
    const int amount_of_beacons = environment->amount_of_beacons;

    Coordinate *device_position = &device->position;
    Coordinate *sensor_position;

    MagneticSensor *sensor;

    // Allocate memory for the segments matrix
    Segment *segments_matrix = (Segment *)malloc(sizeof(Segment) *
                                                 amount_of_magnetic_sensors *
                                                 amount_of_beacons);

    buildSegmentsMatrix(device, environment, segments_matrix, BEACON);

    estimateBeaconsPositions(device, environment, segments_matrix);

    for (int i = 0; i < device->amount_of_magnetic_sensors; i++) {
        sensor = &device->magnetic_sensors[i];

        // Clear the spectrum and indexer for the sensor
        clearPastSpectrum(&sensor->spectrum, &sensor->indexer);
    }

    // Free the segments matrix
    free(segments_matrix);

    // Indicate that the magnetic beacon source position estimation is complete
    printf("Magnetic beacon source position estimation complete.\n");
}

/**
 * @brief Builds the matrix of magnetic field strength segments between each magnetic sensor and each beacon.
 *
 * @param device Pointer to the device.
 * @param environment Pointer to the environment.
 * @param segments_matrix Pointer to the segments matrix to be filled.
 * @param reference An integer to indicate whether the reference should be the beacon or the sensor.
 */
void buildSegmentsMatrix(Device *device, Environment *environment,
                         Segment *segments_matrix, int reference) {
    const int amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;
    const int amount_of_beacons = environment->amount_of_beacons;

    Segment *current_segment;
    Beacon *current_beacon;
    MagneticSensor *current_sensor;

    for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensors; sensor_index++) {
        current_sensor = &device->magnetic_sensors[sensor_index];

        for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
            int indexer = sensor_index * amount_of_beacons + beacon_index;

            current_beacon = &environment->beacons[beacon_index];

            current_segment =
                &segments_matrix[indexer];

            current_segment->magnitude = calculateDistanceFromBeacon(current_sensor, current_beacon);

            current_segment->reference =
                reference == BEACON ? current_sensor->device_position
                                    : current_beacon->magnetic_field_source.position;
        }
    }
}

/**
 * @brief Estimates the positions of magnetic sensors in the given device using trilateration.
 *
 * @param[in] device Pointer to the device containing magnetic sensors to be located
 * @param[in] environment Pointer to the environment containing beacons used for locating magnetic sensors
 * @param[in] segments_matrix Pointer to a matrix of magnetic sensor distances to the beacons
 */
void estimateMagneticSensorsPositions(Device *device, Environment *environment,
                                      Segment *segments_matrix) {
    const int amount_of_magnetic_sensor = device->amount_of_magnetic_sensors;
    const int amount_of_beacons = environment->amount_of_beacons;

    Segment *references;

    references = (Segment *)malloc(sizeof(Segment) * amount_of_beacons);

    for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index++) {
        for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
            int indexer = sensor_index * amount_of_beacons + beacon_index;

            references[beacon_index] = segments_matrix[indexer];
        }

        Coordinate *sensor_position = &device->magnetic_sensors[sensor_index].local_position;

        calculatePositionByTrilateration(references, sensor_position, amount_of_beacons);
    }

    free(references);
}

/**
 * @brief Estimates the positions of beacons in the given environment using trilateration.
 *
 * @param[in] device Pointer to the device containing magnetic sensors used for locating beacons
 * @param[in] environment Pointer to the environment containing beacons to be located
 * @param[in] segments_matrix Pointer to a matrix of magnetic sensor distances to the beacons
 */
void estimateBeaconsPositions(Device *device, Environment *environment,
                              Segment *segments_matrix) {
    const int amount_of_magnetic_sensor = device->amount_of_magnetic_sensors;
    const int amount_of_beacons = environment->amount_of_beacons;

    Segment *references;

    references = (Segment *)malloc(sizeof(Segment) * amount_of_magnetic_sensor);

    for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
        for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index++) {
            int indexer = sensor_index * amount_of_beacons + beacon_index;

            references[sensor_index] = segments_matrix[indexer];
        }

        Coordinate *source_position = &environment->beacons[beacon_index].magnetic_field_source.position;

        calculatePositionByTrilateration(references, source_position, amount_of_magnetic_sensor);
    }

    free(references);
}

/**
 * @brief Calculates the position of a point using trilateration.
 *
 * For further reference: https://www.101computing.net/cell-phone-trilateration-algorithm/
 *
 * @param[in] segments Array of segments representing the distance from a point to several reference points
 * @param[out] position Pointer to the calculated position
 * @param[in] available_references Number of available reference points (should be >= 3)
 */
void calculatePositionByTrilateration(Segment *segments,
                                      Coordinate *position,
                                      int available_references) {
    if (available_references >= 3) {
        float A;
        float B;
        float C;
        float D;
        float E;
        float F;

        A = 2 * segments[1].reference.x - 2 * segments[0].reference.x;
        B = 2 * segments[1].reference.y - 2 * segments[0].reference.y;

        C = segments[0].magnitude * segments[0].magnitude - segments[1].magnitude * segments[1].magnitude -
            segments[0].reference.x * segments[0].reference.x + segments[1].reference.x * segments[1].reference.x -
            segments[0].reference.y * segments[0].reference.y + segments[1].reference.y * segments[1].reference.y;

        D = 2 * segments[2].reference.x - 2 * segments[1].reference.x;
        E = 2 * segments[2].reference.y - 2 * segments[1].reference.y;

        F = segments[1].magnitude * segments[1].magnitude - segments[2].magnitude * segments[2].magnitude -
            segments[1].reference.x * segments[1].reference.x + segments[2].reference.x * segments[2].reference.x -
            segments[1].reference.y * segments[1].reference.y + segments[2].reference.y * segments[2].reference.y;

        position->x = (C * E - F * B) / (E * A - B * D);
        position->y = (C * D - A * F) / (B * D - A * E);
        position->z = 0;
    }
}
