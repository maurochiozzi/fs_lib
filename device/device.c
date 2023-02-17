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

void getCoordinates(Beacon *beacons, MagneticSensor *sensors,
                    const int amount_of_beacons,
                    const int amount_of_magnetic_sensor,
                    int reference, Coordinate *coordinates) {
    Segment *segments = (Segment *)malloc(sizeof(Segment) *
                                          amount_of_magnetic_sensor *
                                          amount_of_beacons);
    Segment *current_segment;
    Beacon *current_beacon;
    MagneticSensor *current_sensor;

    // Build the matrix o distances [s x b]
    for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index++) {
        for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
            current_beacon = &beacons[beacon_index];
            current_sensor = &sensors[sensor_index];
            current_segment = &segments[sensor_index * amount_of_magnetic_sensor + beacon_index];

            current_segment->magnitude = getDistanceFromSensor(*current_sensor, *current_beacon);

            current_segment->reference = reference == BEACON ? current_beacon->position
                                                             : current_sensor->device_position;
        }
    }

    if (reference == BEACON) {
        for (int beacon_index = 0; beacon_index < 3; beacon_index++) {
            int base_index = beacon_index * 3;

            Segment references[] = {segments[base_index + 0],
                                    segments[base_index + 1],
                                    segments[base_index + 2]};

            coordinates[beacon_index] = getSpacePosition(references, 3);
        }
    } else {
        for (int beacon_index = 0; beacon_index < 3; beacon_index++) {
            int base_index = beacon_index;

            Segment references[] = {segments[base_index + 0],
                                    segments[base_index + 3],
                                    segments[base_index + 6]};

            coordinates[beacon_index] = getSpacePosition(references, 3);
        }
    }

    free(segments);
}

Coordinate getDevicePosition(Coordinate *coordinates, int available_points) {
    Coordinate position;

    for (int index = 0; index < available_points; index++) {
        position.x += coordinates[index].x / available_points;
        position.y += coordinates[index].y / available_points;
        position.z += coordinates[index].z / available_points;
    }

    return position;
}
