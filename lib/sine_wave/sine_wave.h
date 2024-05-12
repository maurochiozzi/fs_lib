#ifndef SINE_WAVE_H
#define SINE_WAVE_H

#include "../../fs_config.h"
#include FS_TARGET

#include <stdint.h>

typedef struct DACObject {
    int16_t resolution;
    int8_t max_output_voltage;  // x10
    DAC_HandleTypeDef hdac;
    uint32_t channel;
    uint32_t alignment;

    int8_t initialized;
} DACObject;

typedef struct SineWave {
    DACObject dac;
    int8_t mode;  // 0 -> zero-floating symmetry, 1 -> peak positive-offset

    uint8_t frequency;
    uint8_t offset;
    float peak;

    int16_t resolution;
    float *shape;
    int8_t *directions;  // 0 -> negative, 1 -> positive

    /**
     * @brief Flag indicating whether the SineWave has been properly initialized.
     */
    int8_t initialized;

} SineWave;

int32_t initDACObject(DACObject *dac, DAC_HandleTypeDef *hdac,
                      int16_t resolution, uint32_t channel,
                      uint32_t alignment, int8_t max_output_voltage);

void initSineWave(SineWave *wave, DACObject *dac, float peak,
                  float frequency, float offset, int8_t mode,
                  int32_t resolution);

float sine_wave_generator(DACObject *dac, int32_t index, int32_t resolution,
                          float peak, float offset, int32_t mode);

void destroySineWave(SineWave *wave);

#endif