
#ifndef UTILS_H
#define UTILS_H

typedef struct SineWaveParams {
    float amplitude;      // > 0
    float frequency;      // Hertz
    float phase;          // radians
    float offset;         // >= 0
    short int direction;  // 0 -> negative, 1 -> positive
    short int mode;       // 0 -> zero-floating symmetry, 1 -> amplitude positive-offset
} SineWaveParams;

float calculateError(float reference, float real);

#endif