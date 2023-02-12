#include "magnetic_sensor.h"

#include "../indexer/indexer.h"
#include "../space/space.h"
#include "../spectrum/spectrum.h"

void initMagneticSensor(MagneticSensor sensor, int i2c) {
    // init sensor buffer
    sensor.samples = (float *)malloc(sizeof(float) * 2 * sensor.sample_size);
    sensor.indexer.sample_size = sensor.sample_size;

    // init sensor connection
}

int addSample(MagneticSensor sensor, Vector vector) {
    const float sample = norm(vector);

    sensor.samples[sensor.indexer.sample] = sample;

    updateSpectrum(sensor.spectrum, sample, sensor.samples, sensor.indexer);

    return incrementIndex(sensor.indexer);
}

void getMagneticSignalStrength(MagneticSensor sensor,
                               Beacon *beacons,
                               MagneticSignalStrength *magnetic_signal_strength,
                               int amount_of_beacons,
                               int reference) {
    magnetic_signal_strength = (MagneticSignalStrength *)malloc(
        sizeof(MagneticSensor) * amount_of_beacons);

    for (int index = 0; index < amount_of_beacons; index++) {
        magnetic_signal_strength[index].reference =
            reference == BEACON ? beacons[index].position : sensor.device_position;

        magnetic_signal_strength[index].intensity =
            getIntensity(sensor.spectrum, beacons[index].spectrum_window,
                         sensor.indexer);
    }
}

/**
 * This function will reset the cache of the previous filled cache.
 */
void resetSampleCache(MagneticSensor sensor) {
    const int previous_cache_index = (sensor.indexer.buffer + 1) % 2;

    for (int index = sensor.indexer.buffer * sensor.sample_size;
         index < (sensor.indexer.buffer + 1) * sensor.sample_size; index++) {
        sensor.samples[index] = 0.0;
    }
}
