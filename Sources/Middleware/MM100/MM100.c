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
 * MM100.c
 *
 * This file contains all necessary library functions for use with the
 * MM100 Head Unit.
 *
 * Author: Stephen Ore
 *
 ************************************************************************/
/* Local includes */
#include "../MM100/MM100.h"

/* Global includes */

/* System includes */

/* Functions */

bool MM100_RX__IsRxData (MM100_RX__data_t* data) {
	if (data->start_byte == MM100_RX__START_BYTE) {
		return true;
	}
  return false;
}

uint8_t MM100_RX__PeekDataRaw (MM100_RX__data_t* data) {
	uint8_t data_byte = 0;
	if (data->start_byte == MM100_RX__START_BYTE) {
		if ((( data->start_byte + data->command_byte.command ) % 256 ) == data->crc_byte ) {
			data_byte = data->command_byte.command;
		}
	}
	return data_byte;
}

uint8_t MM100_RX__PeekData (MM100_RX__data_t* data, MM100_RX__commands_t cmd) {
	uint8_t data_byte = 0;
	if (data->start_byte == MM100_RX__START_BYTE) {
		if ((( data->start_byte + data->command_byte.command ) % 256 ) == data->crc_byte ) {
			if (data->command_byte.bits.commands == cmd) {
				data_byte = data->command_byte.bits.value;
			}
		}
	}
	return data_byte;
}

bool MM100_RX__PeekDataHeadOnOff (MM100_RX__data_t* data) {
	bool data_byte = false;
	if (data->start_byte == MM100_RX__START_BYTE) {
		if ((( data->start_byte + data->command_byte.command ) % 256 ) == data->crc_byte ) {
			if (data->command_byte.bits.commands == MM100_RX__CMD_HEAD_UNIT_OFF) {
				data_byte = true;
			}
		}
	}
	return data_byte;
}

uint8_t MM100_RX__PeekDataInterval (MM100_RX__data_t* data) {
	uint8_t data_byte = 0;
	if (data->start_byte == MM100_RX__START_BYTE) {
		if ((( data->start_byte + data->command_byte.command ) % 256 ) == data->crc_byte ) {
			if (data->command_byte.bits.commands == MM100_RX__CMD_REPEAT_INTERVAL) {
				data_byte = data->command_byte.bits.value;
			}
		}
	}
	return data_byte;
}

uint8_t MM100_RX__PeekDataIllumination (MM100_RX__data_t* data) {
	uint8_t data_byte = 0;
	if (data->start_byte == MM100_RX__START_BYTE) {
		if ((( data->start_byte + data->command_byte.command ) % 256 ) == data->crc_byte ) {
			if (data->command_byte.bits.commands == MM100_RX__CMD_ILL_LVL) {
				data_byte = data->command_byte.bits.value;
			}
		}
	}
	return data_byte;
}

MM100_RX__sources_t MM100_RX__PeekDataSource (MM100_RX__data_t* data) {
	MM100_RX__sources_t data_byte = MM100_RX__SOURCE_UNKNOWN;
	if (data->start_byte == MM100_RX__START_BYTE) {
		if ((( data->start_byte + data->command_byte.command ) % 256 ) == data->crc_byte ) {
			if (data->command_byte.bits.commands == MM100_RX__CMD_SOURCE) {
				data_byte = data->command_byte.bits.value;
			}
		}
	}
	return data_byte;
}

bool MM100_RX_ProcessData (MM100_RX__data_t* data, MM100_RX__indicators_t indicators) {
	uint8_t data_byte;
	bool result = false;

	if (data->start_byte == MM100_RX__START_BYTE) {

		if ((( data->start_byte + data->command_byte.command ) % 256 ) == data->crc_byte ) {

			data_byte = data->command_byte.bits.value;

			switch (data->command_byte.bits.commands) {
				case MM100_RX__CMD_HEAD_UNIT_OFF:
					indicators.head_unit_off = true;
					result = true;
					break;
				case MM100_RX__CMD_REPEAT_INTERVAL:
					indicators.repeat_interval = data_byte;
					result = true;
					break;
				case MM100_RX__CMD_ILL_LVL:
					indicators.illumination_lvl = data_byte;
					if(indicators.illumination_lvl > 1){
						indicators.head_unit_off = false;
					}
					result = true;
					break;
				case MM100_RX__CMD_SOURCE:
					indicators.sources = data_byte;
					result = true;
					break;
				default:
					// result already false
					break;
			}

		}
		// result already false
	}
	return result;
}

void MM100_TX__InitData (MM100_TX__data_t data) {
	data.data = MM100_TX__DATA_INIT;
}

void MM100_TX__ClearData (MM100_TX__data_t data) {
	data.data = MM100_TX__DATA_INIT;
}

MM100_TX__data_t MM100_TX__ReturnData(MM100_TX__buttons_t event, MM100_TX__held_t hold) {
    MM100_TX__data_t data;
    data.data = MM100_TX__DATA_INIT;
	data.bits.button = event;
	data.bits.held= hold;
    return (MM100_TX__data_t)data.data;
}

void MM100_TX__SetEvent(MM100_TX__data_t data, MM100_TX__buttons_t event) {
	data.bits.button = event;
}

void MM100_TX__SetHold (MM100_TX__data_t data, MM100_TX__held_t hold) {
	 data.bits.held = hold;
}

void MM100_TX__SendData (void (*function)(), MM100_TX__data_t data) {
	function(data);
}

void MM100_TX__SendDataParam (void (*function)(), MM100_TX__data_t data, MM100_TX__buttons_t event, MM100_TX__held_t hold) {
    data.data = MM100_TX__DATA_INIT;
	data.bits.button = event;
	data.bits.held= hold;
	function(data);
}

void MM100_TX__SendParam (void (*function)(), MM100_TX__buttons_t event, MM100_TX__held_t hold) {
	MM100_TX__data_t data;
	data.data = MM100_TX__DATA_INIT;
	data.bits.button = event;
	data.bits.held= hold;
	function(data);
}
