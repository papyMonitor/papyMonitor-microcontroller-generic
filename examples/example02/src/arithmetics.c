/*
 * arithmetics.c
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#include <stdint.h>
#include "defines.h"
#include "enums.h"
#include "structures.h"


// All the system variables
extern sGlobVarsPars_t GVP;

/** \brief Modulo 180 operation
 *
 * @param[in] angle between -360[ and +360]
 * @return modulo( angle ) between -180[ and +180]
 */
static float c180(float angle) {
	if ( angle > 180.0) angle -= 360.0f;
	if ( angle <= -180.0) angle += 360.0f;
	return angle;
}

/** \brief Circular subtraction
 *
 * @param[in] angle1 between -180[ and +180]
 * @param[out] angle2 between -180[ and +180]
 * @return modulo( angle1 - angle2 ) between -180[ and +180]
 */
float subModulo180(float angle1, float angle2) {
	return c180(angle1 - angle2);
}

/** \brief Circular addition
 *
 * @param[in] angle1 between -180[ and +180]
 * @param[out] angle2 between -180[ and +180]
 * @return modulo( angle1 + angle2 ) between -180[ and +180]
 */
float addModulo180(float angle1, float angle2) {
	return c180(angle1 + angle2);
}
