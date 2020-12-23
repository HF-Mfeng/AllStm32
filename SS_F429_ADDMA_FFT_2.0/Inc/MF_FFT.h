
#ifndef _MF_FFT_H
#define _MF_FFT_H

#define Length_Of_FFT 1024

extern float Fs ;

extern float MF_FFT_Inputbuff[2*Length_Of_FFT];
extern float MF_FFT_Outputbuff[Length_Of_FFT];

double MF_CalculateTHD(void);
void MF_FFT_MagOperation(void);

#endif


