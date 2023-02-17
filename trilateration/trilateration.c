#include "trilateration.h"

#include "../space/space.h"

/**
 * For further reference: https://www.101computing.net/cell-phone-trilateration-algorithm/
 */

Coordinate getSpacePosition(Segment *segments, int available_references) {
    Coordinate position = {.x = 0.0,
                           .y = 0.0,
                           .z = 0.0};

    if (available_references == 3) {
        float A;
        float B;
        float C;
        float D;
        float E;
        float F;

        A = 2 * segments[1].reference.x - 2 * segments[0].reference.x;
        B = 2 * segments[1].reference.y - 2 * segments[0].reference.y;

        C = segments[0].magnitude * segments[0].magnitude - segments[1].magnitude * segments[1].magnitude -
            segments[0].reference.x * segments[0].reference.x + segments[1].reference.x * segments[1].reference.x -
            segments[0].reference.y * segments[0].reference.y + segments[1].reference.y * segments[1].reference.y;

        D = 2 * segments[2].reference.x - 2 * segments[1].reference.x;
        E = 2 * segments[2].reference.y - 2 * segments[1].reference.y;

        F = segments[1].magnitude * segments[1].magnitude - segments[2].magnitude * segments[2].magnitude -
            segments[1].reference.x * segments[1].reference.x + segments[2].reference.x * segments[2].reference.x -
            segments[1].reference.y * segments[1].reference.y + segments[2].reference.y * segments[2].reference.y;

        position.x = (C * E - F * B) / (E * A - B * D);
        position.y = (C * D - A * F) / (B * D - A * E);
    }

    return position;
}
