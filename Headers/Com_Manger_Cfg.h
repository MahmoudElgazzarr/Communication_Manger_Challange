/*
 * Com_Manger_Cfg.h
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_COM_MANGER_CFG_H_
#define HEADERS_COM_MANGER_CFG_H_

#define Num_Signal 2
#define Num_Pdu 2
#define Com_Task_Periodicity 5

/*Structure For PDU*/
typedef struct PDU_S
{
    uint8_t PDU_ID;
    uint8_t SDU;
    uint8_t Periodicity;
    uint8_t Priority;
    uint8_t Remaining_Ticks;
}PDU_S_T;

/*Structure For Signals*/
typedef struct Signal_S
{
    uint8_t Signal_ID;
    uint8_t Length;
    uint8_t Start_Bit;
    uint8_t PDU_ID;
}Signal_S_T;

/*PDU Signals*/
enum PDU_ID
{
    PDU_ID0,
    PDU_ID1,
    PDU_ID2,
    PDU_ID3,
    PDU_ID4,
    PDU_ID5,
    PDU_ID6,
};
enum Signal_ID
{
    Signal_ID0,
    Signal_ID1,
    Signal_ID2,
    Signal_ID3,
    Signal_ID4,
    Signal_ID5,
    Signal_ID6,
    Signal_ID7,
};

/*Periodicity*/
enum Periodicity
{
    Periodicity_5MS = 5,
    Periodicity_10MS = 10,
};
enum Priority
{
    Priority1 = 1,
    Priority2,
    Priority3,
    Priority4,
    Priority5,
};
enum Length
{
    Length_2Bit = 2,
    Length_3Bit,
    Length_4Bit,
    Length_5Bit,
    Length_6Bit,
};
enum Start_Bit
{
    Bit0,
    Bit1,
    Bit2,
    Bit3,
    Bit4,
    Bit5,
    Bit6,
    Bit7,
};
enum Remaining_Ticks
{
    Remaining_5MS = 5,
    Remaining_10MS = 10,
};
#endif /* HEADERS_COM_MANGER_CFG_H_ */
