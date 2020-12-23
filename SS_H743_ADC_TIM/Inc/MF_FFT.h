
#ifndef _MF_FFT_H
#define _MF_FFT_H

//采用的是 1024 个点
#define Length_Of_FFT 1024

double MF_FFT_Get_1KHz_Base_THD(void);   			//测1khz的基波的THD
double MF_FFT_Get_Unkown_Frequency_THD(void);	//测未知频率的基波的THD


extern float MF_FFT_Inputbuff[2*Length_Of_FFT];
extern float MF_FFT_Outputbuff[Length_Of_FFT];


void MF_FFT_MagOperation(void);

#endif


