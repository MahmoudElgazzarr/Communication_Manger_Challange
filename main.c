#include <FreeRTOS.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "Task.h"
#include "led_task.h"
#include "Spi.h"
#include "Com_Manger_Cfg.h"
#include "Com_Manger.h"


void InitConsole(void);

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif

int main(void)
{
    // Set the clocking to run at 50 MHz from the PLL.

    //ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
    //SYSCTL_OSC_MAIN);

    /*Inalize UART*/
    InitConsole();
    /*Inalize SPI*/
    SPI0_Master_Init();
    /*Inatilalieze Com Module*/
    Com_Init();

    /*Send Data ID 0 , data = 2*/
    Com_Send_Signal(0,1);

    /*Create Init Task For Led*/
    xTaskCreate(LEDS_Task_init, (const portCHAR *) "LED_Init", 128, NULL, 13, NULL);

    /*Add Task For Led*/
    xTaskCreate(LED_Task, (const portCHAR *) "Led_Task", 150, NULL, 3, NULL);

    /*Add Task For Led*/
    xTaskCreate(LED2_Task, (const portCHAR *) "Led_Task", 150, NULL, 3, NULL);

    /*Start Schedular*/
    vTaskStartScheduler();
    while (1)
    {
    }
    return 0;
}

void
InitConsole(void)
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
