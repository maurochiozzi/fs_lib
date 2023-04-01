

#include "spectrum.h"

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../indexer/indexer.h"
#include "../spectrum/spectrum.h"

float complex* phases;
int phases_initialized;
int amount_of_phases;

void initSpectrum(Spectrum* spectrum, int sample_size, int amount_of_buffers) {
    if (sample_size <= 10 || amount_of_buffers < 1) return;

    spectrum->amount_of_buffers = amount_of_buffers;
    spectrum->sample_size = sample_size;

    spectrum->samples = (float complex*)malloc(
        sizeof(float complex) *
        amount_of_buffers * sample_size);

    for (int index = 0; index < amount_of_buffers * sample_size; index++) {
        spectrum->samples[index] = 0.0;
    }

    spectrum->double_per_sample_size = 2.0 / sample_size;

    initSpectrumAngles(sample_size);

    spectrum->initialized = 1;
}

void initSpectrumAngles(int sample_size) {
    if (phases_initialized == 0) {
        amount_of_phases = sample_size;

        phases = (float complex*)malloc(
            sizeof(float complex) *
            amount_of_phases * amount_of_phases);

        for (int i = 0; i < amount_of_phases; i++) {  // this will be the current_index
            for (int j = 0; j < amount_of_phases; j++) {
                phases[i * amount_of_phases + j] =
                    cexp(-(2 * i * j * (M_PI)*I) / amount_of_phases);
            }
        }

        phases_initialized = 1;
    } else if (amount_of_phases != sample_size)
        return;
}

int isSpectrumInitialized(Spectrum* spectrum) {
    int check_sum = 0;

    if (phases_initialized == 1) {
        check_sum++;
    }

    if (spectrum->initialized == 1) {
        check_sum++;
    }

    if (spectrum->sample_size > 10) {
        check_sum++;
    }

    return check_sum == SPECTRUM_INITIALIZATION_CHECK_SUM;
}

float getSpectrumWindowIntensity(Spectrum* spectrum, int window, Indexer* indexer) {
    int spectrum_window;
    float intensity;

    // Increment index buffer and get its mod from amount of buffers to get the
    // previous buffer already finished
    spectrum_window = ((indexer->buffer + 1) % indexer->amount_of_buffers) * indexer->sample_size +
                      window;

    // Calculate the intensity modulus
    intensity = cabsf(spectrum->samples[spectrum_window]);

    return intensity;
}

void clearPastSpectrum(Spectrum* spectrum, Indexer* indexer) {
    int index_base = ((indexer->buffer + 1) % indexer->amount_of_buffers) * indexer->sample_size;

    for (int i = 0; i < indexer->sample_size; i++) {
        spectrum->samples[index_base + i] = 0;
    }
}