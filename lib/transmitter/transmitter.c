#include "transmitter.h"

#include "../beacon/beacon.h"
#include "../current_sensor/current_sensor.h"
#include "../sine_wave/sine_wave.h"

int initTransmitter(Transmitter *transmitter, SineWave *wave,
                    short int signal_output_pin,
                    short int signal_direction_pin) {
    transmitter->initialized = 0;

    if (wave->initialized == 0) return transmitter->initialized;

    transmitter->wave = *wave;

    transmitter->signal_index = 0;

    transmitter->signal_output_pin = signal_output_pin;
    transmitter->signal_direction_pin = signal_direction_pin;

    transmitter->initialized = 1;

    return transmitter->initialized;
}

float write_signal(Transmitter *transmitter) {
    SineWave *wave = &transmitter->wave;

    float value = wave->shape[transmitter->signal_index];
    int direction = wave->directions[transmitter->signal_index];

    // set direction output
    // set DAC value

    transmitter->signal_index = (transmitter->signal_index + 1) % wave->resolution;

    return value * (-1 + 2 * direction);
}

float write_unsigned_signal(Transmitter *transmitter) {
    // if transmitter->mode equals to 1, all signal directions
    // will be 1 (always positive), so no need to expend extra
    // resources retrieving the direction and updating pin output
    SineWave *wave = &transmitter->wave;

    float value = wave->shape[transmitter->signal_index];

    // set DAC value

    transmitter->signal_index = (transmitter->signal_index + 1) % wave->resolution;

    return value;
}

int setCurrentSensor(Transmitter *transmitter, CurrentSensor *sensor) {
    if (sensor->initialized == 0) return 0;

    transmitter->sensor = *sensor;

    return 1;
}
