#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846 /**< Definition of Pi constant */
#endif

float sine_wave_generator(int index, int resolution, float amplitude, float frequency, float phase, float offset) {
    float trunc = 1000.0;

    return ((int)(trunc * amplitude * sin(2 * frequency * M_PI * index / resolution + phase))) / trunc;
}

float get_signal(int index, float *wave_form) {
    return fabs(wave_form[index]);
}

int set_direction(int index, short int *direction, short int *zero_crossings) {
    (*direction) = ((*direction) + zero_crossings[index]) % 2;
}

float write_signal(float value, int direction) {
    // set direction output
    // set DAC value
}

int main() {
    const int SIGNAL_RESOLUTION = 32;
    int index;

    float *wave_form;
    short int *zero_crossing;
    short int *signal_directions;
    float previous_signal_value;

    float amplitude = 1;      // > 0
    float frequency = 4;      // Hertz
    float phase = 0;          // radians
    float offset = 0;         // 0 to 1
    short int direction = 0;  // 0 -> negative, 1 -> positive

    wave_form = (float *)malloc(sizeof(float) * SIGNAL_RESOLUTION);
    zero_crossing = (short int *)malloc(sizeof(short int) * SIGNAL_RESOLUTION);
    signal_directions = (short int *)malloc(sizeof(short int) * SIGNAL_RESOLUTION);

    for (index = 0; index < SIGNAL_RESOLUTION; index++) {
        previous_signal_value = sine_wave_generator(index - 1, SIGNAL_RESOLUTION, amplitude, frequency, phase, offset);
        wave_form[index] = sine_wave_generator(index, SIGNAL_RESOLUTION, amplitude, frequency, phase, offset);

        zero_crossing[index] = ((!signbit(wave_form[index])) != !signbit(previous_signal_value));
        signal_directions[index] = wave_form[index] >= 0;
        wave_form[index] = fabs(wave_form[index]);

        // printf("%f, %d\n", wave_form[index], zero_crossing[index]);
    }

    for (int loop = 0; loop < 2 * SIGNAL_RESOLUTION; loop++) {
        index = loop % SIGNAL_RESOLUTION;

        set_direction(index, &direction, zero_crossing);

        printf("index %d, signal %f, direction %d, direction %d, original %f\n",
               index, get_signal(index, wave_form), direction, signal_directions[index], wave_form[index]);
    }

    free(wave_form);
    free(zero_crossing);
    free(signal_directions);

    return 0;
}