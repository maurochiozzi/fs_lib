#ifndef MOCK_H
#define MOCK_H

#include "../environment/environment.h"
#include "../space/space.h"

/**
 * @brief Mocks a magnetic field in an environment given a Coordinate reference and a timestamp.
 *
 * @param environment The Environment to calculate the magnetic field for.
 * @param reference The Coordinate that will be used to calculate the magnetic field.
 * @param timestamp The timestamp that will be used to calculate the magnetic field.
 *
 * @return Returns the calculated magnetic field in the environment.
 */
float mockEnvironmentMagneticField(Environment *environment,
                                   Coordinate *reference, float timestamp);

#endif