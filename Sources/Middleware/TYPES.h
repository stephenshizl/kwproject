/* ###############################################################################################
##  MODULE: Types
##
##  FILE DESCRIPTION:
##      Defines all system-wide types and constants
## #############################################################################################*/
#ifndef __HEADER_FILE_PROTECTION__TYPES
#define __HEADER_FILE_PROTECTION__TYPES

/*--------------------------------------------------------------------
                              INCLUDES
--------------------------------------------------------------------*/

#include <stddef.h>
#include "Middleware/DERIVATIVE.h"

/*--------------------------------------------------------------------
                               DEFINES
--------------------------------------------------------------------*/

#if defined( MCU__FAMILY__KINETIS )
	#if defined(  NULL )
		#undef NULL
	#endif
	#define NULL                    ( 0 )
#endif

#define NA                          ( 0 )

#define UNIVERSAL_ANSWER            ( 42 ) //Arbitrarily chosen value. Have you watched Hitchhikers guide to the galaxy? I haven't, but everyone seems to agree that the answer is 42.

#define FLASH_ERASED_STATE__8_BIT   ( 0xFF )
#define FLASH_ERASED_STATE__16_BIT  ( 0xFFFF )
#define FLASH_ERASED_STATE__32_BIT  ( 0xFFFFFFFF )

//Minimum & Maximum values by type
#define MAX__u8                     (  0xFF )
#define MIN__u8                     (  0x00 )
#define MAX__s8                     (  0x7F )
#define MIN__s8                     ( (s8)0x80 )

#define MAX__u16                    (  0xFFFF )
#define MIN__u16                    (  0x0000 )
#define MAX__s16                    (  0x7FFF )
#define MIN__s16                    ( (s16)0x8000 )

#define MAX__u32                    (  0xFFFFFFFF )
#define MIN__u32                    (  0x00000000 )
#define MAX__s32                    (  0x7FFFFFFF )
#define MIN__s32                    ( (s32)0x80000000 )

#define MAX__f32                    (  3.40282347e+38 )
#define MIN__f32                    (  0 )

#define MAX__f64                    ( 1.79769313486231571e+308 )
#define MIN__f64                    ( 0 )

#define MAX__percent                ( PERCENT__MULTIPLIER )
#define MIN__percent                (    0 )

#if defined( MCU__TI__CC3200 )
	#ifndef FALSE
		#define FALSE      (0)
	#endif
	#ifndef TRUE
		#define TRUE       (1)
	#endif
#endif
#if defined( MCU__FAMILY__KINETIS )
	#if defined( MCU__NXP__KW2X )
		#define FALSE
		#define TRUE
	#endif
	#if defined( MCU__NXP__KW41Z )
		#ifndef FALSE
			#define FALSE      (0)
		#endif
		#ifndef TRUE
			#define TRUE       (1)
		#endif
	#endif
#endif
#if defined( MCU__NXP__HCS08 )
	#undef FALSE
	#undef TRUE
	#define FALSE
	#define TRUE
#endif

/*--------------------------------------------------------------------
                               MACROS
--------------------------------------------------------------------*/

//Handle structure packing which is specific per compiler
#if defined( gcc )
	#define PACKED_STRUCT struct __attribute__ ((__packed__))
	#define PACKED_UNION  union __attribute__ ((__packed__))
#endif
#if defined( nxp )
	#define PACKED_STRUCT struct /* TODO: Improve this */
	#define PACKED_UNION  union  /* TODO: Improve this */
#endif
#if defined( iar )
	#define PACKED_STRUCT __packed struct
	#define PACKED_UNION __packed union
#endif

#if defined( MCU__NXP__HCS08 )
	#pragma MESSAGE DISABLE C4000  /* Disables Information: Condition always TRUE. */
	#pragma MESSAGE DISABLE C1420  /* Disables Warning: Result of function-call is ignored. */
#endif

#define __ASM            __asm /*!< asm keyword for GNU Compiler          */

/*--------------------------------------------------------------------
                         ENUMERATIONS & TYPES
--------------------------------------------------------------------*/

