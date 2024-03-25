/**
 * @file navigation.h
 * @brief Navigation module header file.
 *
 * This header file provides function prototypes for the navigation module. The navigation module is responsible for
 * estimating device position using magnetic sensors and beacons.
 */

#ifndef NAVIGATION_H
#define NAVIGATION_H

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
 * @param device Pointer to the device struct.
 * @param environment Pointer to the environment struct.
 * @param segments_matrix Pointer to the segments matrix to be built.
 * @param reference Reference type to be used for estimating device position.
 */
void buildSegmentsMatrix(Device *device, Environment *environment,
                         Segment *segments_matrix, int reference);

/**
 * @brief Estimates the position of a magnetic sensor in relation to the device position and heading.
 *
 * @param device Pointer to the device struct.
 * @param environment Pointer to the environment struct.
 */
void estimateMagneticSensorPosition(Device *device, Environment *environment);

/**
 * @brief Estimates the positions of all magnetic sensors in relation to the device position and heading.
 *
 * @param device Pointer to the device struct.
 * @param environment Pointer to the environment struct.
 * @param segments_matrix Pointer to the segments matrix used for estimating device position.
 */
void estimateMagneticSensorsPositions(Device *device, Environment *environment,
                                      Segment *segments_matrix);

/**
 * @brief Estimates the position of the magnetic beacon source in relation to the device position and heading.
 *
 * @param device Pointer to the device struct.
 * @param environment Pointer to the environment struct.
 */
void estimateMagneticBeaconSourcePosition(Device *device, Environment *environment);

/**
 * @brief Estimates the positions of all beacons in relation to the device position and heading.
 *
 * @param device Pointer to the device struct.
 * @param environment Pointer to the environment struct.
 * @param segments_matrix Pointer to the segments matrix used for estimating device position.
 */
void estimateBeaconsPositions(Device *device, Environment *environment,
                              Segment *segments_matrix);

/**
 * @brief Calculates the device position by trilateration.
 *
 * @param segments Pointer to the segments array used for trilateration.
 * @param position Pointer to the position struct to be updated with the estimated device position.
 * @param available_references Number of available references used for estimating device position.
 */
void calculatePositionByTrilateration(Segment *segments, Coordinate *position,
                                      int available_references);

#endif
