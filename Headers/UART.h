/*
 * UART.h
 *
 *  Created on: Mar 12, 2019
 *      Author: AVE-LAP-016
 */

#ifndef UART_H_
#define UART_H_

void UART0_init(void);
extern void UART0_Send(uint8_t data);
extern uint8_t UART0_Recv(void);
extern void UartRecv_Task(void *pvParameters);

extern volatile uint8_t UART_Flag ;
extern volatile uint8_t DataToSend  ;

#endif /* UART_H_ */
