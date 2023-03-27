#ifndef TEST_INDEXER
#define TEST_INDEXER

#include <stdio.h>

#include "../minunit/minunit.h"
#include "indexer.h"

static char *test_indexer_initialized() {
    Indexer indexer = {0};

    initIndexer(&indexer, 110, 2);

    mu_assert("error, indexer initialization",
              isIndexerInitialized(&indexer) == 1);

    return 0;
}

static char *test_indexer_not_initialized() {
    Indexer indexer = {0};

    mu_assert("error, indexer initialization misinterpreting",
              isIndexerInitialized(&indexer) == 0);

    return 0;
}

static char *indexer_all_tests() {
    mu_run_test(test_indexer_not_initialized);
    mu_run_test(test_indexer_initialized);

    return 0;
}

#endif