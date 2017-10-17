/*! *********************************************************************************
 * \addtogroup Wireless UART Application
 * @{
 ********************************************************************************** */
/*!
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 * \file app.c
 * This file is the source file for the Wireless UART Application
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
/* Framework / Drivers */
#include "RNG_Interface.h"
#include "Keyboard.h"
#include "LED.h"
#include "TimersManager.h"
#include "FunctionLib.h"
#include "Panic.h"
#include "SerialManager.h"
#include "MemManager.h"
#include "board.h"

/* BLE Host Stack */
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gap_interface.h"
#include "gatt_db_handles.h"

/* Profile / Services */
#include "wireless_uart_interface.h"
#include "battery_interface.h"
#include "current_time_interface.h"
#include "health_thermometer_interface.h"

/* Wrappers */
#include "ble_conn_manager.h"

#include "board.h"
#include "ApplMain.h"
#include "app.h"

/* 802.15.4 */
#include "PhyInterface.h"
#include "MacInterface.h"

/************************************************************************************
 *************************************************************************************
 * Private macros
 *************************************************************************************
 ************************************************************************************/
/*! Thermometer Intermediate Temperature Update Rate in ms */
#define mIntTempUpdateRate_c 1000
/* 802.15.4 definitions */
#define mDefaultValueOfChannel_c (0x07FFF800)
#define mDefaultValueOfShortAddress_c (0xCAFE)
#define mDefaultValueOfPanId_c (0xBEEF)
#define mMacExtendedAddress_c (0x1111111111111111)
#define mMaxKeysToReceive_c (32)

#define mAppUartBufferSize_c   			gAttMaxWriteDataSize_d(gAttMaxMtu_c) /* Local Buffer Size */

#define mAppUartFlushIntervalInMs_c   	(7) 	/* Flush Timeout in Ms */

#define mBatteryLevelReportInterval_c   (10)	/* battery level report interval in seconds  */
/************************************************************************************
 *************************************************************************************
 * Private type definitions
 *************************************************************************************
 ************************************************************************************/
typedef enum appEvent_tag{
    mAppEvt_PeerConnected_c,
    mAppEvt_PairingComplete_c,
    mAppEvt_ServiceDiscoveryComplete_c,
    mAppEvt_ServiceDiscoveryFailed_c,
    mAppEvt_GattProcComplete_c,
    mAppEvt_GattProcError_c
}appEvent_t;

typedef enum appState_tag
{
    mAppIdle_c,
    mAppExchangeMtu_c,
    mAppServiceDisc_c,
    mAppRunning_c
} appState_t;


typedef struct advState_tag
{
    bool_t advOn;
} advState_t;
/************************************************************************************
 *************************************************************************************
 * Private memory declarations
 *************************************************************************************
 ************************************************************************************/

uint8_t mMacInstance;
resultType_t MCPS_NWK_SapHandler (mcpsToNwkMessage_t* pMsg, instanceId_t instanceId);
resultType_t MLME_NWK_SapHandler (nwkMessage_t* pMsg, instanceId_t instanceId);


#if gAppUseBonding_d
static bool_t mRestoringBondedLink = FALSE;
#endif

/* Adv Parameters */
static advState_t mAdvState;
static bool_t   mScanningOn = FALSE;
static deviceId_t mPeerDeviceId = gInvalidDeviceId_c;

static uint16_t mCharMonitoredHandles[1] = { value_uart_stream};

/* Service Data*/
static htsUserData_t mUserData;

/* Service Data*/
static wusConfig_t mWuServiceConfig;
static basConfig_t mBasServiceConfig = {service_battery, 0};
//static htsConfig_t htsServiceConfig = { service_health_therm,
static htsConfig_t htsServiceConfig = { service_wireless,
        mIntTempUpdateRate_c,
        gHts_UnitInCelsius_c,
        &mUserData };

static tmrTimerID_t mAppTimerId;
static tmrTimerID_t mUartStreamFlushTimerId;
static tmrTimerID_t mBatteryMeasurementTimerId;

static uint8_t gAppSerMgrIf;
static appState_t mAppState = mAppIdle_c;


/************************************************************************************
 *************************************************************************************
 * Private functions prototypes
 *************************************************************************************
 ************************************************************************************/

/* Gatt and Att callbacks */
static void BleApp_AdvertisingCallback(gapAdvertisingEvent_t* pAdvertisingEvent);
static void BleApp_ConnectionCallback
(
    deviceId_t peerDeviceId,
    gapConnectionEvent_t* pConnectionEvent
);
static void BleApp_GattServerCallback
(
   deviceId_t deviceId,
   gattServerEvent_t* pServerEvent
);

