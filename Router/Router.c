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
    SPI0_Send(Data);
}
