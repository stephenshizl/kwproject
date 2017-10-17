/*! *********************************************************************************
* \defgroup HTTP Proxy Service
* @{
*********************************************************************************** */
/*!
* Copyright (c) 2016, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file http_proxy_interface.h
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

#ifndef _HTTP_PROXY_INTERFACE_H_
#define _HTTP_PROXY_INTERFACE_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/
typedef enum
{
    gHps_State_Idle_c = 0x00,
    gHps_State_Busy_c,
} hpsState_tag;

typedef uint8_t hpsState_t;

typedef enum
{
    gHps_HTTP_GET_Req_c = 0x01,
    gHps_HTTP_HEAD_Req_c,
    gHps_HTTP_POST_Req_c,
    gHps_HTTP_PUT_Req_c,
    gHps_HTTP_DELETE_Req_c,
    gHps_HTTPS_GET_Req_c,
    gHps_HTTPS_HEAD_Req_c,
    gHps_HTTPS_POST_Req_c,
    gHps_HTTPS_PUT_Req_c,
    gHps_HTTPS_DELETE_Req_c,
    gHps_HTTP_Req_Cancel_c,
    
} hpsHttpCommand_tag;

typedef uint8_t hpsHttpCommand_t;

typedef uint16_t hpsStatusCode_t;

typedef enum
{
    gHps_HeadersReceived_c      = 0x01,
    gHps_HeadersTruncated_c     = 0x02,
    gHps_BodyReceived_c         = 0x04,
    gHps_BodyTruncated_c        = 0x08,
} hpsDataStatus_tag;

typedef uint8_t hpsDataStatus_t;

typedef struct hpsHttpStatusCode_tag
{
    hpsStatusCode_t     statusCode;
    hpsDataStatus_t     dataStatus;
} hpsHttpStatusCode_t;

typedef enum
{
    gHps_UriSet         = 0x01,
    gHps_HeadersSet     = 0x02,
    gHps_BodySet        = 0x04
} hpsFlags_tag;

typedef uint8_t hpsFlags_t;

typedef enum
{
    gHpsErrCodeInvalidRequest_c                 = 0x81,
    gHpsErrCodeCccdImproperlyConfigured_c       = 0xFD,
    gHpsErrCodeProcedureAlreadyInProgress_c     = 0xFE,
} attErrorCode_tag;

/*! Pulse Oximeter Service - Configuration */
typedef struct hpsConfig_tag
{
    uint16_t            serviceHandle;
    uint8_t             uriLength;
    uint8_t*            uri;
    uint16_t            httpHeadersLength;
    uint8_t*            httpHeaders;
    uint16_t            httpBodyLength;
    uint8_t*            httpBody;
    hpsHttpStatusCode_t httpStatusCode;
    hpsHttpCommand_t    command;
    hpsState_t          state;
    hpsFlags_t          flags;
} hpsConfig_t;

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!**********************************************************************************
* \brief        Starts HTTP Proxy Service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server 
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hps_Start (hpsConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Stops HTTP Proxy Service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server 
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hps_Stop (hpsConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Subscribes a GATT client to the HTTP Proxy service
*
* \param[in]    clientdeviceId  Client Id in Device DB
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hps_Subscribe(deviceId_t clientdeviceId);

/*!**********************************************************************************
* \brief        Unsubscribes a GATT client from the HTTP Proxy service
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Hps_Unsubscribe();

/*!**********************************************************************************
* \brief        Handles write operations on the URI characteristic.
*
* \param[in]    pServiceConfig	Pointer to structure that contains server 
*                               configuration information.
*
* \param[in]    pEvent			Pointer to the GATT Server event.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t     Hps_URIWrittenHandler(hpsConfig_t *pServiceConfig, gattServerAttributeWrittenEvent_t *pEvent);

/*!**********************************************************************************
* \brief        Handles write operations on the HTTP Headers characteristic.
*
* \param[in]    pServiceConfig	Pointer to structure that contains server 
*                               configuration information.
*
* \param[in]    pEvent			Pointer to the GATT Server event.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t     Hps_HTTPHeadersWrittenHandler(hpsConfig_t *pServiceConfig, gattServerAttributeWrittenEvent_t *pEvent);

/*!**********************************************************************************
* \brief        Handles write operations on the HTTP Body characteristic.
*
* \param[in]    pServiceConfig	Pointer to structure that contains server 
*                               configuration information.
*
* \param[in]    pEvent			Pointer to the GATT Server event.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t     Hps_HTTPBodyWrittenHandler(hpsConfig_t *pServiceConfig, gattServerAttributeWrittenEvent_t *pEvent);

/*!**********************************************************************************
* \brief        Handles write operations on the HTTP CP characteristic.
*
* \param[in]    pServiceConfig	Pointer to structure that contains server 
*                               configuration information.
*
* \param[in]    pEvent			Pointer to the GATT Server event.
*
* \return       gHpsSuccess_c or error.
************************************************************************************/
uint16_t        Hps_HTTPControlPointHandler(hpsConfig_t *pServiceConfig, gattServerAttributeWrittenEvent_t *pEvent);

/*!**********************************************************************************
* \brief        Updates the HTTP Headers characteristic.
*
* \param[in]    pServiceConfig	Pointer to structure that contains server 
*                               configuration information.
*
* \param[in]    pEvent			Pointer to the GATT Server event.
*
* \return       gHpsSuccess_c or error.
************************************************************************************/
bleResult_t     Hps_UpdateHttpHeadersChar (hpsConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Updates the HTTP Body characteristic.
*
* \param[in]    pServiceConfig	Pointer to structure that contains server 
*                               configuration information.
*
* \param[in]    pEvent			Pointer to the GATT Server event.
*
* \return       gHpsSuccess_c or error.
************************************************************************************/
bleResult_t     Hps_UpdateHttpBodyChar (hpsConfig_t *pServiceConfig);

#ifdef __cplusplus
}
#endif 

#endif /* _HTTP_PROXY_INTERFACE_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */