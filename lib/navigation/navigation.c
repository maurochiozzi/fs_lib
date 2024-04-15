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

    MagneticSensor *sensor;

    // Allocate memory for the segments matrix
    Segment *segments_matrix = (Segment *)malloc(sizeof(Segment) *
                                                 amount_of_magnetic_sensors *
                                                 amount_of_beacons);

    // Populate the segments matrix with the segments between the sensors and the beacons
    buildSegmentsMatrix(device, environment, segments_matrix, SENSOR);
    // Estimate the positions of the magnetic sensors based on the segments matrix
    estimateMagneticSensorsPositions(device, environment, segments_matrix);

    // Loop through all magnetic sensors and clear their past spectrum and indexer
    for (int i = 0; i < device->amount_of_magnetic_sensors; i++) {
        sensor = &device->magnetic_sensors[i];

        // Clear the spectrum and indexer for the sensor
        clearPastSpectrum(&sensor->spectrum, &sensor->indexer);
    }

    // Free the segments matrix
    free(segments_matrix);
}

/**
 * @brief Estimates the position of the magnetic field source of the beacon based on the detected magnetic fields.
 *
 * @param device Pointer to the device.
 * @param environment Pointer to the environment.
 *
 * Note: This function assumes that the magnetic sensor positions have already been estimated using estimateMagneticSensorPosition().
 */
void estimateMagneticBeaconSourcePosition(Device *device, Environment *environment) {
    const int amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;
    const int amount_of_beacons = environment->amount_of_beacons;

    MagneticSensor *sensor;

    // Allocate memory for the segments matrix
    Segment *segments_matrix = (Segment *)malloc(sizeof(Segment) *
                                                 amount_of_magnetic_sensors *
                                                 amount_of_beacons);

    // Build the segments matrix for the magnetic sensors and beacon sources
    buildSegmentsMatrix(device, environment, segments_matrix, BEACON);

    // Estimate the positions of the beacon sources based on the segments matrix
    estimateBeaconsPositions(device, environment, segments_matrix);

    // Clear the past spectrum and indexer for each magnetic sensor
    for (int i = 0; i < device->amount_of_magnetic_sensors; i++) {
        sensor = &device->magnetic_sensors[i];

        // Clear the spectrum and indexer for the sensor
        clearPastSpectrum(&sensor->spectrum, &sensor->indexer);
    }

    // Free the segments matrix memory
    free(segments_matrix);
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

    // Loop through each magnetic sensor
    for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensors; sensor_index++) {
        current_sensor = &device->magnetic_sensors[sensor_index];

        // Loop through each beacon
        for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
            int indexer = sensor_index * amount_of_beacons + beacon_index;

            current_beacon = &environment->beacons[beacon_index];

            current_segment = &segments_matrix[indexer];

            // Calculate the distance between the current sensor and current beacon,
            // and store it in the current segment
            current_segment->magnitude = calculateDistanceFromBeacon(current_sensor, current_beacon);

            // Set the reference point for the current segment
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

    // Allocate memory for the references array
    references = (Segment *)malloc(sizeof(Segment) * amount_of_beacons);

    // Loop through each magnetic sensor
    for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index++) {
        // Loop through each beacon
        for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
            int indexer = sensor_index * amount_of_beacons + beacon_index;

            // Copy the segment for the current sensor and beacon pair to the references array
            references[beacon_index] = segments_matrix[indexer];
        }

        // Get a pointer to the current sensor's position
        Coordinate *sensor_position = &device->magnetic_sensors[sensor_index].local_position;

        // Calculate the position of the current sensor using trilateration
        calculatePositionByTrilateration(references, sensor_position, amount_of_beacons);
    }

    // Free the references array
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

    // Allocate memory for the references matrix
    references = (Segment *)malloc(sizeof(Segment) * amount_of_magnetic_sensor);

    // For each beacon in the environment
    for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
        // For each magnetic sensor in the device
        for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index++) {
            // Calculate the index of the segment in the matrix
            int indexer = sensor_index * amount_of_beacons + beacon_index;

            // Copy the segment to the references matrix
            references[sensor_index] = segments_matrix[indexer];
        }

        // Get a pointer to the position of the magnetic field source of the beacon
        Coordinate *source_position = &environment->beacons[beacon_index].magnetic_field_source.position;

        // Estimate the position of the magnetic field source using trilateration
        calculatePositionByTrilateration(references, source_position, amount_of_magnetic_sensor);
    }

    // Free the references matrix
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
    // Check if at least three references are available for trilateration
    if (available_references >= 3) {
        float A;
        float B;
        float C;
        float D;
        float E;
        float F;

        // Set up equations to be solved using matrix algebra
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

        // Solve matrix equations to calculate x and y coordinates
        position->x = (C * E - F * B) / (E * A - B * D);
        position->y = (C * D - A * F) / (B * D - A * E);
        position->z = 0;  // Assume z-coordinate is 0 for now
    }
}
