/*
 * Router.h
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */

#ifndef HEADERS_ROUTER_H_
#define HEADERS_ROUTER_H_

enum IDS
{
    ID_0,
    ID_1,
    ID_2,
};
/*Router Init*/
void Router_Init();

/*Router Recive Function*/
void RouterRecive_Data();

/*Router Send Function*/
void RouterSend_Data(uint8_t Data);


#endif /* HEADERS_ROUTER_H_ */
