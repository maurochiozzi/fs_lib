
#ifndef SINE_WAVE_H
#define SINE_WAVE_H

typedef struct SineWave {
    short int mode;  // 0 -> zero-floating symmetry, 1 -> amplitude positive-offset

    int resolution;
    float *shape;
    short int *directions;  // 0 -> negative, 1 -> positive

    /**
     * @brief Flag indicating whether the SineWave has been properly initialized.
     */
    short int initialized;

} SineWave;

void initSineWave(SineWave *wave, float amplitude,
                  float frequency, float phase,
                  float offset, short int mode,
                  int resolution);

float sine_wave_generator(int index, int resolution,
                          float amplitude, float frequency,
                          float phase, float offset, int mode);

void destroySineWave(SineWave *wave);

#endif