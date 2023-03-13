#include "device.h"

#include <stdio.h>
#include <stdlib.h>

#include "../beacon/beacon.h"
#include "../environment/environment.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../navigation/navigation.h"
#include "../space/space.h"

void initDevice(Device *device, MagneticSensor *magnetic_sensors, int amount_of_magnetic_sensors) {
    if (amount_of_magnetic_sensors < 1) return;

    setCoordinate(&device->position, 0.0, 0.0, 0.0);
    setVector(&device->heading, 0.0, 0.0, 0.0);

    device->amount_of_magnetic_sensors = amount_of_magnetic_sensors;

    device->magnetic_sensors = magnetic_sensors;
    device->configured = 0;
    device->ready = 0;

    device->initialized = 1;
}

int isDeviceInitialized(Device *device) {
    Coordinate *position = &device->position;
    Vector *heading = &device->heading;

    int check_sum = 0;

    if (device->initialized == 1) {
        check_sum++;
    }

    if (device->amount_of_magnetic_sensors > 0) {
        check_sum++;
    }

    if ((position->x == 0.0 &&
         position->y == 0.0 &&
         position->z == 0.0)) {
        check_sum++;
    }

    if (heading->x == 0.0 &&
        heading->y == 0.0 &&
        heading->z == 0.0) {
        check_sum++;
    }

    return check_sum == DEVICE_INITIALIZATION_CHECK_SUM;
}

int isDeviceReady(Device *device) {
    int check_sum = 0;

    check_sum += isDeviceInitialized(device);

    // Check if all magnetic sensors are correctly initialized
    for (int index = 1; index < device->amount_of_magnetic_sensors; index++) {
        if (isMagneticSensorInitialized(&device->magnetic_sensors[index]) == 0) {
            // If at least one sensor is wrongly initialized, device is not ready

            return 0;
        }
    }

    // If all sensors are correctly configured, check the flag as true
    device->configured = 1;
    check_sum++;

    if (check_sum == DEVICE_READY_CHECK_SUM) device->ready = 1;

    // return check_sum verification instead of ready status. If device is
    // not properly initialized, it's not possible to know the value of 'ready'
    return check_sum == DEVICE_READY_CHECK_SUM;
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
