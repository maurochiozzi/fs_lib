#ifndef SPACE_H
#define SPACE_H

// defines a spacial position
typedef struct Coordinate {
    float x;
    float y;
    float z;
} Coordinate;

// defines a vector
typedef struct Vector {
    float x;
    float y;
    float z;
} Vector;

typedef struct Baseline {
    Coordinate initial_point;
    Coordinate ending_point;
} Baseline;

/**
 * A segment defined by its origin and magnitude
 */
typedef struct Segment {
    Coordinate reference;

    float magnitude;
} Segment;

void setCoordinate(Coordinate *point, float x, float y, float z);
void setVector(Vector *vector, float x, float y, float z);

float norm(Vector vector);
float euclideanDistance2(Coordinate *start, Coordinate *end);
void sumCoordinateOffset(Coordinate *point, Coordinate *offset, Coordinate *result);

float calculatePositionError(Coordinate *reference, Coordinate *real);

void printCoordinate(Coordinate *point);

#endif