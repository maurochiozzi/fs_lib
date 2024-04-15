

#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#ifndef TRUNCATION
#define TRUNCATION 1000.0
#endif

#if FS_COMPILER == 1
#include FS_TARGET
#endif

#include "../../fs_config.h"
#include "../beacon/beacon.h"
#include "../current_sensor/current_sensor.h"
#include "../sine_wave/sine_wave.h"

#define TRANSMITTER_INITIALIZATION_CHECK_SUM 3

typedef struct Transmitter {
    Beacon beacon;
    CurrentSensor sensor;
    SineWave wave;

    int signal_index;  // Indexer for signal writing

#if FS_COMPILER == 0
    short int signal_output_pin;
    short int signal_direction_pin;
#else
    short int signal_output_pin;
    short int signal_direction_pin;
#endif
    /**
     * @brief Flag indicating whether the Transmitter has been properly initialized.
     */
    short int initialized;
} Transmitter;

int initTransmitter(Transmitter *transmitter, SineWave *wave,
                    short int signal_output_pin,
                    short int signal_direction_pin);

float update(Transmitter *transmitter);

void write_signal(int pin, int signal);
void set_direction(int pin, int direction);

int setCurrentSensor(Transmitter *transmitter, CurrentSensor *sensor);

#endif