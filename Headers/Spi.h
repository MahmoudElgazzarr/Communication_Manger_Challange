/*
 * Spi.h
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-062
 */

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_


extern void SPI0_Master_Init(void);
extern void SPI0_Send(uint8_t data_to_send);
extern uint32_t SPI3_Recieve(void);

#endif /* INCLUDES_SPI_H_ */
