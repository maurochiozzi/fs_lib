#ifndef NAVIGATION_H

#define NAVIGATION_H

#include "../device/device.h"
#include "../environment/environment.h"
#include "../space/space.h"

enum Reference { BEACON,
                 SENSOR };

void buildSegmentsMatrix(Device *device, Environment *environment,
                         Segment *segments_matrix, int reference);

void estimateMagneticSensorPosition(Device *device, Environment *environment);
void estimateMagneticSensorsPositions(Device *device, Environment *environment,
                                      Segment *segments_matrix);

void estimateMagneticBeaconSourcePosition(Device *device, Environment *environment);
void estimateBeaconsPositions(Device *device, Environment *environment,
                              Segment *segments_matrix);

void calculatePositionByTrilateration(Segment *segments, int available_references,
                                      Coordinate *position);
#endif