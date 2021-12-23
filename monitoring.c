/*
 * monitoring.c
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"
#include "math.h"

#include "monitoring.h"

extern char msgFromHost[];		// defined in uart.c
extern bool messagePending;		// defined in uart.c
extern void sendDataHost( char* message ); // defined in uart.c

extern sVariables_t variables[];
extern const uint8_t nbVariables;

//extern sCommands_t commands[];
//extern const uint8_t nbCommands;

// mapping of ASCII characters to hex values
static const uint8_t hashmap[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //  !"#$%&'
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ()*+,-./
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // 01234567
  0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89:;<=>?
  0x00, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, // @ABCDEFG
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // HIJKLMNO
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // PQRSTUVW
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // XYZ[\]^_
  0x00, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, // `abcdefg
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // hijklmno
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // pqrstuvw
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // xyz{|}~.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // ........
};

/*****************************************************************************
 * Private functions
 ****************************************************************************/
static void getValueFromHex( eDataType_t varType, void* value, char* dataRx ) {

	uint8_t var1;
	uint8_t pVar2[2];
	uint8_t pVar4[4];

	switch ( varType ) {

		// mem: 4 bytes types
		case eComDataType_Float:
		case eComDataType_U32:
		case eComDataType_I32:
			// form of '?XXYWWWWWWWW\0' only
			if ( (dataRx[12] == '\0')) {
				pVar4[0] = (uint8_t)(hashmap[(uint8_t)dataRx[4]] << 4) | hashmap[(uint8_t)dataRx[5]];
				pVar4[1] = (uint8_t)(hashmap[(uint8_t)dataRx[6]] << 4) | hashmap[(uint8_t)dataRx[7]];
				pVar4[2] = (uint8_t)(hashmap[(uint8_t)dataRx[8]] << 4) | hashmap[(uint8_t)dataRx[9]];
				pVar4[3] = (uint8_t)(hashmap[(uint8_t)dataRx[10]] << 4) | hashmap[(uint8_t)dataRx[11]];
				// Store the variable
				memcpy( value, pVar4, 4 );
			}
			break;

		// mem: 2 bytes types
		case eComDataType_U16:
		case eComDataType_I16:
			// form of '?XXYWWWW\0' only
			if ( (dataRx[8] == '\0') ) {
				pVar2[0] = (uint8_t)(hashmap[(uint8_t)dataRx[4]] << 4) | hashmap[(uint8_t)dataRx[5]];
				pVar2[1] = (uint8_t)(hashmap[(uint8_t)dataRx[6]] << 4) | hashmap[(uint8_t)dataRx[7]];
				// Store the variable
				memcpy( value, pVar2, 2 );
			}
			break;

		// mem: 1 byte types A
		case eComDataType_U8:
		case eComDataType_I8:
			// form of '?XXYWW\0' only
			if ( (dataRx[6] == '\0') ) {
				var1 = (uint8_t)(hashmap[(uint8_t)dataRx[4]] << 4) | hashmap[(uint8_t)dataRx[5]];
				*((uint8_t *)value) = var1;
			}
			break;
	}
}

static void setValue( char* dataRx ) {

	uint8_t varIdx;
	eDataType_t varType;

	varIdx = (uint8_t)(hashmap[(uint8_t)dataRx[1]] << 4) | hashmap[(uint8_t)dataRx[2]];

	if ( varIdx < nbVariables ) {

		varType = (eDataType_t)dataRx[3];

		// Value type to store must be the same as the data type
		if ( varType == variables[varIdx].type ) {
			// GetnStore
			getValueFromHex(varType, variables[varIdx].data, dataRx);
			// Call the callback if any
			if ( variables[varIdx].cb != NULL )
				variables[varIdx].cb(varIdx);
		}
	}
}

