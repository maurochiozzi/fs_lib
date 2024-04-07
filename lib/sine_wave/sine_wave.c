#include "sine_wave.h"

#include <math.h>
#include <stdlib.h>

void initSineWave(SineWave *wave, float amplitude,
                  float frequency, float phase,
                  float offset, short int mode,
                  int resolution) {
    wave->initialized = 0;

    wave->mode = mode;
    wave->resolution = resolution;

    wave->shape = (float *)malloc(sizeof(float) * resolution);

    if (mode == 0) {
        wave->directions = (short int *)malloc(sizeof(short int) * resolution);
    }

    for (int index = 0; index < resolution; index++) {
        wave->shape[index] = sine_wave_generator(index, resolution, amplitude, frequency, phase, offset, mode);

        if (mode == 0) {
            wave->directions[index] = wave->shape[index] >= 0;
        }

        wave->shape[index] = fabs(wave->shape[index]);
    }

    wave->initialized = 1;
}

void destroySineWave(SineWave *wave) {
    free(wave->shape);

    free(wave->directions);
}

float sine_wave_generator(int index, int resolution, float amplitude, float frequency, float phase, float offset, int mode) {
    offset = mode * amplitude + offset;

    float trunc = 1000.0;

    return ((int)(trunc * ((amplitude)*sin(2 * frequency * M_PI * index / resolution + phase) + offset))) / trunc;
}