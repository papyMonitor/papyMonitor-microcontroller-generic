/*
 * PID.c
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#include "structures.h"
#include "arithmetics.h"
#include "PID.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
float PID(stPIDPars_t* PIDPars, stPIDVars_t* PIDVars, stPIDVals_t* PIDVals, float error) {

	/*
	* Proportional
	*/
	PIDVars->proportional = PIDPars->Kp * error;

	/*
	* Integral
	*/
    PIDVars->integral = PIDVars->integral +
    	0.5f * PIDPars->Ki * PIDPars->dt * (PIDVars->proportional + PIDVars->lastProportional);

	/* Anti-wind-up via integrator clamping */
    if (PIDVars->integral > PIDPars->limMaxInt) {
    	PIDVars->integral = PIDPars->limMaxInt;
    } else {
    	if (PIDVars->integral < PIDPars->limMinInt)
    		PIDVars->integral = PIDPars->limMinInt;
    }

	/*
	* Derivative (band-limited differentiator)
	*/
	/* Note: derivative on measurement, therefore minus sign in front of equation! */
    PIDVars->differential = -(2.0f * PIDPars->Kd * (PIDVals->value - PIDVars->prevMeasurement)
                        + (2.0f * PIDPars->tau - PIDPars->dt) * PIDVars->differential)
                        / (2.0f * PIDPars->tau + PIDPars->dt);

	/* Store error and measurement for later use */
    PIDVars->lastProportional = PIDVars->proportional;
    PIDVars->prevMeasurement = PIDVals->value;

    PIDVals->control = PIDVars->proportional + PIDVars->integral + PIDVars->differential;

    if ( PIDVals->control < PIDPars->limMinOutPid ) {
    	PIDVals->control = PIDPars->limMinOutPid;
    }

	if ( PIDVals->control > PIDPars->limMaxOutPid ) {
		PIDVals->control = PIDPars->limMaxOutPid;
	}

	/* Return controller output */
    return PIDVals->control;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/
float PIDUpdate(stPIDPars_t* PIDPars, stPIDVars_t* PIDVars, stPIDVals_t* PIDVals) {

	float error;
	/*
	* Error signal
	*/
	error = PIDVals->consign - PIDVals->value;

	return PID(PIDPars, PIDVars, PIDVals, error);
}

float PIDUpdateModulo180(stPIDPars_t* PIDPars, stPIDVars_t* PIDVars, stPIDVals_t* PIDVals) {

	float error;
	/*
	* Error signal
	*/
	error = subModulo180(PIDVals->consign, PIDVals->value);

	return PID(PIDPars, PIDVars, PIDVals, error);
}
