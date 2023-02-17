#include "beacon.h"

#include "../space/space.h"

void initBeacon(Beacon beacon, int sample_rate, int sample_size) {
    beacon.survey_status = 0;
    beacon.spectrum_window = beacon.frequency * (sample_rate / sample_size);

    setCoordinate(&beacon.position, 0.0, 0.0, 0.0);
}