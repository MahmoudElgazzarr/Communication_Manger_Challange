/*
 * Router_Cfg.c
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */

#include "stdint.h"
#include "Router_Cfg.h"

PDU_T PDUS_Arr[NUM_OF_PDUS] =
{
    {   PDU_ID0, Phyiscal_ID0, SPI},
    {   PDU_ID1, Phyiscal_ID1, SPI},
    {   PDU_ID2, Phyiscal_ID2, SPI},
    {   PDU_ID3, Phyiscal_ID3, SPI},
};
PDU_T PDUS_Received_Arr[NUM_OF_PDUS_Received] =
{
    {  PDU_ID4, Phyiscal_ID4, UART},
};
