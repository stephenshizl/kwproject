/*! *********************************************************************************
* \defgroup MESH_TEMP Mesh Temperature Profile
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file mesh_temperature_client.h
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

#ifndef _MESH_TEMPERATURE_CLIENT_H_
#define _MESH_TEMPERATURE_CLIENT_H_

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
/*! Temperature client event types. */
typedef enum meshTemperatureClientEventType_tag
{
    gMeshTemperatureReceivedTemperature_c,      /*!< Temperature has been reported by a temperature server. */
    gMeshTemperatureReceivedReportState_c,      /*!< Temperature report state has been reported by a temperature server. */
} meshTemperatureClientEventType_t;

/*! Temperature client event structure. */
typedef struct meshTemperatureClientEvent_tag
{
    meshTemperatureClientEventType_t  eventType;        /*!< Event type. */
    union
    {
        struct
        {
            meshAddress_t   source;         /*!< Temperature server address. */
            int16_t         tempCelsius;    /*!< Temperature value in degrees Celsius. */
        } receivedTemperature;  /*!< Data for gMeshTemperatureReceivedTemperature_c. */
        
        struct
        {
            meshAddress_t   source;             /*!< Temperature server address. */
            bool_t          reportOn;           /*!< Report state. */
            uint16_t        intervalSeconds;    /*!< Report interval, measured in seconds, valid if report state is TRUE. */
        } receivedReportState;  /*!< Data for gMeshTemperatureReceivedReportState_c. */
        
    } eventData;                                        /*!< Event data, interpreted based on event type. */
} meshTemperatureClientEvent_t;

/*! Temperature client event callback. */
typedef meshResult_t (*meshTemperatureClientCallback_t)
(
    meshTemperatureClientEvent_t* pEvent        /*!< Pointer to the event structure. */
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
* \brief  Registers the temperature client callback.
*
* \param[in] callback  Temperature client callback.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t MeshTemperatureClient_RegisterCallback
(
    meshTemperatureClientCallback_t callback
);

/*! *********************************************************************************
* \brief  Retrieves the temperature value from a temperature server.
*
* \param[in] destination        Destination address of the temperature server.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshTemperatureClient_GetTemperature
(
    meshAddress_t   destination
);

/*! *********************************************************************************
* \brief  Enables or disables the periodic report on a temperature server.
*
* \param[in] destination        Destination address of the temperature server.
* \param[in] enable             TRUE to enable the period report, FALSE to disable.
* \param[in] intervalSeconds    Report interval, measured in seconds, valid only when report is enabled.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshTemperatureClient_EnablePeriodicReports
(
    meshAddress_t   destination,
    bool_t          enable,
    uint16_t        intervalSeconds
);

/*! *********************************************************************************
* \brief  Retrieves the periodic report settings on a temperature server.
*
* \param[in] destination        Destination address of the temperature server.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshTemperatureClient_GetPeriodicReportState
(
    meshAddress_t   destination
);
   
#ifdef __cplusplus
}
#endif

#endif /* _MESH_TEMPERATURE_CLIENT_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
