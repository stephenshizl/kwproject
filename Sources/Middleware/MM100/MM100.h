 /************************************************************************
 *
 * COMPANY CONFIDENTIAL
 * __________________
 *
 *  Company Systems Incorporated
 *  All Rights Reserved.
 * 
 * NOTICE:  All information contained herein is, and remains
 * the property of "Company Systems Incorporated" and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to "Company Systems Incorporated"
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from "Company Systems Incorporated".
 *
 *************************************************************************
 *
 * MM100.h
 *
 * This file contains all necessary library functions for use with the
 * MM100 Head Unit.
 * 
 * Author: Stephen Ore
 *
 ************************************************************************/
#ifndef MM100_H_
#define MM100_H_

/* Includes */
 #include <stdbool.h>
 #include <stdint.h>

/* Variables */

/* Defines */




/* Miscellaneous */
typedef enum{
	MM100_TX__DATA_INIT     = 0xA0, // Used for Initialization of TX Data
	MM100_RX__START_BYTE    = 0x89	// Used to test Header Byte
}MM100__misc_t;

/* Button Events */
typedef enum{
	MM100_TX__BTN_PRESS    = 0,// Button Pressed
	MM100_TX__BTN_HOLD     = 1 // Button Held
}MM100_TX__held_t;

/* Buttons Actions */
typedef enum{
	MM100_TX__BTN_NONE          = 0x00, // No Button
	MM100_TX__BTN_SEEK_DOWN     = 0x01, // Seek Left/Down Button
	MM100_TX__BTN_SEEK_UP       = 0x02, // Seek Right/Up Button
	MM100_TX__BTN_PLAY_PAUSE    = 0x03, // Play or Pause Button
	MM100_TX__BTN_SOURCE        = 0x04, // Source Button
	MM100_TX__BTN_VOLUME_DOWN   = 0x05, // Volume Up Button
	MM100_TX__BTN_VOLUME_UP     = 0x06, // Volume Down Button
	MM100_TX__BTN_PWR_t         = 0x07  // Place Holder for Power Button (use source with hold condition)
}MM100_TX__buttons_t;

/* TX Data */
typedef union{
	uint8_t data;
	struct{
		MM100_TX__buttons_t button  :3; // Button data
		MM100_TX__held_t held       :1;	// Button event
		uint8_t reserved            :4;	//
	}bits;
}MM100_TX__data_t;


/* Commands */
typedef enum{
	MM100_RX__CMD_HEAD_UNIT_OFF     = 0x01, //
	MM100_RX__CMD_REPEAT_INTERVAL   = 0x03, //
	MM100_RX__CMD_ILL_LVL           = 0x04, //
	MM100_RX__CMD_SOURCE            = 0x05  //
}MM100_RX__commands_t;

/* Masks */
typedef enum {
    MM100_RX__CMD_MASK  = 0x70, // Mask to separate the command from data
	MM100_RX__DATA_MASK = 0x0F  // Mask to separate the data from command
} MM100_RX__masks_t;

/* Sources */
typedef enum{
	MM100_RX__SOURCE_AM         = 0x00, //
	MM100_RX__SOURCE_FM         = 0x01, //
	MM100_RX__SOURCE_WB         = 0x02, //
	MM100_RX__SOURCE_SXM        = 0x03, //
	MM100_RX__SOURCE_BT         = 0x04, //
	MM100_RX__SOURCE_AUX        = 0x05, //
	MM100_RX__SOURCE_USB        = 0x06, //
	MM100_RX__SOURCE_UNKNOWN    = 0x0F  // Unknown Source
}MM100_RX__sources_t;

/* Indicators */
typedef struct{
	bool head_unit_off;             //
	uint8_t repeat_interval;        //
	uint8_t illumination_lvl;       //
	MM100_RX__sources_t sources;	//
}MM100_RX__indicators_t;

/* Command Byte */
typedef union {
	uint8_t command;
	struct {
		uint8_t value                   :4;
		MM100_RX__commands_t commands   :3;
		bool reserved                   :1;
	}bits;
}MM100_RX__command_byte_t;

/* RX Data */
typedef struct {
	uint8_t start_byte;
	MM100_RX__command_byte_t command_byte;
	uint8_t crc_byte;
}MM100_RX__data_t;



/* Receive Data Functions */
bool MM100_RX__IsRxData (MM100_RX__data_t*);
uint8_t MM100_RX__PeekDataRaw (MM100_RX__data_t*);
uint8_t MM100_RX__PeekData (MM100_RX__data_t*, MM100_RX__commands_t);
bool MM100_RX__PeekDataHeadOnOff (MM100_RX__data_t*);
uint8_t MM100_RX__PeekDataInterval (MM100_RX__data_t*);
uint8_t MM100_RX__PeekDataIllumination (MM100_RX__data_t*);
MM100_RX__sources_t MM100_RX__PeekDataSource (MM100_RX__data_t*);
bool MM100_RX_ProcessData (MM100_RX__data_t*, MM100_RX__indicators_t);


/* Transmit Data Functions */
void MM100_TX__InitData (MM100_TX__data_t);
void MM100_TX__ClearData (MM100_TX__data_t);
MM100_TX__data_t MM100_TX__ReturnData(MM100_TX__buttons_t, MM100_TX__held_t);
void MM100_TX__SetEvent(MM100_TX__data_t, MM100_TX__buttons_t);
void MM100_TX__SetHold (MM100_TX__data_t, MM100_TX__held_t);
void MM100_TX__SendData (void (*function)(), MM100_TX__data_t);
void MM100_TX__SendDataParam (void (*function)(), MM100_TX__data_t, MM100_TX__buttons_t, MM100_TX__held_t);
void MM100_TX__SendParam (void (*function)(), MM100_TX__buttons_t, MM100_TX__held_t);

#endif
