/*! *********************************************************************************
* \defgroup MESH_LIGHT Mesh Light Profile
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file mesh_light_client.h
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

#ifndef _MESH_LIGHT_CLIENT_H_
#define _MESH_LIGHT_CLIENT_H_

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
/*! Light client event types. */
typedef enum meshLightClientEventType_tag
{
    gMeshLightReceivedLightState_c,     /*!< Light state has been reported by a light server. */
    gMeshLightReceivedReportState_c,    /*!< Light report state has been reported by a light server. */
} meshLightClientEventType_t;

/*! Light client event structure. */
typedef struct meshLightClientEvent_tag
{
    meshLightClientEventType_t  eventType;      /*!< Event type. */
    union
    {
        struct
        {
            meshAddress_t   source;     /*!< Light server address. */
            bool_t          lightOn;    /*!< Light state. */
        } receivedLightState;   /*!< Data for gMeshLightReceivedLightState_c. */
        
        struct
        {
            meshAddress_t   source;             /*!< Light server address. */
            bool_t          reportOn;           /*!< Report state. */
            uint16_t        intervalSeconds;    /*!< Report interval, measured in seconds, valid if report state is TRUE. */
        } receivedReportState;  /*!< Data for gMeshLightReceivedReportState_c. */
        
    } eventData;                                /*!< Event data, interpreted based on event type. */
} meshLightClientEvent_t;

/*! Light client event callback. */
typedef meshResult_t (*meshLightClientCallback_t)
(
    meshLightClientEvent_t* pEvent      /*!< Pointer to the event structure. */
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
* \brief  Registers the light client callback.
*
* \param[in] callback  Light client callback.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t MeshLightClient_RegisterCallback
(
    meshLightClientCallback_t callback
);

/*! *********************************************************************************
* \brief  Sets the light state on a light server.
*
* \param[in] destination        Destination address of the light server.
* \param[in] lightOn            New light state.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshLightClient_SetLightState
(
    meshAddress_t   destination,
    bool_t          lightOn
);

/*! *********************************************************************************
* \brief  Publishes the light set message on the configured publish address.
*
* \param[in] lightOn            New light state.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshLightClient_PublishSetLight
(
    bool_t          lightOn
);

/*! *********************************************************************************
* \brief  Retrieves the light state from a light server.
*
* \param[in] destination        Destination address of the light server.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshLightClient_GetLightState
(
    meshAddress_t   destination
);

/*! *********************************************************************************
* \brief  Toggles the light state on a light server.
*
* \param[in] destination        Destination address of the light server.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshLightClient_ToggleLight
(
    meshAddress_t   destination
);

/*! *********************************************************************************
* \brief  Publishes the light toggle message on the configured publish address.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshLightClient_PublishToggleLight();

/*! *********************************************************************************
* \brief  Enables or disables the periodic report on a light server.
*
* \param[in] destination        Destination address of the light server.
* \param[in] enable             TRUE to enable the period report, FALSE to disable.
* \param[in] intervalSeconds    Report interval, measured in seconds, valid only when report is enabled.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshLightClient_EnablePeriodicReports
(
    meshAddress_t   destination,
    bool_t          enable,
    uint16_t        intervalSeconds
);

/*! *********************************************************************************
* \brief  Retrieves the periodic report settings on a light server.
*
* \param[in] destination        Destination address of the light server.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshLightClient_GetPeriodicReportState
(
    meshAddress_t   destination
);
   
#ifdef __cplusplus
}
#endif

#endif /* _MESH_LIGHT_CLIENT_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
