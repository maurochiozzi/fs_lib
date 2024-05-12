/**
 * @file spectrum.h
 *
 * @brief This file contains the declaration of the Spectrum struct and functions for processing audio signals in the frequency domain.
 */

#ifndef SPECTRUM_H
#define SPECTRUM_H

#ifndef M_PI
#define M_PI 3.14159265358979323846 /**< Definition of Pi constant */
#endif

#include <complex.h>
#include <stdint.h>

#include "../indexer/indexer.h"

#define SPECTRUM_INITIALIZATION_CHECK_SUM 3 /**< Constant used to check if the Spectrum struct is properly initialized */

extern float complex *phases;      /**< Array of complex numbers representing phases of sine waves used in the DFT algorithm */
extern int32_t phases_initialized; /**< Flag indicating whether the phases array is initialized or not */
extern int32_t amount_of_phases;   /**< Total number of phases stored in the phases array */

/**
 * @brief Struct representing an audio signal in the frequency domain.
 */
typedef struct
{
    float complex *samples; /**< Array of complex numbers representing the signal's samples in the frequency domain */

    int32_t amount_of_buffers; /**< Number of buffers in the signal */
    int32_t sample_size;       /**< Number of samples per buffer */

    float complex double_per_sample_size; /**< Constant used in the DFT algorithm */
    int32_t initialized;                  /**< Flag indicating whether the Spectrum struct is properly initialized */

} Spectrum;

/**
 * @brief Initializes a Spectrum struct with the given sample size and number of buffers.
 *
 * @param spectrum pointer to the Spectrum struct to be initialized.
 * @param sample_size The number of samples per buffer in the audio signal.
 * @param amount_of_buffers The number of buffers in the audio signal.
 */
void initSpectrum(Spectrum *spectrum, int32_t sample_size, int32_t amount_of_buffers);

/**
 * @brief Initializes the phases array for the DFT algorithm.
 *
 * @param sample_size The number of samples per buffer in the audio signal.
 */
void initSpectrumAngles(int32_t sample_size);

/**
 * @brief Checks whether a Spectrum struct is properly initialized.
 *
 * @param spectrum pointer to the Spectrum struct to be checked.
 *
 * @return 1 if the Spectrum struct is properly initialized, 0 otherwise.
 */
int32_t isSpectrumInitialized(Spectrum *spectrum);

/**
 * @brief Calculates the int32_tensity of the audio signal in the given window in the frequency domain.
 *
 * @param spectrum pointer to the Spectrum struct containing the audio signal in the frequency domain.
 * @param window The index of the window to calculate the int32_tensity for.
 * @param indexer pointer to an Indexer struct used to index the audio signal's buffers.
 *
 * @return The int32_tensity of the audio signal in the given window in the frequency domain.
 */
float getSpectrumWindowint32_tensity(Spectrum *spectrum, int32_t window, Indexer *indexer);

/**
 * @brief Clears the past audio signal data from the Spectrum struct.
 *
 * @param spectrum pointer to the Spectrum struct to be cleared.
 * @param indexer pointer to an Indexer struct used to index the audio signal's buffers.
 */
void clearPastSpectrum(Spectrum *spectrum, Indexer *indexer);

#endif
