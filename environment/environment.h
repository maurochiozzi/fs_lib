/**
 * @file environment.h
 * @brief This header file contains the functions and structures to manage an environment.
 */

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "../beacon/beacon.h"
#include "../space/space.h"

/**
 * @brief Represents an environment.
 */
typedef struct
{
    /**
     * @brief An array of Coordinates that define the environment's edges.
     */
    Coordinate *edges;

    /**
     * @brief The amount of edges that define the environment.
     */
    int amount_of_edges;

    /**
     * @brief An array of beacons that are placed in the environment.
     */
    Beacon *beacons;

    /**
     * @brief The amount of beacons in the environment.
     */
    int amount_of_beacons;

    /**
     * @brief The product of all initialized struct members to validate initialization of the environment.
     */
    int check_prd;

    /**
     * @brief The sum of all initialized struct members to validate initialization of the environment.
     */
    int check_sum;

    /**
     * @brief A boolean flag to indicate if the environment has been initialized.
     */
    int initialized;

} Environment;

/**
 * @brief Initializes an Environment structure.
 *
 * @param environment The Environment structure to be initialized.
 * @param beacons An array of Beacons that are placed in the environment.
 * @param edges An array of Coordinates that define the environment's edges.
 * @param amount_of_beacons The amount of Beacons in the environment.
 * @param amount_of_edges The amount of Coordinates that define the environment's edges.
 */
void initEnvironment(Environment *environment, Beacon *beacons,
                     Coordinate *edges, int amount_of_beacons, int amount_of_edges);

/**
 * @brief Checks if an Environment structure has been initialized.
 *
 * @param environment The Environment structure to be checked for initialization.
 *
 * @return Returns 1 if the structure is initialized and 0 otherwise.
 */
int isEnvironmentInitialized(Environment *environment);

/**
 * @brief Checks if a point is inside an Environment structure.
 *
 * @param environment The Environment structure to check the point against.
 * @param point The Coordinate to check if is inside the environment.
 *
 * @return Returns 1 if the point is inside the environment and 0 otherwise.
 */
int isPointInsideEnvironment(Environment *environment, Coordinate *point);

#endif
