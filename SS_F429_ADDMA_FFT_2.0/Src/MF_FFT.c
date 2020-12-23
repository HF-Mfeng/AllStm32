
#include "MF_FFT.h"
#include "arm_math.h"
#include "math.h"

#define Fs 500
#define COUNT 5  //计算五次谐波
float MF_FFT_Inputbuff[2*Length_Of_FFT];
float MF_FFT_Outputbuff[Length_Of_FFT];

void MF_FFT_MagOperation(void){
	arm_cfft_radix4_instance_f32 scfft;
	arm_cfft_radix4_init_f32(&scfft,(uint16_t)Length_Of_FFT,0,1);//初始化scfft结构体，设定FFT相关参数
	arm_cfft_radix4_f32(&scfft,MF_FFT_Inputbuff);	//FFT计算（基于4）
	arm_cmplx_mag_f32(MF_FFT_Inputbuff,MF_FFT_Outputbuff,Length_Of_FFT);	//把运算结果求得模值 
}

void MF_DataImprove(void){

	
}


double MF_CalculateTHD(void){
	
	int i , j ;
//	float max = MF_FFT_Outputbuff[1] ;
//	int BaseFrequency = 1 ;     //基波的下标
	float sum = 0 ;
	
	//认定频率就是500HZ的方法
//	for ( i = 2 ; i < Length_Of_FFT/2 ; i++ ){
//		if( max < MF_FFT_Outputbuff[i] ){
//				max = MF_FFT_Outputbuff[i];
//				BaseFrequency =  i ;
//		}
//	}										//找出基波
//	
//	for ( i = 2 ; i <= count ; i++){
//			sum = sum + MF_FFT_Outputbuff[ i*BaseFrequency ] * MF_FFT_Outputbuff[ i*BaseFrequency ] ;
//	}
//	sum = sqrt(sum) ;
	
	float countFrequency[COUNT] = {0} ;
	
	countFrequency[0] = MF_FFT_Outputbuff[0] ;
	//找出前几个大值的方法，找出前COUNT个值的方法
	
	for( i = 1 ; i < Length_Of_FFT / 2 ; i++ ) {           //先找出基波，是最大的那个
		if( countFrequency[0] < MF_FFT_Outputbuff[i] ) {
			countFrequency[0] = MF_FFT_Outputbuff[i]; 
		}
	}
	
	
	for( j = 1 ; j < COUNT ; j++){												//找出谐波
		countFrequency[j] = -1 ;
		
		for( i = 1 ; i < Length_Of_FFT / 2 ; i++ )
			if( ( countFrequency[j] < MF_FFT_Outputbuff[i] ) && (MF_FFT_Outputbuff[i] < countFrequency[j-1]) )
					countFrequency[j] = MF_FFT_Outputbuff[i];
			
	}
	
	for( i = 1 ; i < COUNT ; i++){
			sum = sum + countFrequency[i] * countFrequency[i] ;
	}
	sum = sqrt(sum) ;
	return ( sum / countFrequency[0] ) ;
	
	//return (sum / MF_FFT_Outputbuff[BaseFrequency]);
	
	

}


