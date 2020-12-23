#ifndef 	 __SIMULATE_I2C_H__
#define    	 __SIMULATE_I2C_H__

#include "stm32f1xx_hal.h"


void I2C_INIT(void);
void SDA_OUT(void);
void SDA_IN(void);
void I2C_Start(void);
void I2C_Stop(void);
uint8_t I2C_Wait_Ack(void);
void I2C_Ack(void);
void I2C_NAck(void);
void I2C_Send_Byte(uint8_t txd);
uint8_t I2C_Read_Byte(void);


void WriteCmd(uint8_t command);
void WriteDat(uint8_t data);
void OLED_Init(void);
void OLED_ON(void);
void OLED_SetPos(unsigned char x, unsigned char y); 
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);//??
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowChinese(unsigned char x, unsigned char y, unsigned char no);


#endif


