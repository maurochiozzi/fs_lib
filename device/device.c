#include "device.h"

#include <stdlib.h>

#include "../beacon/beacon.h"
#include "../environment/environment.h"
#include "../navigation/navigation.h"
#include "../space/space.h"

void initDevice(Device *device) {
    setCoordinate(&device->position, 0.0, 0.0, 0.0);
    setVector(&device->heading, 0.0, 0.0, 0.0);

    device->magnetic_sensors =
        (MagneticSensor *)malloc(sizeof(MagneticSensor) * device->amount_of_magnetic_sensors);

    device->initialized = 1;
}

int isDeviceReady(Device *device) {
    Coordinate *position = &device->position;
    Vector *heading = &device->heading;

    int check_sum_device_ready = 0;

    if (device->initialized) {
        check_sum_device_ready++;
    }

    if ((position->x == 0.0 &&
         position->y == 0.0 &&
         position->z == 0.0)) {
        check_sum_device_ready++;
    }

    if (heading->x == 0.0 &&
        heading->y == 0.0 &&
        heading->z == 0.0) {
        check_sum_device_ready++;
    }

    return check_sum_device_ready == TOTAL_INITIALIZATION_CHECK_SUM;
}

void updateDevicePosition(Device *device, Environment *environment) {
    const int amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;

    Coordinate *device_position = &device->position;
    Coordinate *sensor_position;

    estimateMagneticSensorPosition(device, environment);

    for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensors; sensor_index++) {
        sensor_position = &device->magnetic_sensors[sensor_index].local_position;

        device_position->x += sensor_position->x / amount_of_magnetic_sensors;
        device_position->y += sensor_position->y / amount_of_magnetic_sensors;
        device_position->z += sensor_position->z / amount_of_magnetic_sensors;
    }
}

void destroyDevice(Device *device) {
    free(device->magnetic_sensors);
}
