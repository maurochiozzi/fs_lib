#ifndef BEACON_H
#define BEACON_H

#include "../magnetic_field/magnetic_field.h"
#include "../space/space.h"

#define BEACON_INITIALIZATION_CHECK_SUM 3

typedef struct Beacon {
    MagneticFieldSource magnetic_field_source;

    int spectrum_window;

    float precision;
    int survey_status;  // 0 will be undiscovered and 1 discovered

    float check_prd;
    float check_sum;

    int initialized;

} Beacon;

void initBeacon(Beacon *beacon, float magnetic_moment_rms, float frequency,
                int sample_rate, int sample_size);

int isBeaconInitialized(Beacon *beacon);

#endif