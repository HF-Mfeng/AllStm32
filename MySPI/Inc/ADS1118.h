//#ifndef __ADS1118_H
//#define __ADS1118_H
//#include "sys.h"

//	#define CS_RESET	GPIO_ResetBits(GPIOA,GPIO_Pin_4)
//	#define CS_SET		GPIO_SetBits(GPIOA,GPIO_Pin_4)	



///*************Channal Define*********************/
//#define MUX_A0     MUX_4      //AINp=AIN0, AINn=GND
//#define MUX_A1     MUX_5      //AINp=AIN1, AINn=GND
//#define MUX_A2     MUX_6      //AINp=AIN2, AINn=GND
//#define MUX_A3     MUX_7      //AINp=AIN3, AINn=GND

///************CONFIG REGISTER*****************/
//#define MUX_0  0x0000  //AINp=AIN0, AINn=AIN1(default)
//#define MUX_1  0x1000  //AINp=AIN0, AINn=AIN3
//#define MUX_2  0x2000  //AINp=AIN1, AINn=AIN3
//#define MUX_3  0x3000  //AINp=AIN2, AINn=AIN3
//#define MUX_4  0x4000  //AINp=AIN0, AINn=GND
//#define MUX_5  0x5000  //AINp=AIN1, AINn=GND
//#define MUX_6  0x6000  //AINp=AIN2, AINn=GND
//#define MUX_7  0x7000  //AINp=AIN3, AINn=GND

//#define PGA_6_144  0x0000   //FS=6.144V
//#define PGA_4_096  0x0200   //FS=4.096V
//#define PGA_2_048  0x0400   //FS=2.048V(default)
//#define PGA_1_024  0x0600   //FS=1.024V
//#define PGA_0_512  0x0800   //FS=0.512V
//#define PGA_0_256  0x0A00   //FS=0.256V
////#define PGA_6  0x0C00   //FS=0.256V
////#define PGA_7  0x0E00   //FS=0.256V

//#define MODE_CON 0x0000		//连续转换模式
//#define MODE_SIN 0x0100		//单次转换模式(default)

//#define DR_8   		0x0000   //Data Rate = 8
//#define DR_16   	0x0020   //Data Rate = 16
//#define DR_32  		0x0040   //Data Rate = 32
//#define DR_64   	0x0060   //Data Rate = 64
//#define DR_128  	0x0080   //Data Rate = 128(default)
//#define DR_250  	0x00A0   //Data Rate = 250
//#define DR_475  	0x00C0   //Data Rate = 475
//#define DR_860   	0x00E0   //Data Rate = 860

//#define TS_MODE_ADC  0x0000		//ADC模式(default)
//#define TS_MODE_TMP  0x0010		//温度传感器模式

//#define PULL_UP_EN_0  0x0000		//禁用DOUT引脚上拉电阻
//#define PULL_UP_EN_1  0x0008		//使能DOUT引脚上拉电阻(default)

//#define	NOP_0	0x0000	//无效数据，不更新配置寄存器内容
//#define	NOP_1	0x0002	//有效数据，更新配置寄存器内容(default)
//#define	NOP_2	0x0004	//无效数据，不更新配置寄存器内容
//#define	NOP_3	0x0006	//无效数据，不更新配置寄存器内容

////函数申明

//void GPIO_ADS_Init();
//void SPI_ADS_Init();

//u8 SPI_ADS_Send(u8 TxData);
//uint32_t ADS1118_GetData(uint32_t Channal);

//#endif
