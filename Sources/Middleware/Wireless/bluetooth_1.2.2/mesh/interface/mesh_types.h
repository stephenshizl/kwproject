/*! *********************************************************************************
* \addtogroup MESH
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file mesh_types.h
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

#ifndef _MESH_TYPES_H_
#define _MESH_TYPES_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "EmbeddedTypes.h"

/************************************************************************************
*************************************************************************************
* Public constants and macros
*************************************************************************************
************************************************************************************/
/*! Maximum application payload size for custom data. */
#define gMeshMaxAppCustomDataSize_c     14

/*! Size of commissioning data structure. */
#define gRawCommissioningDataSize_c     22

/*! Size of the mesh network key. */
#define gMeshKeySize_c                  16

/*! Maximum value of the TTL. */
#define gMaxTtl_c                       63

/*! Invalid value for a mesh address. */
#define gInvalidAddress_c               0x0000

/*! Bitmask identifying a multicast address. */
#define gMulticastAddressMask_c         0x2000

/*! The value of the broadcast address. */
#define gBroadcastAddress_c             0x3fff

/*! Checks for a valid mesh address. */
#define Mesh_IsValidAddress(address) (((address) > gInvalidAddress_c) && ((address) <= gBroadcastAddress_c))

/*! Checks for a valid unicast address. */
#define Mesh_IsValidUnicastAddress(address) (((address) > gInvalidAddress_c) && ((address) < gMulticastAddressMask_c))

/*! Checks for a valid multicast address. */
#define Mesh_IsValidMulticastAddress(address) ((((address) & gMulticastAddressMask_c) != 0) && ((address) < gBroadcastAddress_c))

/************************************************************************************
*************************************************************************************
* Public types
*************************************************************************************
************************************************************************************/
/*! Mesh error codes returned by the APIs. */
typedef enum meshResult_tag
{
    gMeshSuccess_c,                 /*!< No error. */
    gMeshInvalidParameter_c,        /*!< One or more invalid parameters have been provided. */
    gMeshOutOfMemory_c,             /*!< Failed to dynamically allocate a memory buffer. */
    gMeshOverflow_c,                /*!< Trying to add elements in a list or array that is already full. */
    gMeshPublishAddressNotSet_c,    /*!< Trying to publish without having set a publish address. */
    gMeshUnsupportedCommand_c,      /*!< Mesh library does not support this API. */
    gMeshInvalidState_c,            /*!< The API has been called while in an invalid state. */
} meshResult_t;

/*! Mesh address type. */
typedef uint16_t meshAddress_t;

/*! Mesh application profile identifier. */
typedef enum meshProfileId_tag
{
    gMeshProfileLighting_c,     /*!< Lighting profile. */
    gMeshProfileTemperature_c,  /*!< Temperature profile. */
} meshProfileId_t;

/*! Mesh custom data structure. */
typedef struct meshCustomData_tag
{
    uint16_t    dataLength;                             /*!< Length of custom data. */
    uint8_t     aData[gMeshMaxAppCustomDataSize_c];     /*!< Custom data. */
} meshCustomData_t;

/*! Mesh commissioning data opaque structure. */
typedef struct meshRawCommissioningData_tag
{
    uint8_t bytes[gRawCommissioningDataSize_c]; /*!< Raw bytes interpreted internally as commissioning data. */
} meshRawCommissioningData_t;

/*! Generic mesh event types. */
typedef enum meshGenericEventType_tag
{
    gMeshInitComplete_c,        /*!< Mesh stack has been initialized. */
    gMeshCustomDataReceived_c,  /*!< Custom application data has been received. */
} meshGenericEventType_t;

/*! Generic mesh event structure. */
typedef struct meshGenericEvent_tag
{
    meshGenericEventType_t  eventType;                  /*!< Event type. */
    union
    {
        struct
        {
            bool_t              deviceIsCommissioned;   /*!< TRUE if device has been commissioned, FALSE if it is an uncommissioned device. */
            meshAddress_t       localUnicastAddress;    /*!< The unicast address of this device, valid only if device has been commissioned. */
        } initComplete;         /*!< Data for gMeshInitComplete_c. */
        
        struct
        {
            meshAddress_t       source; /*!< Unicast address of the data sender. */
            meshCustomData_t    data;   /*!< Data that has been received. */
        } customDataReceived;   /*!< Data for gMeshCustomDataReceived_c. */
        
    } eventData;                                        /*!< Event data, interpreted based on event type. */
} meshGenericEvent_t;

/*! Generic mesh event callback. */
typedef meshResult_t (*meshGenericCallback_t)
(
    meshGenericEvent_t* pEvent  /*!< Pointer to the event structure. */
);

#endif /* _MESH_TYPES_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
