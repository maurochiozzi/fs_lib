/**
 * @file indexer.h
 *
 * @brief Header file for the Indexer struct and associated functions.
 */

#ifndef INDEXER_H
#define INDEXER_H

#include <stdint.h>

#include "../space/space.h"

/**
 * @brief Checksum value used to verify that an Indexer has been properly initialized.
 */
#define INDEXER_INITIALIZATION_CHECK_SUM 3

/**
 * @brief Struct representing a slot indexer.
 */
typedef struct Indexer {
    /**
     * @brief The total number of buffers in the slot indexer.
     */
    int32_t amount_of_buffers;

    /**
     * @brief The size of each buffer in the slot indexer.
     */
    int32_t sample_size;

    /**
     * @brief The current sample in the slot indexer.
     */
    int32_t sample;

    /**
     * @brief The current buffer in the slot indexer.
     */
    int32_t buffer;

    /**
     * @brief Flag indicating whether the slot indexer has been initialized.
     */
    int32_t initialized;
} Indexer;

/**
 * @brief Initializes an Indexer with the specified sample size and amount of buffers.
 *
 * @param indexer pointer to the Indexer struct to be initialized.
 * @param sample_size The size of each buffer in the slot indexer.
 * @param amount_of_buffers The total number of buffers in the slot indexer.
 */
void initIndexer(Indexer *indexer, int32_t sample_size, int32_t amount_of_buffers);

/**
 * @brief Checks whether an Indexer has been properly initialized.
 *
 * @param indexer pointer to the Indexer struct to be checked.
 *
 * @return 1 if the Indexer has been properly initialized, 0 otherwise.
 */
int32_t isIndexerInitialized(Indexer *indexer);

/**
 * @brief Increments the current index of the Indexer and returns the new index.
 *
 * @param indexer pointer to the Indexer struct to increment.
 *
 * @return The new index after incrementing.
 */
int32_t incrementIndex(Indexer *indexer);

/**
 * @brief Prevents the sample and buffer indices of an Indexer from being updated simultaneously.
 *
 * This function can be used in a multi-threaded context to ensure that only one thread updates the sample and buffer indices
 * at any given time.
 *
 * @param indexer pointer to the Indexer struct to lock.
 */
void mutexSampleCache(Indexer *indexer);

#endif
