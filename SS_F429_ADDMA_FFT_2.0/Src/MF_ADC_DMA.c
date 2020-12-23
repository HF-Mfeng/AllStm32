

#include "MF_ADC_DMA.h"
//#define Precision 12.0


#include "main.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "math.h"
#include "arm_math.h"

#include "MF_FFT.h"

//debug
#include "stdio.h"



//为fft输入数组进行赋值，输入参数
void MF_SignalInput(void){
	int i ;
	
	uint32_t Value[Length_Of_FFT] ;	
	HAL_ADC_Start_DMA(&hadc1,Value,Length_Of_FFT);		//开启DMA通道
	HAL_Delay(1000);																	//等待转化完成
	HAL_ADC_Stop_DMA(&hadc1);													//关闭DMA通道
	
	for( i = 0 ; i < Length_Of_FFT ; i++ ){
		MF_FFT_Inputbuff[2*i] = (
															1782 
														- 1752 *arm_cos_f32 ( 0.00008719 * ( (double) Value[i] * MF_Frequency )   ) 
														+ 11270 *arm_sin_f32( 0.00008719 * ( (double) Value[i] * MF_Frequency )   )
														)  /1000;
		MF_FFT_Inputbuff[2*i+1] = 0 ;
	}				//第二次的拟合，效果还行
		
}			//函数结束处


float u32tofloat(uint32_t input){
	float output ;
//	int i ;
	//uint32_t 与 float 储存位相反
	//	u32 a = 0x00 1F C5 07 的值应该是 07 C5 1F，转为十进制应该是 509215
	//	但是如果直接强制转 a = (float)b ，它会按照 1F C5 07 的顺序转十进制 2082055
	uint32_t temp = 0 ;
	uint8_t u8temp ;
//	for( i = 0 ; i < 4 ; i++)

	u8temp = (uint8_t)( (input << 24 ) >> 24 );
	temp = (uint32_t)u8temp & 0x000000ff ;
	temp = temp << 8 ;
	
	u8temp = (uint8_t)( (input << 16) >> 24 );
	temp = temp | ( (uint32_t)u8temp & 0x000000ff ) ;
	temp = temp << 8 ;
	
	u8temp = (uint8_t)( (input << 8) >> 24 );
	temp = temp | ( (uint32_t)u8temp & 0x000000ff ) ;
	temp = temp << 8 ;
	
	u8temp = (uint8_t)( (input) >> 24 );
	temp = temp | ( (uint32_t)u8temp & 0x000000ff ) ;
	
	output = (float)temp ;
	
	return output ;
	
}


