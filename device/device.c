#include "device.h"

#include <stdlib.h>

#include "../beacon/beacon.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../space/space.h"
#include "../trilateration/trilateration.h"

void initDevice(Device *device) {
    setCoordinate(&device->position, 0.0, 0.0, 0.0);
    setVector(&device->heading, 0.0, 0.0, 0.0);
}

void updatePosition(Device *device, Coordinate position, Vector heading) {
    device->position = position;
    device->heading = heading;
}

void getCoordinates(Device *device, Environment *environment, int reference) {
    const int amount_of_magnetic_sensor = device->amount_of_magnetic_sensors;
    const int amount_of_beacons = environment->amount_of_beacons;

    Segment *segments = (Segment *)malloc(sizeof(Segment) *
                                          amount_of_magnetic_sensor * amount_of_beacons);
    Segment *references;
    Segment *current_segment;
    Beacon *current_beacon;
    MagneticSensor *current_sensor;

    // Build the matrix of distances [s x b]
    for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index++) {
        current_sensor = &device->magnetic_sensors[sensor_index];

        for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
            current_beacon = &environment->beacons[beacon_index];

            current_segment = &segments[sensor_index * amount_of_magnetic_sensor + beacon_index];

            current_segment->magnitude = getDistanceFromSensor(*current_sensor, *current_beacon);

            current_segment->reference = reference == BEACON ? current_beacon->position
                                                             : current_sensor->device_position;
        }
    }

    if (reference == BEACON) {
        references = (Segment *)malloc(sizeof(Segment) * amount_of_magnetic_sensor);

        for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
            int base_index = amount_of_beacons + beacon_index;

            for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index) {
                references[sensor_index] = segments[sensor_index * base_index];
            }

            environment->beacons[beacon_index].position =
                getSpacePosition(references, amount_of_magnetic_sensor);
        }

    } else {
        references = (Segment *)malloc(sizeof(Segment) * amount_of_beacons);

        for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index++) {
            int base_index = sensor_index * amount_of_beacons;

            for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index) {
                references[beacon_index] = segments[beacon_index * base_index];
            }

            device->magnetic_sensors[sensor_index].local_position =
                getSpacePosition(references, amount_of_beacons);
        }
    }

    free(references);
    free(segments);
}

void estimateDevicePosition(Device *device, Environment *environment) {
    const int amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;

    Coordinate *device_position = &device->position;
    Coordinate *sensor_position;

    for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensors; sensor_index++) {
        sensor_position = &device->magnetic_sensors[sensor_index].local_position;

        device_position->x += sensor_position->x / amount_of_magnetic_sensors;
        device_position->y += sensor_position->y / amount_of_magnetic_sensors;
        device_position->z += sensor_position->z / amount_of_magnetic_sensors;
    }
}
