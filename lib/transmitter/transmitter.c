#include "../../fs_config.h"

#include FS_TARGET

#include <stdint.h>
#include <stdio.h>

#include "../beacon/beacon.h"
#include "../current_sensor/current_sensor.h"
#include "../sine_wave/sine_wave.h"
#include "transmitter.h"

int32_t initTransmitter(Transmitter *transmitter, SineWave *wave,
                        int8_t signal_direction_pin) {
    transmitter->initialized = 0;

    if (wave->initialized == 0)
        return transmitter->initialized;

    transmitter->wave = *wave;

    transmitter->signal_index = 0;

    transmitter->signal_direction_pin = signal_direction_pin;

    transmitter->initialized = 1;

    return transmitter->initialized;
}

float updateTransmitterSignal(Transmitter *transmitter) {
    SineWave *wave = &transmitter->wave;
    DACObject *dac = &wave->dac;

    int16_t value = wave->shape[transmitter->signal_index];  //(10 *  * dac->resolution) / (dac->max_output_voltage);
    int16_t direction = wave->directions[transmitter->signal_index];

    HAL_DAC_SetValue(&dac->hdac, dac->channel, dac->alignment, value);
    //printf("%04d\r\n", value);

    transmitter->signal_index = (transmitter->signal_index + 1) % wave->resolution;

    return value * (-1 + 2 * direction);
}

int32_t setCurrentSensor(Transmitter *transmitter, CurrentSensor *sensor) {
    if (sensor->initialized == 0)
        return 0;

    transmitter->sensor = *sensor;

    return 1;
}
