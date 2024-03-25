/**
 * @file spectrum.c
 * @brief Implementation of the Spectrum data structure.
 *
 * @see spectrum.h
 *
 */

#include "spectrum.h"

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../indexer/indexer.h"
#include "../spectrum/spectrum.h"

float complex* phases;  /**< Array of complex phase values used in the FFT calculation. */
int phases_initialized; /**< Flag indicating whether the phases array has been initialized. */
int amount_of_phases;   /**< Number of elements in the phases array. */

/**
 * @brief Initializes the Spectrum data structure with the specified sample size and number of buffers.
 *
 * @param spectrum Pointer to the Spectrum data structure.
 * @param sample_size Size of the sample buffer.
 * @param amount_of_buffers Number of sample buffers.
 */
void initSpectrum(Spectrum* spectrum, int sample_size, int amount_of_buffers) {
    if (sample_size <= 10 || amount_of_buffers < 1) return;

    spectrum->amount_of_buffers = amount_of_buffers;
    spectrum->sample_size = sample_size;

    // Allocate memory for the sample buffer.
    spectrum->samples = (float complex*)malloc(
        sizeof(float complex) *
        amount_of_buffers * sample_size);

    // Initialize the sample buffer to 0.
    for (int index = 0; index < amount_of_buffers * sample_size; index++) {
        spectrum->samples[index] = 0.0;
    }

    // Calculate a constant used in the FFT calculation.
    spectrum->double_per_sample_size = 2.0 / sample_size;

    // Initialize the phases array used in the FFT calculation.
    initSpectrumAngles(sample_size);

    // Set the initialization flag to indicate that the Spectrum data structure is properly initialized.
    spectrum->initialized = 1;
}

/**
 * @brief Initializes the phases array used in the FFT calculation with the specified sample size.
 *
 * @param sample_size Size of the sample buffer.
 */
void initSpectrumAngles(int sample_size) {
    if (phases_initialized == 0) {
        // Allocate memory for the phases array.
        amount_of_phases = sample_size;
        phases = (float complex*)malloc(
            sizeof(float complex) *
            amount_of_phases * amount_of_phases);

        // Calculate the complex phase values and store them in the phases array.
        for (int i = 0; i < amount_of_phases; i++) {
            for (int j = 0; j < amount_of_phases; j++) {
                phases[i * amount_of_phases + j] =
                    cexp(-(2 * i * j * (M_PI)*I) / amount_of_phases);
            }
        }

        // Set the initialization flag to indicate that the phases array is properly initialized.
        phases_initialized = 1;
    } else if (amount_of_phases != sample_size)
        return;
}

/**
 * @brief Checks if the Spectrum data structure has been properly initialized.
 *
 * @param spectrum Pointer to the Spectrum data structure.
 *
 * @return 1 if the Spectrum data structure has been properly initialized, 0 otherwise.
 */
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

/**
 * @brief Get the intensity of a specific window in the spectrum.
 *
 * This function calculates the intensity of a specific window in the spectrum. The
 * intensity is calculated as the modulus of the complex value of the sample at that
 * window.
 *
 * @param spectrum Pointer to the Spectrum data structure.
 * @param window The index of the window in the spectrum.
 * @param indexer Pointer to the Indexer data structure.
 *
 * @return The intensity of the sample at the specified window in the spectrum.
 */
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

/**
 * @brief Clears the samples in the buffer of a past spectrum.
 *
 * This function clears the samples in the buffer of a past spectrum that has
 * already been processed. The index of the buffer is maintained by the
 * `Indexer` data structure.
 *
 * @param spectrum Pointer to the `Spectrum` data structure.
 * @param indexer Pointer to the `Indexer` data structure.
 */
void clearPastSpectrum(Spectrum* spectrum, Indexer* indexer) {
    int index_base = ((indexer->buffer + 1) % indexer->amount_of_buffers) * indexer->sample_size;

    for (int i = 0; i < indexer->sample_size; i++) {
        spectrum->samples[index_base + i] = 0;
    }
}