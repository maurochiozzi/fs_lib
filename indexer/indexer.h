#ifndef INDEXER_H
#define INDEXER_H

typedef struct
{
    int sample_size;

    int sample;
    int buffer;
} Indexer;

int incrementIndex(Indexer indexer);
void mutexSampleCache(Indexer indexer);

#endif