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

/*Signal Buffer*/
uint8_t Signals[Num_Signal];

/*Buffer To Send Data*/
uint8_t Data_To_Send[Num_Pdu];

/*Concatenate Function For PDUS*/
static uint8_t Concatenate(uint8_t Signal_ID);

/*Segment Function For PDUS*/
static uint8_t Segment();

/*PDU Arr For PDUS*/
extern PDU_S_T PDU_Arr[Num_Pdu];

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
    return 0;
}

/*Periodic Task That Sends Data Periodicity*/
void Com_Main_Tx()
{
    uint8_t index;
    /*Todo Handling Priority*/
    for(index=0;index<Num_Pdu;index++)
    {
        /*Decrease Remaining*/
        PDU_Arr[index].Remaining_Ticks = PDU_Arr[index].Remaining_Ticks - Com_Task_Periodicity;
        /*If Remaining Ticks Is zero which means data need To be sent*/
        if(PDU_Arr[index].Remaining_Ticks == 0)
        {
            /*reset remaining Ticks*/
            PDU_Arr[index].Remaining_Ticks = PDU_Arr[index].Periodicity;
            /*Send Data*/
            RouterSend_Data(Data_To_Send[index]);
        }
    }

}

/*Periodic Task That Recives Data Perioducaly Data Periodicaly*/
void Com_Main_Rx()
{

}
static uint8_t Concatenate(uint8_t Signal_ID)
{
    uint8_t PDU_ID;

    uint8_t index;
    /*Search For PDU ID For The Signal*/
    for(index=0;index<Num_Signal;index++)
    {
        /*search for index in the arr of signals*/
        if(Signal_ID == Signals_Arr[index].Signal_ID)
        {
            PDU_ID = Signals_Arr[index].PDU_ID;
        }
    }
    /*Concatenate Data*/
    /*Todo Protect OTher Signals If Data IS Wrong*/
     PDU_Arr[PDU_ID].SDU |= (uint8_t)((Signals[Signal_ID]) << (Signals_Arr[Signal_ID].Start_Bit));

     /*Add ID To The SDU*/
     Data_To_Send[PDU_ID] |=  (PDU_Arr[PDU_ID].SDU);

     /*Send Over UART*/
     UARTprintf("Data = %3d \r",Data_To_Send[PDU_ID]);
}

static uint8_t Segment()
{

}
