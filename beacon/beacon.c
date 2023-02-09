#include "beacon.h"

#include "../space/space.h"

void initBeacon(Beacon *beacon) {
    beacon->survey_status = 0;

    setCoordinate(&beacon->position, 0.0, 0.0, 0.0);
}