

#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include "../../fs_config.h"

#include FS_TARGET

#include <stdint.h>

#include "../beacon/beacon.h"
#include "../current_sensor/current_sensor.h"
#include "../sine_wave/sine_wave.h"

#define TRANSMITTER_INITIALIZATION_CHECK_SUM 3

typedef struct Transmitter {
    Beacon beacon;
    CurrentSensor sensor;
    SineWave wave;

    int32_t signal_index;  // Indexer for signal writing

    int8_t signal_direction_pin;

    /**
     * @brief Flag indicating whether the Transmitter has been properly initialized.
     */
    int8_t initialized;
} Transmitter;

int32_t initTransmitter(Transmitter *transmitter, SineWave *wave,
                        int8_t signal_direction_pin);

float updateTransmitterSignal(Transmitter *transmitter);

void write_signal(uint32_t value);
void set_direction(int32_t pin, int32_t direction);

int32_t setCurrentSensor(Transmitter *transmitter, CurrentSensor *sensor);

#endif
