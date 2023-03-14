#ifndef SPECTRUM_H
#define SPECTRUM_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <complex.h>

#include "../indexer/indexer.h"

#define SPECTRUM_INITIALIZATION_CHECK_SUM 3

extern float complex *angles;
extern int angles_initialized;
extern int amount_of_angles;

typedef struct
{
    float complex *samples;

    int amount_of_buffers;
    int sample_size;

    float complex double_per_sample_size;

    int initialized;

} Spectrum;

void initSpectrum(Spectrum *spectrum, int sample_size, int amount_of_buffers);
void initSpectrumAngles(int sample_size);

int isSpectrumInitialized(Spectrum *spectrum);

void updateSpectrum(Spectrum *spectrum, const float sample,
                    const float *samples, Indexer *indexer);

float getSpectrumWindowIntensity(Spectrum *spectrum, int window, Indexer *indexer);

#endif