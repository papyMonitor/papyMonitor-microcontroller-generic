/*
 * nv.h
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#ifndef NV_H_
#define NV_H_

#include "structures.h"

void loadNVarsFromEEPROM( sPars_t* params );
void saveNVarsToEEPROM( sPars_t* params );

#endif /* NV_H_ */
