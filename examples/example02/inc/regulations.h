/*
 * regulations.h
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#ifndef REGULATIONS_H_
#define REGULATIONS_H_

#include "lpc_types.h"

/*
 * Two separates functions because not reentrant
 */
float elevationRegulation( void );
float azimuthRegulation( void );

#endif /* REGULATIONS_H_ */
