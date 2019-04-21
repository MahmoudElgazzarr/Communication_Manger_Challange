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


volatile uint8_t UART_Flag = 0 ;
volatile uint8_t DataToSend = 0 ;
extern QueueHandle_t xUartRecv ;

#define UART_PERIODICITY 10

/*******************************************************************/
/* UART0_init                                                      */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : N/A                                                       */
/* Return : void                                                   */
/* fn that init  on UART0                                          */
/*******************************************************************/
void UART0_init(void)
{
    //
        // Enable the UART0 module.
        //
        //
        // Enable the GPIOB peripheral
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        //
        // Wait for the GPIOB module to be ready.
        //
        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
        {
        }

        /* Configure GPIO Port B pins 0 and 1 to be used as UART1.*/
        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
        //
        // Enable UART1 functionality on GPIO Port B pins 0 and 1.
        //
        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

        /* Wait for the UART0 module to be ready. */
        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
        {
        }
        // Initialize the UART. Set the baud rate, number of data bits, turn off
        // parity, number of stop bits, and stick mode. The UART is enabled by the
        // function call.
        //
        UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 38400,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
        UART_CONFIG_PAR_NONE));
}

/*******************************************************************/
/* UART0_Send                                                      */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : N/A                                                       */
/* Return : void                                                   */
/* fn that send data on UART0                                      */
/*******************************************************************/
void UART0_Send(uint8_t data)
{
  UARTCharPut(UART0_BASE, data);
}

/*******************************************************************/
/* UART0_Recv                                                      */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : N/A                                                       */
/* Return : void                                                   */
/* fn that recv data on UART0                                      */
/*******************************************************************/
uint8_t UART0_Recv(void)
{
    uint8_t data = 0;
    if(UARTCharsAvail(UART0_BASE))
    {
        data = UARTCharGetNonBlocking(UART0_BASE);
    }
    return data ;
}

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
    vTaskDelay(500);
    while(1)
    {
        uint8_t data = 0 ;
        if(UARTCharsAvail(UART0_BASE))
        {
            data = UART0_Recv();
                xQueueSendToBack(xUartRecv, &data , 10 );
        }
        vTaskDelay(50);
    }
}
