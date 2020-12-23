#ifndef 	 __SIMULATE_I2C_H__
#define    	 __SIMULATE_I2C_H__

#include "stm32f10x.h"


void I2C_INIT(void);
void SDA_OUT(void);
void SDA_IN(void);
void I2C_Start(void);
void I2C_Stop(void);
u8 I2C_Wait_Ack(void);
void I2C_Ack(void);
void I2C_NAck(void);
void I2C_Send_Byte(u8 txd);
u8 I2C_Read_Byte(void);


void WriteCmd(u8 command);
void WriteDat(u8 data);
void OLED_Init(void);
void OLED_ON(void);
void OLED_SetPos(unsigned char x, unsigned char y); 
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);//??
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowChinese(unsigned char x, unsigned char y, unsigned char no);


#endif


