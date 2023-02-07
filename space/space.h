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

void setCoordinate(Coordinate *point, float x, float y, float z);
void setVector(Vector *vector, float x, float y, float z);

float euclideanDistance2(Coordinate point_a, Coordinate point_b);

#endif