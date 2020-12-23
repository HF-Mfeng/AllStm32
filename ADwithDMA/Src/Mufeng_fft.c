
#include "Mufeng_fft.h"
#include "stdio.h"
#include "table_fft.h"  //一个问题，如果在.h中引入这个东西，
												//那么这个里面的变量就会被重复定义，
												//一般来说，变量都是在.c文件中定义，然后用extern在.h中声明一下
#include "math.h"

double Fs;//采样频率

/*
 * 1、这两个数组，上面是输入，下面是输出，都是高16位为实部，低16位为虚部。
 * 2、对于输入数组而言，低16为永远为0，所以，从cr4_fft_256_stm32函数中出来的数据，需要进行移位
 * 3、得到原波有 哪几种频率的正弦波组成 又因为 MF_FFT_Mag 每一组都是 y+jx 实部：y，虚部：x
 *		可以得出以下结论：
 *			幅度：sqrt(x*x+y*y)，这个已经保存在MF_FFT_Mag函数中了，不需要再进行计算
 * 			移相角度：arctan(x/y) , 注意角度与弧度的换算
 * 
 * 4、函数 MF_FFT_GetMag 给一个名为 MF_FFT_Mag 的数组进行了赋值，数组中下标为 index ，fft分辨率为 f HZ 
 *	频率值为 (index*f)HZ 的频率幅度值为 MF_FFT_Mag[index] 
 *	关于fft分辨率 f 的计算是：
 *		采样频率为 Fs，信号频率为 Fn，采样点数为 N(这里为256)
 *			那么 f = Fs/N 
 *			采样频率 Fs 需大于被采样波形频率的两倍（假设你需要采样的波形频率为50Hz，则采样频率必须在100Hz以上）。
 *			如果采样频率是 20kHZ 那么分辨率就是 78.125HZ		
 * 
 * 5、一般信号都会分为一个直流与多个正弦信号的合体，直流信号幅度值就是 MF_FFT_GetMag[0]，
 * 6、实部 y=(uint16_t)mag[i] >> 16 ; x=(uint16_t)((mag[i] << 16) >> 16);
*/
uint32_t MF_InputBox[Length]={0};	
uint32_t MF_OutputBox[Length]={0}; 	

uint32_t MF_FFT_Mag[Length/2]={0}; 


void MF_FFT_GetMag(){

	uint16_t lx,ly;
	float MX,MY,Mag;
	int i ;
	for ( i = 0; i < Length/2; i++) {			//由于FFT的频谱结果是关于奈奎斯特频率对称的，所以只计算一半的点即可

		lx = (uint16_t)((MF_OutputBox[i] << 16)>>16);		//取低16位，做虚部
		ly = (uint16_t)(MF_OutputBox[i] >>16);				//取高16位，做实部

		MX = Length * ((float)lx) / 32768;
		MY = Length * ((float)ly) / 32768;

// 官方fft 函数出来之后得到的数组每个元素应该是一个序数，即低16为虚部，高16为实部
// y+jx  那么幅度值mag = sqrt(x*x+y*y) 
		Mag = sqrt(MX*MX + MY*MY) / Length ; 		

		MF_FFT_Mag[i] = (uint32_t)(Mag * 65536) ;   //前面除以32768，之后乘以65536是为了满足float运算规律
	}
	MF_FFT_Mag[0] /= 2  ;
}

double MF_FFT_GetFrequency(int MinMag,float size,int *index){
	int i ;
	for ( i = (*index); i < Length/2; i++)
	{
		if(MF_FFT_Mag[i] >= MinMag*size){		//得到目标值就返回
			(*index) = i+1 ;
			return Fs/Length*i;
		}
	}
	return -1;
}
int MF_FFT_GetFrequencyAndPhase(int MinMag,float size,int *index,MFSign *asign){
	int i ;
	if((*index) >= Length/2)
		return -1 ;
	for ( i = (*index); i < Length/2; i++)
	{
		if(MF_FFT_Mag[i] >= MinMag*size){		//得到目标值就返回
			(*index) = i+1 ;
			asign->Frequency = Fs/Length*i;
			asign->Phase = 
					atan2(	(double)	(	(int)  (  (MF_FFT_Mag[i] << 16) >> 16  )	) ,  	//虚部
							(double)	(	(int)  (   MF_FFT_Mag[i]  >> 16		   )	) ) 	//实部
					* 360 / 2 / 3.1415926 ;
			return 0;
		}
	}
	return -1 ;
}

void MF_FFT_Init(double F){
	Fs = F;
	cr4_fft_256_stm32(MF_OutputBox,MF_InputBox,Length);
	MF_FFT_GetMag();
}

double MF_FFT_Phase(double f){
	// atan2(x,y)*360/2/3.1415926535   返回x/y的角度，符号为°
	// f*Length/Fs
	int i = (int)f*Length/Fs;
	if(i >= Length/2)
		return -361;
	return atan2(	(double)	(	(int)  (  (MF_FFT_Mag[i] << 16) >> 16  )	) ,  			//虚部
							(double)	(	(int)  (   MF_FFT_Mag[i]  >> 16		   )	) ) 	//实部
					* 360 / 2 / 3.1415926 ;											//返回某一个角度，可能是正，可能是负，应该有bug
}




// void MF_FFT_InputSignal(double v,int i){
// 	if(i >= Length)
// 		return ;
// 	MF_InputBox[i] = v ;
// }




