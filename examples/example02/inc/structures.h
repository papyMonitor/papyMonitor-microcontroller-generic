/*
 * structures.h
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include "chip.h"

#include "enums.h"
#include "defines.h"

#include "PID.h"

/*------------------------------------------------------------------------------------
 *  							Global variables
 *------------------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__)) {
	union {
		struct {

			union {
				struct __attribute__((__packed__)) {
					bool simulSquareCH0:		1;
					bool simulSquareCH1:		1;
					bool simulSquareCH2:		1;
					bool simulSquareCH3:		1;
					bool simulSquareCH4:		1;
					bool wdIMUTurret:			1;
					bool wdCAN: 				1;
					bool res1: 					1;
				};
				uint8_t B0Raw;
			};
			union {
				struct __attribute__((__packed__)) {
					bool ANAButtonsOverrided: 		1;
					bool DIGButtonsOverrided:		1;
					bool GNR_Joy_Overrided:			1;
					bool CMD_Joy_Overrided:			1;
					bool inSVDSightsSimulationMode: 1;
					bool inSCTBoreSighting:			1;
					bool inDNCSBoreSighting:		1;
					bool statusStabreserved1:		1;
				};
				uint8_t B1Raw;
			};

			uint8_t B2Raw;
			uint8_t B3Raw;
		} bits;

		uint32_t raw;
	};
} statusMachine_t;

typedef struct __attribute__((__packed__)) {
	float squareValue;
	float squareValueVelocity;
	float filter;
} simulVals_t;

typedef struct __attribute__((__packed__)) {

	stPIDVars_t	PIDvar[5];
	stPIDVals_t PIDval[5];
	simulVals_t simulVal[5];
	statusMachine_t statusMachine;
} sVars_t;

/*------------------------------------------------------------------------------------
 *  							Global parameters
 *------------------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__)) {

	float table[TABLE_LINES];
	stPIDPars_t	PIDPars[5];

} sPars_t;


/*------------------------------------------------------------------------------------
 *  		Global structure
 *------------------------------------------------------------------------------------*/
typedef struct __attribute__ ((packed, aligned(4))) {
	sPars_t pars;
	sVars_t vars;
} sGlobVarsPars_t;


#endif /* STRUCTURES_H_ */
