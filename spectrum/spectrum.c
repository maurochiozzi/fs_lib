

#include "spectrum.h"

#include <complex.h>
#include <math.h>
#include <stdlib.h>

#include "../indexer/indexer.h"

float complex* angles;
int angles_initialized;
int amount_of_angles;

void initSpectrum(Spectrum* spectrum, int sample_size, int amount_of_buffers) {
    if (sample_size <= 10 || amount_of_buffers < 1) return;

    spectrum->amount_of_buffers = amount_of_buffers;
    spectrum->sample_size = sample_size;

    spectrum->samples = (float complex*)malloc(
        sizeof(float complex) *
        spectrum->amount_of_buffers * spectrum->sample_size);

    spectrum->double_per_sample_size = 2.0 / spectrum->sample_size;

    initSpectrumAngles(sample_size);

    spectrum->initialized = 1;
}

void initSpectrumAngles(int sample_size) {
    if (angles_initialized == 0) {
        amount_of_angles = sample_size;

        angles = (float complex*)malloc(
            sizeof(float complex) *
            amount_of_angles * amount_of_angles);

        for (int i = 0; i < amount_of_angles; i++) {  // this will be the current_index
            for (int j = 0; j < amount_of_angles; j++) {
                angles[i * amount_of_angles + j] =
                    cexp(i * j * amount_of_angles * (-(M_PI)*I));
            }
        }

        angles_initialized = 1;
    } else if (amount_of_angles != sample_size)
        return;
}

int isSpectrumInitialized(Spectrum* spectrum) {
    int check_sum = 0;

    if (angles_initialized == 1) {
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

void updateSpectrum(Spectrum* spectrum, const float sample,
                    const float* samples, Indexer* indexer) {
    float complex angle;

    for (int i = 0; i < indexer->sample + 1; i++) {
        angle = angles[indexer->sample * indexer->sample_size + i];

        spectrum->samples[indexer->buffer * indexer->sample_size + i] +=
            spectrum->double_per_sample_size * (sample * (angle));
    }

    for (int i = 0; i < indexer->sample; i++) {
        angle = angles[indexer->sample * indexer->sample_size + i];

        spectrum->samples[indexer->buffer * indexer->sample_size + indexer->sample] +=
            spectrum->double_per_sample_size * (samples[i] * (angle));
    }
}

float getIntensity(Spectrum spectrum, int window, Indexer indexer) {
    float intensity;

    intensity = spectrum.samples[indexer.buffer * indexer.sample_size + window];

    return intensity;
}
