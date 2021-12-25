/*
 * PID.h
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#ifndef PID_H_
#define PID_H_

#include "structures.h"

typedef struct __attribute__ ((packed)) {
	float dt;
	float Kp, Ki, Kd;
	float limMinInt, limMaxInt;
	float limMinOutPid, limMaxOutPid;
	/* Derivative low-pass filter time constant */
	float tau;
	float feedForwardCoef;
} stPIDPars_t;

typedef struct __attribute__ ((packed)) {
	float proportional;
	float integral;
	float differential;
	float lastProportional;
	float prevMeasurement;
	float feedForward;
} stPIDVars_t;

typedef struct __attribute__((__packed__)) {
	float consign;
	float control;
	float value;
} stPIDVals_t;

float PIDUpdate(stPIDPars_t* PIDPars, stPIDVars_t* PIDVars, stPIDVals_t* PIDVals);

float PIDUpdateModulo(stPIDPars_t* PIDPars, stPIDVars_t* PIDVars, stPIDVals_t* PIDVals);

#endif /* PID_H_ */
