/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : pin_mux.c
**     Project     : frdmkw41z
**     Processor   : MKW41Z512VHT4
**     Component   : PinSettings
**     Version     : Component 01.002, Driver 1.1, CPU db: 3.00.000
**     Compiler    : IAR ARM C Compiler
**     Date/Time   : 2013-12-10, 14:58, # CodeGen: 7
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         GPIO                - void pin_mux_GPIO(uint32_t instance);
**         I2C                 - void pin_mux_I2C(uint32_t instance);
**         TPM                 - void pin_mux_TPM(uint32_t instance);
**         RTC                 - void pin_mux_RTC(uint32_t instance);
**         SPI                 - void pin_mux_SPI(uint32_t instance);
**         LPUART              - void pin_mux_LPUART(uint32_t instance);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file pin_mux.c
** @version 1.1
** @brief
**
*/
/*!
**  @addtogroup pin_mux_module pin_mux module documentation
**  @{
*/

/* MODULE pin_mux. */

#include "fsl_device_registers.h"
#include "fsl_port.h"
#include "board.h"
#include "GPIO_Adapter.h"  
#include "pin_mux.h"

  
void configure_gpio_pins(uint32_t instance)
{
  switch(instance) {
    case 0:                             /* PTA */
      /* PORTA_PCR18 */
      GpioSetPinMux(gpioPort_A_c, 18u, pinMux_Gpio_c);
      /* PORTA_PCR19 */
      GpioSetPinMux(gpioPort_A_c, 19u, pinMux_Gpio_c);
      break;
    case 1:                             /* PTB */
      break;
    case 2:                             /* PTC */
      /* PORTC_PCR1 */
      GpioSetPinMux(gpioPort_C_c, 1u, pinMux_Gpio_c);
#if gKBD_TsiElectdCount_c > 0
      GpioSetPinMux(gpioPort_C_c, 16, pinMux_PinDisabledOrAnalog_c);
#endif
#if gKBD_TsiElectdCount_c > 1
      GpioSetPinMux(gpioPort_C_c, 19, pinMux_PinDisabledOrAnalog_c);
#endif
      break;
    default:
      break;
  }
}

void configure_i2c_pins(uint32_t instance)
{
  switch(instance) {
    case 0:                          /* I2C0 */
      /* PORTB_PCR0 */
      GpioSetPinMux(gpioPort_B_c, 0u, pinMux_Alt3_c);
      GpioSetPinPullMode(gpioPort_B_c, 0u, pinPull_Up_c);
      GpioSetPassiveFilter(gpioPort_B_c, 0u, false);
      /* PORTB_PCR1 */
      GpioSetPinMux(gpioPort_B_c, 1u, pinMux_Alt3_c);
      GpioSetPinPullMode(gpioPort_B_c, 1u, pinPull_Up_c);
      GpioSetPassiveFilter(gpioPort_B_c, 1u, false);

      break;
    case 1:
      /* PORTC_PCR2 */
      GpioSetPinMux(gpioPort_C_c, 2u, pinMux_Alt3_c);
      GpioSetPinPullMode(gpioPort_C_c, 2u, pinPull_Up_c);
      GpioSetPassiveFilter(gpioPort_C_c, 2u, false);
      /* PORTC_PCR3 */
      GpioSetPinMux(gpioPort_C_c, 3u, pinMux_Alt3_c);
      GpioSetPinPullMode(gpioPort_C_c, 3u, pinPull_Up_c);
      GpioSetPassiveFilter(gpioPort_C_c, 3u, false);
      break;
    case 2:
      break;
    case 3:
      break;
      case 4:
      break;
    default:
      break;
  }
}

void configure_rtc_pins(uint32_t instance)
{
    /* PORTB_PCR3 */
    GpioSetPinMux(gpioPort_B_c, 3u, pinMux_Alt7_c);

}

