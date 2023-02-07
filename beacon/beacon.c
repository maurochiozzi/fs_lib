#include "beacon.h"

#include "../space/space.h"

void initBeacon(Beacon *beacon) {
    setCoordinate(&beacon->position, 0.0, 0.0, 0.0);
}