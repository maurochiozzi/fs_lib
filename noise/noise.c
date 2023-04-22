#include "noise.h"

#include <stdlib.h>
#include <time.h>

void initNoiseGenerator() {
    srand(time(NULL));
}

void noise() {
    return ((float)rand() / RAND_MAX) * 2 - 1;
}