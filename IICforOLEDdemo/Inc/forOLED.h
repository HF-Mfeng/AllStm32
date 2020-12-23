/* USER CODE BEGIN  */

#include "main.h"

#define SIZE 16

#define Max_Column	128
#define Max_Row		64
//#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	  
  						  



void OLED_WR_Byte(uint8_t dat,unsigned char cmd);
		   

void OLED_Set_Pos(unsigned char x, unsigned char y) ;
   
void OLED_Display_On(void);
   
void OLED_Display_Off(void);	   			 
 
void OLED_Clear(void)  ;
void OLED_ClearWhite(void) ;
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr);

unsigned long oled_pow(unsigned char m,unsigned char n);			  
		  
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size);
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr);

void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no);

void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
				    
void OLED_Init(void);


/* USER CODE END */