static void BleApp_GattClientCallback
(
    deviceId_t              serverDeviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error
);

static void BleApp_Config (void);
static void BleApp_Advertise (void);

void BleApp_StateMachineHandler
(
    deviceId_t peerDeviceId,
    uint8_t event
);

static bool_t BleApp_CheckScanEvent (gapScannedDevice_t* pData);

/* Timer Callbacks */
static void ScaningTimerCallback (void *);
static void UartStreamFlushTimerCallback(void *);
static void BatteryMeasurementTimerCallback (void *);

/* Uart Tx/Rx Callbacks*/
static void Uart_RxCallBack(void *pData);
static void Uart_TxCallBack(void *pBuffer);

static void BleApp_FlushUartStream(void *pParam);
static void BleApp_ReceivedUartStream(uint8_t *pStream, uint16_t streamLength);
/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

resultType_t MLME_NWK_SapHandler(nwkMessage_t* pMsg, instanceId_t instanceId) {
	switch (pMsg->msgType) {
		case gMlmeScanCnf_c:
		/* Process the Scan confirm. */
		break;
		case gMlmeStartCnf_c:
		/* Process the MLME-START confirm. */
		break;
		case gMlmeAssociateInd_c:
		/* A device sent us an Associate Request. We must send back a response. */
		break;

		default:
			break;
}
	MEM_BufferFree( pMsg );
	return gSuccess_c;
}

resultType_t MCPS_NWK_SapHandler (mcpsToNwkMessage_t* pMsg, instanceId_t instanceId)
	{
	switch(pMsg->msgType)
		{
		case gMcpsDataCnf_c:
		/* The MCPS-Data confirm is sent by the MAC to the network
		or application layer when data has been sent. */
		break;
		case gMcpsDataInd_c:
		/* The MCPS-Data indication is sent by the MAC to the network
		or application layer when data has been received. */
		break;

		default:
			break;
		}
	MEM_BufferFree( pMsg );
	return gSuccess_c;
	}

/*! *********************************************************************************
* \brief    Initializes application specific functionality before the BLE stack init.
*
********************************************************************************** */
void BleApp_Init(void)
{
	//Initialize the MAC layer
	mMacInstance = BindToMAC(0);
	Mac_RegisterSapHandlers(MCPS_NWK_SapHandler, MLME_NWK_SapHandler, mMacInstance);

	/* Start 802.15.4 */
	//App_StartScan(gScanModeED_c);

    /* Initialize application support for drivers */
    BOARD_InitAdc();

    /* UI */
    SerialManager_Init();

    /* Register Serial Manager interface */
    Serial_InitInterface(&gAppSerMgrIf, APP_SERIAL_INTERFACE_TYPE, APP_SERIAL_INTERFACE_INSTANCE);

    Serial_SetBaudRate(gAppSerMgrIf, gUARTBaudRate115200_c);

    /* Install Controller Events Callback handler */
    Serial_SetRxCallBack(gAppSerMgrIf, Uart_RxCallBack, NULL);
}

/*! *********************************************************************************
 * \brief    Starts the BLE application.
 *
 * \param[in]    mGapRole    GAP Start Role (Central or Peripheral).
 ********************************************************************************** */
void BleApp_Start(void)
{
	gPairingParameters.localIoCapabilities = gIoDisplayOnly_c;
	BleApp_Advertise();
}

/*! *********************************************************************************
* \brief        Handles keyboard events.
*
* \param[in]    events    Key event structure.
********************************************************************************** */
void BleApp_HandleKeys(key_event_t events)
{
    switch (events)
    {
        case gKBD_EventPressPB1_c:
        {
            LED_StopFlashingAllLeds();
            Led1Flashing();

		BleApp_Start();
            break;
        }
        case gKBD_EventLongPB1_c:
        {
		if (mPeerDeviceId != gInvalidDeviceId_c)
			Gap_Disconnect(mPeerDeviceId);
            break;
        }
        case gKBD_EventPressPB2_c:
        case gKBD_EventLongPB2_c:
            break;
    default:
        break;
    }
}

