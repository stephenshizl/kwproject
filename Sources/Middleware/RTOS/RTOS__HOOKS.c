/* ###############################################################################################
##  MODULE: FreeRTOS Hooks
##
##  FILE DESCRIPTION:
##      This file handles Callbacks from FreeRTOS
## #############################################################################################*/

//#include "Config/CONFIG__NONVOL.h"
#include "Middleware/RTOS/RTOS.h"
//#include "Middleware/SYSTEM.h"
#include "Middleware/TYPES.h"
//#include "Middleware/Tools/DEBUG.h"
//#include "Middleware/Tools/TIMERS__SW.h"

#if defined( USE_FREERTOS )
//*****************************************************************************
// FreeRTOS User Hook Functions enabled in FreeRTOSConfig.h
//*****************************************************************************

// ===============================================================================================
//  FUNCTION DESCRIPTION:
//      Handle RTOS asserts.
//===============================================================================================
void vAssertCalled
  (
  const s8 *pcFile,
  u32 ulLine
  )
	{
	//Handle Assert here
//	ERROR__critical( "FreeRTOS - Assert" );
	} //vAssertCalled()

// ===============================================================================================
//  FUNCTION DESCRIPTION:
//      RTOS Idle task.
//===============================================================================================
void vApplicationIdleHook
  (
  void
  )
	{
	u32 i;

	//Perform 1ms loop (calibrated on this platform at 80MHz)
	while( 1 )
		{
		//Loop for calibrated period of time
		for( i = 0; i < 5321; i++ )
			{;}

		//Increment the millisecond counter
//		SYSTEM__idle_hook_time__ms++;
		}
	} //vApplicationIdleHook()

// ===============================================================================================
//  FUNCTION DESCRIPTION:
//      Handle memory allocation failure.
//===============================================================================================
void vApplicationMallocFailedHook
  (
  void
  )
	{
    //Handle Memory Allocation Errors
	//Note: Getting here likely means that you don't have enough HEAP allocated in your linker.ld file.
//	ERROR__critical( "FreeRTOS - Ran out of HEAP!" );
	if( DEBUG_SESSION_ACTIVE )
		__asm("BKPT #0\n");
	} //vApplicationMallocFailedHook()

// ===============================================================================================
//  FUNCTION DESCRIPTION:
//      Handle RTOS stack overflow.
//===============================================================================================
void vApplicationStackOverflowHook
  (
  void *task,
  char *name
  )
	{
	//Handle FreeRTOS Stack Overflow
//	ERROR__critical( "FreeRTOS - Stack Overflow" );
	if( DEBUG_SESSION_ACTIVE )
		__asm("BKPT #0\n");
	} //vApplicationStackOverflowHook()

#endif //USE_FREERTOS
