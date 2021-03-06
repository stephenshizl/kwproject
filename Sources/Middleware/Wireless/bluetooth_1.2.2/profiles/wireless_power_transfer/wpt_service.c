/*! *********************************************************************************
 * \addtogroup WPT Custom Profile
 * @{
 ********************************************************************************** */
/*!
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * \file wpt_service.c
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

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "FunctionLib.h"
#include "ble_general.h"
#include "gatt_db_app_interface.h"
#include "gatt_db_handles.h"
#include "gatt_server_interface.h"
#include "gap_interface.h"
#include "wpt_interface.h"
/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/*! WPT Service - Subscribed Client*/
static deviceId_t mWpt_SubscribedPtuDevice;
static uint16_t mWpt_ServiceHandle = 0xFFFF;
/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/
static bleResult_t Wpt_SendAlertNotification
(
    uint16_t handle
);
/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
bleResult_t Wpt_Start 
(
 uint16_t serviceHandle, 
 wptPruStaticParamCharacteristic_t*  pPruStaticParameters
)
{    
        
    bleResult_t result;
    uint16_t handle;
    
    mWpt_SubscribedPtuDevice = gInvalidDeviceId_c;
    
    mWpt_ServiceHandle = serviceHandle;
    
    bleUuid_t* pUuid = (bleUuid_t*)uuid_characteristic_pru_static;
    
    /* Get handle of PRU Static characteristic */
    result = GattDb_FindCharValueHandleInService(mWpt_ServiceHandle,
                                                 gBleUuidType128_c, pUuid, &handle);
    if(result != gBleSuccess_c)
        return result;
    
    /* Update characteristic value */
    result = GattDb_WriteAttribute(handle, 
                                   20, 
                                   (uint8_t*)pPruStaticParameters);
    return result;
}

bleResult_t Wpt_Stop()
{
    return Wpt_Unsubscribe();
}

bleResult_t Wpt_Subscribe(deviceId_t deviceId)
{
    mWpt_SubscribedPtuDevice = deviceId;
    
    return gBleSuccess_c;
}

bleResult_t Wpt_Unsubscribe()
{
    uint8_t i = 0;
    uint16_t handle;
    uint8_t maResetValue[20] = {0};
    bleUuid_t* paUuid[4] = {
        (bleUuid_t*)uuid_characteristic_pru_dynamic, (bleUuid_t*)uuid_characteristic_ptu_static,
        (bleUuid_t*)uuid_characteristic_pru_control, (bleUuid_t*)uuid_characteristic_pru_alert
    };        
    uint16_t maHandleSizes[4] = {20, 17, 5, 1};
    bleResult_t result = gBleSuccess_c;
    
    for(i = 0; i < NumberOfElements(maHandleSizes); ++i)
    {  
        /* Get handle of the characteristics */
        result = GattDb_FindCharValueHandleInService(mWpt_ServiceHandle,
                                                     gBleUuidType128_c, paUuid[i], &handle);
        if(result != gBleSuccess_c)
            return result;
        
        result = GattDb_WriteAttribute(handle, maHandleSizes[i], maResetValue);
        if(gBleSuccess_c != result)
        {
            return result;
        }
    }
    mWpt_SubscribedPtuDevice = gInvalidDeviceId_c;
    
    return result;
}

bleResult_t Wpt_RecordPruDynamic
(
 wptPruDynamicParamCharacteristic_t* pPruDynamic
)
{
    bleResult_t result;
    uint16_t handle;
    
    bleUuid_t* pUuid = (bleUuid_t*)uuid_characteristic_pru_dynamic;
    
    /* Get handle of PRU Dynamic characteristic */
    result = GattDb_FindCharValueHandleInService(mWpt_ServiceHandle,
                                                 gBleUuidType128_c, pUuid, &handle);
    if(result != gBleSuccess_c)
        return result;
    
    /* Update characteristic value */
    result = GattDb_WriteAttribute(handle, 20, (uint8_t*)pPruDynamic);

    if (result != gBleSuccess_c)
        return result;
        
    return gBleSuccess_c;
}