/*! *********************************************************************************
* \brief        Handles BLE generic callback.
*
* \param[in]    pGenericEvent    Pointer to gapGenericEvent_t.
********************************************************************************** */
void BleApp_GenericCallback (gapGenericEvent_t* pGenericEvent)
{
    /* Call BLE Conn Manager */
    BleConnManager_GenericEvent(pGenericEvent);

    switch (pGenericEvent->eventType)
    {
        case gInitializationComplete_c:
        {
            BleApp_Config();
        }
        break;

        case gAdvertisingParametersSetupComplete_c:
        {
            App_StartAdvertising(BleApp_AdvertisingCallback, BleApp_ConnectionCallback);
        }
        break;

        default:
            break;
    }
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief        Configures BLE Stack after initialization. Usually used for
*               configuring advertising, scanning, white list, services, et al.
*
********************************************************************************** */
static void BleApp_Config()
{
    /* Configure as GAP Dual Role */
	BleConnManager_GapPeripheralConfig();

    /* Register for callbacks */
    App_RegisterGattServerCallback(BleApp_GattServerCallback);
    App_RegisterGattClientProcedureCallback(BleApp_GattClientCallback);
    GattServer_RegisterHandlesForWriteNotifications(NumberOfElements((mCharMonitoredHandles)), mCharMonitoredHandles);

    /* By default, always start node as GAP central */
    mAdvState.advOn = FALSE;
    mScanningOn = FALSE;

    /* Start services */
    Wus_Start(&mWuServiceConfig);

    mBasServiceConfig.batteryLevel = BOARD_GetBatteryLevel();
    Bas_Start(&mBasServiceConfig);
	Hts_Start(&htsServiceConfig);


    /* Allocate application timer */
    mAppTimerId = TMR_AllocateTimer();
    mUartStreamFlushTimerId = TMR_AllocateTimer();
    mBatteryMeasurementTimerId = TMR_AllocateTimer();

}

/*! *********************************************************************************
* \brief        Configures GAP Advertise parameters. Advertise will start after
*               the parameters are set.
*
********************************************************************************** */
static void BleApp_Advertise(void)
{
    /* Set advertising parameters*/
    Gap_SetAdvertisingParameters(&gAdvParams);
}

/*! *********************************************************************************
* \brief        Handles BLE Advertising callback from host stack.
*
* \param[in]    pAdvertisingEvent    Pointer to gapAdvertisingEvent_t.
********************************************************************************** */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent)
{
    switch (pAdvertisingEvent->eventType)
    {
        case gAdvertisingStateChanged_c:
        {
            mAdvState.advOn = !mAdvState.advOn;
            LED_StopFlashingAllLeds();
            Led1Flashing();

            if(!mAdvState.advOn)
            {
                Led2Flashing();
                Led3Flashing();
                Led4Flashing();
            }
        }
        break;

        case gAdvertisingCommandFailed_c:
        {
            panic(0,0,0,0);
        }
        break;

        default:
            break;
    }
}

/*! *********************************************************************************
* \brief        Handles BLE Connection callback from host stack.
*
* \param[in]    peerDeviceId        Peer device ID.
* \param[in]    pConnectionEvent    Pointer to gapConnectionEvent_t.
********************************************************************************** */
static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent)
{
    switch (pConnectionEvent->eventType)
    {
        case gConnEvtConnected_c:
        {
		mPeerDeviceId = peerDeviceId;

            /* Advertising stops when connected */
            mAdvState.advOn = FALSE;

            /* Subscribe client*/
            Wus_Subscribe(peerDeviceId);
            Bas_Subscribe(peerDeviceId);
		Hts_Subscribe(peerDeviceId);


            /* UI */
            LED_StopFlashingAllLeds();
            Led1On();

            /* Stop Advertising Timer*/
            mAdvState.advOn = FALSE;
            TMR_StopTimer(mAppTimerId);

            /* Start battery measurements */
            TMR_StartLowPowerTimer(mBatteryMeasurementTimerId, gTmrLowPowerIntervalMillisTimer_c,
                       TmrSeconds(mBatteryLevelReportInterval_c), BatteryMeasurementTimerCallback, NULL);

#if gAppUsePairing_d


#if gAppUseBonding_d
            Gap_CheckIfBonded(peerDeviceId, &mPeerInformation.isBonded);

            if ((mPeerInformation.isBonded) &&
                (gBleSuccess_c == Gap_LoadCustomPeerInformation(peerDeviceId,
                    (void*) &mPeerInformation.clientInfo, 0, sizeof (wucConfig_t))))
            {
                mRestoringBondedLink = TRUE;
                /* Restored custom connection information. Encrypt link */
                Gap_EncryptLink(peerDeviceId);
            }
            else
#endif /* gAppUseBonding_d*/
            {
                if (mGapRole == gGapCentral_c)
                {
//                    Gap_Pair(peerDeviceId, &gPairingParameters);
                }
            }
#endif /* gAppUsePairing_d */
		BleApp_StateMachineHandler(mPeerDeviceId, mAppEvt_PeerConnected_c);
        }
        break;

        case gConnEvtDisconnected_c:
        {
		mAppState = mAppIdle_c;

            /* Unsubscribe client */
            Wus_Unsubscribe();
            Bas_Unsubscribe();

            TMR_StopTimer(mBatteryMeasurementTimerId);

            /* UI */
            LED_TurnOffAllLeds();
            LED_StartFlash(LED_ALL);

		BleApp_Start();

        }
        break;

#if gAppUsePairing_d
        case gConnEvtPairingComplete_c:
        {
            if (pConnectionEvent->eventData.pairingCompleteEvent.pairingSuccessful)
            {
                BleApp_StateMachineHandler(peerDeviceId, mAppEvt_PairingComplete_c);
            }
        }
        break;
#endif /* gAppUsePairing_d */

    default:
        break;
    }

    /* Connection Manager to handle Host Stack interactions */
	BleConnManager_GapPeripheralEvent(peerDeviceId, pConnectionEvent);
}

