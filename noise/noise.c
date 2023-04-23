#include "noise.h"

#include <stdlib.h>
#include <time.h>

void initNoiseGenerator() {
    srand(time(NULL));
}

float noise() {
    return ((float)rand() / RAND_MAX) * 2 - 1;
}

float unsigned_noise() {
    return ((float)rand() / RAND_MAX);
}