/**
 * @file device.h
 * @brief Defines a device used for position estimation using magnetic fields.
 */

#ifndef DEVICE_H
#define DEVICE_H

#include "../beacon/beacon.h"
#include "../environment/environment.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../space/space.h"

/**
 * @brief The Device struct represents a device used for position estimation using magnetic fields.
 */
typedef struct
{
    Coordinate position; /**< The current position of the device. */
    Vector attitude;     /**< The current attitude of the device. */

    Baseline *baseline; /**< The baseline to use for position estimation. */

    MagneticSensor *magnetic_sensors; /**< An array of magnetic sensors. */
    int amount_of_magnetic_sensors;   /**< The number of magnetic sensors in the array. */

    int baseline_configured; /**< Flag indicating whether the baseline has been configured. */

    int check_prd; /**< Parity check of device ID. */
    int check_sum; /**< Parity check of baseline values. */

    int initialized; /**< Flag indicating whether the device has been initialized. */

} Device;

/**
 * @brief Initializes the given device with the given magnetic sensors.
 *
 * @param device The device to initialize.
 * @param magnetic_sensors An array of magnetic sensors.
 * @param amount_of_magnetic_sensors The number of magnetic sensors in the array.
 */
void initDevice(Device *device, MagneticSensor *magnetic_sensors, int amount_of_magnetic_sensors);

/**
 * @brief Sets the baseline for the given device.
 *
 * @param device The device to set the baseline for.
 * @param baseline The baseline to use for position estimation.
 */
void setBaseline(Device *Device, Baseline *baseline);

/**
 * @brief Returns whether the given device has been initialized.
 *
 * @param device The device to check.
 *
 * @return 1 if the device has been initialized, otherwise 0.
 */
int isDeviceInitialized(Device *device);

/**
 * @brief Updates the position, attitude and heading of the given device based on the given environment.
 *
 * @param device The device to update.
 * @param environment The environment to use for position estimation.
 */
void updateDevicePosition(Device *device, Environment *environment);

void updateDeviceAttitude(Device *device);

/**
 * @brief Calculates the coordinates of the given device based on the given environment and reference.
 *
 * @param device The device to get the coordinates of.
 * @param environment The environment to use for position estimation.
 * @param reference The reference to use for position estimation.
 */
void getCoordinates(Device *device, Environment *environment, int reference);

/**
 * @brief Estimates the position of the given device based on the given environment.
 *
 * @param device The device to estimate the position of.
 * @param environment The environment to use for position estimation.
 */
void estimateDevicePosition(Device *device, Environment *environment);

#endif