static void variablesSend( uint32_t index ) {

	char msgString[15];

	uint8_t var1;
	uint8_t pVar2[2];
	uint8_t pVar4[4];

	msgString[0] = eIReportValue;
	sprintf( &msgString[1], "%02X", (int)index );
	msgString[3] = variables[index].type;

	switch ( variables[index].type ) {

		// mem: 4 bytes types
		case eComDataType_Float:
		case eComDataType_U32:
		case eComDataType_I32:
			memcpy( pVar4, variables[index].data, 4 );
			sprintf( &msgString[4], "%02X", pVar4[0] );
			sprintf( &msgString[6], "%02X", pVar4[1] );
			sprintf( &msgString[8], "%02X", pVar4[2] );
			sprintf( &msgString[10], "%02X", pVar4[3] );
			msgString[12] = '\n';
			msgString[13] = '\0';
			break;

		// mem: 2 bytes types
		case eComDataType_U16:
		case eComDataType_I16:
			memcpy( pVar2, variables[index].data, 2 );
			sprintf( &msgString[4], "%02X", pVar2[0] );
			sprintf( &msgString[6], "%02X", pVar2[1] );
			msgString[8] = '\n';
			msgString[9] = '\0';
			break;

		// mem: 1 byte types A
		case eComDataType_U8:
		case eComDataType_I8:
			var1 = *((uint8_t *)variables[index].data);
			sprintf( &msgString[4], "%02X", var1 );
			msgString[6] = '\n';
			msgString[7] = '\0';
			break;
	}

	// Send result
	sendDataHost( msgString );
}

/*
 * Seek and send from the sVariables_t struct for the next variable to report.
 * Each time this function is called, the index is set to the next variable
 * whose report value is set to eReportOn and send it. 
 * When arrived at the end of struct, go to the beginning as a loop.
 * Detect is no variables have their report value to eReportOn (no endless loop)
 */
static void variablesSendNext( void ) {

	static uint32_t index = 0;
	static uint32_t lastIndex = 0;
	bool indexFound = false;

	// Find next index
	while ( true ) {

		if ( ++index == nbVariables )
			index = 0;

		if ( variables[index].report == eReportOn) {
			indexFound = true;
			break;
		}

		if ( index == lastIndex )
			break;
	}

	if ( indexFound ) {
		lastIndex = index;
		variablesSend( index );
	}
}

static void setVariablesReporting( char* dataRx, bool set ) {

	uint8_t varIdx = (uint8_t)(hashmap[(uint8_t)dataRx[1]] << 4) | hashmap[(uint8_t)dataRx[2]];
	uint8_t nbIndexes = (uint8_t)(hashmap[(uint8_t)dataRx[4]] << 4) | hashmap[(uint8_t)dataRx[5]];

	for (uint32_t i=varIdx; i<varIdx+nbIndexes; i++)
		if ( i < nbVariables )
			if (variables[i].report != eNeverReport)
				variables[i].report = set ? eReportOn : eReportOff;
}
 
/*****************************************************************************
 * Public function
 ****************************************************************************/
bool setVariablesReportingAllOn( uint8_t dummy ) {

	for (uint32_t i=0; i<nbVariables; i++)
		if (variables[i].report != eNeverReport)
			variables[i].report = eReportOn;

	return false;
}

bool setVariablesReportingAllOff( uint8_t dummy ) {

	for (uint32_t i=0; i<nbVariables; i++)
		if (variables[i].report != eNeverReport)
			variables[i].report = eReportOff;

	return false;
}

/*
 * Must be called Every X microsecond
 * Report variables
 */
void update( void ) {

	// Detect if a msg is received and execute it
	if ( messagePending ) {

		messagePending = false;

		switch ( (eHostMonitoringCmd_t)msgFromHost[0] ) {

			case eSetValue:
				setValue( msgFromHost );
				break;

			case eReportValueOn:
				setVariablesReporting( msgFromHost, true );
				break;

			case eReportValueOff:
				setVariablesReporting( msgFromHost, false );
				break;

			default:
				break;
		}
	}

	// Send next monitoring variable
	variablesSendNext();
}

