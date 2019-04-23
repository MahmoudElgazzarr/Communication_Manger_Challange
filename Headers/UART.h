/*
 * UART.h
 *
 *  Created on: Mar 12, 2019
 *      Author: AVE-LAP-016
 */

#ifndef UART_H_
#define UART_H_

void InitConsole(void);
extern void UartRecv_Task(void *pvParameters);
extern volatile uint8_t UART_Flag ;
extern volatile uint8_t DataToSend  ;

#endif /* UART_H_ */
