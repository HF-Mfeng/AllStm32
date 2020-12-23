
#include "MF_FFT.h"
#include "arm_math.h"

float MF_FFT_Inputbuff[2*Length_Of_FFT];
float MF_FFT_Outputbuff[Length_Of_FFT];

void MF_FFT_MagOperation(void){
	arm_cfft_radix4_instance_f32 scfft;
	arm_cfft_radix4_init_f32(&scfft,Length_Of_FFT,0,1);//初始化scfft结构体，设定FFT相关参数
	arm_cfft_radix4_f32(&scfft,MF_FFT_Inputbuff);	//FFT计算（基于4）
	arm_cmplx_mag_f32(MF_FFT_Inputbuff,MF_FFT_Outputbuff,Length_Of_FFT);	//把运算结果求得模值 
}

