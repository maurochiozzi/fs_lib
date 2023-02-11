#include "space.h"

#include "math.h"

void setCoordinate(Coordinate *point, float x, float y, float z) {
    point->x = x;
    point->y = y;
    point->z = z;
}

void setVector(Vector *vector, float x, float y, float z) {
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

float norm(Vector vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

float euclideanDistance2(Coordinate a, Coordinate b) {
    float delta_x = a.x - b.x;
    float delta_y = a.y - b.y;
    float delta_z = a.z - b.z;

    return delta_x * delta_x + delta_y * delta_y + delta_z * delta_z;
}