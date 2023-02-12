#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <complex.h>

#include "../indexer/indexer.h"

extern float complex *angles;

typedef struct
{
    float complex *samples;
    int sample_size;

} Spectrum;

void initSpectrumAngles(int sample_size);

void initSpectrum(Spectrum spectrum);
void updateSpectrum(Spectrum spectrum, const float sample,
                    const float *samples, Indexer indexer);

float getIntensity(Spectrum spectrum, int window, Indexer indexer);

#endif