/*! *********************************************************************************
* \brief        Handles GATT client callback from host stack.
*
* \param[in]    serverDeviceId      GATT Server device ID.
* \param[in]    procedureType    	Procedure type.
* \param[in]    procedureResult    	Procedure result.
* \param[in]    error    			Callback result.
********************************************************************************** */
static void BleApp_GattClientCallback(
    deviceId_t              serverDeviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error
)
{
    if (procedureResult == gGattProcError_c)
    {
        BleApp_StateMachineHandler(serverDeviceId, mAppEvt_GattProcError_c);
    }
    else if (procedureResult == gGattProcSuccess_c)
    {
    	BleApp_StateMachineHandler(serverDeviceId, mAppEvt_GattProcComplete_c);
    }

}

/*! *********************************************************************************
 * \brief        Handles GATT server callback from host stack.
 *
 * \param[in]    deviceId        Client peer device ID.
 * \param[in]    pServerEvent    Pointer to gattServerEvent_t.
 ********************************************************************************** */
static void BleApp_GattServerCallback (
                                       deviceId_t deviceId,
                                       gattServerEvent_t* pServerEvent)
{
    switch (pServerEvent->eventType)
    {
        case gEvtAttributeWrittenWithoutResponse_c:
        {
            if (pServerEvent->eventData.attributeWrittenEvent.handle == value_uart_stream)
            {
            	BleApp_ReceivedUartStream(pServerEvent->eventData.attributeWrittenEvent.aValue,
                            pServerEvent->eventData.attributeWrittenEvent.cValueLength);
            }
            break;
        }
    default:
        break;
    }
}


