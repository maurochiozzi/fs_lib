#include "sine_wave.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int32_t initDACObject(DACObject *dac, DAC_HandleTypeDef *hdac,
                      int16_t resolution, uint32_t channel,
                      uint32_t alignment, int8_t max_output_voltage) {
    dac->initialized = 0;

    dac->hdac = *hdac;
    dac->resolution = resolution;
    dac->channel = channel;
    dac->alignment = alignment;
    dac->max_output_voltage = max_output_voltage;

    dac->initialized = 1;

    return dac->initialized;
}

void initSineWave(SineWave *wave, DACObject *dac, float peak, float frequency,
                  float offset, int8_t mode, int32_t resolution) {
    wave->initialized = 0;

    wave->mode = mode;
    wave->resolution = resolution;

    wave->frequency = frequency;
    wave->offset = offset;

    wave->shape = (float *)malloc(sizeof(float) * resolution);

    if (mode == 0) {
        wave->directions = (int8_t *)malloc(sizeof(int8_t) * resolution);
    }

    peak = fabs(peak);
    wave->dac = *dac;

    if (mode == 0 && fabs(peak) > (dac->max_output_voltage)) {
        peak = dac->max_output_voltage;
    } else if (mode == 1 && fabs(peak) > (dac->max_output_voltage / 20.0)) {
        peak = (dac->max_output_voltage / 20.0);
    }

    for (int32_t index = 0; index < resolution; index++) {
        wave->shape[index] = sine_wave_generator(dac, index, resolution, peak,
                                                 offset, mode);

        if (mode == 0) {
            wave->directions[index] = wave->shape[index] >= 0;
        } else {
            wave->directions[index] = 0;
        }

        wave->shape[index] = fabs(wave->shape[index]);
    }

    wave->initialized = 1;
}

void destroySineWave(SineWave *wave) {
    free(wave->shape);

    free(wave->directions);
}

float sine_wave_generator(DACObject *dac, int32_t index, int32_t resolution, float peak,
                          float offset, int32_t mode) {
    offset = mode * peak + offset;

    float trunc = 1000.0;

    float sine_value;
    int32_t dac_value;

    sine_value = ((int32_t)(trunc * ((peak)*sin(2 * M_PI * index / resolution) + offset))) / trunc;
    dac_value = (10.0 * sine_value * dac->resolution) / (dac->max_output_voltage);

    return dac_value;
}
