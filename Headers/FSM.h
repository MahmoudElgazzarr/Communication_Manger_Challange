/*
 * FSM.h
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-062
 */

#ifndef INCLUDES_FSM_H_
#define INCLUDES_FSM_H_

uint8_t AlignData(uint8_t Cmd , uint8_t Dist);

extern void Lcd_Task(void *pvParameters);

extern void FSM_Handler_Task(void *pvParameters);

#endif /* INCLUDES_FSM_H_ */
