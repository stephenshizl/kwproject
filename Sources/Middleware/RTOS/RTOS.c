/* ###############################################################################################
##  MODULE: RTOS (Real-Time Operating System)
##
##  FILE DESCRIPTION:
##      Handles all interactions wit the RTOS.
## #############################################################################################*/

/*--------------------------------------------------------------------
                              INCLUDES
--------------------------------------------------------------------*/

#include "Middleware/DERIVATIVE.h"
#if defined( USE_FREERTOS )

#include "Middleware/RTOS/FreeRTOS/source/include/FreeRTOS.h"
#include "Middleware/RTOS/FreeRTOS/source/include/task.h"
#include "Middleware/RTOS/RTOS.h"
#include "Middleware/TYPES.h"

/*--------------------------------------------------------------------
                               DEFINES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                         ENUMERATIONS & TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                               MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              FUNCTIONS
--------------------------------------------------------------------*/

// ===============================================================================================
//  FUNCTION DESCRIPTION:
//      Defer processing to other RTOS tasks/processes.
//===============================================================================================
void RTOS__sleep
  (
  u32  sleep_duration //milliseconds
  )
	{
	TickType_t xDelay = sleep_duration / portTICK_PERIOD_MS;
	vTaskDelay( xDelay );
	} //RTOS__sleep()

// ===============================================================================================
//  FUNCTION DESCRIPTION:
//      Create RTOS Task.
//
//  OUTPUTS:
//      RETURN - RESULT__SUCCESS if success. RESULT__FAIL otherwise.
//===============================================================================================
result_t RTOS__task__create
  (
  RTOS__func_ptr     func_ptr,
  const char * const name,
  u16                stack_size,
  void              *task_parameters,
  u32                priority,
  void              *handle
  )
	{
	result_t result;

	result = xTaskCreate( func_ptr, (char const*)name, stack_size / sizeof(portSTACK_TYPE), task_parameters, (unsigned portBASE_TYPE)priority, handle );

	return result;
	} //RTOS__task__create()

// ===============================================================================================
//  FUNCTION DESCRIPTION:
//      Start the Task scheduler.
//===============================================================================================
void RTOS__scheduler__start
  (
  void
  )
	{
	vTaskStartScheduler();
	} //RTOS__scheduler__start()

#endif //USE_FREERTOS
