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

void getCoordinates(Device *device, Beacon *beacons,
                    const int amount_of_beacons, int reference) {
    const int amount_of_magnetic_sensor = device->amount_of_sensors;

    Segment *segments = (Segment *)malloc(sizeof(Segment) *
                                          amount_of_magnetic_sensor * amount_of_beacons);
    Segment *references;
    Segment *current_segment;
    Beacon *current_beacon;
    MagneticSensor *current_sensor;

    // Build the matrix of distances [s x b]
    for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index++) {
        current_sensor = &device->sensors[sensor_index];

        for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
            current_beacon = &beacons[beacon_index];

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

            beacons[beacon_index].position =
                getSpacePosition(references, amount_of_magnetic_sensor);
        }

    } else {
        references = (Segment *)malloc(sizeof(Segment) * amount_of_beacons);

        for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index++) {
            int base_index = sensor_index * amount_of_beacons;

            for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index) {
                references[beacon_index] = segments[beacon_index * base_index];
            }

            device->sensors[sensor_index].local_position =
                getSpacePosition(references, amount_of_beacons);
        }
    }

    free(references);
    free(segments);
}

Coordinate getDevicePosition(Device *device) {
    Coordinate position;

    for (int index = 0; index < available_points; index++) {
        position.x += coordinates[index].x / available_points;
        position.y += coordinates[index].y / available_points;
        position.z += coordinates[index].z / available_points;
    }

    return position;
}
