/*
 * Com_Manger_Cfg.c
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */
#include <stdint.h>
#include "Com_Manger_Cfg.h"

/*Array Of PDUS*/
PDU_S_T PDU_Arr[Num_Pdu] = {{PDU_ID0,0,Periodicity_5MS,Priority1,Remaining_5MS},{PDU_ID1,0,Periodicity_10MS,Priority2,Remaining_5MS}};


/*Array Of Signals*/
Signal_S_T Signals_Arr[Num_Signal] = {{Signal_ID0,Length_3Bit,Bit0,PDU_ID0}};