//Standard types
typedef signed char         s8;
typedef signed short int    s16;
typedef signed long int     s32;
typedef unsigned char       u8;
typedef unsigned short int  u16;
typedef unsigned long int   u32;
typedef float               f32;
typedef double              f64;

#if defined( MCU__TI__CC3200 )
	typedef u32 mcu_address__type;
#endif
#if defined( MCU__FAMILY__KINETIS )
	typedef u32 mcu_address__type;
#endif
#if defined( MCU__NXP__HCS08 )
	typedef u16 mcu_address__type;
#endif

//Support legacy types and other code that might be ported to this platform
typedef s8                  int8_t;
typedef s16                 int16_t;
typedef s32                 int32_t;
typedef s8                  sint8_t;
typedef s16                 sint16_t;
typedef s32                 sint32_t;
typedef u8                  uint8_t;
typedef u16                 uint16_t;
typedef u32                 uint32_t;
typedef s8                  INT8;
typedef s16                 INT16;
typedef s32                 INT32;
typedef u8                  _UINT8;
typedef u16                 _UINT16;
typedef u32                 _UINT32;

//Custom types to improve code's self-documentation
#define PERCENT__MULTIPLIER  ( 100 * 100 ) //10,000 - Multiplier used to avoid float math. Results in precision within 100ths of a percent.
#define PERCENT__STEP        ( PERCENT__MULTIPLIER / 100 ) //100 - Represents 1% of a percentage_t value
typedef u32                 percent_t; //Standard/Known percent value * PERCENT__MULTIPLIER
typedef u8                  bitfield_t;
typedef u16                 crc16_t;
typedef u32                 crc32_t;

//Standard function pointer that accepts and returns no parameters
typedef void (*const func_ptr)(void);

#undef bool
typedef u8 bool; enum
	{
	OFF = 0,  NO = 0,  LOW = 0, DISABLE = 0, DISABLED = 0, INACTIVE = 0,   ACTIVE__ = 0,
	 ON = 1, YES = 1, HIGH = 1,  ENABLE = 1,  ENABLED = 1,   ACTIVE = 1, INACTIVE__ = 1
	};

//Useful in reporting TRUE/FALSE statuses that sometimes have special results
typedef u8 result_t; enum
	{
	RESULT__FAIL        = 0,
	RESULT__SUCCESS     = 1,
	RESULT__SPECIAL     = 2 //Unique definition with each implementation
	};

//Defines direction of data flow
typedef u8 direction_t; enum
	{
	INPUT  = 0, PULLDOWN = 0, DIRECTION__IN   = 0, DIRECTION__DOWN = 0, DIRECTION__MASTER = 0, DIRECTION__RX = 0, DIRECTION__WRITE = 0,
	OUTPUT = 1, PULLUP   = 1, DIRECTION__OUT  = 1, DIRECTION__UP   = 1, DIRECTION__SLAVE  = 1, DIRECTION__TX = 1, DIRECTION__READ  = 1,
	            PULL_NA  = 2, DIRECTION__NA   = 2,
                              DIRECTION__BOTH = 3
	};

//List of supported Debug peripherals
typedef u8 peripheral__type; enum
	{
	PERIPHERAL__TYPE__DEFAULT,   //Used to route data to the default communications (COMMS) peripheral: i.e. Bluetooth, SMAC, or WiFi

	//Wired
	PERIPHERAL__TYPE__UART,
	PERIPHERAL__TYPE__SPI,
	PERIPHERAL__TYPE__I2C,
	PERIPHERAL__TYPE__1WIRE,

	//Wireless
	PERIPHERAL__TYPE__BLUETOOTH,
	PERIPHERAL__TYPE__SMAC,       //IEEE 802.15.4 - 2.4GHz Simple MAC
	PERIPHERAL__TYPE__WIFI,
	PERIPHERAL__TYPE__ZIGBEE,
	PERIPHERAL__TYPE__ZWAVE,

	PERIPHERAL__TYPE__CNT
	};

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              FUNCTIONS
--------------------------------------------------------------------*/  

#endif /* __HEADER_FILE_PROTECTION__TYPES */
