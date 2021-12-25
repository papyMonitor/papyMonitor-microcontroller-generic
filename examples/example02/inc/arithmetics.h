/*
 * arithmetics.h
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#ifndef ARITHMETICS_H_
#define ARITHMETICS_H_

/*
 * angle1 and angle2 between -180 and +180
 */
float subModulo180(float angle1, float angle2);

/*
 * angle1 and angle2 between -180 and +180
 */
float addModulo180(float angle1, float angle2);

/*
 * EVPU Angle convertion in/out
 */
float EVPUSCTValueToElevPos( uint16_t value );
float EVPUDNCSValueToElevPos( uint16_t value );
float EVPUDNCSValueToAzimPos( uint16_t value );

uint16_t elevPosToEVPUSCTValue( float position );
uint16_t elevPosToEVPUDNCSValue( float position );
uint16_t azimPosToEVPUDNCSValue( float position );

#endif /* ARITHMETICS_H_ */