bleResult_t Wpt_ReadCharacteristic
(
 uint8_t* charUuid128,
 uint8_t* aOutBuffer,
 uint16_t* pOutLen
)
{
    bleResult_t result;
    uint16_t handle;
    
    bleUuid_t* pUuid = (bleUuid_t*)charUuid128;

    /* Get handle of the characteristic */
    result = GattDb_FindCharValueHandleInService(mWpt_ServiceHandle,
        gBleUuidType128_c, pUuid, &handle);
    
    if(gBleSuccess_c != result)
        return result;
    
    result = GattDb_ReadAttribute(handle, 20, aOutBuffer, pOutLen);
    
    return result;
}
    
bleResult_t Wpt_RecordPruAlertAndNotifyIfCccdWritten
(
 wptPruAlertCharacteristic_t* pPruAlert
)
{
    bleResult_t result;
    uint16_t handle;

    bleUuid_t* pUuid = (bleUuid_t*)uuid_characteristic_pru_alert;
    
    /* Get handle of PRU Alert characteristic */
    result = GattDb_FindCharValueHandleInService(mWpt_ServiceHandle,
                                                 gBleUuidType128_c, pUuid, &handle);
    if(result != gBleSuccess_c)
        return result;
        /* Update characteristic value */
    result = GattDb_WriteAttribute(handle, 1, (uint8_t*)pPruAlert);
    
    if (result != gBleSuccess_c)
        return result;
    
    return Wpt_SendAlertNotification(handle);
}

bleResult_t Wpt_PruRecordPtuStaticParamCharacteristic
(
 wptPtuStaticParamCharacteristic_t* pPtuStatic
)
{
    bleResult_t result;
    uint16_t handle;
    
    bleUuid_t* pUuid = (bleUuid_t*)uuid_characteristic_ptu_static;
    
    /* Get handle of PRU Static characteristic */
    result = GattDb_FindCharValueHandleInService(mWpt_ServiceHandle,
                                                 gBleUuidType128_c, pUuid, &handle);
    if(result != gBleSuccess_c)
        return result;
    
    /* Update characteristic value */
    result = GattDb_WriteAttribute(handle, 17, (uint8_t*)pPtuStatic);
    
    if (result != gBleSuccess_c)
        return result;
    
    return gBleSuccess_c;
}
    
bleResult_t Wpt_PruRecordPruControlCharacteristic
(
 wptPruControlCharacteristic_t* pPruControl
)
{
    bleResult_t result;
    uint16_t handle;
    
    bleUuid_t* pUuid = (bleUuid_t*)uuid_characteristic_pru_control;
    
    /* Get handle of PRU Control characteristic */
    result = GattDb_FindCharValueHandleInService(mWpt_ServiceHandle,
                                                 gBleUuidType128_c, pUuid, &handle);
    if(result != gBleSuccess_c)
        return result;
    
    /* Update characteristic value */
    result = GattDb_WriteAttribute(handle, 5, (uint8_t*)pPruControl);
    
    if (result != gBleSuccess_c)
        return result;
    
    return gBleSuccess_c;
}
                                                 
/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/
static bleResult_t Wpt_SendAlertNotification
(
 uint16_t handle
)
{
    bleResult_t result;
    uint16_t  hCccd;
    bool_t isNotificationActive;

    /* Get handle of CCCD */
    result = GattDb_FindCccdHandleForCharValueHandle(handle, &hCccd);
    if (gBleSuccess_c != result)
        return result;

    result = Gap_CheckNotificationStatus(mWpt_SubscribedPtuDevice, 
                                         hCccd, 
                                         &isNotificationActive);
    if(gBleSuccess_c != result)
        return result;
    
    result = gBleSuccess_c;
    
    if (TRUE == isNotificationActive)
    {
        result = GattServer_SendNotification(mWpt_SubscribedPtuDevice, handle);
    }
    return result;
}

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
