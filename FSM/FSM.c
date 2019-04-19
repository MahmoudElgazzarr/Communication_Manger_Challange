/*
 * FSM.c
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-062
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "FSM.h"
#include "Btn.h"
#include "Manager.h"
#include "Spi.h"
#include "UART.h"
#include "Com_Manger_Cfg.h"
#include "Com_Manger.h"
/*FreeRtos Includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

typedef enum
{
    IgnitionOff,
    MaintainSpeed,
    IncreaseSpeed,
    DecreaseSpeed,
    Brake,
    FireAirbag,
    SystemOn
} CarState_e;

extern EventGroupHandle_t xBtnEventGroup;

/*******************************************************************/
/* FSM_Handler_Task                                                */
/* Parameters :                                                    */
/* I/p : *pvParameter                                              */
/* O/p : N/A                                                       */
/* Return : void                                                   */
/* Task that checks sensor data and send action on SPI             */
/*******************************************************************/
void FSM_Handler_Task(void *pvParameters)
{

    uint8_t IgnitionFlag = 0;
    static uint8_t CurrentState = IgnitionOff;
    uint8_t Distance = 0;

    /*Event Group Variables*/
    EventBits_t uxBits;
    const TickType_t xTicksToWait = 100 / portTICK_PERIOD_MS;

    while (1)
    {
        Com_Send_Signal(Signal_ID0, 5);
        Com_Send_Signal(Signal_ID1, 6);
        /* Get Distance */
        Distance = Get_Distance();
        /* Check for DistEventFlag */
        uxBits = xEventGroupWaitBits(xBtnEventGroup, /* The event group being tested. */
                                     DISTANCE_FLAG | BTN1_FLAG, /* The bits within the event group to wait for. */
                                     pdTRUE, /* BIT_0 & BIT_4 should be cleared before returning. */
                                     pdFALSE, /* Don't wait for both bits, either bit will do. */
                                     xTicksToWait);/* Wait a maximum of 100ms for either bit to be set. */

        /* Check for event flag ( Btn==1 for 1sec)*/
        if (((uxBits & BTN1_FLAG) != 0) && (CurrentState == IgnitionOff))
        {
            IgnitionFlag = 1;
            if ((Distance >= 0) && (Distance <= 5))
            {
                CurrentState = SystemOn;
                /*Send To Com Manger Current State*/
                Com_Send_Signal(Signal_ID0, CurrentState);
            }
            else if ((Distance > 5) && (Distance <= 20))
            {
                CurrentState = Brake;
                /*Send Two Signals*/
                Com_Send_Signal(Signal_ID0, CurrentState);
                Com_Send_Signal(Signal_ID1, Distance);
            }
            else if ((Distance > 20) && (Distance <= 90))
            {
                CurrentState = DecreaseSpeed;
                /*Send Two Signals*/
                Com_Send_Signal(Signal_ID0, CurrentState);
                Com_Send_Signal(Signal_ID1, Distance);
            }
            else if ((Distance > 90) && (Distance <= 160))
            {
                CurrentState = MaintainSpeed;
                /*Send Two Signals*/
                Com_Send_Signal(Signal_ID0, CurrentState);
                Com_Send_Signal(Signal_ID1, Distance);
            }
            else if ((Distance > 160) && (Distance <= 255))
            {
                CurrentState = IncreaseSpeed;
                /*Send Two Signals*/
                Com_Send_Signal(Signal_ID0, CurrentState);
                Com_Send_Signal(Signal_ID1, Distance);
            }
        }

        /* If Btn already Pressed */
        if (IgnitionFlag == 1)
        {
            /* If Distance Sent */
            if ((uxBits & DISTANCE_FLAG) != 0)
            {
                if ((Distance >= 0) && (Distance <= 5))
                {
                    CurrentState = FireAirbag;
                    /*Send Two Signals*/
                    Com_Send_Signal(Signal_ID0, CurrentState);
                    Com_Send_Signal(Signal_ID1, Distance);
                }
                else if ((Distance > 5) && (Distance <= 20))
                {
                    CurrentState = Brake;
                    /*Send Two Signals*/
                    Com_Send_Signal(Signal_ID0, CurrentState);
                    Com_Send_Signal(Signal_ID1, Distance);
                }
                else if ((Distance > 20) && (Distance <= 90))
                {
                    CurrentState = DecreaseSpeed;
                    /*Send Two Signals*/
                    Com_Send_Signal(Signal_ID0, CurrentState);
                    Com_Send_Signal(Signal_ID1, Distance);
                }
                else if ((Distance > 90) && (Distance <= 160))
                {
                    CurrentState = MaintainSpeed;
                    /*Send Two Signals*/
                    Com_Send_Signal(Signal_ID0, CurrentState);
                    Com_Send_Signal(Signal_ID1, Distance);
                }
                else if ((Distance > 160) && (Distance <= 255))
                {
                    CurrentState = IncreaseSpeed;
                    /*Send Two Signals*/
                    Com_Send_Signal(Signal_ID0, CurrentState);
                    Com_Send_Signal(Signal_ID1, Distance);
                }
            }
            else
            {
                /*Error*/
            }
        }
        vTaskDelay(50);
    }
}

