/**
 * @file indexer.h
 *
 * @brief Header file for the Indexer struct and associated functions.
 */

#ifndef INDEXER_H
#define INDEXER_H

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
    int amount_of_buffers;

    /**
     * @brief The size of each buffer in the slot indexer.
     */
    int sample_size;

    /**
     * @brief The current sample in the slot indexer.
     */
    int sample;

    /**
     * @brief The current buffer in the slot indexer.
     */
    int buffer;

    /**
     * @brief Flag indicating whether the slot indexer has been initialized.
     */
    int initialized;
} Indexer;

/**
 * @brief Initializes an Indexer with the specified sample size and amount of buffers.
 *
 * @param indexer Pointer to the Indexer struct to be initialized.
 * @param sample_size The size of each buffer in the slot indexer.
 * @param amount_of_buffers The total number of buffers in the slot indexer.
 */
void initIndexer(Indexer *indexer, int sample_size, int amount_of_buffers);

/**
 * @brief Checks whether an Indexer has been properly initialized.
 *
 * @param indexer Pointer to the Indexer struct to be checked.
 *
 * @return 1 if the Indexer has been properly initialized, 0 otherwise.
 */
int isIndexerInitialized(Indexer *indexer);

/**
 * @brief Increments the current index of the Indexer and returns the new index.
 *
 * @param indexer Pointer to the Indexer struct to increment.
 *
 * @return The new index after incrementing.
 */
int incrementIndex(Indexer *indexer);

/**
 * @brief Prevents the sample and buffer indices of an Indexer from being updated simultaneously.
 *
 * This function can be used in a multi-threaded context to ensure that only one thread updates the sample and buffer indices
 * at any given time.
 *
 * @param indexer Pointer to the Indexer struct to lock.
 */
void mutexSampleCache(Indexer *indexer);

#endif
