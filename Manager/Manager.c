
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
#include "Com_Manger_Cfg.h"
#include "Com_Manger.h"
#include "UART.h"

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
    /*Get Data Received Which is From UART*/
    uint8_t duty_Cycle = Com_Recive_Signal(Signal_ID0);
    uint8_t Object_Detected = Com_Recive_Signal(Signal_ID1);

    /*If Object Detected*/
    if(Object_Detected == 1)
    {
        UART0_Send('O');
    }

    /*Variable To Save Echo Recived From ULTRASONIC*/
    double ULTRASONIC_Echo_Pulse;
    double Total_Time;

    /*Variable To hold value of distance Calculated*/
    uint8_t Distance = 1;

    /*If Received Data*/
    uint8_t Received_Data_Flag = 1;
    if(Received_Data_Flag == 1)
     {
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
        }
     }
    return Distance ;
}
