/*
 * PushBtn.c
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LAP-062
 */


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "Btn.h"


extern EventGroupHandle_t xBtnEventGroup;

/*******************************************************************/
/* Btns_Init                                                       */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : N/A                                                       */
/* Return : void                                                   */
/* Function that init btns                                         */
/*******************************************************************/
void Btns_Init(void)
{
    /* Set Btn1 peripheral clock (PORT B) */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    /* Set Btns pins to I/P */
    GPIOPinTypeGPIOInput(PUSHBTN1PORT, PUSHBTN1PIN);

    /* Unlcok PF0 */
    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= 0x01;

    /*Enable Internal PullUps */
    GPIOPadConfigSet(PUSHBTN1PORT,PUSHBTN1PIN,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}

/*******************************************************************/
/* Btn1_Read                                                       */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : N/A                                                       */
/* Return : uint32                                                 */
/* Function that return btn1 state                                 */
/*******************************************************************/
uint32_t Btn1_Read(void)
{
    uint32_t BtnState = 0 ;
    BtnState = GPIOPinRead(PUSHBTN1PORT,PUSHBTN1PIN);
    if (!BtnState)
        BtnState = BTN1_ON ;
    else if(BtnState)
        BtnState = BTN1_OFF ;
    else{}
    return BtnState ;
}

/*******************************************************************/
/* Btn1_Task                                                        */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : N/A                                                       */
/* Return : N/a                                                    */
/* Task that read btn1                                             */
/*******************************************************************/
void Btn1_Task(void *pvParameters)
{
    uint8_t Btn1_State=0 ;
    static uint16_t Counter = 0 ;
    while(1)
    {
        /* Read BTN1 */
        Btn1_State = Btn1_Read();
        if(Btn1_State)
        {
            Counter ++ ;
        }
        else
        {
            Counter = 0 ;
        }
        if(Counter > 1000 )
        {
            xEventGroupSetBits(xBtnEventGroup, BTN1_FLAG);
            vTaskSuspend(NULL);
        }
        vTaskDelay(1);
    }
}

