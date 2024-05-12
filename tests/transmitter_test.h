#ifndef TRANSMITTER_TEST
#define TRANSMITTER_TEST

#include <complex.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lib/beacon/beacon.h"
#include "../lib/current_sensor/current_sensor.h"
#include "../lib/minunit/minunit.h"
#include "../lib/sine_wave/sine_wave.h"
#include "../lib/spectrum/spectrum.h"
#include "../lib/transmitter/transmitter.h"

static char *transmitter_dft() {
    CurrentSensor sensor;
    const int32_t amount_of_buffers = 2;
    const int32_t sample_size = 110;
    const int32_t sample_rate = 110;
    const int32_t i2c_address = 0xE1;
    const int32_t i2c_int32_terface = 0xE1;

    initCurrentSensor(&sensor, sample_size, amount_of_buffers, i2c_address, i2c_int32_terface);

    // Check if device was correctly initialized
    mu_assert("error, beacon transmitter - current sensor initialization",
              isCurrentSensorInitialized(&sensor) == 1);

    SineWave wave;
    const int8_t amplitude = 2;  // > 0
    const int8_t frequency = 5;  // Hertz
    const int8_t phase = 0;      // radians
    const int8_t offset = 0;     // 0 to 1
    const short mode = 0;        // 0- zero-floating symmetry, 1 -> half-amplitude positive-offset
    const int32_t resolution = 110;

    initSineWave(&wave, amplitude, frequency, phase, offset, mode, resolution);

    Beacon beacon;
    const float magnetic_moment = 0.6997897635871264 * 1.257 * pow(10, -6);

    initBeacon(&beacon, magnetic_moment, frequency, sample_rate, sample_size);

    // Check if device was correctly initialized
    mu_assert("error, beacon transmitter - beacon initialization",
              isBeaconInitialized(&beacon) == 1);

    Transmitter transmitter;
    const int32_t out_put_pin = 10;
    const int32_t signal_direction_pin = 10;

    initTransmitter(&transmitter, &wave, out_put_pin, signal_direction_pin);

    // Check if device was correctly initialized
    mu_assert("error, beacon transmitter - transmitter initialization",
              isBeaconInitialized(&beacon) == 1);

    setCurrentSensor(&transmitter, &sensor);

    int32_t index;

    float trunc = 1000.0;
    float error = 0.001;

    float calculated_amplitude;

    printf("%f, %d, %d, %f, %d\n", frequency, sample_rate, sample_size, (sample_rate / (float)sample_size), (trunc * frequency / (sample_rate / (float)sample_size)) / trunc);
    printf("%d %d %d %d\n", sizeof(transmitter), sizeof(beacon), sizeof(wave), sizeof(wave.shape) * resolution);
    printf("Window: %d\n", beacon.spectrum_window);

    int32_t current_sensor_sample_period = 1000 / sample_rate;
    int32_t magnetic_source_update_period = 1000 / frequency;

    int32_t waveform_index = 0;
    float current = 0;

    int32_t time_run = 1000 / sample_rate;

    printf("Window: %d\n", beacon.spectrum_window);

    for (int32_t tk = 0; tk < sample_size; tk++) {
        current = update(&transmitter);

        // printf("index %03d, signal %02d, original %2.4f, current %2.4f\n",
        //        waveform_index, wave.directions[waveform_index], wave.shape[waveform_index], current);

        waveform_index = (waveform_index + 1) % resolution;

        addSampleCurrent(&sensor, current);
    }

    Spectrum spectrum = sensor.spectrum;
    float complex *samples = spectrum.samples;

    // for (int32_t i = 0; i < sample_size; i++) {
    //     printf("(%d, %.4f)\n", i, fabs(sensor.spectrum.samples[i]));
    // }

    calculated_amplitude = getCurrentint32_tensity(&sensor, &beacon);

    printf("Final current: %f, error: %f\n", calculated_amplitude, calculateError(amplitude, calculated_amplitude));

    mu_assert("Current sensor final value error",
              cabsf(
                  calculateError(
                      amplitude,
                      calculated_amplitude)) < error);

    destroySineWave(&wave);

    return 0;
}

#endif