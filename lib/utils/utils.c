#include "utils.h"

float calculateError(float reference, float real) {
    return (reference - real) / reference;
}
