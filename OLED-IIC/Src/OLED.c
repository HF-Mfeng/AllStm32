#include "stm32f10x.h"
#include "OLED.h"
#include "delay.h"
#include "cobe.h"
#include "math.h"
 
 
#define SCL_H      GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define SCL_L      GPIO_ResetBits(GPIOA,GPIO_Pin_11)
#define SDA_H      GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define SDA_L      GPIO_ResetBits(GPIOA,GPIO_Pin_12)

 

 
void I2C_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructer;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructer.GPIO_Pin=GPIO_Pin_11 | GPIO_Pin_12; //6--SCL   7--SDA
    GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_Out_PP;


    GPIO_Init(GPIOA, &GPIO_InitStructer);

}
 
void SDA_OUT(void){
    GPIO_InitTypeDef GPIO_InitStructer;
    GPIO_InitStructer.GPIO_Pin= GPIO_Pin_12;
    GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_Out_PP;                   
    GPIO_Init(GPIOA, &GPIO_InitStructer);
}

void SDA_IN(void){
	GPIO_InitTypeDef GPIO_InitStructer;
	GPIO_InitStructer.GPIO_Pin= GPIO_Pin_12;
	GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IPU;                    
	GPIO_Init(GPIOA, &GPIO_InitStructer);
}

void I2C_Start(void)
{
    SDA_OUT();     //这种东西把，是这样子的
    
    SDA_H;
    SCL_H;

    delay_us(2); //

    SDA_L;
    delay_us(2);
    
    SCL_L;
	delay_us(2);
}
 

void I2C_Stop(void)
{
    //SDA_OUT();
    
    SCL_H;

    SDA_L;
    
	delay_us(2);
    
    //SCL_H;
    
    SDA_H;
    delay_us(2);                                   
}

u8 I2C_Wait_Ack(void)
{
	u8 ucErrTime = 0; 

	SDA_IN(); 

	SCL_H;
	delay_us(2);     

	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12))
	{
		ucErrTime++;
		if(ucErrTime > 250)
		{
			return 1;             
		}
	}

	SCL_L;
	delay_us(2);
    
	return 0;  
}
 

void I2C_Ack(void)
{
   
    SCL_L;
    
    SDA_OUT();
    
    SDA_L;
    
    delay_us(2);
    
    SCL_H;
    
    delay_us(2);
    
    SCL_L;

}
 

void I2C_NAck(void)
{
    SCL_L;
    SDA_OUT();
    
    SDA_H;
    delay_us(2);
    
    SCL_H;
    delay_us(2);
    
    SCL_L;
}
 
void I2C_Send_Byte(u8 data)
{                        
    u8 i;  
   
	SDA_OUT();      
	
    for(i = 0; i < 8; i++)
    {   
		SCL_L;  
		delay_us(2);
        if(data&0x80)
            SDA_H;
        else
            SDA_L;
  
        SCL_H;       
        delay_us(2);
		
        SCL_L;    
        delay_us(2); 
		
		data <<= 1; 
    }     
} 
 
u8 I2C_Read_Byte(void)
{
    unsigned char i, receive = 0;
    
    SDA_IN();
    
    for(i = 0; i < 8; i++ )
    {

		SCL_L;
		delay_us(2);

		SCL_L;

		receive = (receive << 1) | GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);

		delay_us(2); 
    }
    
    return receive;
}


void WriteCmd(u8 command)
{
    I2C_Start();
    I2C_Send_Byte(0x78);//OLED??
    I2C_Wait_Ack();
    I2C_Send_Byte(0x00);//?????
    I2C_Wait_Ack();
    I2C_Send_Byte(command);
    I2C_Wait_Ack();
    I2C_Stop();
}


void WriteDat(u8 data)
{
    I2C_Start();
    I2C_Send_Byte(0x78);
    I2C_Wait_Ack();
    I2C_Send_Byte(0x40);
    I2C_Wait_Ack();
    I2C_Send_Byte(data);
    I2C_Wait_Ack();
    I2C_Stop();
}

void OLED_Init(void)
{
    delay_ms(100); 

    WriteCmd(0xAE); //display off
    WriteCmd(0x20); //Set Memory Addressing Mode    
    WriteCmd(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    WriteCmd(0xb0); //Set Page Start Address for Page Addressing Mode,0-7
    WriteCmd(0xc8); //Set COM Output Scan Direction
	
    WriteCmd(0x00); //---set low column address
    WriteCmd(0x10); //---set high column address
    WriteCmd(0x40); //--set start line address
    WriteCmd(0x81); //--set contrast control register
    WriteCmd(0xff); //???? 0x00~0xff
	
    WriteCmd(0xa1); //--set segment re-map 0 to 127
    WriteCmd(0xa6); //--set normal display
    WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
    WriteCmd(0x3F); //
    WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	
    WriteCmd(0xd3); //-set display offset
    WriteCmd(0x00); //-not offset
    WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
    WriteCmd(0xf0); //--set divide ratio
    WriteCmd(0xd9); //--set pre-charge period
		
    WriteCmd(0x22); //
    WriteCmd(0xda); //--set com pins hardware configuration
    WriteCmd(0x12);
    WriteCmd(0xdb); //--set vcomh
    WriteCmd(0x20); //0x20,0.77xVcc
		
    WriteCmd(0x8d); //--set DC-DC enable
    WriteCmd(0x14); //
    WriteCmd(0xaf); //--turn on oled panel
}



void OLED_ON(void)
{
    WriteCmd(0X8D);  
    WriteCmd(0X14);  
    WriteCmd(0XAF);  
}


 
void OLED_SetPos(unsigned char x, unsigned char y) 
{ 
    WriteCmd(0xb0+y);
    WriteCmd(((x&0xf0)>>4)|0x10);
    WriteCmd((x&0x0f)|0x01);
}


void OLED_Fill(unsigned char fill_Data)
{
    unsigned char m,n;
    for(m=0;m<8;m++)
    {
        WriteCmd(0xb0+m);       //page0-page1
        WriteCmd(0x00);     //low column start address
        WriteCmd(0x10);     //high column start address
        for(n=0;n<128;n++)
            {
                WriteDat(fill_Data);
            }
    }
}

void OLED_CLS(void)
{
    OLED_Fill(0x00);
}



void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
    unsigned char c = 0,i = 0,j = 0;
    switch(TextSize)
    {
        case 1:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 126)
                {
                    x = 0;
                    y+=1;
                }
                OLED_SetPos(x,y);
                for(i=0;i<6;i++)
                    WriteDat(F6x8[c][i]);
                x += 6;
                j++;
            }
        }break;
        case 2:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 120)
                {
                    x = 0;
                    y++;
                }
                OLED_SetPos(x,y);
                for(i=0;i<8;i++)
                    WriteDat(F8X16[c*16+i]);
                OLED_SetPos(x,y+1);
                for(i=0;i<8;i++)
                    WriteDat(F8X16[c*16+i+8]);
                x += 8;
                j++;
            }
        }break;
				
    }
}

void OLED_ShowChinese(unsigned char x, unsigned char y, unsigned char no)
{
	unsigned char i;
		if(x > 120)
		{
			x = 0;
			y++;
		}
		OLED_SetPos(x,y);
		for(i=0;i<32;i++)
			WriteDat(F16x16[2*no][i]);
		
		OLED_SetPos(x,y+1);
		for(i=0;i<32;i++)
			WriteDat(F16x16[2*no+1][i]);
		
		
}
