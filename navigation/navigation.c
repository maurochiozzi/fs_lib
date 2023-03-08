#include "navigation.h"

#include <stdlib.h>

#include "../beacon/beacon.h"
#include "../device/device.h"
#include "../environment/environment.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../space/space.h"

void estimateMagneticSensorPosition(Device *device, Environment *environment) {
    const int amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;
    const int amount_of_beacons = environment->amount_of_beacons;

    Coordinate *device_position = &device->position;
    Coordinate *sensor_position;

    Segment *segments_matrix = (Segment *)malloc(sizeof(Segment) *
                                                 amount_of_magnetic_sensors *
                                                 amount_of_beacons);

    buildSegmentsMatrix(device, environment, segments_matrix, SENSOR);
    estimateMagneticSensorsPositions(device, environment, segments_matrix);

    free(segments_matrix);
}

void estimateMagneticBeaconSourcePosition(Device *device, Environment *environment) {
    const int amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;
    const int amount_of_beacons = environment->amount_of_beacons;

    Coordinate *device_position = &device->position;
    Coordinate *sensor_position;

    Segment *segments_matrix = (Segment *)malloc(sizeof(Segment) *
                                                 amount_of_magnetic_sensors *
                                                 amount_of_beacons);

    buildSegmentsMatrix(device, environment, segments_matrix, BEACON);
    estimateBeaconsPositions(device, environment, segments_matrix);

    free(segments_matrix);
}

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
            current_beacon = &environment->beacons[beacon_index];

            current_segment =
                &segments_matrix[sensor_index * amount_of_magnetic_sensors + beacon_index];

            current_segment->magnitude = calculateDistanceFromBeacon(*current_sensor, *current_beacon);

            current_segment->reference = reference == BEACON ? current_beacon->position
                                                             : current_sensor->device_position;
        }
    }
}

void estimateMagneticSensorsPositions(Device *device, Environment *environment,
                                      Segment *segments_matrix) {
    const int amount_of_magnetic_sensor = device->amount_of_magnetic_sensors;
    const int amount_of_beacons = environment->amount_of_beacons;

    Segment *references;

    references = (Segment *)malloc(sizeof(Segment) * amount_of_beacons);

    for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index++) {
        int base_index = sensor_index * amount_of_beacons;

        for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index) {
            references[beacon_index] = segments_matrix[beacon_index * base_index];
        }

        calculatePositionByTrilateration(
            references, amount_of_beacons,
            &device->magnetic_sensors[sensor_index].local_position);
    }

    free(references);
}

void estimateBeaconsPositions(Device *device, Environment *environment,
                              Segment *segments_matrix) {
    const int amount_of_magnetic_sensor = device->amount_of_magnetic_sensors;
    const int amount_of_beacons = environment->amount_of_beacons;

    Segment *references;

    references = (Segment *)malloc(sizeof(Segment) * amount_of_magnetic_sensor);

    for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
        int base_index = amount_of_beacons + beacon_index;

        for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index) {
            references[sensor_index] = segments_matrix[sensor_index * base_index];
        }

        calculatePositionByTrilateration(
            references, amount_of_magnetic_sensor,
            &environment->beacons[beacon_index].position);
    }

    free(references);
}

/**
 * For further reference: https://www.101computing.net/cell-phone-trilateration-algorithm/
 */

void calculatePositionByTrilateration(Segment *segments, int available_references,
                                      Coordinate *position) {
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
