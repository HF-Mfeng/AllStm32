#ifndef _IIC_H_
#define _IIC_H_

#include"sys.h"
#include"delay.h"

#define SCL_H      GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define SCL_L      GPIO_ResetBits(GPIOA,GPIO_Pin_11)
#define SDA_H      GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define SDA_L      GPIO_ResetBits(GPIOA,GPIO_Pin_12)

//IIC_function--------------------------------------
void IIC_Init(void);
void SDA_OUT(void);
void SDA_IN(void);
void IIC_Start(void);
void IIC_Stop(void);
u8 IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(u8 txd);
u8 IIC_Read_Byte(void);
//IIC_function--------------------------------------









#endif

