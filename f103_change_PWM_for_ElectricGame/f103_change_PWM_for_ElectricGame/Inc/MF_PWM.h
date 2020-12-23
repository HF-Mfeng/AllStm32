
#ifndef MF_PWM_H_2020_12_9
#define MF_PWM_H_2020_12_9

// 设置最大频率为 20khz
#define MF_Frequency_Max 20000
#define MF_Frequency_Min 10

void MF_setPWM_Frequency_Duty(int Frequency, int Duty);
void MF_setPWM_Tms_Duty(double T_ms, int Duty);
void MF_setPWM_du(int du);


#endif


