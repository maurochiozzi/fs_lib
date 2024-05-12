// Ref https://jera.com/techinfo/jtns/jtn002
#include <stdint.h>

#define mu_assert(message, test)     \
    do {                             \
        if (!(test)) return message; \
    } while (0)
#define mu_run_test(test)            \
    do {                             \
        char *message = test();      \
        tests_run++;                 \
        if (message) return message; \
    } while (0)
#define mu_run_all_sub_tests(test)   \
    do {                             \
        char *message = test();      \
        if (message) return message; \
    } while (0)

extern int32_t tests_run;