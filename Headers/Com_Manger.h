/*
 * Com_Manger.h
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_COM_MANGER_H_
#define HEADERS_COM_MANGER_H_

void Com_Init(void);
void Com_Send_Signal(uint8_t ID,uint8_t data);
uint8_t Com_Recive_Signal(uint8_t ID);

/*Periodic Tasks That Sends And Recives*/
void Com_Main_Tx();

/*Com Manger Send Task*/
void Com_Main_Tx_Task();
/*Com Manger Receive Task*/
void Com_Main_Rx();


#endif /* HEADERS_COM_MANGER_H_ */
