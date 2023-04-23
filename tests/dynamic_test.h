

#ifndef DYNAMIC_TEST
#define DYNAMIC_TEST

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../device/device.h"
#include "../magnetic_sensor/magnetic_sensor.h"
#include "../minunit/minunit.h"
#include "../mock/mock.h"
#include "../navigation/navigation.h"

#define OUTPUT_RESULTS 0

static char *dynamic_device_beacon_survey() {
    // Auxiliary variables to help during simulations
    int with_error = 0;

    MagneticSensor *sensor;
    float device_heading = 45.0;

    float environment_magnetic_field_intensity;

    const int amount_of_buffers = 2;
    const int sample_size = 110;
    const int sample_rate = 220;

    float delta_time = 1.0 / sample_rate;
    float timestamp = 0.0;

    const float error_check = 0.001;
    float norm_est;
    float norm_real;

    Coordinate origin = {0};

    // Device velocity, in m/s
    Vector velocity_step = {.x = -0.02, .y = 0.03, .z = 0};
    Vector device_velocity = {.x = 0.0, .y = 0.0, .z = 0};
    Vector device_position_offset = {0};
    Coordinate final_device_position = {0};

    // Mocked environment will be used to mock beacons and get the magnetic
    // field intensity from them.
    Environment mocked_environment = {0};
    Beacon *mocked_beacons;

    Coordinate mocked_beacons_positions[] = {
        [0] = {.x = -2.0, .y = -1.0, .z = 0},
        [1] = {.x = -1.5, .y = +1.5, .z = 0},
        [2] = {.x = +2.5, .y = +0.5, .z = 0},
        [3] = {.x = +1.5, .y = -1.5, .z = 0}};

    // Define device and its sensors
    Device device = {0};

    Baseline baseline = {0};

    const int amount_of_magnetic_sensors = 3;
    MagneticSensor *device_sensors;

    Coordinate device_sensors_position[] = {
        [0] = {.x = -0.5, .y = -0.2886751345948, .z = 0},
        [1] = {.x = +0.0, .y = +0.5773502691869, .z = 0},
        [2] = {.x = +0.5, .y = -0.2886751345948, .z = 0}};

    const int sensors_i2c_address[] = {0xE1, 0xE2, 0xE3};

    // Define environment with its beacons. No edges will be used at this moment
    Environment environment = {0};

    const int amount_of_beacons = 4;
    Beacon *beacons;

    const float beacons_source_magnetic_moment = 6.999 * pow(10, -8);
    const float beacons_source_frequency[] = {36, 40, 80, 52};

    const int amount_of_edges = 10;
    Coordinate *edges;

    // Initialize sensors, devices, beacons and environment
    device_sensors = (MagneticSensor *)malloc(sizeof(MagneticSensor) * amount_of_magnetic_sensors);

    for (int index = 0; index < amount_of_magnetic_sensors; index++) {
        device_sensors[index].device_position = device_sensors_position[index];

        initMagneticSensor(&device_sensors[index],
                           sample_size, amount_of_buffers,
                           sensors_i2c_address[index]);
    }

    baseline.initial_point = &device_sensors[0].local_position;
    baseline.ending_point = &device_sensors[2].local_position;

    initDevice(&device, device_sensors, amount_of_magnetic_sensors);
    setBaseline(&device, &baseline);

    // Check if device was correctly initialized
    mu_assert("error, beacon survey - device initialization",
              isDeviceInitialized(&device) == 1);

    beacons = (Beacon *)malloc(sizeof(Beacon) * amount_of_beacons);
    mocked_beacons = (Beacon *)malloc(sizeof(Beacon) * amount_of_beacons);

    for (int index = 0; index < amount_of_beacons; index++) {
        initBeacon(&beacons[index],
                   beacons_source_magnetic_moment,
                   beacons_source_frequency[index],
                   sample_rate, sample_size);

        initBeacon(&mocked_beacons[index],
                   beacons_source_magnetic_moment,
                   beacons_source_frequency[index],
                   sample_rate, sample_size);

        mocked_beacons[index].magnetic_field_source.position = mocked_beacons_positions[index];
    }

    initEnvironment(&environment, beacons, edges, amount_of_beacons, amount_of_edges);
    initEnvironment(&mocked_environment, mocked_beacons, edges, amount_of_beacons, amount_of_edges);

    // Check if environment was correctly initialized
    mu_assert("error, beacon survey - environment initialization",
              isEnvironmentInitialized(&environment) == 1);

    // start surveying beacons
    mockBeaconSurveyRun(
        &device, &environment,
        &mocked_environment,
        sample_rate, sample_size, with_error);

    estimateMagneticBeaconSourcePosition(&device, &environment);

    // check beacons surveyed

    for (int index = 0; index < amount_of_beacons; index++) {
        mu_assert("beacon survey error",
                  calculatePositionError(&mocked_beacons[index].magnetic_field_source.position,
                                         &beacons[index].magnetic_field_source.position) < error_check);
    }

    if (OUTPUT_RESULTS == 1) {
        printf("interation, vx, vy, vz, attitude_x, attitude_y, attitude_z, heading, heading_error, est_position_x, est_position_y, est_position_z, real_position_x, real_position_y, real_position_z, norm_est, norm_real, norm_error, error\r\n");
    }

    for (int velocity_increase = 1; velocity_increase < 10; velocity_increase++) {
        device_velocity.x += velocity_step.x;
        device_velocity.y += velocity_step.y;
        device_velocity.z += velocity_step.z;

        // final_device_position.x = 0;
        // final_device_position.y = 0;
        // final_device_position.z = 0;

        device_position_offset.x = 0;
        device_position_offset.y = 0;
        device_position_offset.z = 0;

        for (int interation = 0; interation < 50; interation++) {
            // Start sampling environment magnetic field from the new position
            mockMagneticFieldSampleRun(
                &device, device_velocity, device_heading,
                &final_device_position, &device_position_offset,
                &environment, sample_rate, sample_size, with_error);

            // Update device position with sensors estimations
            updateDevicePosition(&device, &environment);

            norm_est = euclideanDistance2(&origin, &device.position);
            norm_real = euclideanDistance2(&origin, &final_device_position);

            if (OUTPUT_RESULTS == 1) {
                printf("%02d, ", interation);

                printVector(&device_velocity, 1);
                printVector(&device.attitude, 1);
                printf("%+07.3f, %+07.3f, ", device.heading,
                       calculateError(device_heading,
                                      device.heading) *
                           100);

                printCoordinate(&device.position, 1);
                printCoordinate(&final_device_position, 1);

                printf("%+07.3f, %+07.3f, %+07.3f, %+07.3f\n", norm_est, norm_real,
                       calculatePositionError(&final_device_position, &device.position),
                       calculateError(norm_real, norm_est) * 100);
            }
        }
    }

    // Reset global variables and free variables
    phases_initialized = 0;
    amount_of_phases = 0;

    free(phases);
    free(device_sensors);
    free(beacons);

    return 0;
}

/**
 * @brief Runs all dynamic tests
 *
 * @return char* NULL
 */
static char *all_dynamic_tests() {
    mu_run_test(dynamic_device_beacon_survey);

    return 0;
}

#endif