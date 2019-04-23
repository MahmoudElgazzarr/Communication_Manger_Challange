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
#include "BitwiseOperation.h"
#include "uartstdio.h"

/*Queue To Put Data Received From UART*/
extern xQueueHandle xUartRecv;

/*Configuration Arrays OF PDUS*/
extern PDU_T PDUS_Arr[NUM_OF_PDUS];
extern PDU_T PDUS_Received_Arr[NUM_OF_PDUS_Received];

/*Router Init*/
void Router_Init()
{

}

/*Router Recive Function*/
uint8_t PduR_Recive_Data()
{
    /*UART PDU ID*/
    uint8_t UART_PDU_ID_Received = 0;
    /*Data Received From UART*/
    uint8_t UART_Data_Received = 0;
    /*Read Data From UART Queue*/
    xQueueReceive(xUartRecv, &UART_Data_Received, 10);
    /*Received ID*/
    UART_PDU_ID_Received = (UART_Data_Received >> (8 - UART_ID_BITS_NUM));

    /*Search For PDU ID*/
    uint8_t index;
    /*Index Of PDU In Arr*/
    uint8_t PDU_Index_In_Arr;
    /*Get PDU ID in which Array Index*/
    for (index = 0; index < NUM_OF_PDUS_Received; index++)
    {
        if (PDUS_Received_Arr[index].Physical_ID == UART_PDU_ID_Received)
        {
            PDU_Index_In_Arr = index;
            break;
        }
    }
    switch (PDUS_Received_Arr[PDU_Index_In_Arr].channel)
    {
    case UART:
        /*Convert Phyiscal ID To Logical ID*/
        Clear_Bit(UART_Data_Received, 8);
        UART_Data_Received |= (PDUS_Received_Arr[PDU_Index_In_Arr].PDU_ID << 7);
        break;
    case SPI:
        /*Convert Phyiscal ID To Logical ID*/
        Clear_Bit(UART_Data_Received, 8);
        Clear_Bit(UART_Data_Received, 7);
        UART_Data_Received |= (PDUS_Received_Arr[PDU_Index_In_Arr].PDU_ID << 6);
    }
    /*Return UART PDU Received*/
    return UART_Data_Received;
}

/*Router Send Function*/
void PduR_ComTransmit(uint8_t PduId, uint8_t SDU)
{
    /*Search For PDU ID*/
    uint8_t index;
    uint8_t PDU_Index_In_Arr;

    /*Get PDU ID in which Array Index*/
    for (index = 0; index < NUM_OF_PDUS; index++)
    {
        if (PDUS_Arr[index].PDU_ID == PduId)
        {
            PDU_Index_In_Arr = index;
            break;
        }
    }
    /*Chose Which channel To Transmit Over Dependant on Configuration*/
    switch (PDUS_Arr[PDU_Index_In_Arr].channel)
    {
    case SPI:
        SDU |=
                (PDUS_Arr[PDU_Index_In_Arr].Physical_ID << (8 - SPI_ID_BITS_NUM));
        SPI0_Send(SDU);
        break;
    case UART:
        SDU |=
                (PDUS_Arr[PDU_Index_In_Arr].Physical_ID
                        << (8 - UART_ID_BITS_NUM));
        UARTprintf(SDU);
        break;
    }

}
