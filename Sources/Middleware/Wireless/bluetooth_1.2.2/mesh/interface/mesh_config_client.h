/*! *********************************************************************************
* \defgroup MESH_CONFIG Mesh Configuration Profile
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file mesh_config_client.h
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

#ifndef _MESH_CONFIG_CLIENT_H_
#define _MESH_CONFIG_CLIENT_H_

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
/*! Configuration client event types. */
typedef enum meshConfigClientEventType_tag
{
    gMeshConfigReceivedRelayState_c,        /*!< Relay state has been reported by a configuration server. */
    gMeshConfigReceivedTtl_c,               /*!< TTL value has been reported by a configuration server. */
    gMeshConfigReceivedPublishAddress_c,    /*!< Publish address has been reported by a configuration server. */
    gMeshConfigReceivedSubscriptionList_c,  /*!< Subscription list has been reported by a configuration server. */
} meshConfigClientEventType_t;

/*! Configuration client event structure. */
typedef struct meshConfigClientEvent_tag
{
    meshConfigClientEventType_t  eventType;     /*!< Event type. */ 
    union
    {
        struct
        {
            meshAddress_t   source;         /*!< Configuration server address. */
            bool_t          relayEnabled;   /*!< Relay state. */
        } receivedRelayState;   /*!< Data for gMeshConfigReceivedRelayState_c. */
        
        struct
        {
            meshAddress_t   source;     /*!< Configuration server address. */
            uint8_t         ttl;        /*!< TTL value. */
        } receivedTtl;      /*!< Data for gMeshConfigReceivedTtl_c. */
        
        struct
        {
            meshAddress_t   source;     /*!< Configuration server address. */
            meshProfileId_t profileId;  /*!< Profile identifier. */
            meshAddress_t   address;    /*!< Publish address for the given profile. */
        } receivedPublishAddress;   /*!< Data for gMeshConfigReceivedPublishAddress_c. */
        
        struct
        {
            meshAddress_t   source;         /*!< Configuration server address. */
            meshProfileId_t profileId;      /*!< Profile identifier. */
            uint8_t         listSize;       /*!< Subscription list size. */
            meshAddress_t*  aAddressList;   /*!< Susbcription list for the given profile. */
        } receivedSubscriptionList; /*!< Data for gMeshConfigReceivedSubscriptionList_c. */
        
    } eventData;                                /*!< Event data, interpreted based on event type. */
} meshConfigClientEvent_t;

/*! Configuration client event callback. */
typedef meshResult_t (*meshConfigClientCallback_t)
(
    meshConfigClientEvent_t* pEvent     /*!< Pointer to the event structure. */
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
* \brief  Registers the configuration client callback.
*
* \param[in] callback  Configuration client callback.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t MeshConfigClient_RegisterCallback
(
    meshConfigClientCallback_t callback
);

/*! *********************************************************************************
* \brief  Enables or disables relaying on a configuration server.
*
* \param[in] destination        Destination address of the configuration server.
* \param[in] enable             TRUE to enable relaying, FALSE to disable.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshConfigClient_EnableRelay
(
    meshAddress_t   destination,
    bool_t          enable
);

/*! *********************************************************************************
* \brief  Retrieves the relay state from a configuration server.
*
* \param[in] destination        Destination address of the configuration server.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshConfigClient_GetRelayState
(
    meshAddress_t   destination
);

/*! *********************************************************************************
* \brief  Sets the TTL value on a configuration server.
*
* \param[in] destination        Destination address of the configuration server.
* \param[in] ttl                New TTL value, shall not be greater than gMaxTtl_c.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshConfigClient_SetTtl
(
    meshAddress_t   destination,
    uint8_t         ttl
);

/*! *********************************************************************************
* \brief  Retrieves the TTL value from a configuration server.
*
* \param[in] destination        Destination address of the configuration server.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshConfigClient_GetTtl
(
    meshAddress_t   destination
);

/*! *********************************************************************************
* \brief  Sets the publish address on a configuration server.
*
* \param[in] destination        Destination address of the configuration server.
* \param[in] profileId          Profile identifier.
* \param[in] publishAddress     New publish address, shall be a valid multicast address.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshConfigClient_SetPublishAddress
(
    meshAddress_t   destination,
    meshProfileId_t profileId,
    meshAddress_t   publishAddress
);

/*! *********************************************************************************
* \brief  Retrieves the publish address from a configuration server.
*
* \param[in] destination        Destination address of the configuration server.
* \param[in] profileId          Profile identifier.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshConfigClient_GetPublishAddress
(
    meshAddress_t   destination,
    meshProfileId_t profileId
);

/*! *********************************************************************************
* \brief  Subscribes a configuration server to a publish address.
*
* \param[in] destination            Destination address of the configuration server.
* \param[in] profileId              Profile identifier.
* \param[in] subscriptionAddress    Publish address to subscribe to, shall be a valid multicast address.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshConfigClient_Subscribe
(
    meshAddress_t   destination,
    meshProfileId_t profileId,
    meshAddress_t   subscriptionAddress
);

/*! *********************************************************************************
* \brief  Unsubscribes a configuration server from a publish address.
*
* \param[in] destination            Destination address of the configuration server.
* \param[in] profileId              Profile identifier.
* \param[in] subscriptionAddress    Publish address to unsubscribe from, shall be a valid multicast address.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshConfigClient_Unsubscribe
(
    meshAddress_t   destination,
    meshProfileId_t profileId,
    meshAddress_t   subscriptionAddress
);

/*! *********************************************************************************
* \brief  Retrieves the subscription list from a configuration server.
*
* \param[in] destination        Destination address of the configuration server.
* \param[in] profileId          Profile identifier.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t MeshConfigClient_GetSubscriptionList
(
    meshAddress_t   destination,
    meshProfileId_t profileId
);
   
#ifdef __cplusplus
}
#endif

#endif /* _MESH_CONFIG_CLIENT_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
