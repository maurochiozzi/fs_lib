/**
 * @file navigation.h
 * @brief Navigation module header file.
 *
 * This header file provides function prototypes for the navigation module. The navigation module is responsible for
 * estimating device position using magnetic sensors and beacons.
 */

#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <stdint.h>

#include "../device/device.h"
#include "../environment/environment.h"
#include "../space/space.h"

/**
 * @brief Enumeration to define the reference type used for estimating device position.
 *
 */
enum Reference {
    BEACON, /**< Use beacons as reference. */
    SENSOR  /**< Use magnetic sensors as reference. */
};

/**
 * @brief Builds the segments matrix used for estimating device position using magnetic sensors or beacons.
 *
 * @param device pointer to the device struct.
 * @param environment pointer to the environment struct.
 * @param segments_matrix pointer to the segments matrix to be built.
 * @param reference Reference type to be used for estimating device position.
 */
void buildSegmentsMatrix(Device *device, Environment *environment,
                         Segment *segments_matrix, int32_t reference);

/**
 * @brief Estimates the position of a magnetic sensor in relation to the device position and heading.
 *
 * @param device pointer to the device struct.
 * @param environment pointer to the environment struct.
 */
void estimateMagneticSensorPosition(Device *device, Environment *environment);

/**
 * @brief Estimates the positions of all magnetic sensors in relation to the device position and heading.
 *
 * @param device pointer to the device struct.
 * @param environment pointer to the environment struct.
 * @param segments_matrix pointer to the segments matrix used for estimating device position.
 */
void estimateMagneticSensorsPositions(Device *device, Environment *environment,
                                      Segment *segments_matrix);

/**
 * @brief Estimates the position of the magnetic beacon source in relation to the device position and heading.
 *
 * @param device pointer to the device struct.
 * @param environment pointer to the environment struct.
 */
void estimateMagneticBeaconSourcePosition(Device *device, Environment *environment);

/**
 * @brief Estimates the positions of all beacons in relation to the device position and heading.
 *
 * @param device pointer to the device struct.
 * @param environment pointer to the environment struct.
 * @param segments_matrix pointer to the segments matrix used for estimating device position.
 */
void estimateBeaconsPositions(Device *device, Environment *environment,
                              Segment *segments_matrix);

/**
 * @brief Calculates the device position by trilateration.
 *
 * @param segments pointer to the segments array used for trilateration.
 * @param position pointer to the position struct to be updated with the estimated device position.
 * @param available_references Number of available references used for estimating device position.
 */
void calculatePositionByTrilateration(Segment *segments, Coordinate *position,
                                      int32_t available_references);

#endif
