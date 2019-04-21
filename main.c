#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "FSM.h"
#include "UART.h"
#include "Btn.h"
#include "Spi.h"
#include "led_task.h"
#include "Com_Manger_Cfg.h"
#include "Com_Manger.h"

void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    /*
     This function can not return, so loop forever.  Interrupts are disabled
     on entry to this function, so no processor interrupts will interrupt
     this loop.
    */
    while(1)
    {
    }
}

QueueHandle_t xUartRecv ;
EventGroupHandle_t xBtnEventGroup;

int main(void)
{

    /* Attempt to create the event group. */
    xBtnEventGroup = xEventGroupCreate();
    /*UartRec Queue*/
    xUartRecv = xQueueCreate(10,sizeof(uint8_t));

    /* The queue was created. */
    xUartRecv = xQueueCreate(10,sizeof(uint8_t));
    /*Init Buttons*/
    Btns_Init();
    /*Uart init*/
    UART0_init();
    /*Inalize SPI*/
    SPI0_Master_Init();
    /*Inatilalieze Com Module*/
    Com_Init();


    /*Buttons Task That Suspend After Pressing The Button*/
    xTaskCreate(Btn1_Task,"Button Task",128,NULL,2,NULL);

    /*Uart Task Receive , Task Instead Of ISR*/
    xTaskCreate(UartRecv_Task,"UART Task",128,NULL,3,NULL);

    /*FSM Task*/
    xTaskCreate(FSM_Handler_Task,"FSM",128,NULL,4,NULL);

    /*Create a Task For The Com Manger*/
     xTaskCreate(Com_Main_Tx_Task,"Com_Manger Send Task",128,NULL,1,NULL);

     /*Todo Com Receive Task That Receives From UART*/

    /*Start Schedular*/
    vTaskStartScheduler();

    while (1)
    {
    }
    return 0;
}
