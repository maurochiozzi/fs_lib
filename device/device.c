#include "device.h"

#include <stdio.h>
#include <stdlib.h>

#include "../beacon/beacon.h"
#include "../environment/environment.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../navigation/navigation.h"
#include "../space/space.h"

void initDevice(Device *device, MagneticSensor *magnetic_sensors, int amount_of_magnetic_sensors) {
    device->initialized = 0;

    if (amount_of_magnetic_sensors < 1) return;

    device->baseline_configured = 0;

    setCoordinate(&device->position, 0.0, 0.0, 0.0);
    setVector(&device->heading, 0.0, 0.0, 0.0);

    device->amount_of_magnetic_sensors = amount_of_magnetic_sensors;
    device->magnetic_sensors = magnetic_sensors;

    device->initialized = 1;
}

void setBaseline(Device *device, Baseline *baseline) {
    device->baseline = baseline;

    device->baseline_configured = 1;
}

int isDeviceInitialized(Device *device) {
    if (device->initialized == 0) return 0;

    // Check if all magnetic sensors are correctly initialized
    for (int index = 0; index < device->amount_of_magnetic_sensors; index++) {
        if (isMagneticSensorInitialized(&device->magnetic_sensors[index]) == 0) {
            // If at least one sensor is wrongly initialized, device is not ready

            return 0;
        }
    }

    return device->amount_of_magnetic_sensors > 0 && device->initialized == 1;
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
