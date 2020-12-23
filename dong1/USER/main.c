#include "main.h"



int main()
{
	GPIO_InitTypeDef G;
	
	IIC_Init();
  delay_init();
	OLED_Init();
	Dac1_Init();
	

		OLED_CLS();
	
	while(1)
	{
		Dac1_Set_Vol((u16)2300);
		OLED_ShowChinese(0,0,0);
		OLED_ShowChinese(18,0,1);
	}
	
	
	
	
	return 0 ;
	
}

