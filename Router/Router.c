/*
 * Router.c
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */
#include <stdint.h>
#include "Spi.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Router_Cfg.h"
#include "Router.h"

extern xQueueHandle xUartRecv;
extern PDU_T PDUS_Arr[NUM_OF_PDUS];
/*Router Init*/
void Router_Init()
{

}

/*Router Recive Function*/
void RouterRecive_Data()
{
    uint8_t UART_Data_Received = 0;
    xQueueReceive(xUartRecv, &UART_Data_Received, 10);
    /*Todo*/
}

/*Router Send Function*/
void PduR_ComTransmit(uint8_t PduId,uint8_t SDU)
{
    /*Search For PDU ID*/
    uint8_t index;
    uint8_t PDU_Index_In_Arr;

    for(index = 0;index<NUM_OF_PDUS;index++)
    {
        if(PDUS_Arr[index].PDU_ID == PduId)
        {
            PDU_Index_In_Arr = index;
            break;
        }
    }
    switch (PDUS_Arr[PDU_Index_In_Arr].channel)
    {
    case SPI:
        SDU |= (PDUS_Arr[PDU_Index_In_Arr].Physical_ID<<( 8 - SPI_ID_BITS_NUM ));
        SPI0_Send(SDU);
        break;
    case UART:
        SDU |= (PDUS_Arr[PDU_Index_In_Arr].Physical_ID<<( 8 - UART_ID_BITS_NUM ));
        UART0_Send(SDU);
        break;
    }

}
