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

void initSpectrumAnalysis(int sample_size);
void initSpectrum(Spectrum spectrum);
void update(Spectrum spectrum, const float sample, const float *samples, int index);

#endif