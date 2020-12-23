#include "AD9959.h"

//并没有用到CH3和CH4
uint8_t CSR_DATA0[1] = {0x10} ; //开CH0
uint8_t CSR_DATA1[1] = {0x10} ; //开CH1
// uint8_t CSR_DATA2[1] = {0x10} ;
// uint8_t CSR_DATA3[1] = {0x10} ;

uint8_t FR2_DATA[2] = {0x00,0x00};//default Value = 0x0000
uint8_t CFR_DATA[3] = {0x00,0x03,0x02};//default Value = 0x000302	   
																	
uint8_t CPOW0_DATA[2] = {0x00,0x00};//default Value = 0x0000   @ = POW/2^14*360
																	


uint8_t LSRR_DATA[2] = {0x00,0x00};//default Value = 0x----
																	
uint8_t RDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------
																	
uint8_t FDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------

//------------------------------------------------------------------------------
//另外一些参数
uint8_t Task_Index = 0;//界面切换
uint8_t Param_Mode = 0;//参数类型切换
uint8_t fre_buf[StrMax]; //参数转化字符缓存
uint8_t display[StrMax]; //参数显示缓存
uint8_t P_Index = 0; //编辑位置
uint8_t Task_First=1;//第一次进入标记
uint8_t _return=0;
uint32_t SinFre[5] = {50, 50, 50, 50};
uint32_t SinAmp[5] = {1023, 1023, 1023, 1023};
uint32_t SinPhr[5] = {0, 4095, 4095*3, 4095*2};
uint32_t SinFre0[4] = {1000};
//扫频参数
uint32_t SweepMinFre = 1000;
uint32_t SweepMaxFre = 10000;
uint32_t SweepStepFre = 100;
uint16_t SweepTime = 1;//ms
uint8_t SweepFlag = 0;

//AD9959初始化
void Init_AD9959(void)  
{ 
	//20倍频 Charge pump control = 75uA FR1<23> -- VCO gain control =0时 system clock below 160 MHz;
 	uint8_t FR1_DATA[3] = {0xD0,0x00,0x00};

		
	Intserve();  //IO初始化
  	IntReset();  //AD9959¸复位  
	
  WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//写功能寄存器1
//  WriteData_AD9959(FR2_ADD,2,FR2_DATA,0);
//  WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);
//  WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
//  WriteData_AD9959(ACR_ADD,3,ACR_DATA,0);
//  WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,0);
//  WriteData_AD9959(RDW_ADD,2,RDW_DATA,0);
//  WriteData_AD9959(FDW_ADD,4,FDW_DATA,1);
   //写入初始频率
	Write_frequence(3,SinFre[3]);
	Write_frequence(0,SinFre[0]); 
	Write_frequence(1,SinFre[1]);
	Write_frequence(2,SinFre[2]);
	
////	Write_frequence(3,50);
////	Write_frequence(0,50);
////	Write_frequence(1,50);
////	Write_frequence(2,50);

	Write_Phase(3, SinPhr[3]);
	Write_Phase(0, SinPhr[0]);
	Write_Phase(1, SinPhr[1]);
	Write_Phase(2, SinPhr[2]);
	
	Write_Amplitude(3, SinAmp[3]);
	Write_Amplitude(0, SinAmp[0]);
	Write_Amplitude(1, SinAmp[1]);
	Write_Amplitude(2, SinAmp[2]);
} 




void delay1 (uint32_t length);
void IntReset(void);	  //AD9959，复位
void IO_Update(void);   //AD9959，更新数据
void Intserve(void);		   //IO口初始化
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData,uint8_t temp);

void Write_frequence(uint8_t Channel,uint32_t Freq);
void Write_Amplitude(uint8_t Channel, uint16_t Ampli);
void Write_Phase(uint8_t Channel,uint16_t Phase);


