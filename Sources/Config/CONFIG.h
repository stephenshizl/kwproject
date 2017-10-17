/* ###############################################################################################
##  MODULE: Configuration of product-specific support packages
##
##  FILE DESCRIPTION:
##      Handles configuration of product-specific support packages.
## #############################################################################################*/

#ifndef __HEADER_FILE_PROTECTION__CONFIG
#define __HEADER_FILE_PROTECTION__CONFIG

/*--------------------------------------------------------------------
                              INCLUDES
--------------------------------------------------------------------*/

#include "App/APP__PRODUCT.h"

/*--------------------------------------------------------------------
                               DEFINES
--------------------------------------------------------------------*/

/* List of available support packages
	SUPPORT__2_4GHZ
	SUPPORT__ADC
	SUPPORT__BLUETOOTH
	SUPPORT__CAN               //Requires SUPPORT__SPI
	SUPPORT__COMMS
	SUPPORT__DEBUG
	SUPPORT__ENCODER
	SUPPORT__GPIO
	SUPPORT__GPIO__ADC         //Requires SUPPORT__GPIO & SUPPORT__ADC
	SUPPORT__GPIO__EXPANDER    //Requires SUPPORT__GPIO & SUPPORT__SPI
	SUPPORT__I2C
	SUPPORT__PIXEL
		SUPPORT__PIXEL__ANIMATION
		SUPPORT__PIXEL__ENCODER
		SUPPORT__PIXEL__EXCLUSION
		SUPPORT__PIXEL__PRESET
	SUPPORT__POWER__CURRENT    //Requires SUPPORT__ADC
	SUPPORT__POWER__VOLTAGE    //Requires SUPPORT__ADC
	SUPPORT__PWM__BIT_BANG     //Requires SUPPORT__PIXEL
	SUPPORT__PWM__CAN          //Requires SUPPORT__PIXEL & SUPPORT__CAN
	SUPPORT__PWM__ITWINKLE     //Requires SUPPORT__PIXEL
	SUPPORT__PWM__MCU          //Requires SUPPORT__PIXEL
	SUPPORT__PWM__TLC59731     //Requires SUPPORT__PIXEL
	SUPPORT__SPI
	SUPPORT__TEMPERATURE       //Requires SUPPORT__I2C
	SUPPORT__TEST
	SUPPORT__UART
	SUPPORT__WIFI
 	*/

#if defined(PRODUCT__TYPE__BOOTLOADER)
	//No Support packages needed
#elif defined(PRODUCT__TYPE__FACTORY_IMAGE)
	//No Support packages needed
#elif defined(PRODUCT__TYPE__BASSCAT)
	//Define RTOS
	#ifndef USE_FREERTOS
		#define USE_FREERTOS
	#endif

	//Define Support packages
	#define SUPPORT__ADC
	#define SUPPORT__CAN
	#define SUPPORT__COMMS
	#define SUPPORT__DEBUG
	#define SUPPORT__GPIO
	#define SUPPORT__GPIO__ADC
	#define SUPPORT__GPIO__EXPANDER
	#define SUPPORT__PIXEL
		#define SUPPORT__PIXEL__ANIMATION
		#define SUPPORT__PIXEL__PRESET
	#define SUPPORT__POWER__CURRENT
	#define SUPPORT__POWER__VOLTAGE
	#define SUPPORT__SPI
	#define SUPPORT__WIFI
#elif defined(PRODUCT__TYPE__KW41_DEMO)
	//Define RTOS
	#ifndef USE_FREERTOS
		#define USE_FREERTOS
	#endif

	//Define Support packages
	#define SUPPORT__BLUETOOTH
	#define SUPPORT__COMMS
	#define SUPPORT__DEBUG
	#define SUPPORT__GPIO
	#define SUPPORT__PIXEL
	#define SUPPORT__SPI
#elif defined(PRODUCT__TYPE__LITEWAVE) | defined(PRODUCT__TYPE__PREMIER_PONTOONS) | defined(PRODUCT__TYPE__SMOKERCRAFT)
	//Define RTOS
	#ifndef USE_FREERTOS
		#define USE_FREERTOS
	#endif

	//Define Support packages
	#define SUPPORT__ADC
	#define SUPPORT__CAN
	#define SUPPORT__COMMS
	#define SUPPORT__DEBUG
	#define SUPPORT__ENCODER
	#define SUPPORT__GPIO
	#define SUPPORT__I2C
	#define SUPPORT__PIXEL
		#define SUPPORT__PIXEL__ANIMATION
		#define SUPPORT__PIXEL__ENCODER
		#define SUPPORT__PIXEL__EXCLUSION
		#define SUPPORT__PIXEL__PRESET
	#define SUPPORT__POWER__CURRENT
	#define SUPPORT__POWER__VOLTAGE
	#define SUPPORT__PWM__MCU
	#define SUPPORT__SPI
	#define SUPPORT__TEMPERATURE
	#define SUPPORT__WIFI
#elif defined(PRODUCT__TYPE__MASTERCRAFT) | defined(PRODUCT__TYPE__MASTERCRAFT__TESTER)
	//Define RTOS
	#ifndef USE_FREERTOS
		#define USE_FREERTOS
	#endif

	//Define Support packages
	#define SUPPORT__ADC
	#define SUPPORT__CAN
	#define SUPPORT__COMMS
	#define SUPPORT__DEBUG
	#define SUPPORT__GPIO
	#define SUPPORT__GPIO__ADC
	#define SUPPORT__GPIO__EXPANDER
	#define SUPPORT__PIXEL
	#define SUPPORT__PIXEL__PRESET
	#if defined(PRODUCT__TYPE__MASTERCRAFT__TESTER)
		#define SUPPORT__PWM__CAN
	#endif
	#define SUPPORT__PWM__TLC59731
	#define SUPPORT__SPI
	#define SUPPORT__WIFI
#elif defined(PRODUCT__TYPE__NITELITER)
	//Define RTOS
	#ifndef USE_FREERTOS
		#define USE_FREERTOS
	#endif

	//Define Support packages
	#define SUPPORT__COMMS
	#define SUPPORT__DEBUG
	#define SUPPORT__GPIO
	#define SUPPORT__PIXEL
	#define SUPPORT__WIFI
#endif /* PRODUCT__TYPE__ */

//Defines the firmware storage location. Use only one of these!
//#define FIRMWARE__DOWNLOAD__STORAGE__FLASH__INTERNAL /* Firmware stored in Internal Flash */
  #define FIRMWARE__DOWNLOAD__STORAGE__FLASH__EXTERNAL /* Firmware store in External Flash */
//#define FIRMWARE__DOWNLOAD__STORAGE__EEPROM          /* Firmware stored in EEPROM */

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

#endif /* __HEADER_FILE_PROTECTION__CONFIG */
