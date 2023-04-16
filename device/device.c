/**
 * @file device.c
 * @brief Implementation of the device API.
 */

#include "device.h"

#include <stdio.h>
#include <stdlib.h>

#include "../beacon/beacon.h"
#include "../environment/environment.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../navigation/navigation.h"
#include "../space/space.h"

/**
 * @brief Initializes the device.
 *
 * @param device Pointer to the device to be initialized.
 * @param magnetic_sensors Array of magnetic sensors to be added to the device.
 * @param amount_of_magnetic_sensors Number of magnetic sensors in the `magnetic_sensors` array.
 *
 * @return None.
 */
void initDevice(Device *device, MagneticSensor *magnetic_sensors, int amount_of_magnetic_sensors) {
    device->initialized = 0;

    if (amount_of_magnetic_sensors < 1) return;

    device->check_sum = 0;
    device->check_prd = 1;

    device->baseline_configured = 0;

    setCoordinate(&device->position, 0.0, 0.0, 0.0);
    setVector(&device->attitude, 0.0, 0.0, 0.0);

    device->amount_of_magnetic_sensors = amount_of_magnetic_sensors;
    device->magnetic_sensors = magnetic_sensors;

    device->initialized = 1;

    // Calculate check sum and product
    device->check_sum += device->initialized;
    device->check_sum += device->amount_of_magnetic_sensors;

    device->check_prd *= device->initialized;
    device->check_prd *= device->amount_of_magnetic_sensors;
}

/**
 * @brief Sets the baseline of the device.
 *
 * @param device Pointer to the device.
 * @param baseline Pointer to the baseline to be set.
 *
 * @return None.
 */
void setBaseline(Device *device, Baseline *baseline) {
    device->baseline = baseline;

    device->baseline_configured = 1;
}

/**
 * @brief Checks if the device is initialized.
 *
 * @param device Pointer to the device.
 *
 * @return 1 if the device is initialized, otherwise 0.
 */
int isDeviceInitialized(Device *device) {
    if (device->initialized == 0) return 0;

    float check_sum = 0;
    float check_prd = 1;

    check_sum += device->initialized;
    check_sum += device->amount_of_magnetic_sensors;

    check_prd *= device->initialized;
    check_prd *= device->amount_of_magnetic_sensors;

    if (!(check_sum == device->check_sum && check_prd == device->check_prd)) return 0;

    // Check if all magnetic sensors are correctly initialized
    for (int index = 0; index < device->amount_of_magnetic_sensors; index++) {
        if (isMagneticSensorInitialized(&device->magnetic_sensors[index]) == 0) {
            // If at least one sensor is wrongly initialized, device is not ready

            return 0;
        }
    }

    return 1;
}

/**
 * @brief Updates the device's position.
 *
 * @param device Pointer to the device.
 * @param environment Pointer to the environment.
 *
 * @return None.
 */
void updateDevicePosition(Device *device, Environment *environment) {
    const int amount_of_magnetic_sensors = device->amount_of_magnetic_sensors;

    Coordinate *device_position = &device->position;
    Coordinate *sensor_position;

    estimateMagneticSensorPosition(device, environment);

    device_position->x = 0;
    device_position->y = 0;
    device_position->z = 0;

    for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensors; sensor_index++) {
        sensor_position = &device->magnetic_sensors[sensor_index].local_position;

        device_position->x += sensor_position->x / amount_of_magnetic_sensors;
        device_position->y += sensor_position->y / amount_of_magnetic_sensors;
        device_position->z += sensor_position->z / amount_of_magnetic_sensors;
    }

    // Update device attitude if the baseline is configured
    if (device->baseline_configured == 1) {
        updateDeviceAttitude(device);
    }
}

void updateDeviceAttitude(Device *device) {
    Baseline *baseline = device->baseline;
    Vector attitude = device->attitude;
    double attitude_norm;

    attitude.x = baseline->ending_point.x - baseline->initial_point.x;
    attitude.y = baseline->ending_point.y - baseline->initial_point.y;
    attitude.z = 0;  // 2 d plane first

    attitude_norm = norm(attitude);

    attitude.x /= attitude_norm;
    attitude.y /= attitude_norm;
}

/**
 * @brief Frees the memory allocated for a device's magnetic sensors.
 *
 * This function deallocates the memory that was allocated for a device's magnetic sensors.
 * It takes a pointer to a `Device` struct that represents the device whose magnetic sensors
 * are being destroyed. The function frees the memory that was allocated for the `magnetic_sensors`
 * array within the `Device` struct.
 *
 * @param device A pointer to a `Device` struct representing the device whose magnetic sensors
 *               are being destroyed.
 */
void destroyDevice(Device *device) {
    free(device->magnetic_sensors);
}
