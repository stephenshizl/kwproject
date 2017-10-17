/* ###############################################################################################
##  MODULE: Derivative
##
##  FILE DESCRIPTION:
##      Selects the correct MCU derivative file.
## #############################################################################################*/

#ifndef __HEADER_FILE_PROTECTION__DERIVATIVE
#define __HEADER_FILE_PROTECTION__DERIVATIVE

/*--------------------------------------------------------------------
                              INCLUDES
--------------------------------------------------------------------*/

#include "Config/CONFIG.h"

/*--------------------------------------------------------------------
                               DEFINES
--------------------------------------------------------------------*/

//Define MCU family
//#define MCU__TI__CC3200
//#define MCU__NXP__KW2X
#define MCU__NXP__KW41Z
//#define MCU__NXP__HCS08

//Define compiler to be used with this MCU
#if defined( MCU__TI__CC3200 )
	#define MCU__FAMILY__TI
	#ifndef gcc
		#define gcc
	#endif
	#ifndef DEBUG
		#define DEBUG
	#endif
#endif
#if defined( MCU__NXP__KW2X ) | defined( MCU__NXP__KW41Z )
	#define MCU__FAMILY__KINETIS
	#ifndef gcc
		#define gcc
	#endif
	#ifndef DEBUG
		#define DEBUG
	#endif
#endif
#if defined( MCU__NXP__HCS08 )
	#define nxp
#endif

//Define global RTOS symbol
#if defined(USE_FREERTOS)
	#define SL_PLATFORM_MULTI_THREAD
#endif

//Create macro to check whether the MCU is actively being debugged.
//More info on this ARM register can be found here: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0337e/CEGCJAHJ.html
#if defined(MCU__TI__CC3200) || defined(MCU__FAMILY__KINETIS)
	#define DHCSR_REG                   (*(u32*)(0xE000EDF0))     /* ARM Cortex Debug Halting Control and Status Register */
	#define C_DEBUGEN                   ( 0x00000001 )            /* Debug enabled bit */
	#define DEBUG_SESSION_ACTIVE        ( DHCSR_REG & C_DEBUGEN ) /* Returns TRUE if a debug session is active. Note: Does NOT indicate whether debug cable is connected. */
	#define UNIT_ADDRESS                ( *(u8*)(ADDRESS__CODE__HEADER + 0x29) )   /* Indented for future use in order to identify multiple units. Currently using the build number from the project identifier section of code as a unique identifier. Note: Need to come up with more universal strategy. */
#endif

/*--------------------------------------------------------------------
                              INCLUDES
--------------------------------------------------------------------*/

//Select the appropriate derivative file for the current MCU
#if defined( MCU__TI__CC3200 )
	#include "SDK__CC3200/inc/hw_types.h"

//	#include "SDK__CC3200/inc/asmdefs.h"
	#include "SDK__CC3200/inc/hw_aes.h"
	#include "SDK__CC3200/inc/hw_apps_config.h"
	#include "SDK__CC3200/inc/hw_apps_rcm.h"
	#include "SDK__CC3200/inc/hw_camera.h"
	#include "SDK__CC3200/inc/hw_common_reg.h"
	#include "SDK__CC3200/inc/hw_des.h"
	#include "SDK__CC3200/inc/hw_dthe.h"
	#include "SDK__CC3200/inc/hw_flash_ctrl.h"
	#include "SDK__CC3200/inc/hw_gpio.h"
	#include "SDK__CC3200/inc/hw_gprcm.h"
	#include "SDK__CC3200/inc/hw_hib1p2.h"
	#include "SDK__CC3200/inc/hw_hib3p3.h"
	#include "SDK__CC3200/inc/hw_i2c.h"
	#include "SDK__CC3200/inc/hw_ints.h"
	#include "SDK__CC3200/inc/hw_mcasp.h"
	#include "SDK__CC3200/inc/hw_mcspi.h"
	#include "SDK__CC3200/inc/hw_memmap.h"
	#include "SDK__CC3200/inc/hw_mmchs.h"
	#include "SDK__CC3200/inc/hw_nvic.h"
	#include "SDK__CC3200/inc/hw_ocp_shared.h"
	#include "SDK__CC3200/inc/hw_shamd5.h"
	#include "SDK__CC3200/inc/hw_stack_die_ctrl.h"
	#include "SDK__CC3200/inc/hw_timer.h"
	#include "SDK__CC3200/inc/hw_uart.h"
	#include "SDK__CC3200/inc/hw_udma.h"
	#include "SDK__CC3200/inc/hw_wdt.h"
#endif

#if defined( MCU__FAMILY__KINETIS__KW2X )
	#include "Boot/MCU/Includes/MKW21D5.h"
#endif

#if defined( MCU__NXP__KW41Z )
	#include "SDK__Kinetis/MKW41Z4/MKW41Z4.h"
#endif

#if defined( MCU__NXP__HCS08 )
	#include <mc13213.h>
#endif

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

#endif //__HEADER_FILE_PROTECTION__DERIVATIVE
