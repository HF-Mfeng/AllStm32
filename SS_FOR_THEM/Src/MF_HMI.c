

#include "MF_HMI.h"

#include "usart.h"
#include "main.h"
#include "MF_FFT.h"
#include "MF_TIMADC.h"
#include "stdio.h"
#include "math.h"

#include "gpio.h"


//0xa1 -->  测量无明显失真的波的THD
//0xa2 -->  测量顶部失真的波的THD
//0xa3 -->  测量底部失真的波的THD
//0xa4 -->  测量双向失真的波的THD
//0xa5 -->  测量交越失真的波的THD
//0xa6 -->  测量外部的THD

//串口屏返回的键值
uint8_t receiveKey = 0 ;

//对输出数据进行怎么样的运算，然后，取平均值等等
#define ManyTimes 5




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART1){
		//witchKey();
		HAL_UART_Receive_IT(&huart1,&receiveKey,1);
	}
}

//发送三个 0xFF 给串口屏结束此次通信
void MF_Send_End_to_HMI(void){ 			
	uint8_t tx = 0xff ;
	HAL_UART_Transmit(&huart1,&tx,1,1000);
	HAL_UART_Transmit(&huart1,&tx,1,1000);
	HAL_UART_Transmit(&huart1,&tx,1,1000);
}


//对THD进行计算 串口屏进行显示
void matchTHD_printfTHD(uint8_t key){
	
	double Show_THD[ManyTimes] ;
	double averageTHD = 0 ;
	int i ;
//	float  a = 0.618 ;
	
	//MF_Send_End_to_HMI();
//	MF_FFT_Get_1KHz_Base_THD();
//	MF_FFT_Get_Unkown_Frequency_THD();  //这两个选哪个，怎么优化，可调
	
	if(key == 0xa6){
			printf("page2.t7.txt=\"Accessed!!!\"");
			MF_Send_End_to_HMI();
		}else{
			printf("page1.t7.txt=\"Accessed!!!\"");
			MF_Send_End_to_HMI();
		}
	
		MF_SignalInput();
		MF_FFT_MagOperation();  //这两个进行了FFT运算
		
	
		
		//以下是几种方案
		//Show_THD[0] = MF_FFT_Get_Unkown_Frequency_THD()  * 100 * 100 *  MF_FFT_Get_Unkown_Frequency_THD() * 0.1;
				Show_THD[0] = MF_FFT_Get_Unkown_Frequency_THD()  * 100 * 1.2 ;
		//			Show_THD[0] = MF_FFT_Get_1KHz_Base_THD() * 100 * 1.5;
		if(key == 0xa6){
			printf("page2.t3.txt=\"%.2f\"",Show_THD[0]);
			MF_Send_End_to_HMI();
			
		}else{
			printf("page1.t3.txt=\"%.2f\"",Show_THD[0]);
			MF_Send_End_to_HMI();
		}

		
	for( i = 1 ; i < ManyTimes ; i++){
		MF_SignalInput();
		MF_FFT_MagOperation();  //这两个进行了FFT运算
		
		Show_THD[i] = MF_FFT_Get_Unkown_Frequency_THD()  * 100 * 1.2;//* a  + Show_THD[i-1]*( 1 - a );
		//Show_THD[i] = MF_FFT_Get_1KHz_Base_THD() * 100 * 1.5 ;
		
		//是否每一个都进行显示，还是之后取平均值显示一次，可调
		if(key == 0xa6){
			printf("page2.t3.txt=\"%.2f\"",Show_THD[i]);
			MF_Send_End_to_HMI();
			
		}else{
			printf("page1.t3.txt=\"%.2f\"",Show_THD[i]);
			MF_Send_End_to_HMI();
		}
		
		
	//	HAL_Delay(1000);
	}
	for( i = 0 ; i < ManyTimes ; i++){
	
		averageTHD += Show_THD[i];
		
	}
	averageTHD = averageTHD/ ManyTimes ;
	printf("page1.t3.txt=\"%.2f\"",averageTHD);
	MF_Send_End_to_HMI();
	
}


void MF_Control_GPIO( GPIO_PinState PinState1 , GPIO_PinState PinState2 , GPIO_PinState PinState3 , GPIO_PinState PinState4){
		
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,PinState1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,PinState2);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,PinState3);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,PinState4);

}


//GPIO输出控制只是 PD 端口,对应 0 1 4 5
//															A B C D

//无明显失真										1 0 0 0
//顶部失真											0 0 1 1
//底部失真											0 1 1 0
//双向失真  										0 1 1 1
//交越失真              				0 0 0 0
void witchKey(void){
	switch(receiveKey){
		case 0xa1:
			//控制 GPIO 输出无明显失真的正弦波 1 0 0 0
		MF_Control_GPIO( GPIO_PIN_SET , GPIO_PIN_RESET , GPIO_PIN_RESET , GPIO_PIN_RESET);
		
		matchTHD_printfTHD(receiveKey);
		receiveKey = 0 ;
			break ;
		
		
		case 0xa2:
			//控制 GPIO 输出顶部失真的正弦波 0 0 1 1
			MF_Control_GPIO( GPIO_PIN_RESET , GPIO_PIN_RESET , GPIO_PIN_SET , GPIO_PIN_SET);
		
		matchTHD_printfTHD(receiveKey);
		receiveKey = 0 ;
			break ;
		
		
		case 0xa3:
			//控制 GPIO 输出底部失真的正弦波 0 1 1 0
			MF_Control_GPIO( GPIO_PIN_RESET , GPIO_PIN_SET , GPIO_PIN_SET , GPIO_PIN_RESET);
		
		matchTHD_printfTHD(receiveKey);
		receiveKey = 0 ;
			break ;
		
		
		case 0xa4:
			//控制 GPIO 输出双向失真的正弦波 0 1 1 1
			MF_Control_GPIO( GPIO_PIN_RESET , GPIO_PIN_SET , GPIO_PIN_SET , GPIO_PIN_SET);
		
		matchTHD_printfTHD(receiveKey);
		receiveKey = 0 ;
			break ;
		
		
		case 0xa5:
			//控制 GPIO 输出交越失真的正弦波 0 0 0 0
			MF_Control_GPIO( GPIO_PIN_RESET , GPIO_PIN_RESET , GPIO_PIN_RESET , GPIO_PIN_RESET);
		
		matchTHD_printfTHD(receiveKey);
		receiveKey = 0 ;
			break ;
		
		
		case 0xa6:
			//控制 GPIO 输出外部失真的正弦波
		
		matchTHD_printfTHD(receiveKey);
		receiveKey = 0 ;
			break ;
	}
}

