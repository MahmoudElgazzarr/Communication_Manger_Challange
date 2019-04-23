/*
 * UART.c
 *
 *  Created on: Mar 12, 2019
 *      Author: AVE-LAP-016
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "UART.h"
/*FreeRtos Includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "uartstdio.h"


volatile uint8_t UART_Flag = 0 ;
volatile uint8_t DataToSend = 0 ;
extern QueueHandle_t xUartRecv ;

#define UART_PERIODICITY 10

/*******************************************************************/
/* UartRecv_Task                                                   */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : N/A                                                       */
/* Return : void                                                   */
/* task that recv data on UART0                                    */
/*******************************************************************/
void UartRecv_Task(void *pvParameters)
{
    static uint8_t data_UART = 0 ;
    vTaskDelay(500);
    while(1)
    {
        data_UART = 0;
        if(UARTCharsAvail(UART0_BASE))
        {
            data_UART = UARTgetc();
            xQueueSendToBack(xUartRecv, &data_UART , 10 );
        }
        vTaskDelay(50);
    }
}

void InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}
