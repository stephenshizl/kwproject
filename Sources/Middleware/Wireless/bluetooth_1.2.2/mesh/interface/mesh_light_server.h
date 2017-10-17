/*! *********************************************************************************
* \addtogroup MESH_LIGHT Mesh Light Profile
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file mesh_light_server.h
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

#ifndef _MESH_LIGHT_SERVER_H_
#define _MESH_LIGHT_SERVER_H_

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
/*! Light server event types. */
typedef enum meshLightServerEventType_tag
{
    gMeshLightSetCommand_c,         /*!< Received light set command from a light client. */
    gMeshLightGetCommand_c,         /*!< Received light get command from a light client. */
    gMeshLightToggleCommand_c,      /*!< Received light toggle command from a light client. */
    gMeshLightSetReportCommand_c,   /*!< Received light report set command from a light client. */
    gMeshLightGetReportCommand_c,   /*!< Received light report get command from a light client. */
} meshLightServerEventType_t;

/*! Light server event structure. */
typedef struct meshLightServerEvent_tag
{
    meshLightServerEventType_t  eventType;      /*!< Event type. */
    union
    {
        struct
        {
            meshAddress_t   source;         /*!< Light client address. */
            bool_t          lightState;     /*!< Requested light state. */
        } setCommand;   /*!< Data for gMeshLightSetCommand_c. */
        
        struct
        {
            meshAddress_t source;   /*!< Light client address. */
        } getCommand;   /*!< Data for gMeshLightGetCommand_c. */
        
        struct
        {
            meshAddress_t   source;             /*!< Light client address. */
            bool_t          enable;             /*!< Requested report state. */
            uint16_t        intervalSeconds;    /*!< Requested report interval, measured in seconds, valid only if requested report state is TRUE. */
        } setReportCommand; /*!< Data for gMeshLightSetReportCommand_c. */
    
        struct
        {
            meshAddress_t   source;     /*!< Light client address. */
        } getReportCommand; /*!< Data for gMeshLightGetReportCommand_c. */
        
    } eventData;                                /*!< Event data, interpreted based on event type. */    
} meshLightServerEvent_t;

/*! Light server event callback. */
typedef meshResult_t (*meshLightServerCallback_t)
(
    meshLightServerEvent_t* pEvent      /*!< Pointer to the event structure. */
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
* \brief  Registers the light server callback.
*
* \param[in] callback  Light server callback.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t MeshLightServer_RegisterCallback
(
    meshLightServerCallback_t callback
);

/*! *********************************************************************************
* \brief  Reports the light state to a unicast or multicast address.
*
* \param[in] destination    Destination address for the report.
* \param[in] lightState     Light state.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshLightServer_SendState
(    
    meshAddress_t   destination,
    bool_t          lightState
);

/*! *********************************************************************************
* \brief  Publishes the light state to the configured publish address.
*
* \param[in] lightState     Light state.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshLightServer_PublishState
(
    bool_t          lightState
);

/*! *********************************************************************************
* \brief  Sends the periodic report settings to a light client.
*
* \param[in] destination        Destination address of the light client.
* \param[in] enabled            TRUE if period report is enabled, FALSE otherwise.
* \param[in] intervalSeconds    Report interval, measured in seconds, valid only if report is enabled.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshLightServer_SendPeriodicReportState
(
    meshAddress_t   destination,
    bool_t          enabled,
    uint16_t        intervalSeconds
);
   
#ifdef __cplusplus
}
#endif

#endif /* _MESH_LIGHT_SERVER_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
