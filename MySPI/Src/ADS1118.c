//#include "ADS1118.h"
//#include "delay.h"
//#include "usart.h"
////*****************************************************************************
////�ļ�����ASD1118
////�ļ����ܣ�SPI1����16-1λADS1118��ȡ��ѹ
////���ߣ��Ƴ�Ǭ
////2020.9.20
////*****************************************************************************

////оƬ��stm32f103
////���Žӿڣ�
////SPI1				
////NSS - A4 - CS			
////CLK - A5 - SCK			
////MISO - A6 - OUT			
////MOSI - A7 - DIN			

//volatile uint8_t readata1;//�Ĵ���ָ���8λ
//volatile uint8_t readata2;//�Ĵ���ָ���8λ
//volatile uint32_t readata;//���ص�����

////void GPIO_ADS_Init()
////{
////	 GPIO_InitTypeDef GPIO_InitStructure;

////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

////		/*���� SCK,MISO,MOSI���ţ�GPIOA^5,GPIOA^6,GPIOA^7 */
////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���ù���
////    GPIO_Init(GPIOA, &GPIO_InitStructure); 

////    /*����CE���ţ�GPIOA^2*/
////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
////    GPIO_Init(GPIOA, &GPIO_InitStructure);
////		

////	
////}
///*******************************************
//�������ƣ�SPI_ADS_Send
//��    �ܣ������뷵������
//��    ����TxData�����͵�����
//����ֵ  �����ص�����
//********************************************/



//u8 SPI_ADS_Send(u8 TxData)
//{		 			 
// 
////  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//�ȴ���������  
////	
//	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ��byte  ����
////		
////  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} //�ȴ�������һ��byte  
//// 
//	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����	
//// 		    
//}
////SpeedSet:
////SPI_BaudRatePrescaler_2   2��Ƶ   (SPI 36M@sys 72M)
////SPI_BaudRatePrescaler_8   8��Ƶ   (SPI 9M@sys 72M)
////SPI_BaudRatePrescaler_16  16��Ƶ  (SPI 4.5M@sys 72M)
////SPI_BaudRatePrescaler_32  32��Ƶ  
////SPI_BaudRatePrescaler_64  64��Ƶ  
////SPI_BaudRatePrescaler_128  128��Ƶ 
////SPI_BaudRatePrescaler_256 256��Ƶ (SPI 281.25K@sys 72M)


///*******************************************
//�������ƣ�ADS1118_GetData
//��    �ܣ���ȡָ��ͨ���ϵ�����
//��    ����uint32_t Channal----����ͨ�� 0, 1, 2, 3
//��		ע��
//����ֵ  ����ȡ��������
//********************************************/
//uint32_t ADS1118_GetData(uint32_t Channal)
//{
//	uint32_t CofigReg;
////	CS_RESET;
//	delay_us(1);				//ʱ��Ҫ��
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
