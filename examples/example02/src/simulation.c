/*
 * simulation.c
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#include "structures.h"
#include "arithmetics.h"

// All the system variables
extern sGlobVarsPars_t GVP;


// Control is in [-1, 1]
void systemSimulation(uint8_t idx) {

	static uint32_t counter[5] = {0,0,0,0,0};
	float filtered;
	float filt = GVP.vars.simulVal[idx].filter;

	filtered = filt + (1.0f - filt) * GVP.vars.PIDval[idx].control;

	GVP.vars.PIDval[idx].value = addModulo180( GVP.vars.PIDval[idx].value, 0.22f * filtered );

	if ( (GVP.vars.statusMachine.bits.B0Raw & (1<<idx)) >> idx) {
		counter[idx]++;
		if (counter[idx] >= GVP.vars.simulVal[idx].squareValueVelocity) {
			counter[idx] = 0;
			GVP.vars.simulVal[idx].squareValue = -GVP.vars.simulVal[idx].squareValue;
			GVP.vars.PIDval[idx].consign = GVP.vars.simulVal[idx].squareValue;
		}
	}
}
