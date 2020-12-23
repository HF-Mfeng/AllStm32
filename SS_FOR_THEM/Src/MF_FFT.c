
#include "MF_FFT.h"
#include "arm_math.h"
#include "stdio.h"

//最高频率是10.24khz
#define A10240HZ

//目前是采用 10Hz 的精度，即一格为 10Hz
#define Precision 10

//目前是采用求取 5 次谐振，现在理论能测 5.12KHz
#define COUNT 5

//优化直流，目前大概是减少20的量
#define DC


//优化 1 KHz，目前尚未解决
#define OneHz


//优化 2 KHz，目前精度尚好误差较小
#define TwoHz


//优化 3 KHz，目前精度尚好，误差第三大
//#define ThreeHz


//优化 4 KHz，目前精度尚好，误差第二大
#define FourHz


//优化 5 KHz，目前精度是最好的，所以暂不优化
//#define FiveHz


float MF_FFT_Inputbuff[2*Length_Of_FFT];
float MF_FFT_Outputbuff[Length_Of_FFT];
float MF_FFT_DataOptimize(float input, int iKHzFrequency,int canSelect);

void MF_FFT_MagOperation(void){
	arm_cfft_radix4_instance_f32 scfft;
	
	arm_cfft_radix4_init_f32(&scfft,Length_Of_FFT,0,1);//初始化scfft结构体，设定FFT相关参数

	arm_cfft_radix4_f32(&scfft,MF_FFT_Inputbuff);	//FFT计算（基于4）

	arm_cmplx_mag_f32(MF_FFT_Inputbuff,MF_FFT_Outputbuff,Length_Of_FFT);	//把运算结果求得模值 
}

//测题目说已知基波为 1KHz 的THD
double MF_FFT_Get_1KHz_Base_THD(void){
	double THD = -1 ;
	int i , j ;	
	int maxIndex ;  	//用于记录最大值的下标
	float temp ;  		//用于查验最大值
	float MF_THD[COUNT] = {1};
	double sum = 0;  	//记录谐波的平方值之和
	
	
	
//	//基波理论上此时是在下标100左右的，因为精度是10Hz，测量就只是测量下标100前后10格的最大值
//	temp = MF_FFT_Outputbuff[100] ;
//	for( i = 100-10 ; i < 100+10 ; i++ ){
//		if( temp < MF_FFT_Outputbuff[i] ){
//			maxIndex = i ;
//			temp = MF_FFT_Outputbuff[i];
//		}
//	}
//	MF_THD[0] = MF_FFT_DataOptimize(temp,1,maxIndex);
	//综合到下面的for循环中了
	
	
	//找 基波 2 3 4 5次谐波，此状态分别从下标为 200 300 400 500 的地方开始找，也是只找前后 10 格 
	for( j = 0 ; j < COUNT ; j++ ){
			temp = MF_FFT_Outputbuff[100*(j+1)] ;
			for( i = 100*(j+1)-10 ; i < 100*(j+1)+10 ; i++ ){
				if( temp < MF_FFT_Outputbuff[i] ){
					maxIndex = i ;
					temp = MF_FFT_Outputbuff[i];
				}
			}
			MF_THD[j] = MF_FFT_DataOptimize(temp,j+1,maxIndex);
	}
	
	//计算THD了
	for( i = 1 ; i < COUNT ; i++ ){
		sum += MF_THD[i] * MF_THD[i] ;
	}
	sum = sqrt(sum) ;
	
	THD = sum / MF_THD[0] ;
	
	return THD ;
}


//测未知频率的基波的THD，比如方波=43.4，三角波=12.8，(理论值)
double MF_FFT_Get_Unkown_Frequency_THD(void){
	double THD = -1;
	double sum = 0;
	int BaseIndex ;
	int i , j ;
	float temp ;
	int maxIndex ;
	int MF_Count = COUNT;
	float MF_THD[COUNT] = {1} ; //初始化为0，可能最后出现除以0的情况
	//找出幅值最大的频率值，下标 1 —— Length_Of_FFT/2, 频率为 10*i ，i表示下标，然后找2*i，3*i，4*i，5*i周围十格以内的最大值为谐波值
	temp = MF_FFT_Outputbuff[1] ;
	for( i = 1 ; i < Length_Of_FFT/2 ; i++){
		if( temp < MF_FFT_Outputbuff[i] ){
			maxIndex = i ;
			temp = MF_FFT_Outputbuff[i] ;
		}
	}
	BaseIndex = maxIndex ;
	
	MF_THD[0] = temp ;  																//用于优化的，测试可以测试测试
//	MF_THD[0] = MF_FFT_DataOptimize(temp,1,maxIndex);  //用于优化的，测试可以测试测试
	
#ifdef A10240HZ	
	//基波如果过大就要考虑改变了
	if( 10*maxIndex > 110 )
		MF_Count--;
	if( 10*maxIndex > 150)
		MF_Count--;
//	if( 10*maxIndex > 220)
//		MF_Count--;
//	if( 10*maxIndex > 260)
//		MF_Count--;
#endif
	
	//找谐波
	for( j = 1 ; j < MF_Count ; j++ ){
			temp = MF_FFT_Outputbuff[(j+1)*BaseIndex] ;
			for( i = (j+1)*BaseIndex-10 ; i < (j+1)*BaseIndex+10 ; i++ ){
				if( temp < MF_FFT_Outputbuff[i] ){
					maxIndex = i ;
					temp = MF_FFT_Outputbuff[i];
				}
			}
			
			MF_THD[j] = temp ;																	//用于优化的，测试可以选择一个
//			MF_THD[j] = MF_FFT_DataOptimize(temp,j+1,maxIndex); //用于优化的，测试可以选择一个
	}
	
	//计算THD了
	for( i = 1 ; i < MF_Count ; i++ ){
		sum += MF_THD[i] * MF_THD[i] ;
	}
	sum = sqrt(sum) ;
	
	THD = sum / MF_THD[0] ;
	
	return THD ;
}



//表示优化 iKHz 的值，目前最高是5，canSelect是可选参数，平常请置0，如果需要的话，一般表示为数组的下标
float MF_FFT_DataOptimize(float input, int i,int canSelect){
	//优化直流
#ifdef DC
	if( i == 0 ){
			return (input-20);
	}
#endif
	
	//优化1k,加上最大值前后和的3分之一
#ifdef OneHz
	if( i == 1 ){
		return ( input + ( MF_FFT_Outputbuff[canSelect-1] + MF_FFT_Outputbuff[canSelect+1] )/3 ) ;
	}
#endif
	
	//优化2k
#ifdef TwoHz
	if( i == 2 ){
			return ( input + ( MF_FFT_Outputbuff[canSelect-1] + MF_FFT_Outputbuff[canSelect+1] )/3 ) ;
	}
#endif
	
	//优化3k
#ifdef ThreeHz
	if( i == 3 ){
			return ( input + ( MF_FFT_Outputbuff[canSelect-1] + MF_FFT_Outputbuff[canSelect+1] )/3 ) ;
	}
#endif
	
	//优化4k
#ifdef FourHz
	if( i == 4 ){
			return ( input + ( MF_FFT_Outputbuff[canSelect-1] + MF_FFT_Outputbuff[canSelect+1] )/3 ) ;
	}
#endif
	
	//优化5k
#ifdef FiveHz
	if( i == 5 ){
			return (input-20);
	}
#endif	


	return input ;
}




