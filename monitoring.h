/*
 * monitoring.h
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#ifndef MONITORING_H_
#define MONITORING_H_

#include "stdint.h"
#include "stdbool.h"

// Meaning codes
typedef enum {
    // Commands from monitor to target;
    eSetValue = '#',
    eReportValueOn = '?',
    eReportValueOff = '!',

    // Messages from target to monitor
    eIReportValue =        ':',
    eIReportTextConsole =  '>',
} eHostMonitoringCmd_t;

typedef enum {
	eComDataType_Float		= 'f', // 8 chars
	eComDataType_U32 		= 'W', // 8 chars
	eComDataType_I32 		= 'w', // 8 chars
	eComDataType_U16 		= 'I', // 4 chars
	eComDataType_I16 		= 'i', // 4 chars
	eComDataType_U8 		= 'B', // 2 chars
	eComDataType_I8 		= 'b', // 2 chars
} eDataType_t;

typedef enum {
	eNeverReport,
	eReportOn,
	eReportOff,
} eReportType_t;

typedef struct {
	void* data;		// Pointer to the data
	eDataType_t type;
	eReportType_t report;
	bool (*cb)(uint8_t); // Callback with index of the variable in the table as argument
} sVariables_t;


// Optional helper functions
bool setVariablesReportingAllOn( uint8_t dummy );
bool setVariablesReportingAllOff( uint8_t dummy );

/*
 * Must be called Every X microsecond
 * Report variables
 */
void update( void );

#endif /* MONITORING_H_ */
