# papyMonitor generic microcontrollers

The files **monitoring.c** and **monitoring.h** are the mandatory files to add to the embedded project. These files must not be modified uykwyad (uykwyad = until you know what you are doing)


Let's take a look to **monitoring.h**:

```c
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
```

There are enum definitions that are used by **monitoring.c** file and the **sVariables_t** structure. The **sVariables_t** structure is defined in your project and contains the variables to report/edit.
The **update** function is a function that you have to call every X (micro or milli) seconds for the variables reporting. One value is reported at a time. This function check also if a command is arrived and execute it.


Let's take a look to the beginning of **monitoring.c**:
```c
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
```

