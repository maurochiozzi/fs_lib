#include "body.h"

#include "space.h"

void initBody(Body *body) {
    setCoordinate(&body->position, 0.0, 0.0, 0.0);
    setVector(&body->heading, 0.0, 0.0, 0.0);

    return 0;
}

void updatePosition(Body *body, Coordinate position, Vector heading) {
    body->position = position;
    body->heading = heading;
}