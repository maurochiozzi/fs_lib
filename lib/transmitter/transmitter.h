

#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#ifndef TRUNCATION
#define TRUNCATION 1000.0
#endif

#include "../beacon/beacon.h"
#include "../current_sensor/current_sensor.h"
#include "../sine_wave/sine_wave.h"

#define TRANSMITTER_INITIALIZATION_CHECK_SUM 3

typedef struct Transmitter {
    Beacon beacon;
    CurrentSensor sensor;
    SineWave wave;

    int signal_index;  // Indexer for signal writing

    short int signal_output_pin;
    short int signal_direction_pin;

    /**
     * @brief Flag indicating whether the Transmitter has been properly initialized.
     */
    short int initialized;
} Transmitter;

int initTransmitter(Transmitter *transmitter, SineWave *wave,
                    short int signal_output_pin,
                    short int signal_direction_pin);

float write_signal(Transmitter *transmitter);

float write_unsigned_signal(Transmitter *transmitter);

int setCurrentSensor(Transmitter *transmitter, CurrentSensor *sensor);

#endif