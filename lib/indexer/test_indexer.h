/**
 * @file test_indexer.h
 *
 * @brief This file contains the unit tests for the Indexer module.
 */

#ifndef TEST_INDEXER
#define TEST_INDEXER

#include <stdint.h>
#include <stdio.h>

#include "../minunit/minunit.h"
#include "indexer.h"

/**
 * @brief Unit test for checking if the Indexer is properly initialized.
 *
 * @return Returns 0 if the test passes, and a failure message otherwise.
 *
 * This function initializes an Indexer object with valid parameters, and checks
 * if the function isIndexerInitialized returns true.
 */
static char *test_indexer_initialized() {
    Indexer indexer = {0};

    initIndexer(&indexer, 110, 2);

    mu_assert("error, indexer initialization",
              isIndexerInitialized(&indexer) == 1);

    return 0;
}

/**
 * @brief Unit test for checking if the Indexer is not initialized.
 *
 * @return Returns 0 if the test passes, and a failure message otherwise.
 *
 * This function creates an Indexer object with default values, and checks if the
 * function isIndexerInitialized returns false.
 */
static char *test_indexer_not_initialized() {
    Indexer indexer = {0};

    mu_assert("error, indexer initialization misint32_terpreting",
              isIndexerInitialized(&indexer) == 0);

    return 0;
}

/**
 * @brief Runs all the unit tests for the Indexer module.
 *
 * @return Returns 0 if all the tests pass, and a failure message otherwise.
 *
 * This function runs all the unit tests for the Indexer module, and returns
 * a failure message if any of the tests fail.
 */
static char *indexer_all_tests() {
    mu_run_test(test_indexer_not_initialized);
    mu_run_test(test_indexer_initialized);

    return 0;
}

#endif
