#include"myspi.h"
#include"main.h"
#include"spi.h"
#include"delay.h"
#include"stdio.h"
#include"stm32f1xx.h"
#include"gpio.h"

/*       移植代码需要注意的点        *///----------------------------------------
#define Myspi hspi1   
#define CPU_FREQUENCY_MHZ    16		// STM32时钟主频  

	#define CS_RESET		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	#define CS_SET			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);	

//#ifndef DELAY_US
//#define DELAY_US

//void delay_us( uint32_t delay) //微秒级别的延时函数
//{
//    int last, curr, val;
//    int temp;

//    while (delay != 0)
//    {
//        temp = delay > 900 ? 900 : delay;
//        last = SysTick->VAL;
//        curr = last - CPU_FREQUENCY_MHZ * temp;
//        if (curr >= 0)
//        {
//            do
//            {
//                val = SysTick->VAL;
//            }
//            while ((val < last) && (val >= curr));
//        }
//        else
//        {
//            curr += CPU_FREQUENCY_MHZ * 1000;
//            do
//            {
//                val = SysTick->VAL;
//            }
//            while ((val <= last) || (val > curr));
//        }
//        delay -= temp;
//    }
//}
//#endif

uint8_t readata1;//寄存器指令高8位
uint8_t readata2;//寄存器指令低8位
uint16_t readata;//返回的数据

// uint8_t SPI_ADS_Send(uint8_t TxData)
// {		 			 
 
//   while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//等待发送区空  
	
// 	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个byte  数据
		
//   while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个byte  
 
// 	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据	
    
 		    
// }

uint16_t ADS1118_GetData(uint32_t Channal)
{
	uint16_t CofigReg;
    uint8_t transData;

	CS_RESET
	delay_us(1);				//时序要求
	switch(Channal)
	{
		case 0:	CofigReg = MUX_A0;	break;
		case 1:	CofigReg = MUX_A1;	break;	
		case 2:	CofigReg = MUX_A2;	break;
		case 3:	CofigReg = MUX_A3;	break;
	}
	CofigReg |= PGA_2_048|MODE_CON|DR_128|TS_MODE_ADC|PULL_UP_EN_1|NOP_1;
	//printf("cofigreg:%x\r\n",CofigReg);
    
    transData = (uint8_t)(CofigReg>>8);                     //DATA MSB 	
    HAL_SPI_Transmit(&Myspi,&transData,1,100); 
	//delay_us(1);
    HAL_SPI_Receive(&Myspi,&readata1,1,100);
 //    HAL_SPI_TransmitReceive(&Myspi,&transData,&readata1,1,10000); 


    transData = (uint8_t)((CofigReg<<8)>>8);	                	//DATA LSB
    HAL_SPI_Transmit(&Myspi,&transData,1,100);
//delay_us(1);	
    HAL_SPI_Receive(&Myspi,&readata2,1,100);
 //    HAL_SPI_TransmitReceive(&Myspi,&transData,&readata2,1,10000); 

	// readata1=HAL_SPI_Transmit(SPI1,(uint8_t)(CofigReg>>8));		//DATA MSB 
	// readata2=HAL_SPI_Transmit((uint8_t)CofigReg);					//DATA LSB
	readata=( (((uint16_t)readata1)<<8) | (uint16_t)readata2 );
	printf("readata1:0x%x\r\n",readata1);
	printf("readata2:0x%x\r\n",readata2);
	printf("readata:0x%x==%d\r\n",readata,readata);
	delay_us(1);
	CS_SET
	return readata;
    
}





