/*! *********************************************************************************
* \defgroup MESH Mesh Interface
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file mesh_interface.h
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

#ifndef _MESH_INTERFACE_H_
#define _MESH_INTERFACE_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "mesh_types.h"

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/
extern const uint8_t gMeshNetworkKey[gMeshKeySize_c];

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*
*
* Initialization and Commissioning
*
*/

/*! *********************************************************************************
* \brief  Initializes the mesh stack on a mesh node.
*
* \param[in] callback   Generic callback used to receive generic mesh events.
*
* \return  gMeshSuccess_c or error.
*
* \remarks Upon successful initialization, a gMeshInitComplete_c generic event 
*          is triggered in the generic callback.
*
********************************************************************************** */
meshResult_t MeshNode_Init
(
    meshGenericCallback_t callback
);

/*! *********************************************************************************
* \brief  Commissions an uncomissioned mesh node.
*
* \param[in] pRawCommissioningData   Pointer to the raw commissioning data structure
*                                    obtained over a secure channel.
*
* \return  gMeshSuccess_c or error.
*
* \remarks Upon successful commissioning, a gMeshInitComplete_c generic event 
*          is triggered in the generic callback.
*
********************************************************************************** */
meshResult_t MeshNode_Commission
(
    meshRawCommissioningData_t* pRawCommissioningData
);

/*! *********************************************************************************
* \brief  Initializes the mesh stack on a mesh commissioner.
*
* \param[in] callback   Generic callback used to receive generic mesh events.
*
* \return  gMeshSuccess_c or error.
*
* \remarks Upon successful initialization, a gMeshInitComplete_c generic event 
*          is triggered in the generic callback.
*
********************************************************************************** */
meshResult_t MeshCommissioner_Init
(
    meshGenericCallback_t genericCallback
);

/*! *********************************************************************************
* \brief  Retrieves commissioning data to be sent to an uncommissioned node.
*
* \param[out] pOutRawCommissioningData  Pointer to the raw commissioning data structure
*                                       to be filled.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t MeshCommissioner_GetNextCommissioningData
(
    meshRawCommissioningData_t* pOutRawCommissioningData
);

/*
*
* Send Custom Data
*
*/
/*! *********************************************************************************
* \brief  Sends custom application data to another mesh node.
*
* \param[in] destination  Address of the destination node.
* \param[in] pData        Data to be sent.
*
* \return  gMeshSuccess_c or error.
*
********************************************************************************** */
meshResult_t Mesh_SendCustomData
(
    meshAddress_t       destination,
    meshCustomData_t*   pData
);

/*
*
* Local Configuration
*
*/
/*! *********************************************************************************
* \brief  Sets local relay state.
*
* \param[in] enable  TRUE to enable relaying on the current node, FALSE to disable it.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t Mesh_SetRelayState
(
    bool_t enable
);

/*! *********************************************************************************
* \brief  Gets the local relay state.
*
* \param[out] pOutRelayEnabled  Will be set to TRUE if relaying is enabled on the current node and FALSE otherwise.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t Mesh_GetRelayState
(
    bool_t* pOutRelayEnabled
);

/*! *********************************************************************************
* \brief  Sets local TTL value, used when sending mesh messages.
*
* \param[in] ttl  TTL value, shall not be greater than gMaxTtl_c.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t Mesh_SetTtl
(
    uint8_t ttl
);

/*! *********************************************************************************
* \brief  Gets the local TTL value.
*
* \param[out] pOutTtl  Will be set to the local TTL.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t Mesh_GetTtl
(
    uint8_t* pOutTtl 
);

/*! *********************************************************************************
* \brief  Sets local publish address for a given application profile.
*
* \param[in] profileId  Profile identifier.
* \param[in] address    Publish address, shall be a valid multicast address.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t Mesh_SetPublishAddress
(
    meshProfileId_t profileId,
    meshAddress_t   address
);

/*! *********************************************************************************
* \brief  Gets local publish address for a given application profile.
*
* \param[in] profileId      Profile identifier.
* \param[in] pOutAddress    Will be set to the requested publish address.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t Mesh_GetPublishAddress
(
    meshProfileId_t profileId,
    meshAddress_t*  pOutAddress
);

/*! *********************************************************************************
* \brief  Subscribes local node to a publish address for a given application profile.
*
* \param[in] profileId  Profile identifier.
* \param[in] address    Publish address, shall be a valid multicast address.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t Mesh_Subscribe
(
    meshProfileId_t profileId,
    meshAddress_t   address
);

/*! *********************************************************************************
* \brief  Unsubscribes local node from a publish address for a given application profile.
*
* \param[in] profileId  Profile identifier.
* \param[in] address    Publish address, shall be a valid multicast address.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t Mesh_Unsubscribe
(
    meshProfileId_t profileId,
    meshAddress_t   address
);

/*! *********************************************************************************
* \brief  Gets the local subscription list for a given application profile.
*
* \param[in] profileId          Profile identifier.
* \param[in] maximumAddresses   Maximum number of addresses to be obtained.
* \param[out] aOutAddresses     Will be filled with addresses from the subscription list.
* \param[out] pOutAddressCount  Will contain the number of addresses filled in the array.
*
* \return  gMeshSuccess_c or error.
*
* \remarks This function executes synchronously.
*
********************************************************************************** */
meshResult_t Mesh_GetSubscriptionList
(
    meshProfileId_t profileId,
    uint8_t         maximumAddresses,
    meshAddress_t*  aOutAddresses,    
    uint8_t*        pOutAddressCount
);

#ifdef __cplusplus
}
#endif

#endif /* _MESH_INTERFACE_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
