#ifndef TEST_INDEXER
#define TEST_INDEXER

#include <stdio.h>

#include "../minunit/minunit.h"
#include "indexer.h"

static char *test_indexer_ready() {
    Indexer indexer;

    initIndexer(&indexer, 110, 2);

    mu_assert("error, indexer initialization",
              isIndexerInitialized(&indexer) == 1);

    return 0;
}

static char *test_indexer_not_ready() {
    Indexer indexer;

    mu_assert("error, indexer initialization misinterpreting",
              isIndexerInitialized(&indexer) != 0);

    return 0;
}

static char *indexer_all_tests() {
    mu_run_test(test_indexer_ready);
    mu_run_test(test_indexer_not_ready);

    return 0;
}

#endif