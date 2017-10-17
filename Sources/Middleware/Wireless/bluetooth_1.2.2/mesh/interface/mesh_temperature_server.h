/*! *********************************************************************************
* \addtogroup MESH_TEMP Mesh Temperature Profile
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file mesh_Temperature_server.h
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _MESH_TEMPERATURE_SERVER_H_
#define _MESH_TEMPERATURE_SERVER_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "mesh_interface.h"

/************************************************************************************
*************************************************************************************
* Public constants and macros
*************************************************************************************
************************************************************************************/


/************************************************************************************
*************************************************************************************
* Public types
*************************************************************************************
************************************************************************************/
/*! Temperature server event types. */
typedef enum meshTemperatureServerEventType_tag
{
    gMeshTemperatureGetCommand_c,           /*!< Received temperature get command from a temperature client. */
    gMeshTemperatureSetReportCommand_c,     /*!< Received temperature set report command from a temperature client. */
    gMeshTemperatureGetReportCommand_c,     /*!< Received temperature get report command from a temperature client. */
} meshTemperatureServerEventType_t;

/*! Temperature server event structure. */
typedef struct meshTemperatureServerEvent_tag
{
    meshTemperatureServerEventType_t  eventType;        /*!< Event type. */
    union
    {       
        struct
        {
            meshAddress_t source;       /*!< Temperature client address. */
        } getCommand;   /*!< Data for gMeshTemperatureGetCommand_c. */
        
        struct
        {
            meshAddress_t   source;             /*!< Temperature client address. */
            bool_t          enable;             /*!< Requested report state. */
            uint16_t        intervalSeconds;    /*!< Requested report interval, measured in seconds, valid only if requested report state is TRUE. */
        } setReportCommand; /*!< Data for gMeshTemperatureSetReportCommand_c. */
    
        struct
        {
            meshAddress_t   source;     /*!< Temperature client address. */
        } getReportCommand; /*!< Data for gMeshTemperatureGetCommand_c. */
        
    } eventData;                                        /*!< Event data, interpreted based on event type. */
} meshTemperatureServerEvent_t;

/*! Temperature server event callback. */
typedef meshResult_t (*meshTemperatureServerCallback_t)
(
    meshTemperatureServerEvent_t* pEvent        /*!< Pointer to the event structure. */
);

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/


/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
* \brief  Registers the temperature server callback.
*
* \param[in] callback  Temperature server callback.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t MeshTemperatureServer_RegisterCallback
(
    meshTemperatureServerCallback_t callback
);

/*! *********************************************************************************
* \brief  Reports the temperature value to a unicast or multicast address.
*
* \param[in] destination  Destination address for the report.
* \param[in] tempCelsius  Temperature value in degrees Celsius.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshTemperatureServer_SendTemperature
(
    meshAddress_t   destination,
    int16_t         tempCelsius
);

/*! *********************************************************************************
* \brief  Publishes the temperature value to the configured publish address.
*
* \param[in] tempCelsius  Temperature value in degrees Celsius.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshTemperatureServer_PublishTemperature
(
    int16_t         tempCelsius
);

/*! *********************************************************************************
* \brief  Sends the periodic report settings to a temperature client.
*
* \param[in] destination        Destination address of the temperature client.
* \param[in] enabled            TRUE if period report is enabled, FALSE otherwise.
* \param[in] intervalSeconds    Report interval, measured in seconds, valid only if report is enabled.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshTemperatureServer_SendPeriodicReportState
(
    meshAddress_t   destination,
    bool_t          enabled,
    uint16_t        intervalSeconds
);

#ifdef __cplusplus
}
#endif

#endif /* _MESH_TEMPERATURE_SERVER_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
