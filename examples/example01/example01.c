/*
 * exampleCode.c
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 *
 * THIS IS A BASIC FILE JUST TO SHOW HOW TO
 * DEFINE AND INITIALIZE THE VARS NEEDED BY monitoring.c
 * THIS FILE IS NOT OPTIMIZED AT ALL
 */

#include "monitoring.h"

#include "string.h"
#include "structures.h"

// Variables the project is using
float myFloat1, myFloat2;

// Create the variables[] var
// In it you put the variables that you want to report
// Each line contains 4 fields
// 1. The variable pointer
// 2. The variable type (see monitoring.h),
// 3. A flag that contains the reporting status (eNeverReport, eReportOff, eReportOn)
//    leave it at eReportOn for the moment, this can be changed with the gui
// 4. A Callback function, leave at NULL for the moment
sVariables_t variables[] = {

	{ (void *) &myFloat1,	eComDataType_Float,	eReportOn, NULL }, // Index 0
	{ (void *) &myFloat2,	eComDataType_Float,	eReportOn, NULL }, // Index 1

};

// Create and init the nbVariables var
const uint8_t nbVariables = sizeof( variables ) / sizeof( sVariables_t );

// Create the msgFromHost[] var
char msgFromHost[14];

// Create the messagePending flag
bool messagePending = false;

/* ****************************************************************************
 * Create your serial receive handler
 * used when the host send a command
 * This handler set msgFromHost[] and messagePending
 ****************************************************************************/
void UART0_IRQHandler( void ) {
    static uint8_t idxRX = 0;
    static uint8_t localBuffer[14]; // Local buffer for double buffering

    // A byte is arrived, store it to a local buffer
	char c = Chip_UART_ReadByte( LPC_USART0 );

    localBuffer[idxRX] = c;

    if ( (c == '\r') || (c == '\n') ) {
        // Copy to msgFromHost for monitoring.c
        memcpy( msgFromHost, interruptMezza2Stab.msgString, idxRX);
        // Say to monitoring.c that a message is pending
        messagePending = true;
        // Reset reception
        idxRX = 0;
    } else {
        idxRX++;
        // Overflow protection
        if ( idxRX == 13)
            idxRX = 0;
    }
}

// Create the sendDataHost function
void sendDataHost( char* msgString )
{
    uint8_t i=0;
	while(msgString[i]!=0) {
        //Your function for serial sending char
        sendChar(msgString[i]);
    }
}

/* ****************************************************************************
 *  Your main function
 ****************************************************************************/
int main( void ) {

    while(1)
    {
        // Do your stuff
        myFloat1 = ...
        muFloat2 = getADCValue(...);

        // Call the update function 
        // each X (micro-milli) second
        if (YourTimerReachXSecond)
            update();
    }

	return 0;
}