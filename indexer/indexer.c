#include "indexer.h"

#include <stdio.h>

void initIndexer(Indexer *indexer, int sample_size, int amount_of_buffers) {
    if (sample_size <= 10 || amount_of_buffers < 1) return;

    indexer->sample_size = sample_size;
    indexer->amount_of_buffers = amount_of_buffers;

    indexer->initialized = 1;
}

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

int incrementIndex(Indexer *indexer) {
    const int sample = indexer->sample;
    const int sample_size = indexer->sample_size;
    const int amount_of_buffers = indexer->amount_of_buffers;

    indexer->sample = (sample + 1) %
                      (amount_of_buffers *
                       sample_size);

    int increment_buffer = sample % sample_size == 0;

    if (increment_buffer) {
        mutexSampleCache(indexer);
    }

    return increment_buffer;
}

void mutexSampleCache(Indexer *indexer) {
    indexer->buffer = (indexer->buffer + 1) %
                      indexer->amount_of_buffers;
}