

//这里是来自vscode中的东东

#include <math.h>
#include "delay.h"
#include "sys.h"
#include "OLED.h"

void name(int i){
	if(i%2+1 == 2){
	OLED_ShowChinese(0,0,0);
	delay_ms(300);
	OLED_ShowChinese(16,0,1);
	delay_ms(300);
	OLED_ShowChinese(32,0,2);
	delay_ms(300);
	OLED_ShowChinese(0,3,0);
	delay_ms(300);
	OLED_ShowChinese(16,3,3);
	delay_ms(300);
	OLED_ShowChinese(32,3,2);
	delay_ms(300);
	OLED_ShowChinese(0,6,0);
	delay_ms(300);
	OLED_ShowChinese(16,6,4);
	delay_ms(300);
	OLED_ShowChinese(32,6,2);
	delay_ms(300);
	}
	if(i%2+1 == 1){
		OLED_ShowChinese(79,0,0);
	delay_ms(300);
	OLED_ShowChinese(95,0,1);
	delay_ms(300);
	OLED_ShowChinese(111,0,2);
	delay_ms(300);
	OLED_ShowChinese(79,3,0);
	delay_ms(300);
	OLED_ShowChinese(95,3,3);
	delay_ms(300);
	OLED_ShowChinese(111,3,2);
	delay_ms(300);
	OLED_ShowChinese(79,6,0);
	delay_ms(300);
	OLED_ShowChinese(95,6,4);
	delay_ms(300);
	OLED_ShowChinese(111,6,2);
	delay_ms(300);
	}
}
int main(void)  
{ 
	
	delay_init();	    
	
	I2C_INIT();
	
	OLED_Init();
	OLED_CLS();

	
	
	
	while(1)
	{
	name(1);
	
	name(2);
	OLED_Fill(0xFF);
	delay_ms(300);
	OLED_Fill(0x00);
		
		name(2);
		name(1);
		OLED_Fill(0xFF);
		delay_ms(300);
	
		OLED_ShowStr(32, 4, (unsigned char *)"Victory!!!", 2);
		delay_ms(300);
		OLED_Fill(0x00);
		
//		OLED_ShowChinese(0,0,0);
//		OLED_ShowChinese(80,0,1);
//		OLED_ShowChinese(36,0,2);
//		OLED_ShowStr(54,0,"!",2);
//		OLED_ShowStr(0,3,"p = 5kHZ\nf = 60%",2);
	
		
	}

	
} 
