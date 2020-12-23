//#include "ADS1118.h"
//#include "delay.h"
//#include "usart.h"
////*****************************************************************************
////文件名：ASD1118
////文件功能：SPI1控制16-1位ADS1118读取电压
////作者：唐承乾
////2020.9.20
////*****************************************************************************

////芯片：stm32f103
////引脚接口：
////SPI1				
////NSS - A4 - CS			
////CLK - A5 - SCK			
////MISO - A6 - OUT			
////MOSI - A7 - DIN			

//volatile uint8_t readata1;//寄存器指令高8位
//volatile uint8_t readata2;//寄存器指令低8位
//volatile uint32_t readata;//返回的数据

////void GPIO_ADS_Init()
////{
////	 GPIO_InitTypeDef GPIO_InitStructure;

////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

////		/*配置 SCK,MISO,MOSI引脚，GPIOA^5,GPIOA^6,GPIOA^7 */
////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能
////    GPIO_Init(GPIOA, &GPIO_InitStructure); 

////    /*配置CE引脚，GPIOA^2*/
////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////    GPIO_Init(GPIOA, &GPIO_InitStructure);
////		

////	
////}
///*******************************************
//函数名称：SPI_ADS_Send
//功    能：发送与返回数据
//参    数：TxData：发送的数据
//返回值  ：返回的数据
//********************************************/



//u8 SPI_ADS_Send(u8 TxData)
//{		 			 
// 
////  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//等待发送区空  
////	
//	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个byte  数据
////		
////  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个byte  
//// 
//	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据	
//// 		    
//}
////SpeedSet:
////SPI_BaudRatePrescaler_2   2分频   (SPI 36M@sys 72M)
////SPI_BaudRatePrescaler_8   8分频   (SPI 9M@sys 72M)
////SPI_BaudRatePrescaler_16  16分频  (SPI 4.5M@sys 72M)
////SPI_BaudRatePrescaler_32  32分频  
////SPI_BaudRatePrescaler_64  64分频  
////SPI_BaudRatePrescaler_128  128分频 
////SPI_BaudRatePrescaler_256 256分频 (SPI 281.25K@sys 72M)


///*******************************************
//函数名称：ADS1118_GetData
//功    能：读取指定通道上的数据
//参    数：uint32_t Channal----采样通道 0, 1, 2, 3
//备		注：
//返回值  ：读取到的数据
//********************************************/
//uint32_t ADS1118_GetData(uint32_t Channal)
//{
//	uint32_t CofigReg;
////	CS_RESET;
//	delay_us(1);				//时序要求
//	switch(Channal)
//	{
//		case 0:	CofigReg = MUX_A0;	break;
//		case 1:	CofigReg = MUX_A1;	break;	
//		case 2:	CofigReg = MUX_A2;	break;
//		case 3:	CofigReg = MUX_A3;	break;
//	}
//	CofigReg |= PGA_2_048|MODE_CON|DR_128|TS_MODE_ADC|PULL_UP_EN_1|NOP_1;
//	printf("%x\n",CofigReg);
//	readata1=SPI_ADS_Send((uint8_t)(CofigReg>>8));		//DATA MSB 
//	readata2=SPI_ADS_Send((uint8_t)CofigReg);					//DATA LSB
//	readata=( ((uint32_t)readata1<<8) | (uint32_t)readata2 );
//	delay_us(1);
////	CS_SET;	
//	return readata;
//}
