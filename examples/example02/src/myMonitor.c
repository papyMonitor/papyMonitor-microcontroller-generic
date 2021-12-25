/*
 * myMonitor.c
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#include "monitoring.h"

#include "string.h"
#include "structures.h"

#include "nv.h"

// All the system variables
extern sGlobVarsPars_t GVP;

// dummy variable for keeping indexes clean
static char dummy;

/******************************************************************
 * 						callBacks
 *******************************************************************/
static bool saveParamToFlash( uint8_t idx )
{
	saveNVarsToEEPROM( &GVP.pars );
	return false;
}

sVariables_t variables[] = {

	{ (void *) &GVP.vars.PIDvar[0].proportional, eComDataType_Float, eReportOff, NULL }, //0
	{ (void *) &GVP.vars.PIDvar[0].integral, 	 eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDvar[0].differential, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDvar[0].feedForward,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDval[0].consign,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDval[0].control,  eComDataType_Float, eReportOff, NULL },//5
	{ (void *) &GVP.vars.simulVal[0].squareValue,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.simulVal[0].squareValueVelocity,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.simulVal[0].filter,  eComDataType_Float, eReportOff, NULL },

	{ (void *) &GVP.vars.PIDval[0].value,  eComDataType_Float, eReportOff, NULL },

	{ (void *) &GVP.pars.PIDPars[0].Kp, eComDataType_Float, eReportOff, NULL },//10
	{ (void *) &GVP.pars.PIDPars[0].Ki, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[0].Kd, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[0].limMinInt, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[0].limMaxInt, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[0].limMinOutPid, eComDataType_Float, eReportOff, NULL },//15
	{ (void *) &GVP.pars.PIDPars[0].limMaxOutPid, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[0].tau, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[0].feedForwardCoef, eComDataType_Float, eReportOff, NULL },
	{ (void *) &dummy, eComDataType_U8, eNeverReport, NULL },

	{ (void *) &GVP.vars.PIDvar[1].proportional, eComDataType_Float, eReportOff, NULL }, //20
	{ (void *) &GVP.vars.PIDvar[1].integral, 	 eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDvar[1].differential, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDvar[1].feedForward,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDval[1].consign,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDval[1].control,  eComDataType_Float, eReportOff, NULL },//25
	{ (void *) &GVP.vars.simulVal[1].squareValue,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.simulVal[1].squareValueVelocity,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.simulVal[1].filter,  eComDataType_Float, eReportOff, NULL },

	{ (void *) &GVP.vars.PIDval[1].value,  eComDataType_Float, eReportOff, NULL },

	{ (void *) &GVP.pars.PIDPars[1].Kp, eComDataType_Float, eReportOff, NULL },//30
	{ (void *) &GVP.pars.PIDPars[1].Ki, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[1].Kd, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[1].limMinInt, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[1].limMaxInt, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[1].limMinOutPid, eComDataType_Float, eReportOff, NULL },//35
	{ (void *) &GVP.pars.PIDPars[1].limMaxOutPid, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[1].tau, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[1].feedForwardCoef, eComDataType_Float, eReportOff, NULL },
	{ (void *) &dummy, eComDataType_U8, eNeverReport, NULL },

	{ (void *) &GVP.vars.PIDvar[2].proportional, eComDataType_Float, eReportOff, NULL },//40
	{ (void *) &GVP.vars.PIDvar[2].integral, 	 eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDvar[2].differential, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDvar[2].feedForward,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDval[2].consign,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDval[2].control,  eComDataType_Float, eReportOff, NULL },//45
	{ (void *) &GVP.vars.simulVal[2].squareValue,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.simulVal[2].squareValueVelocity,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.simulVal[2].filter,  eComDataType_Float, eReportOff, NULL },

	{ (void *) &GVP.vars.PIDval[2].value,  eComDataType_Float, eReportOff, NULL },

	{ (void *) &GVP.pars.PIDPars[2].Kp, eComDataType_Float, eReportOff, NULL },//50
	{ (void *) &GVP.pars.PIDPars[2].Ki, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[2].Kd, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[2].limMinInt, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[2].limMaxInt, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[2].limMinOutPid, eComDataType_Float, eReportOff, NULL },//55
	{ (void *) &GVP.pars.PIDPars[2].limMaxOutPid, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[2].tau, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[2].feedForwardCoef, eComDataType_Float, eReportOff, NULL },
	{ (void *) &dummy, eComDataType_U8, eNeverReport, NULL },

	{ (void *) &GVP.vars.PIDvar[3].proportional, eComDataType_Float, eReportOff, NULL },//60
	{ (void *) &GVP.vars.PIDvar[3].integral, 	 eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDvar[3].differential, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDvar[3].feedForward,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDval[3].consign,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDval[3].control,  eComDataType_Float, eReportOff, NULL },//65
	{ (void *) &GVP.vars.simulVal[3].squareValue,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.simulVal[3].squareValueVelocity,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.simulVal[3].filter,  eComDataType_Float, eReportOff, NULL },

	{ (void *) &GVP.vars.PIDval[3].value,  eComDataType_Float, eReportOff, NULL },

	{ (void *) &GVP.pars.PIDPars[3].Kp, eComDataType_Float, eReportOff, NULL },//70
	{ (void *) &GVP.pars.PIDPars[3].Ki, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[3].Kd, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[3].limMinInt, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[3].limMaxInt, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[3].limMinOutPid, eComDataType_Float, eReportOff, NULL },//75
	{ (void *) &GVP.pars.PIDPars[3].limMaxOutPid, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[3].tau, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[3].feedForwardCoef, eComDataType_Float, eReportOff, NULL },
	{ (void *) &dummy, eComDataType_U8, eNeverReport, NULL },

	{ (void *) &GVP.vars.PIDvar[4].proportional, eComDataType_Float, eReportOff, NULL },//80
	{ (void *) &GVP.vars.PIDvar[4].integral, 	 eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDvar[4].differential, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDvar[4].feedForward,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDval[4].consign,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.PIDval[4].control,  eComDataType_Float, eReportOff, NULL },//85
	{ (void *) &GVP.vars.simulVal[4].squareValue,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.simulVal[4].squareValueVelocity,  eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.vars.simulVal[4].filter,  eComDataType_Float, eReportOff, NULL },

	{ (void *) &GVP.vars.PIDval[4].value,  eComDataType_Float, eReportOff, NULL },

	{ (void *) &GVP.pars.PIDPars[4].Kp, eComDataType_Float, eReportOff, NULL },//90
	{ (void *) &GVP.pars.PIDPars[4].Ki, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[4].Kd, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[4].limMinInt, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[4].limMaxInt, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[4].limMinOutPid, eComDataType_Float, eReportOff, NULL },//95
	{ (void *) &GVP.pars.PIDPars[4].limMaxOutPid, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[4].tau, eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.PIDPars[4].feedForwardCoef, eComDataType_Float, eReportOff, NULL },
	{ (void *) &dummy, eComDataType_U8, eNeverReport, NULL },

	{ (void *) &GVP.pars.table[0], eComDataType_Float, eReportOff, NULL },// 100
	{ (void *) &GVP.pars.table[1], eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.table[2], eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.table[3], eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.table[4], eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.table[5], eComDataType_Float, eReportOff, NULL },// 105
	{ (void *) &GVP.pars.table[6], eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.table[7], eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.table[8], eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.table[9], eComDataType_Float, eReportOff, NULL },
	{ (void *) &GVP.pars.table[10], eComDataType_Float, eReportOff, NULL },// 110
	{ (void *) &GVP.pars.table[11], eComDataType_Float, eReportOff, NULL },
	{ (void *) &dummy, eComDataType_U8, eNeverReport, NULL },
	{ (void *) &dummy, eComDataType_U8, eNeverReport, NULL },
	{ (void *) &dummy, eComDataType_U8, eNeverReport, NULL },

	{ (void *) &GVP.vars.statusMachine.bits.B0Raw, eComDataType_U8, eReportOff, NULL },// 115
	{ (void *) &GVP.vars.statusMachine.bits.B1Raw, eComDataType_U8, eReportOff, NULL },
	{ (void *) &GVP.vars.statusMachine.bits.B2Raw, eComDataType_U8, eReportOff, NULL },
	{ (void *) &GVP.vars.statusMachine.bits.B3Raw, eComDataType_U8, eReportOff, NULL },

	// Commands (never report a command value)
	{ (void *) &dummy, eComDataType_U8, eNeverReport, saveParamToFlash },
	// Helper functions defined in monitoring.c
	{ (void *) &dummy, eComDataType_U8, eNeverReport, setVariablesReportingAllOn },// 120
	{ (void *) &dummy, eComDataType_U8, eNeverReport, setVariablesReportingAllOff },
};
const uint8_t nbVariables = sizeof( variables ) / sizeof( sVariables_t );

