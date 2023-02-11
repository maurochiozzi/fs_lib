#include "indexer.h"

int incrementIndex(Indexer indexer) {
    indexer.sample = (indexer.sample + 1) % 2 * indexer.sample_size;

    int increment_buffer = indexer.sample % indexer.sample_size;

    if (increment_buffer == 0) {
        mutexSampleCache(indexer);
    }

    return increment_buffer;
}

void mutexSampleCache(Indexer indexer) {
    indexer.buffer = (indexer.buffer + 1) % 2;
}