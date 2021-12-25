/*
 * nv.c
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#include <string.h>

#include "defines.h"
#include "enums.h"
#include "structures.h"

#include "board.h"

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/
void loadNVarsFromEEPROM( sPars_t* params )
{
	EEPROM_Read( EEPROM_START_PAGE_NVARS, (uint8_t *)params, sizeof(sPars_t) );
}

void saveNVarsToEEPROM( sPars_t* params )
{
	EEPROM_Write( EEPROM_START_PAGE_NVARS, (uint8_t *)params, sizeof(sPars_t) );
}

