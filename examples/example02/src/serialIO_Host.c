/*
 * serialIO_Host.c
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#include "string.h"

#include "chip.h"

#include "defines.h"
#include "enums.h"
#include "structures.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/*****************************************************************************
 * Public configuration/status structure
 * Affected by commands
 ****************************************************************************/
#define RX_BUFFER_SIZE 	14

/*****************************************************************************
 * Public types/enumerations/variables/declaration
 ****************************************************************************/
char msgFromHost[RX_BUFFER_SIZE];
bool messagePending;
void sendDataHost( char* message );

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
static char rxCMDBuffer[RX_BUFFER_SIZE]; // Used only here

/*****************************************************************************
 * Private functions
 ****************************************************************************/
/* ****************************************************************************
 *  Interrupt Handlers
 ****************************************************************************/
void UART0_IRQHandler( void ) {

	static uint32_t rxCMDIndex = 0;

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	uint32_t intFlags = Chip_UART_ReadLineStatus( LPC_USART0 );

    /*******************************************************************
     * 									RX
     *******************************************************************/
	while ( intFlags & UART_LSR_RDR ) {

		rxCMDBuffer[rxCMDIndex++] = Chip_UART_ReadByte( LPC_USART0 );

		if ( rxCMDBuffer[rxCMDIndex-1] == '\n') {
			// EOL received, replace it with 0
			rxCMDBuffer[rxCMDIndex-1] = 0;
			// and copy to msgFromHost
			strcpy( msgFromHost, rxCMDBuffer);
			// then reset buffer index
			rxCMDIndex = 0;
			// tell timer_CB in monitor.c that message arrived
			messagePending = true;
		}

		// Avoid overflow
		if (rxCMDIndex == RX_BUFFER_SIZE)
			rxCMDIndex = 0;

		intFlags = Chip_UART_ReadLineStatus( LPC_USART0 );
	}

    /*******************************************************************
     *
     * 									TX
     *
     *******************************************************************/
	if ( LPC_USART0->IER & UART_IER_THREINT ) {
		// If FIFO empty, disable interrupt and give the semaphore for next
		if (LPC_USART0->LSR & UART_LSR_THRE) {
			LPC_USART0->IER &= ~UART_IER_THREINT;
		}
	}

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

    /*! @name ISR exit barrier
     * @{
     *
     * ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
     * exception return operation might vector to incorrect interrupt.
     * For Cortex-M7, if core speed much faster than peripheral register write speed,
     * the peripheral interrupt flags may be still set after exiting ISR, this results to
     * the same error similar with errata 83869.
     */
    __DSB();
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/


/*************************************
 * *************************************
 * It's assumed that the message length is <= 15 bytes, the TX FIFO size
 * *************************************
 **************************************/
void sendDataHost( char* message ) {

	for ( uint8_t i=0; i< strlen(message); i++)
		LPC_USART0->THR = message[i];
	// Begin to send
	LPC_USART0->IER |=  UART_IER_THREINT;
}


