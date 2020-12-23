#ifndef MUFENG_FFT_H
#define MUFENG_FFT_H

#include "stm32_dsp.h"

#define TWOFIVESIX		//设置采样点数，为256点

#ifdef TWOFIVESIX
#define Length 256 
#else
#ifdef ONEZEROTWOFOUR
#define Length 1024
#else 
#ifdef SIXFOUR
#define Length 64
#endif
#endif
#endif

typedef struct 
{
	double Frequency;
	double Phase;
}MFSign;


extern uint32_t MF_InputBox[Length] ;
extern uint32_t MF_OutputBox[Length] ;
extern uint32_t MF_FFT_Mag[Length/2] ;
extern double Fs;



/********************************************************************************************************
函数名称:MF_FFT_GetMag()
函数功能:计算各次谐波幅值
返回值：无
参数说明:无
备　　注:先将 MF_OutputBox 分解成实部(Y)和虚部(X)，然后计算幅频特性序列MF_FFT_Mag
         本函数参考网页：https://wenku.baidu.com/view/08ccee0984868762cbaed532.html，关于幅频特性计算部分
作	 者:沐风，QQ:2498369702
**********************************************************************************************************/
void MF_FFT_GetMag(void);


/********************************************************************************************************
函数名称:MF_FFT_GetFrequency(int MinMag,float size,int index)
函数功能:得到复杂信号包括的频率
返回值：double,意义就是频率值
参数说明:MinMag为复杂信号中预估计幅度的最小值，小于 MinMag*(1-size) 的会被过滤掉;
		size,表示查找最低值；
		只会找出下标大于等于index，小于Length/2的
备　　注:需要调用此函数进行多次调用，直到找出所有的频率为止
			调用方法：
				while(temp=MF_FFT_GetFrequency(minmag,size,&m)!=-1)(run code);
作	 者:沐风，QQ:2498369702
**********************************************************************************************************/
double MF_FFT_GetFrequency(int MinMag,float size,int *index);

/********************************************************************************************************
函数名称:MF_FFT_GetFrequencyAndPhase(int MinMag,float size,int index)
函数功能:得到复杂信号包括的频率
返回值：int,返回0表示正确，返回-1，表示出问题了
参数说明:MinMag为复杂信号中预估计幅度的最小值，小于 MinMag*(1-size) 的会被过滤掉;
		size,表示查找最低值；
		只会找出下标大于等于index，小于Length/2的
		asign为结构体指针，可以进行传参
备　　注:需要调用此函数进行多次调用，直到找出所有的频率为止
			调用方法：
				while(MF_FFT_GetFrequencyAndPhase(minmag,size,&m,&t)!=-1)(run code);
作	 者:沐风，QQ:2498369702
**********************************************************************************************************/
int MF_FFT_GetFrequencyAndPhase(int MinMag,float size,int *index,MFSign *asign);



/********************************************************************************************************
函数名称:MF_FFT_Init(double F);
函数功能:初始化FFT
返回值：无
参数说明:F表示采样频率
备　　注:无
作	 者:沐风，QQ:2498369702
**********************************************************************************************************/
void MF_FFT_Init(double F);

//void MF_FFT_InputSignal(double v,int i);

/********************************************************************************************************
函数名称:MF_FFT_Phase(double f);
函数功能:计算出相位
返回值：相位，是°，而不是弧度
参数说明:f表示所求某一频率
备　　注:无
作	 者:沐风，QQ:2498369702
**********************************************************************************************************/
double MF_FFT_Phase(double f);
#endif
