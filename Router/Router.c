/*
 * Router.c
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */
#include <stdint.h>
#include "Spi.h"
#include "Router.h"

/*Router Init*/
void Router_Init()
{

}

/*Router Recive Function*/
void RouterRecive_Data()
{

}

/*Router Send Function*/
void RouterSend_Data(uint8_t Data)
{
    /*Todo Check Which Channel To Send To*/
    uint8_t PDU_ID = (Data >> 6);
    switch (PDU_ID)
    {
    case ID_0:
        SPI0_Send(Data);
        break;
    case ID_1:
        SPI0_Send(Data);
                break;
    case ID_2:
        SPI0_Send(Data);
                break;
    }

}
