/*
 * Router.h
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_ROUTER_H_
#define HEADERS_ROUTER_H_

/*Router Init*/
void Router_Init();

/*Router Recive Function*/
void RouterRecive_Data();

/*Router Send Function*/
void PduR_ComTransmit(uint8_t PduId,uint8_t SDU);


#endif /* HEADERS_ROUTER_H_ */
