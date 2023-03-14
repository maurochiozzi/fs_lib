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

float euclideanDistance2(Coordinate *start, Coordinate *end) {
    float delta_x = start->x - end->x;
    float delta_y = start->y - end->y;
    float delta_z = start->z - end->z;

    return delta_x * delta_x + delta_y * delta_y + delta_z * delta_z;
}