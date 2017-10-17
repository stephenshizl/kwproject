//// GATT
//PRIMARY_SERVICE(service_gatt, gBleSig_GenericAttributeProfile_d)
//        CHARACTERISTIC(char_service_changed, gBleSig_GattServiceChanged_d, (gGattCharPropRead_c | gGattCharPropNotify_c) )
//            VALUE(value_service_changed, gBleSig_GattServiceChanged_d, (gPermissionNone_c), 4, 0x00, 0x00, 0x00, 0x00)
//            CCCD(cccd_service_changed)
//
//// GAP
//PRIMARY_SERVICE(service_gap, gBleSig_GenericAccessProfile_d)
//    CHARACTERISTIC(char_device_name, gBleSig_GapDeviceName_d, (gGattCharPropRead_c) )
//            VALUE(value_device_name, gBleSig_GapDeviceName_d, (gPermissionFlagReadable_c), 16, "FSL_WIRLESS_UART")
//    CHARACTERISTIC(char_appearance, gBleSig_GapAppearance_d, (gGattCharPropRead_c) )
//            VALUE(value_appearance, gBleSig_GapAppearance_d, (gPermissionFlagReadable_c), 2, 0x00, 0x00)

// Wireless Uart Service
PRIMARY_SERVICE_UUID128(service_wireless, uuid_service_wireless)
    CHARACTERISTIC_UUID128(char_uart_stream, uuid_uart_tx, (gGattCharPropWriteWithoutRsp_c))
        VALUE_UUID128_VARLEN(value_uart_stream, uuid_uart_tx, (gPermissionFlagWritable_c), gAttMaxWriteDataSize_d(gAttMaxMtu_c), 1, 0x00)

	CHARACTERISTIC_UUID128(char_temp_measurement, uuid_uart_rx, (gGattCharPropIndicate_c | gGattCharPropRead_c))
		VALUE_UUID128_VARLEN(value_temp_measurement, uuid_uart_rx, (gPermissionFlagReadable_c), 13, 1, 0)
		CCCD(cccd_temp_measurement)

// Health Thermometer Service
//PRIMARY_SERVICE_UUID128(service_health_therm, uuid_service_wireless_rx)
//	CHARACTERISTIC(char_temp_measurement, gBleSig_TemperatureMeasurement_d, (gGattCharPropIndicate_c | gGattCharPropRead_c))
//		VALUE_VARLEN(value_temp_measurement, gBleSig_TemperatureMeasurement_d, (gPermissionFlagReadable_c), 13, 5, 0x01, 0x02, 0x03, 0x04, 0x05)
//		CCCD(cccd_temp_measurement)

//	CHARACTERISTIC(char_temp_type, gBleSig_TemperatureType_d, (gGattCharPropRead_c))
//		VALUE(value_temp_type, gBleSig_TemperatureType_d, (gPermissionFlagReadable_c), 1, 0)
//	CHARACTERISTIC(char_interm_temp, gBleSig_IntermediateTemperature_d, (gGattCharPropNotify_c))
//		VALUE_VARLEN(value_interm_temp, gBleSig_IntermediateTemperature_d, (gPermissionNone_c), 13, 5, 0x00, 0x00, 0x00, 0x00, 0x00)
//		CCCD(cccd_interm_temp)
//	CHARACTERISTIC(char_measure_int, gBleSig_MeasurementInterval_d, (gGattCharPropRead_c | gGattCharPropIndicate_c | gGattCharPropWrite_c))
//		VALUE(value_measure_int, gBleSig_MeasurementInterval_d, (gPermissionFlagReadable_c | gPermissionFlagWritable_c | gPermissionFlagWriteWithAuthentication_c), 2, 0x01, 0x00)
//		CCCD(cccd_measure_int)
//		DESCRIPTOR(desc_measure_int, gBleSig_ValidRangeDescriptor_d, (gPermissionFlagReadable_c), 4, 0x01, 0x00, 0x05, 0x00)

// Battery Service
PRIMARY_SERVICE(service_battery, gBleSig_BatteryService_d)
    CHARACTERISTIC(char_battery_level, gBleSig_BatteryLevel_d, (gGattCharPropNotify_c | gGattCharPropRead_c))
        VALUE(value_battery_level, gBleSig_BatteryLevel_d, (gPermissionFlagReadable_c), 1, 0x5A)
        DESCRIPTOR(desc_bat_level, gBleSig_CharPresFormatDescriptor_d, (gPermissionFlagReadable_c), 7, 0x04, 0x00, 0xAD, 0x27, 0x01, 0x01, 0x00)
        CCCD(cccd_battery_level)

// Device information
PRIMARY_SERVICE(service_device_info, gBleSig_DeviceInformationService_d)
    CHARACTERISTIC(char_manuf_name, gBleSig_ManufacturerNameString_d, (gGattCharPropRead_c) )
        VALUE(value_manuf_name, gBleSig_ManufacturerNameString_d, (gPermissionFlagReadable_c), sizeof(MANUFACTURER_NAME), MANUFACTURER_NAME)
    CHARACTERISTIC(char_model_no, gBleSig_ModelNumberString_d, (gGattCharPropRead_c) )
        VALUE(value_model_no, gBleSig_ModelNumberString_d, (gPermissionFlagReadable_c), 18, "Wireless UART Demo")
    CHARACTERISTIC(char_serial_no, gBleSig_SerialNumberString_d, (gGattCharPropRead_c) )
        VALUE(value_serial_no, gBleSig_SerialNumberString_d, (gPermissionFlagReadable_c), 7, "BLESN01")
    CHARACTERISTIC(char_hw_rev, gBleSig_HardwareRevisionString_d, (gGattCharPropRead_c) )
        VALUE(value_hw_rev, gBleSig_HardwareRevisionString_d, (gPermissionFlagReadable_c), sizeof(BOARD_NAME), BOARD_NAME)
    CHARACTERISTIC(char_fw_rev, gBleSig_FirmwareRevisionString_d, (gGattCharPropRead_c) )
        VALUE(value_fw_rev, gBleSig_FirmwareRevisionString_d, (gPermissionFlagReadable_c), 5, "1.1.1")
    CHARACTERISTIC(char_sw_rev, gBleSig_SoftwareRevisionString_d, (gGattCharPropRead_c) )
        VALUE(value_sw_rev, gBleSig_SoftwareRevisionString_d, (gPermissionFlagReadable_c), 5, "1.1.4")
