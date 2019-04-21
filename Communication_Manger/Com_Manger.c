/*
 * Com_Manger.c
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */
#include "stdbool.h"
#include <stdint.h>
#include "Com_Manger_Cfg.h"
#include "Router.h"
#include "Com_Manger.h"
#include "driverlib/uart.h"
#include "BitwiseOperation.h"
#include "FreeRTOS.h"
#include "task.h"
#include "BitwiseOperation.h"

/*Signal Buffer*/
uint8_t Signals[Num_Signal];

/*Signals Received Buffer*/
uint8_t Signals_Received[Num_Signal_Received];

/*Buffer To Send Data*/
uint8_t Data_To_Send[Num_Pdu];

/*Concatenate Function For PDUS*/
static void Concatenate(uint8_t Signal_ID);

/*Segment Function For PDUS*/
static void Segment(uint8_t Data_Received_Logical_ID, uint8_t Data_Received);

/*PDU Arr For PDUS*/
extern PDU_S_T PDU_Arr[Num_Pdu];

/*Arrays Of Signals Received*/
extern Signal_S_T Signals_Received_Arr[Num_Signal_Received];

/*PDU Array Received*/
extern PDU_S_T PDU_Arr_Received[Num_Pdu_Received];

/*Signal Arr*/
extern Signal_S_T Signals_Arr[Num_Signal];

/*Inatialization For The Module*/
void Com_Init(void)
{
    uint8_t i;
    for (i = 0; i < Num_Pdu; i++)
    {
        /*Add Header Of PDU Signal To The PDU */
        Data_To_Send[i] = PDU_Arr[i].PDU_ID;
    }
}

/*Function That Is Called By Application*/
/*ID From Zero To Seven*/
void Com_Send_Signal(uint8_t ID, uint8_t data)
{
    /*Update Signal Buffer*/
    Signals[ID] = data;

    /*Concatinate Data And Update Array*/
    Concatenate(ID);
}

/*Function That Is Called By App*/
uint8_t Com_Recive_Signal(uint8_t ID)
{
    return Signals_Received[ID];
}

/*Periodic Task That Sends Data Periodicity*/
void Com_Main_Tx()
{
    uint8_t index;
    /*Todo Handling Priority*/
    for (index = 0; index < Num_Pdu; index++)
    {
        /*Decrease Remaining*/
        PDU_Arr[index].Remaining_Ticks = PDU_Arr[index].Remaining_Ticks
                - Com_Task_Periodicity;
        /*If Remaining Ticks Is zero which means data need To be sent*/
        if (PDU_Arr[index].Remaining_Ticks == 0)
        {
            /*reset remaining Ticks*/
            PDU_Arr[index].Remaining_Ticks = PDU_Arr[index].Periodicity;
            /*Send Data*/
            PduR_ComTransmit(PDU_Arr[index].PDU_ID, PDU_Arr[index].SDU);
        }
    }
}
void Com_Main_Tx_Task()
{
    while (1)
    {
        Com_Main_Tx();
        vTaskDelay(300);
    }
}

/*Periodic Task That Recives Data Perioducaly Data Periodicaly*/
void Com_Main_Rx()
{
    uint8_t Data_Received;
    uint8_t Data_Received_Logical_ID = 0;
    /*Read Data Recived From Router*/
    Data_Received = PduR_Recive_Data();
    if (Data_Received != 0)
    {
        /*Get Logical ID*/
        Data_Received_Logical_ID = (Data_Received >> 7);
        /*Get SDU*/
        Clear_Bit(Data_Received, 8);
        /*Get Signals In PDU*/
        Segment(Data_Received_Logical_ID, Data_Received);
    }
}
/*Rx Task*/
void Com_Main_Rx_Task(void *pv)
{
    while (1)
    {
        Com_Main_Rx();
        vTaskDelay(5);
    }
}
static void Concatenate(uint8_t Signal_ID)
{
    uint8_t PDU_ID_COM = 0;
    uint8_t index;
    /*Search For PDU ID For The Signal*/
    for (index = 0; index < Num_Signal; index++)
    {
        /*search for index in the arr of signals*/
        if (Signal_ID == Signals_Arr[index].Signal_ID)
        {
            PDU_ID_COM = Signals_Arr[index].PDU_ID;
        }
    }
    /*Clear Bit That Need To be Concatinataed*/
    uint8_t Bit_Number;
    /*Mask Data That Need To Be Concatinated*/
    for (Bit_Number = 0; Bit_Number < Signals_Arr[Signal_ID].Length;
            Bit_Number++)
    {
        /*Clear Bits in PDU*/
        Clear_Bit(PDU_Arr[PDU_ID_COM].SDU,
                  Bit_Number + Signals_Arr[Signal_ID].Start_Bit);
    }
    /*Concatenate Data*/
    /*Todo Protect OTher Signals If Data IS Wrong*/
    PDU_Arr[PDU_ID_COM].SDU |= (uint8_t) ((Signals[Signal_ID])
            << (Signals_Arr[Signal_ID].Start_Bit));

    /*Add ID To The SDU*/
    Data_To_Send[PDU_ID_COM] |= (PDU_Arr[PDU_ID_COM].SDU);
}

static void Segment(uint8_t Data_Received_Logical_ID, uint8_t Data_Received)
{
    /*Update Signals*/
    uint8_t PDU_INDEX_IN_ARR = 0;
    uint8_t index;
    uint8_t Local_Signal_R;
    /*Search For PDU ID For The Signal*/
    for (index = 0; index < Num_Pdu_Received; index++)
    {
        /*search for index in the arr of signals*/
        if (Data_Received_Logical_ID == PDU_Arr_Received[index].PDU_ID)
        {
            PDU_INDEX_IN_ARR = index;
            break;
        }
    }
    /*Put Data Into SDU*/
    PDU_Arr_Received[PDU_INDEX_IN_ARR].SDU = Data_Received;
    /*Search For The Signals In PDU & Segment PDU To Signals*/
    for (index = 0; index < Num_Signal_Received; index++)
    {
        if (PDU_Arr_Received[PDU_INDEX_IN_ARR].PDU_ID == Signals_Received_Arr[index].PDU_ID)
        {
            /*Put Signal Into It's Place*/
            /*Shift Right With Start Bit To Remove Other Signals*/
            Local_Signal_R = (PDU_Arr_Received[PDU_INDEX_IN_ARR].SDU >> Signals_Received_Arr[index].Start_Bit);
            /*Shift Left To Remove Signals To The Right*/
            Local_Signal_R = (Local_Signal_R << (8 - Signals_Received_Arr[index].Length));
            /*Align Signal Wanted*/
            Signals_Received[index] = (Local_Signal_R >> (8 - Signals_Received_Arr[index].Length));
        }
    }
}
