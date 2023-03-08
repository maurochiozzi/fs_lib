// #include <stdio.h>
// #include <stdlib.h>

// #include "beacon/beacon.h"
// #include "device/device.h"
// #include "magnetic_sensor/magnetic_sensor.h"
// #include "space/space.h"
// #include "station/station.h"

// Device device;
// Device *previous_positions;

// int previous_position_index;
// const int device_position_history_size = 10;

// // stores beacons frequency, magnetic moment and location
// int amount_of_beacons;

// Beacon *beacons;

// // An array of nodes will define a environment boundary
// #define MAX_ENVIRONMENT_NODES 3

// Coordinate *environment;

// // stores magnetic data
// const int sample_size = 110;
// const int sample_rate = 220;  // Hz

// const int amount_of_magnetic_sensor = 3;
// MagneticSensor magnetic_sensors[3];

// int init();
// int initPreviousPositionArray(Device *previous_positions);
// int initBeacons(Beacon *beacons);
// int initEnvironments(Coordinate *environment);

// int initSensors();

// int surveyBeacons(Beacon *beacons, Coordinate *environment);

// int acquireDevicePosition();

// int main(void) {
//     init();

//     surveyBeacons(beacons, environment);

//     acquireDevicePosition();

//     return 0;
// }

// int init() {
//     printf("Initializing...\n");

//     initDevice(&device);

//     printf("%0.2f,%0.2f,%0.2f\n",
//            device.position.x,
//            device.position.y,
//            device.position.z);

//     initPreviousPositionArray(previous_positions);

//     initBeacons(beacons);
//     initEnvironments(environment);
//     initSensors();

//     return 0;
// }

// int initPreviousPositionArray(Device *previous_positions) {
//     previous_position_index = 0;

//     previous_positions = (Device *)malloc(device_position_history_size * sizeof(Device));

//     // its not required to init it with positions at zero

//     return 0;
// }

// int initBeacons(Beacon *beacons) {
//     amount_of_beacons = requestStationNumberOfBeacons();

//     beacons = (Beacon *)malloc(amount_of_beacons * sizeof(Beacon));

//     requestBeaconsInformation(beacons, amount_of_beacons);

//     for (int index = 0; index < amount_of_beacons; index++) {
//         initBeacon(beacons[index], sample_rate, sample_size);
//     }

//     return 0;
// }

// int initEnvironments(Coordinate *environment) {
//     environment = (Coordinate *)malloc(MAX_ENVIRONMENT_NODES * sizeof(Coordinate));

//     // doesn't need to init coordinates since the environment data
//     // will be fetched from station

//     return 0;
// }

// int initSensors() {
//     for (int index = 0; index < amount_of_magnetic_sensor; index++) {
//         initMagneticSensor(magnetic_sensors[index], 0);
//     }

//     return 0;
// }

// int surveyBeacons(Beacon *beacons, Coordinate *environment) {
//     printf("Surveying beacons...\n");

//     for (int sample = 0; sample < sample_size; sample++) {
//         for (int index = 0; index < amount_of_magnetic_sensor; index++) {
//             Vector vector = sampleMagneticSignal(magnetic_sensors[index]);
//             addSampleMagneticSignal(magnetic_sensors[index], vector);
//         }
//     }

//     for (int sensor_index = 0; sensor_index < amount_of_magnetic_sensor; sensor_index++) {
//         for (int beacon_index = 0; beacon_index < amount_of_beacons; beacon_index++) {
//         }
//     }

//     return 0;
// }

// int acquireDevicePosition() {
//     printf("Acquiring position...\n");

//     while (1) {
//         // while (magnetic_intensity_samples < MAGNETIC_SAMPLE_SIZE) {
//         //     sample_magnetic_space(&magnetic_space_samples, magnetic_intensity_samples);

//         //     update_magnetic_space_spectrum(&magnetic_space_samples);
//         // }

//         // estimate_position();

//         // send_position();
//     }

//     return 0;
// }
