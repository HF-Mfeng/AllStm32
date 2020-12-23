#ifndef __OLED_H__
#define __OLED_H__

#include"sys.h"
#include"stdlib.h"
#include "IIC.h"



#define OLED_CMD  0	//write command
#define OLED_DATA 1	//write data

//The next ones are not mine--------------------------------------
void WriteCmd(u8 command);
void WriteDat(u8 data);
void OLED_Init(void);
void OLED_ON(void);
void OLED_SetPos(unsigned char x, unsigned char y); 
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);//??
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowChinese(unsigned char x, unsigned char y, unsigned char no);

//----------------------------------------------------------------

//The next ones are mine-------------------------------
//void OLED_WR_Byte(u8 dat,u8 cmd);	    
//void OLED_Display_On(void);
//void OLED_Display_Off(void);
//void OLED_Refresh_Gram(void);		   
//							   		    
//void OLED_Init(void);
//void OLED_Clear(void);
//void OLED_DrawPoint(u8 x,u8 y,u8 t);
//void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
//void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
//void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
//void OLED_ShowString(u8 x,u8 y,unsigned char ch[],u8 size);	 
//u32 mypow(u8 m,u8 n);
//MINE----------------------------------------------------------

#endif

