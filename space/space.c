/**
 * @file space.c
 * @brief Implementation of functions for working with 3D coordinates and vectors
 *
 * @see space.h
 */

#include "space.h"

#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Sets the x, y, and z coordinates of a Coordinate struct
 *
 * @param point A pointer to the Coordinate struct to be set
 * @param x The x-coordinate to set
 * @param y The y-coordinate to set
 * @param z The z-coordinate to set
 */
void setCoordinate(Coordinate *point, float x, float y, float z) {
    point->x = x;
    point->y = y;
    point->z = z;
}

/**
 * @brief Sets the x, y, and z components of a Vector struct
 *
 * @param vector A pointer to the Vector struct to be set
 * @param x The x-component to set
 * @param y The y-component to set
 * @param z The z-component to set
 */
void setVector(Vector *vector, float x, float y, float z) {
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

/**
 * @brief Calculates the norm (magnitude) of a Vector struct
 *
 * @param vector The Vector struct to calculate the norm of
 * @return The magnitude of the vector
 */
float norm(Vector vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

/**
 * @brief Calculates the squared Euclidean distance between two Coordinate structs
 *
 * @param start A pointer to the starting Coordinate struct
 * @param end A pointer to the ending Coordinate struct
 * @return The squared Euclidean distance between start and end
 */
float euclideanDistance2(Coordinate *start, Coordinate *end) {
    float delta_x = start->x - end->x;
    float delta_y = start->y - end->y;
    float delta_z = start->z - end->z;

    return sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}

/**
 * @brief Adds two Coordinate structs together and stores the result in a third Coordinate struct
 *
 * @param point A pointer to the first Coordinate struct to be added
 * @param offset A pointer to the second Coordinate struct to be added
 * @param result A pointer to the Coordinate struct to store the result in
 */
void translate(Coordinate *point, Vector *offset, Coordinate *result) {
    result->x = point->x + offset->x;
    result->y = point->y + offset->y;
    result->z = point->z + offset->z;
}

void rotate2d(Coordinate *point, float angle, Coordinate *result) {
    // Convert the angle to radians
    angle = angle * M_PI / 180.0;

    // Calculate the sin and cosine values of the angle
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    // Rotate the point around the Z axis
    result->x = point->x * cosAngle - point->y * sinAngle;
    result->y = point->x * sinAngle + point->y * cosAngle;
    result->z = 0;
}

/**
 * @brief Calculates the position error between two Coordinate structs
 *
 * @param reference A pointer to the reference Coordinate struct
 * @param real A pointer to the real Coordinate struct
 * @return The position error between reference and real
 */
float calculatePositionError(Coordinate *reference, Coordinate *real) {
    Vector error;

    error.x = (reference->x - real->x);
    error.y = (reference->y - real->y);
    error.z = (reference->z - real->z);

    return norm(error);
}

float calculateError(float reference, float real) {
    return (reference - real) / reference;
}

/**
 * @brief Prints the x, y, and z coordinates of a Coordinate struct to stdout
 *
 * @param point A pointer to the Coordinate struct to be printed
 */
void printCoordinate(Coordinate *point) {
    printf("(%3.6f, %3.6f, %3.6f)\n", point->x, point->y, point->z);
}

/**
 * @brief Prints the x, y, and z coordinates of a Vector struct to stdout
 *
 * @param vector A pointer to the Coordinate struct to be printed
 */
void printVector(Vector *vector) {
    printf("(%3.6f, %3.6f, %3.6f)\n", vector->x, vector->y, vector->z);
}
