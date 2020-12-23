
#include "MF_TIMADC.h"

#include "MF_FFT.h"
#include "tim.h"
#include "adc.h"
#include "stdio.h"
#include "gpio.h"
#include "arm_math.h"



uint32_t Value[Length_Of_FFT]={0};

int i = 0 ;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM1){
		if(i < Length_Of_FFT ){	
			HAL_TIM_Base_Stop_IT(&htim1) ;  //关闭定时器
			

			HAL_ADC_Start(&hadc3);
			if( HAL_ADC_PollForConversion(&hadc3, 100) == HAL_OK ){
       			Value[i++] = HAL_ADC_GetValue(&hadc3);
   		}
			HAL_ADC_Stop(&hadc3);
			

//			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_1);
			
			HAL_TIM_Base_Start_IT(&htim1);  //重新打开定时器
			
		}else{
			HAL_TIM_Base_Stop_IT(&htim1);
		}
	}
}

void MF_SignalInput(void){
	i = 0 ;
	int j ;

//	for( j =0 ; j < Length_Of_FFT ; j++ ){
//		Value[j] = 0 ;
//	}
//	
	
	//adc自检程序
//	HAL_ADCEx_Calibration_Start(&hadc3,0xff);

	
	//定时器中断来采集
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_Delay(1000);										//等待采样值采样完
			

	

		for( j = 0 ; j < Length_Of_FFT ; j++ ){
			MF_FFT_Inputbuff[2*j] = (float)(
															( 91710000
															-	91710000 * arm_cos_f32( 0.0000002463 * ( (double)Value[j] * MF_Frequency ) )
															+	4077000  * arm_sin_f32( 0.0000002463 * ( (double)Value[j] * MF_Frequency ) ) 
															) * 
															( 1 - 0.11) - 58.0 ) 
															/1000;
			
//			MF_FFT_Inputbuff[2*j] = ( (double)Value[j] * MF_Frequency  * 1.018 - 53.45
//															)   /1000;		
		

			MF_FFT_Inputbuff[2*j+1] = 0 ;
		}
		
		
//			MF_FFT_Inputbuff[2*j] = ( (double)Value[i] * MF_Frequency  * 1.018 - 53.45
//															) ; //  /1000;		
		
		
		
		
		
		

//		for( j = 0 ; j < Length_Of_FFT ; j++ ){
//			//printf("%d --> %.3f  V \r\n", j , MF_FFT_Inputbuff[2*j] );
//			printf("%d ===> %d\r\n",j , Value[j] );
//		}




		return ;
}





