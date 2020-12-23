

#include "MF_ADC_DMA.h"
#define Precision 12.0


#include "main.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "math.h"


#include "MF_FFT.h"



//为fft输入数组进行赋值，输入参数
void MF_SignalInput(void){
	int i ;
//	float Voltage ;
	uint32_t Value[Length_Of_FFT] ;

	HAL_ADC_Start_DMA(&hadc1,Value,Length_Of_FFT);		//开启双通道
	HAL_Delay(1000);																	//等待转化完成
	HAL_ADC_Stop_DMA(&hadc1);

	for ( i = 0; i < Length_Of_FFT/2; i+=2){
		MF_FFT_Inputbuff[i] = (float)(Value[i]*MF_Frequency);
	}
}

