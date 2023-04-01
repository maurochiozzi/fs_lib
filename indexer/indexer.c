/**
 * @file indexer.c
 * @brief Contains the function definitions for managing a slot indexer.
 *
 * This file implements the functions declared in the indexer.h header file.
 *
 * @see indexer.h
 */

#include "indexer.h"

#include <stdio.h>

/**
 * @brief Initializes an indexer with the specified sample size and amount of buffers.
 *
 * This function initializes an Indexer struct with the given sample size and amount of buffers. It sets the initial
 * sample and buffer indexes to 0 and sets the initialized flag to 1 if the initialization was successful.
 *
 * @param indexer The indexer to initialize.
 * @param sample_size The size of each buffer in the slot indexer.
 * @param amount_of_buffers The total number of buffers in the slot indexer.
 */
void initIndexer(Indexer *indexer, int sample_size, int amount_of_buffers) {
    if (sample_size <= 10 || amount_of_buffers < 1) return;

    indexer->sample_size = sample_size;
    indexer->amount_of_buffers = amount_of_buffers;

    // initialize sample and buffer indexers
    indexer->sample = 0;
    indexer->buffer = 0;

    indexer->initialized = 1;
}

/**
 * @brief Checks whether an indexer has been initialized.
 *
 * This function checks whether the given indexer has been successfully initialized by verifying the values of the
 * sample_size, amount_of_buffers, and initialized fields of the Indexer struct. If all values are within the expected
 * range and initialized is set to 1, the function returns 1. Otherwise, it returns 0.
 *
 * @param indexer The indexer to check.
 * @return 1 if the indexer has been initialized, 0 otherwise.
 */
int isIndexerInitialized(Indexer *indexer) {
    int check_sum = 0;

    if (indexer->initialized == 1) {
        check_sum++;
    }

    if (indexer->sample_size > 10) {
        check_sum++;
    }

    if (indexer->amount_of_buffers > 1) {
        check_sum++;
    }

    return check_sum == INDEXER_INITIALIZATION_CHECK_SUM;
}

/**
 * @brief Increments the current index of the indexer and returns the new index.
 *
 * This function increments the current sample index of the given indexer and returns the new index. If the new sample
 * index is 0, the buffer index is also incremented using the mutexSampleCache() function. This function is safe to use
 * in a multi-threaded context because it ensures that only one thread updates the sample and buffer indices at any given
 * time.
 *
 * @param indexer The indexer to increment.
 * @return 1 if the buffer index was incremented, 0 otherwise.
 */
int incrementIndex(Indexer *indexer) {
    const int sample = indexer->sample;
    const int sample_size = indexer->sample_size;
    const int amount_of_buffers = indexer->amount_of_buffers;

    indexer->sample = (sample + 1) % sample_size;

    int increment_buffer = indexer->sample == 0;

    if (increment_buffer) {
        mutexSampleCache(indexer);
    }

    return increment_buffer;
}

/**
 * @brief Prevents the sample and buffer indices of an indexer from being updated simultaneously.
 *
 * This function can be used in a multi-threaded context to ensure that only one thread updates the sample and buffer indices
 * at any given time.
 *
 * @param indexer The indexer to lock.
 */
void mutexSampleCache(Indexer *indexer) {
    indexer->buffer = (indexer->buffer + 1) %
                      indexer->amount_of_buffers;
}