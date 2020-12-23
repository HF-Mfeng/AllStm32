/* USER CODE BEGIN */

#include "forOLED.h"
#include "OLED_Font.h"
#include "OLED_Bmp.h"

#define OLED_CMD 0
#define OLED_DATA 1
extern I2C_HandleTypeDef hi2c2;

void OLED_WR_Byte(uint8_t dat,unsigned char cmd){
	uint8_t m = 0x00 , n = 0x78;
	if(cmd == OLED_DATA)  m = 0x40;
//	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0x11, &n, sizeof(int8_t), 10000);
//	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0x11, &m, sizeof(int8_t), 10000);
//	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0x11, &dat, sizeof(int8_t), 10000);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0x78, &n, sizeof(int8_t), 10000);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0x78, &m, sizeof(int8_t), 10000);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0x78, &dat, sizeof(int8_t), 10000);
//	HAL_I2C_Slave_Transmit(&hi2c2, &n, sizeof(uint8_t), 10000);
//	HAL_I2C_Slave_Transmit(&hi2c2, &m, sizeof(uint8_t), 10000);
//	HAL_I2C_Slave_Transmit(&hi2c2, &dat, sizeof(uint8_t), 10000);
	return ;
}
		   

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	  
   
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X14,OLED_CMD);  
	OLED_WR_Byte(0XAF,OLED_CMD);  
}
   
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X10,OLED_CMD);  
	OLED_WR_Byte(0XAE,OLED_CMD);  
}		   			 
 
void OLED_Clear(void)  
{  
	unsigned char i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //?????(0~7)
		OLED_WR_Byte (0x02,OLED_CMD);      //??????—????
		OLED_WR_Byte (0x10,OLED_CMD);      //??????—????   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //????
}
void OLED_ClearWhite(void)  
{  
	unsigned char i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //?????(0~7)
		OLED_WR_Byte (0x02,OLED_CMD);      //??????—????
		OLED_WR_Byte (0x10,OLED_CMD);      //??????—????   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //????
}

void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//???????			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(SIZE ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y+1);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}

unsigned long oled_pow(unsigned char m,unsigned char n)
{
	unsigned long result=1;	 
	while(n--)result*=m;    
	return result;
}				  
		  
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size)
{         	
	unsigned char t,temp;
	unsigned char enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 

void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{      			    
	unsigned char t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}

void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 
				    
void OLED_Init(void)
{
  
	OLED_WR_Byte(0xae,OLED_CMD);	//--turn off oled panel

	OLED_WR_Byte(0x00,OLED_CMD);	//--set low column address
	OLED_WR_Byte(0x10,OLED_CMD);	//--set high column address

	OLED_WR_Byte(0x40,OLED_CMD);	//--set start line address

	OLED_WR_Byte(0xb0,OLED_CMD);	//--set page address

	OLED_WR_Byte(0x81,OLED_CMD);	//--set contrast control register
	OLED_WR_Byte(0xff,OLED_CMD);

	OLED_WR_Byte(0xa1,OLED_CMD);	//--set segment re-map 127 to 0   a0:0 to seg127
	OLED_WR_Byte(0xa6,OLED_CMD);	//--set normal display

	OLED_WR_Byte(0xc9,OLED_CMD);	//--set com(N-1)to com0  c0:com0 to com(N-1)

	OLED_WR_Byte(0xa8,OLED_CMD);	//--set multiples ratio(1to64)
	OLED_WR_Byte(0x3f,OLED_CMD);	//--1/64 duty

	OLED_WR_Byte(0xd3,OLED_CMD);	//--set display offset
	OLED_WR_Byte(0x00,OLED_CMD);	//--not offset

	OLED_WR_Byte(0xd5,OLED_CMD);	//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);	//--set divide ratio

	OLED_WR_Byte(0xd9,OLED_CMD);	//--set pre-charge period
	OLED_WR_Byte(0xf1,OLED_CMD);

	OLED_WR_Byte(0xda,OLED_CMD);	//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);

	OLED_WR_Byte(0xdb,OLED_CMD);	//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);

	OLED_WR_Byte(0x8d,OLED_CMD);	//--set chare pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);	//--set(0x10) disable
							//Write_Command3(0x10);	//--set(0x10) disable
	OLED_WR_Byte(0xaf,OLED_CMD);	//--turn on oled panel
	// OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	// OLED_WR_Byte(0x02,OLED_CMD);//---set low column address
	// OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	// OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	// OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	// OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	// OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0???? 0xa1??
	// OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0???? 0xc8??
	// OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	// OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	// OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	// OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	// OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	// OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	// OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	// OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	// OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	// OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	// OLED_WR_Byte(0x12,OLED_CMD);
	// OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	// OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	// OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	// OLED_WR_Byte(0x02,OLED_CMD);//
	// OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	// OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	// OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	// OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	// OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	// OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	//OLED_Clear();
	//OLED_Set_Pos(0,0); 
		
}  





/* USER CODE END*/

