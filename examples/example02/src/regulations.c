/*
 * regulations.c
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#include "lpc_types.h"
#include "structures.h"
#include "enums.h"
#include "PID.h"
#include "string.h"
#include "arithmetics.h"

//#include "helperFunctions.h"

/*****************************************************************************
 * Public declaration
 *****************************************************************************/
// All the system variables
extern sGlobVarsPars_t GVP;

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 *  \brief Elevation PID regulation
 *
 *  Do the elevation (**cannon**) regulation with the call of the PID function. Add a feedforward to the consign
 *
 * @param[in] vars System parameters structure
 * @return the SVD control value
 *
 **/
void regulation( uint8_t idx ) {

	GVP.vars.PIDvar[idx].feedForward = 0.0f;

	GVP.vars.PIDval[idx].control =
			PIDUpdate(&GVP.pars.PIDPars[idx], &GVP.vars.PIDvar[idx], &GVP.vars.PIDval[idx] );
}



