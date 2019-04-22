/*
 * Com_Manger_Cfg.c
 *
 *  Created on: Apr 14, 2019
 *      Author: AVE-LAP-040
 */
#include <stdint.h>
#include "Com_Manger_Cfg.h"

/*Array Of PDUS*/
PDU_S_T PDU_Arr[Num_Pdu] = { { PDU_ID0, 0, Periodicity_50MS, Priority1, Remaining_50MS },
                             { PDU_ID1, 0, Periodicity_50MS, Priority1, Remaining_50MS } };

/*Array Of Signals*/
Signal_S_T Signals_Arr[Num_Signal] = {
        { Signal_ID0, Length_6Bit, Bit0, PDU_ID0 }, { Signal_ID1, Length_6Bit, Bit0, PDU_ID1 } };

/*Array Of PDUS Received*/
PDU_S_T PDU_Arr_Received[Num_Pdu_Received] = { { PDU_ID0, 0, Periodicity_50MS, Priority1, Remaining_50MS },
                                               { PDU_ID1, 0, Periodicity_50MS, Priority1, Remaining_50MS } };

/*Array Of Signals Received*/
Signal_S_T Signals_Received_Arr[Num_Signal_Received] = { { Signal_ID0,Length_6Bit,Bit0, PDU_ID0 },
                                                         { Signal_ID1, Length_1Bit,Bit7,PDU_ID0 },
                                                         { Signal_ID2,Length_7Bit, Bit0,PDU_ID1 } };

