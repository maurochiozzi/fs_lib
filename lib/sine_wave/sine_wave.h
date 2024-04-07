
#ifndef SINE_WAVE_H
#define SINE_WAVE_H

#ifndef M_PI
#define M_PI 3.14159265358979323846 /**< Definition of Pi constant */
#endif

typedef struct SineWave {
    float amplitude;  // > 0
    float frequency;  // Hertz
    float phase;      // radians
    float offset;     // >= 0
    short int mode;   // 0 -> zero-floating symmetry, 1 -> amplitude positive-offset

    int resolution;
    float *shape;
    short int *directions;  // 0 -> negative, 1 -> positive

    /**
     * @brief Flag indicating whether the SineWave has been properly initialized.
     */
    int initialized;

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