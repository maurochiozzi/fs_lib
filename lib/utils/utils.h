
#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

typedef struct SineWaveParams {
    float amplitude;   // > 0
    float frequency;   // Hertz
    float phase;       // radians
    float offset;      // >= 0
    int8_t direction;  // 0 -> negative, 1 -> positive
    int8_t mode;       // 0 -> zero-floating symmetry, 1 -> amplitude positive-offset
} SineWaveParams;

float calculateError(float reference, float real);

#endif