/**
 * @file space.h
 * @brief Defines data structures and functions related to spacial coordinates and vectors.
 */

#ifndef SPACE_H
#define SPACE_H

/**
 * @brief Represents a point in a 3D space.
 */
typedef struct Coordinate {
    float x; /**< The x-coordinate of the point. */
    float y; /**< The y-coordinate of the point. */
    float z; /**< The z-coordinate of the point. */
} Coordinate;

/**
 * @brief Represents a 3D vector.
 */
typedef struct Vector {
    float x; /**< The x-component of the vector. */
    float y; /**< The y-component of the vector. */
    float z; /**< The z-component of the vector. */
} Vector;

/**
 * @brief Represents a line segment in a 3D space.
 */
typedef struct Segment {
    Coordinate reference; /**< The starting point of the line segment. */
    float magnitude;      /**< The magnitude (length) of the line segment. */
} Segment;

/**
 * @brief Represents a line segment defined by its two endpoints.
 */
typedef struct Baseline {
    Coordinate initial_point; /**< The starting point of the line segment. */
    Coordinate ending_point;  /**< The ending point of the line segment. */
} Baseline;

/**
 * @brief Sets the coordinates of a point.
 *
 * @param point Pointer to the point whose coordinates are being set.
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @param z The z-coordinate of the point.
 */
void setCoordinate(Coordinate *point, float x, float y, float z);

/**
 * @brief Sets the components of a vector.
 *
 * @param vector Pointer to the vector whose components are being set.
 * @param x The x-component of the vector.
 * @param y The y-component of the vector.
 * @param z The z-component of the vector.
 */
void setVector(Vector *vector, float x, float y, float z);

/**
 * @brief Calculates the Euclidean norm of a vector.
 *
 * @param vector The vector whose norm is being calculated.
 *
 * @return The Euclidean norm of the vector.
 */
float norm(Vector vector);

/**
 * @brief Calculates the Euclidean distance between two points.
 *
 * @param start Pointer to the starting point.
 * @param end Pointer to the ending point.
 *
 * @return The Euclidean distance between the two points.
 */
float euclideanDistance2(Coordinate *start, Coordinate *end);

/**
 * @brief Calculates the result of adding an offset to a point.
 *
 * @param point Pointer to the point being offset.
 * @param offset Pointer to the offset to be added to the point.
 * @param result Pointer to the result of the addition.
 */
void translate(Coordinate *point, Coordinate *offset, Coordinate *result);
void rotate2d(Coordinate *point, float angle);

/**
 * @brief Calculates the position error between a reference point and a real point.
 *
 * @param reference Pointer to the reference point.
 * @param real Pointer to the real point.
 *
 * @return The position error between the two points.
 */
float calculatePositionError(Coordinate *reference, Coordinate *real);

/**
 * @brief Prints the coordinates of a point to the console.
 *
 * @param point Pointer to the point being printed.
 */
void printCoordinate(Coordinate *point);

#endif
