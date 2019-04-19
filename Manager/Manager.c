
#include <stdbool.h>
#include <stdint.h>
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
#include "Manager.h"

extern QueueHandle_t xUartRecv ;
extern EventGroupHandle_t xBtnEventGroup;

#define ULTRASONIC_FREQUANCY 6700

/*******************************************************************/
/* Get_Distance                                                    */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : uint8                                                     */
/* Return : void                                                   */
/* fn that get distance from uart queue                            */
/*******************************************************************/
uint8_t Get_Distance(void)
{
    /*varibable to hold data Recived From UART Which Represents Duty Cycle*/
    uint8_t duty_Cycle=0;

    /*Variable To Save Echo Recived From ULTRASONIC*/
    double ULTRASONIC_Echo_Pulse;
    double Total_Time;

    /*Variable To hold value of distance Calculated*/
    uint8_t Distance = 1;

    if(uxQueueMessagesWaiting(xUartRecv))
     {
        xQueueReceive(xUartRecv,&duty_Cycle,10);
        xEventGroupSetBits(xBtnEventGroup, DISTANCE_FLAG);

        /* Equation */
        Total_Time = ( 1000000 / ULTRASONIC_FREQUANCY );
        ULTRASONIC_Echo_Pulse = duty_Cycle * Total_Time ;
        /*OUT Of Range*/
        if ((ULTRASONIC_Echo_Pulse < 150) || (ULTRASONIC_Echo_Pulse > 16000))
        {
            Distance = 1 ;
        }
        else
        {
            /*Distance in CM */
            Distance = (uint8_t)( (ULTRASONIC_Echo_Pulse * 0.0343) / 2 );
            Distance = Distance / 8.5;
        }
     }
    return Distance ;
}
