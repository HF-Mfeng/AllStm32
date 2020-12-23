#include "MF_PWM.h"

#include "tim.h"

//这里是你用哪个定时器，哪个通道，目前来说只能用一个定时器，一个通道
#define MF_TIM1
#define MF_TIM_CHANNEL_1

//设置定时器系统时钟频率
//set TIM's clock  (MHz)
#define TIMxClock 32  
#define TIMxPeriod 100



#define MF_Perscaler_Max 1000000/MF_Frequency*TIMxClock
#define MF_Perscaler_Min 1000000/MF_Frequency*TIMxClock

#ifdef MF_TIM1 
#define MF_TIM htim1
#elif MF_TIM2
#define MF_TIM htim2 
#elif MF_TIM3
#define MF_TIM htim3
#elif MF_TIM4
#define MF_TIM htim4
#endif

#ifdef MF_TIM_CHANNEL_1 
#define MF_TIM_CHANNEL TIM_CHANNEL_1
#elif MF_TIM_CHANNEL_2
#define MF_TIM_CHANNEL TIM_CHANNEL_2 
#elif MF_TIM_CHANNEL_3
#define MF_TIM_CHANNEL TIM_CHANNEL_3
#elif MF_TIM_CHANNEL_4
#define MF_TIM_CHANNEL TIM_CHANNEL_4
#elif MF_TIM_CHANNEL_ALLL
#define MF_TIM_CHANNEL TIM_CHANNEL_ALL
#endif

// Freuency (Hz)
// Duty %
void MF_setPWM_Frequency_Duty(int Frequency, int Duty){

	int perscaler = 0 ;
	int period = 0 ;
	int pulse = 0 ;
	
	if( Frequency >=  MF_Frequency_Min && Frequency <= MF_Frequency_Max && Duty > 4 && Duty < 96 ){
		perscaler = (int)( (double)1000000/Frequency*TIMxClock/TIMxPeriod - 1 );
		period = TIMxPeriod-1 ;
		pulse = Duty;
		MX_TIM1_Init(perscaler,period,pulse);	
		HAL_TIM_PWM_Start(&MF_TIM,MF_TIM_CHANNEL);	
	}
}

//T'unit is ms 
void MF_setPWM_Tms_Duty(double T_ms, int Duty){

	int perscaler = 0 ;
	int period = 0 ;
	int pulse = 0 ;
	double Frequency = 1000.0/T_ms;
	if( Frequency >=  MF_Frequency_Min && Frequency <= MF_Frequency_Max && Duty > 4 && Duty < 96 ){
		perscaler = (int)( (double)1000000/Frequency*TIMxClock/TIMxPeriod - 1 );
		period = TIMxPeriod-1 ;
		pulse = Duty;
		MX_TIM1_Init(perscaler,period,pulse);	
		HAL_TIM_PWM_Start(&MF_TIM,MF_TIM_CHANNEL);	
	}
}

//驱动舵机 0.5 ms ~ 2.5 ms的高电平
//    对应  0°    ~ 180°
void MF_setPWM_du(int du){

	int perscaler = 0 ;
	int pulse = 0 ;
	
	double Frequency ;
	
	if(du < 0 || du > 180)
		return;
	// 频率是50hz
	
	  Frequency = 45000.0/(du+45);
		perscaler = (int)( (double)1000000/Frequency*TIMxClock/TIMxPeriod - 1 );
		MX_TIM1_Init(perscaler,TIMxPeriod-1,50);	
		HAL_TIM_PWM_Start(&MF_TIM,MF_TIM_CHANNEL);	

}

