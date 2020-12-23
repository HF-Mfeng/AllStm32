

#include "MF_ADC_DMA.h"
#define Precision 12.0


#include "main.h"
#include "adc.h"
#include "bdma.h"
#include "gpio.h"
#include "math.h"
#include "arm_math.h"

#include "MF_FFT.h"



//为fft输入数组进行赋值，输入参数
void MF_SignalInput(void){
	int i ;
//	float Voltage ;
	uint32_t Value[Length_Of_FFT] ;

	HAL_ADC_Start_DMA(&hadc3,Value,Length_Of_FFT);		//开启DMA通道
	HAL_Delay(1000);																	//等待转化完成
	HAL_ADC_Stop_DMA(&hadc3);													//关闭DMA通道

//	for ( i = 0; i < 2*Length_Of_FFT; i+=2){
//		MF_FFT_Inputbuff[i] = 1782 - 1752 *arm_cos_f32(0.00008719*(Value[i]*MF_Frequency)) + 11270 *arm_sin_f32( 0.00008719 *(Value[i]*MF_Frequency));
//		
//		MF_FFT_Inputbuff[i+1] = 0 ;
//		//1782 - 1752 *arm_cos_f32(0.00008719*(Value[i]*MF_Frequency)) + 11270 *arm_sin_f32( 0.00008719 *(Value[i]*MF_Frequency))
//	}
	
	for( i = 0 ; i < Length_Of_FFT ; i++ ){
		MF_FFT_Inputbuff[2*i] = 1782 
														- 1752 *arm_cos_f32(0.00008719*(Value[i]*MF_Frequency)) 
														+ 11270 *arm_sin_f32( 0.00008719 *(Value[i]*MF_Frequency));
		MF_FFT_Outputbuff[2*i+1] = 0 ;
	}
	
	
}

