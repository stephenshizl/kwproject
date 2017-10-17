/*! *********************************************************************************
* \addtogroup MESH_CONFIG Mesh Configuration Profile
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file mesh_config_server.h
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

#ifndef _MESH_CONFIG_SERVER_H_
#define _MESH_CONFIG_SERVER_H_

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
/*! Configuration server event types. */
typedef enum meshConfigServerEventType_tag
{
    gMeshConfigRelayStateChanged_c,         /*!< Local relay state has been changed by the configuration client. */
    gMeshConfigTtlChanged_c,                /*!< Local TTL value has been changed by the configuration client. */
    gMeshConfigPublishAddressChanged_c,     /*!< Local publish address has been changed by the configuration client. */
    gMeshConfigSubscriptionListChanged_c,   /*!< Local subscription list has been changed by the configuration client. */
} meshConfigServerEventType_t;

/*! Configuration server event structure. */
typedef struct meshConfigServerEvent_tag
{
    meshConfigServerEventType_t  eventType;     /*!< Event type. */
    union
    {
        struct
        {
            bool_t relayEnabled;    /*!< New relay state. */
        } relayStateChanged;    /*!< Data for gMeshConfigRelayStateChanged_c. */
        
        struct
        {
            uint8_t ttl;    /*!< New TTL. */
        } ttlChanged;   /*!< Data for gMeshConfigTtlChanged_c. */
        
        struct
        {
            meshProfileId_t profileId;  /*!< Profile identifier. */
            meshAddress_t   address;    /*!< New publish address for the given profile. */
        } publishAddressChanged;    /*!< Data for gMeshConfigPublishAddressChanged_c. */
        
        struct
        {
            meshProfileId_t profileId;      /*!< Profile identifier. */
            uint8_t         listSize;       /*!< New subscription list size. */
            meshAddress_t*  aAddressList;   /*!< New subscription list for the given profile. */
        } subscriptionListChanged;  /*!< Data for gMeshConfigSubscriptionListChanged_c. */
        
    } eventData;                                /*!< Event data, interpreted based on event type. */
} meshConfigServerEvent_t;

/*! Configuration server event callback. */
typedef meshResult_t (*meshConfigServerCallback_t)
(
    meshConfigServerEvent_t* pEvent     /*!< Pointer to the event structure. */
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
* \brief  Registers the configuration server callback.
*
* \param[in] callback  Configuration server callback.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t MeshConfigServer_RegisterCallback
(
    meshConfigServerCallback_t callback
);
   
#ifdef __cplusplus
}
#endif

#endif /* _MESH_CONFIG_SERVER_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
