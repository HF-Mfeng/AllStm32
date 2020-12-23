
#ifndef __AD9959_H
#define __AD9959_H

#include "stdint.h"

// #define u8 uint8_t
// #define u16 uint16_t
// #define u32 uint32_t

//AD9959寄存器地址定义
#define CSR_ADD   0x00   //CSR 通道选择寄存器
#define FR1_ADD   0x01   //FR1 功能寄存器1
#define FR2_ADD   0x02   //FR2 功能寄存器2
#define CFR_ADD   0x03   //CFR 通道功能寄存器
#define CFTW0_ADD 0x04   //CTW0	通道频率转换字寄存器
#define CPOW0_ADD 0x05   //CPW0	通道相位转换字寄存器
#define ACR_ADD   0x06   //ACR 幅度控制寄存器
#define LSRR_ADD  0x07   //LSR 通道线性扫描寄存器
#define RDW_ADD   0x08   //RDW 通道线性向上扫描寄存器
#define FDW_ADD   0x09   //FDW 通道线性向下扫描寄存器

//AD9959管脚宏定义
#define CS0   		HAL_GPIO_WritePin(CS_GPIO_Port,		CS_Pin,		GPIO_PIN_RESET);
#define CS1   		HAL_GPIO_WritePin(CS_GPIO_Port,		CS_Pin,		GPIO_PIN_SET);

#define SCLK0 		HAL_GPIO_WritePin(SCK_GPIO_Port,	SCK_Pin,	GPIO_PIN_RESET);
#define SCLK1  		HAL_GPIO_WritePin(SCK_GPIO_Port,	SCK_Pin,	GPIO_PIN_SET);

#define UPDATE0		HAL_GPIO_WritePin(UP_GPIO_Port,		UP_Pin,		GPIO_PIN_RESET);
#define UPDATE1		HAL_GPIO_WritePin(UP_GPIO_Port,		UP_Pin,		GPIO_PIN_SET);

#define PS00		HAL_GPIO_WritePin(PS0_GPIO_Port,	PS0_Pin,	GPIO_PIN_RESET);
#define PS01		HAL_GPIO_WritePin(PS0_GPIO_Port,	PS0_Pin,	GPIO_PIN_SET);

#define PS10		HAL_GPIO_WritePin(PS1_GPIO_Port,	PS1_Pin,	GPIO_PIN_RESET);
#define PS11		HAL_GPIO_WritePin(PS1_GPIO_Port,	PS1_Pin,	GPIO_PIN_SET);

#define SDIO00		HAL_GPIO_WritePin(SD0_GPIO_Port,	SD0_Pin,	GPIO_PIN_RESET);
#define SDIO01		HAL_GPIO_WritePin(SD0_GPIO_Port,	SD0_Pin,	GPIO_PIN_SET);

#define SDIO10		HAL_GPIO_WritePin(SD1_GPIO_Port,	SD1_Pin,	GPIO_PIN_RESET);
#define SDIO11		HAL_GPIO_WritePin(SD1_GPIO_Port,	SD1_Pin,	GPIO_PIN_SET);

#define ReSet0 		HAL_GPIO_WritePin(RST_GPIO_Port,	RST_Pin,	GPIO_PIN_RESET);
#define ReSet1 		HAL_GPIO_WritePin(RST_GPIO_Port,	RST_Pin,	GPIO_PIN_SET);

#define AD9959_PWR0 HAL_GPIO_WritePin(PWR_GPIO_Port,	PWR_Pin,	GPIO_PIN_RESET);
#define AD9959_PWR1 HAL_GPIO_WritePin(PWR_GPIO_Port,	PWR_Pin,	GPIO_PIN_SET);

//另一个文件中的
#define Interface 3//½çÃæ×ÜÊý
#define StrMax    10//»º´æÊý¾Ý´óÐ¡


void delay1 (uint32_t length);
void IntReset(void);	  //AD9959，复位
void IO_Update(void);   //AD9959，更新数据
void Intserve(void);		   //IO口初始化
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData,uint8_t temp);
void Init_AD9959(void);
void Write_frequence(uint8_t Channel,uint32_t Freq);
void Write_Amplitude(uint8_t Channel, uint16_t Ampli);
void Write_Phase(uint8_t Channel,uint16_t Phase);


#endif


