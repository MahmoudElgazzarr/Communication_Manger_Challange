/*
 * Com_Manger.c
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */

#include <stdint.h>
#include "Com_Manger_Cfg.h"
#include "Com_Manger.h"

/*Inatialization For The Module*/
void Com_Init(void)
{
    uint8_t i;
    for(i=0;i<Num_Signal;i++)
    {
        /*Add Header Of PDU Signal To The PDU */
        /*PDU_Arr[i] =  */
    }
}

/*Function That Is Called By Application*/
void Com_Send_Signal(uint8_t ID,uint8_t data)
{

}

/*Function That Is Called By App*/
uint8_t Com_Recive_Signal(uint8_t ID)
{
    return 0;
}

/*Periodic Task That Sends Data Periodicaly*/
void Com_Main_Tx()
{

}

/*Periodic Task That Recives Data Perioducaly Data Periodicaly*/
void Com_Main_Rx()
{

}
static uint8_t Concatenate()
{

}
