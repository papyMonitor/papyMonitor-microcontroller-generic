/*
 * main.c
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#include "board.h"

#include <cr_section_macros.h>
#include <regulations.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "math.h"

#include "defines.h"
#include "enums.h"
#include "structures.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "nv.h"

#include "arithmetics.h"


// All the system variables
sGlobVarsPars_t GVP;


/*****************************************************************************
 * Public declaration
 *****************************************************************************/
extern void regulation( uint8_t idx );
extern void systemSimulation(uint8_t idx);
extern void update( void ); 		// Monitoring
extern void vInitFreeRTOSMemory( void );	// FreeRTOS

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
static void init() {

	// Load the system non volatile parameters
	loadNVarsFromEEPROM( &GVP.pars );

	//Enable monitoring rx/tx
	Chip_UART_IntEnable( LPC_USART0, (UART_IER_RBRINT | UART_IER_RLSINT) );
	NVIC_SetPriority( USART0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1 );
	NVIC_EnableIRQ( USART0_IRQn );
}

// Task that do PID regulation on 5 variables
static void vTaskRegulation(void *pvParameters) {

	const uint32_t tick = 1;

	init();

	for (uint idx=0; idx<5; idx++) {
		GVP.pars.PIDPars[idx].dt = 0.001 * tick;
	}

	while (1) {
		// Regulation every 1ms
		vTaskDelay(tick / portTICK_PERIOD_MS);

		for (uint idx=0; idx<5; idx++) {
			systemSimulation(idx);
			regulation(idx);
		}
	}
}

// Task that call the monitoring update function every 1ms
static void vTask_Monitor(void *pvParameters)
{
	while (1) {

		vTaskDelay(1 / portTICK_PERIOD_MS);

		// Monitoring
		update();
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/
int main(void)
{
	// Setup and config the hardware
    SystemCoreClockUpdate();

    Hardware_Init();

    // Mandatory for use with heap5.c
    vInitFreeRTOSMemory();

	// Regulation Task
	xTaskCreate(vTaskRegulation, 	"vTaskRegulation",	200, NULL,	(tskIDLE_PRIORITY + 1UL), NULL);

	// Task for monitoring
	xTaskCreate(vTask_Monitor, 		"vTskMonit",		130, NULL,	(tskIDLE_PRIORITY + 1UL), NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

    return 0 ;
}

void HardFault_Handler(void) {

	__disable_irq();

    while (1) {
    };
}

void vApplicationStackOverflowHook( TaskHandle_t pxCurrentTCB, char* pcTaskName )
{
	while (1);
}

void vApplicationMallocFailedHook( void )
{
	while (1);
}
