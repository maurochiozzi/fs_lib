#ifndef INDEXER_H
#define INDEXER_H

#define INDEXER_INITIALIZATION_CHECK_SUM 3

typedef struct
{
    int amount_of_buffers;
    int sample_size;

    int sample;
    int buffer;

    int initialized;
} Indexer;

void initIndexer(Indexer *indexer, int sample_size, int amount_of_buffers);
int isIndexerInitialized(Indexer *indexer);
int incrementIndex(Indexer *indexer);
void mutexSampleCache(Indexer *indexer);

#endif