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
