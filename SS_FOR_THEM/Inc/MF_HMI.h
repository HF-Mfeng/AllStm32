#ifndef _MF_HMI_H
#define _MF_HMI_H

#include "main.h"

extern uint8_t receiveKey ;

void witchKey(void);
void MF_Send_End_to_HMI(void);
void MF_Control_GPIO( GPIO_PinState PinState1 , GPIO_PinState PinState2 , GPIO_PinState PinState3 , GPIO_PinState PinState4);
//用来控制模拟开关的

#endif

