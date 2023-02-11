
#include "spectrum.h"

#include <complex.h>
#include <math.h>

#include "../indexer/indexer.h"

void initSpectrumAnalysis(int sample_size) {
    angles = (float complex*)malloc(sizeof(float complex) * sample_size * sample_size);

    for (int i = 0; i < sample_size; i++) {  // this will be the current_index
        for (int j = 0; j < sample_size; j++) {
            angles[i * sample_size + j] = cexp(i * j * sample_size * (-M_PI * I));
        }
    }
}

void initSpectrum(Spectrum spectrum) {
    spectrum.samples = (float complex*)malloc(sizeof(float complex) * 2 * spectrum.sample_size);
}

void update(Spectrum spectrum, const float sample, const float* samples, int index) {
    const float complex double_per_sample_size = 2.0 / spectrum.sample_size;
    float complex angle;

    for (int i = 0; i < index + 1; i++) {
        angle = angles[index * spectrum.sample_size + i];

        spectrum.samples[i] += double_per_sample_size * (sample * (angle));
    }

    for (int i = 0; i < index; i++) {
        angle = angles[index * spectrum.sample_size + i];

        spectrum.samples[index] += double_per_sample_size * (samples[i] * (angle));
    }
}