static bool_t MatchDataInAdvElementList (
                                         gapAdStructure_t *pElement,
                                         void *pData,
                                         uint8_t iDataLen)
{
    uint8_t i;

    for (i = 0; i < pElement->length; i += iDataLen)
    {
        if (FLib_MemCmp(pData, &pElement->aData[i], iDataLen))
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*! *********************************************************************************
 * \brief        Checks Scan data for a device to connect.
 *
 * \param[in]    pData    Pointer to gapScannedDevice_t.
 ********************************************************************************** */
static bool_t BleApp_CheckScanEvent (gapScannedDevice_t* pData)
{
    uint8_t index = 0;
    bool_t foundMatch = FALSE;

    while (index < pData->dataLength)
    {
        gapAdStructure_t adElement;

        adElement.length = pData->data[index];
        adElement.adType = (gapAdType_t) pData->data[index + 1];
        adElement.aData = &pData->data[index + 2];

        /* Search for Temperature Custom Service */
        if ((adElement.adType == gAdIncomplete128bitServiceList_c)
            || (adElement.adType == gAdComplete128bitServiceList_c))
        {
            foundMatch = MatchDataInAdvElementList(&adElement,
                &uuid_service_wireless, 16);
        }

        /* Move on to the next AD elemnt type */
        index += adElement.length + sizeof(uint8_t);
    }

    return foundMatch;
}

static void BleApp_SendUartStream(deviceId_t deviceId, uint8_t *pRecvStream, uint8_t streamSize)
{
    gattCharacteristic_t characteristic;

	characteristic.value.handle = uuid_service_wireless;

    GattClient_WriteCharacteristicValue(deviceId, &characteristic,
                                        streamSize, pRecvStream, TRUE,
                                        FALSE, FALSE, NULL);
}

void BleApp_StateMachineHandler(deviceId_t peerDeviceId, uint8_t event)
{
	switch (mAppState)
    {
        case mAppIdle_c:
        {
            if (event == mAppEvt_PeerConnected_c)
            {
                /* Let the central device initiate the Exchange MTU procedure*/
			/* Moving to Exchange MTU State */
			mAppState = mAppExchangeMtu_c;
			GattClient_ExchangeMtu(peerDeviceId);
            }
        }
        break;

        case mAppExchangeMtu_c:
        {
            if (event == mAppEvt_GattProcComplete_c)
            {
                /* Moving to Service Discovery State*/
			mAppState = mAppRunning_c;
            }
            else if (event == mAppEvt_GattProcError_c)
            {
                Gap_Disconnect(peerDeviceId);
            }
        }
        break;

        case mAppRunning_c:
                break;
        default:
                break;
    }
}

/*! *********************************************************************************
 * \brief        Handles scanning timer callback.
 *
 * \param[in]    pParam        Calback parameters.
 ********************************************************************************** */
static void ScaningTimerCallback (void * pParam)
{
    /* Stop scanning and start advertising */
    Gap_StopScanning();
    gPairingParameters.localIoCapabilities = gIoDisplayOnly_c;

    BleApp_Advertise();
}


static void BleApp_FlushUartStream(void *pParam)
{
	uint8_t *pMsg = NULL;
	uint16_t bytesRead = 0;

//    if (mPeerInformation.appState != mAppRunning_c)
//    {
//        return;
//    }

    /* Allocate buffer for GATT Write */
    pMsg = MEM_BufferAlloc(mAppUartBufferSize_c);
    if (pMsg == NULL)
    {
    	return;
    }

    /* Collect the data from the serial manager buffer */
    if ( Serial_Read( gAppSerMgrIf, pMsg, mAppUartBufferSize_c, &bytesRead) == gSerial_Success_c )
    {
        if (bytesRead != 0)
        {
            /* Send data over the air */
//            BleApp_SendUartStream(mPeerDeviceId, pMsg, bytesRead);
//			Hts_RecordTemperatureMeasurement(service_health_therm, &pMsg);
			Hts_RecordTemperatureMeasurement(service_wireless, pMsg, bytesRead);
        }
    }
    /* Free Buffer */
    MEM_BufferFree(pMsg);
}

static void BleApp_ReceivedUartStream(uint8_t *pStream, uint16_t streamLength)
{
    uint8_t *pBuffer = NULL;

    /* Allocate buffer for asynchronous write */
    pBuffer = MEM_BufferAlloc(streamLength);

    if (pBuffer != NULL)
    {
        Serial_AsyncWrite(gAppSerMgrIf, pStream, streamLength, Uart_TxCallBack, pBuffer);
    }
}

static void UartStreamFlushTimerCallback(void *pData)
{
    App_PostCallbackMessage(BleApp_FlushUartStream, NULL);
}

/*! *********************************************************************************
* \brief        Handles UART Receive callback.
*
* \param[in]    pData        Parameters.
********************************************************************************** */
static void Uart_RxCallBack(void *pData)
{
    uint16_t byteCount;

    Serial_RxBufferByteCount(gAppSerMgrIf, &byteCount);

    if (byteCount < mAppUartBufferSize_c)
    {
		/* Restart flush timer */
		TMR_StartLowPowerTimer(mUartStreamFlushTimerId,
			gTmrLowPowerSingleShotMillisTimer_c,
			mAppUartFlushIntervalInMs_c,
			UartStreamFlushTimerCallback, NULL);
    }
    else
    {
    	App_PostCallbackMessage(BleApp_FlushUartStream, NULL);
    }
}

/*! *********************************************************************************
* \brief        Handles UART Transmit callback.
*
* \param[in]    pData        Parameters.
********************************************************************************** */
static void Uart_TxCallBack(void *pBuffer)
{
    MEM_BufferFree(pBuffer);
}


/*! *********************************************************************************
* \brief        Handles battery measurement timer callback.
*
* \param[in]    pParam        Calback parameters.
********************************************************************************** */
static void BatteryMeasurementTimerCallback(void * pParam)
{
    mBasServiceConfig.batteryLevel = BOARD_GetBatteryLevel();
    Bas_RecordBatteryMeasurement(mBasServiceConfig.serviceHandle, mBasServiceConfig.batteryLevel);
}

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