void configure_lpuart_pins(uint32_t instance)
{
  switch(instance) {
    case 0:                             /* LPUART0 */
#if (BOARD_UART_CONFIG == BOARD_USE_DEBUG_UART)
      /* PORTC_PCR6 */
      GpioSetPinMux(gpioPort_C_c, 6u, pinMux_Alt4_c);/* RX */
      /* PORTC_PCR7 */
      GpioSetPinMux(gpioPort_C_c, 7u, pinMux_Alt4_c);/* TX */
#elif (BOARD_UART_CONFIG == BOARD_USE_FRDM_HDR_UART)
      /* PORTC_PCR17 */
      GpioSetPinMux(gpioPort_C_c, 17u, pinMux_Alt4_c);/* RX */
      /* PORTC_PCR18 */
      GpioSetPinMux(gpioPort_C_c, 18u, pinMux_Alt4_c);/* TX */
#elif (BOARD_UART_CONFIG == BOARD_USE_FRDM_HDR_UART_ALT)
      /* PORTC_PCR2 */
      GpioSetPinMux(gpioPort_C_c, 2u, pinMux_Alt4_c);/* RX */ /* Shared with default I2C1_SCL */
      /* PORTC_PCR3 */
      GpioSetPinMux(gpioPort_C_c, 3u, pinMux_Alt4_c);/* TX */ /* Shared with default I2C1_SDA */
      /* PORTC_PCR0 */
      GpioSetPinMux(gpioPort_C_c, 0u, pinMux_Alt4_c);/* CTS */ /* Shared with default LED4 */
      /* PORTC_PCR1 */
      GpioSetPinMux(gpioPort_C_c, 1u, pinMux_Alt4_c);/* RTS */ /* Shared with default LED3 */
#endif      
      break;
    default:
      break;
  }
}

void configure_spi_pins(uint32_t instance)
{
  switch(instance) {
    case 0:                          /* SPI0 */
      /* PORTC_PCR18 */
      GpioSetPinMux(gpioPort_C_c, 18u, pinMux_Alt2_c); /* MOSI */
      /* PORTC_PCR17 */
      GpioSetPinMux(gpioPort_C_c, 17u, pinMux_Alt2_c);/* MISO */
      /* PORTC_PCR16 */
      GpioSetPinMux(gpioPort_C_c, 16u, pinMux_Alt2_c);/* CLK */
      /* PORTC_PCR19 */
      GpioSetPinMux(gpioPort_C_c,19u, pinMux_Alt2_c);/* PCS0 */
      break;
    case 1:                          /* SPI1 */
      /* PORTA_PCR16 */
     GpioSetPinMux(gpioPort_A_c,16u, pinMux_Alt2_c);/* MISO */
      /* PORTA_PCR17 */
     GpioSetPinMux(gpioPort_A_c,17u, pinMux_Alt2_c);/* MOSI */
      /* PORTA_PCR18 */
     GpioSetPinMux(gpioPort_A_c,18u, pinMux_Alt2_c);/* SCK */
      /* PORTA_PCR19 */
     GpioSetPinMux(gpioPort_A_c,19u, pinMux_Alt2_c);/* PCS0 */
      break;
    default:
      break;
  }
}

void configure_tpm_pins(uint32_t instance)
{
  switch(instance) {
    case 0:                             /* TPM0 */
      /* PORTC_PCR0 */
      GpioSetPinMux(gpioPort_C_c,0u, pinMux_Alt5_c);/* TPM0_CH1 */
      break;
    case 1:                             /* TPM1 */
      break;
    default:
      break;
  }
}

void configure_tsi_pins(uint32_t instance)
{
    switch (instance)
    {
        case 0U:
            break;
        default:
            break;
    }
}

void configure_dac_pins(uint32_t instance)
{
    switch (instance)
    {
        case 0U:
          /* PORTB_PCR18 */
          GpioSetPinMux(gpioPort_B_c,18u, pinMux_PinDisabledOrAnalog_c);/* DAC0 */ 
          break;
        default:
            break;
    }
}

void configure_rgb_led_pwm(void)
{
    GpioSetPinMux(gpioPort_C_c,1u,  pinMux_Alt5_c); /* Red */ 
    GpioSetPinMux(gpioPort_A_c,19u, pinMux_Alt5_c);/* Green */ 
    GpioSetPinMux(gpioPort_A_c,18u, pinMux_Alt5_c);/* Blue */ 
}

/* END pin_mux. */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
