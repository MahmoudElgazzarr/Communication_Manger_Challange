/*
 * Router_Cfg.h
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_ROUTER_CFG_H_
#define HEADERS_ROUTER_CFG_H_

/*Num Of PDUS Sent*/
#define NUM_OF_PDUS 5

/*Num Of PDUS Received*/
#define NUM_OF_PDUS_Received 2

/*The Number Of ID Bits In Data Sent*/
#define UART_ID_BITS_NUM 1
#define SPI_ID_BITS_NUM 2

/*Structure To Hold Channel Mapping*/
typedef struct PDU
{
    uint8_t PDU_ID;
    uint8_t Physical_ID;
    uint8_t channel;
}PDU_T;

enum Channels
{
    UART,
    SPI,
};
enum PDU_ID
{
    PDU_ID0,
    PDU_ID1,
    PDU_ID2,
    PDU_ID3,
    PDU_ID4,
    PDU_ID5,
    PDU_ID6,
    PDU_ID7,
};

enum Phyiscal_ID
{
    Phyiscal_ID0,
    Phyiscal_ID1,
    Phyiscal_ID2,
    Phyiscal_ID3,
    Phyiscal_ID4,
    Phyiscal_ID5,
    Phyiscal_ID6,
    Phyiscal_ID7,
};

#endif /* HEADERS_ROUTER_CFG_H_ */
