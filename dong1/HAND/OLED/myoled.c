#include"oledfont.h"
#include"myoled.h"

void WriteCmd(u8 command)
{
    IIC_Start();
    IIC_Send_Byte(0x78);//OLED??
    IIC_Wait_Ack();
    IIC_Send_Byte(0x00);//?????
    IIC_Wait_Ack();
    IIC_Send_Byte(command);
    IIC_Wait_Ack();
    IIC_Stop();
}


void WriteDat(u8 data)
{
    IIC_Start();
    IIC_Send_Byte(0x78);
    IIC_Wait_Ack();
    IIC_Send_Byte(0x40);
    IIC_Wait_Ack();
    IIC_Send_Byte(data);
    IIC_Wait_Ack();
    IIC_Stop();
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
		for(i=0;i<16;i++)
			WriteDat(F16x16[2*no][i]);
		
		OLED_SetPos(x,y+1);
		for(i=0;i<16;i++)
			WriteDat(F16x16[2*no+1][i]);
		
		
}




//u8 OLED_GRAM[128][64];

//void OLED_WR_Byte(u8 dat,u8 cmd )
//{
//	IIC_Start();
//	IIC_Send_Byte(0x78);
//	IIC_Wait_Ack();
//	if( cmd == OLED_CMD ) 
//		IIC_Send_Byte(0x00);
//	if( cmd == OLED_DATA )
//		IIC_Send_Byte(0x40);
//	IIC_Wait_Ack();
//	IIC_Send_Byte( dat );
//	IIC_Wait_Ack();
//	IIC_Stop();
//	
//}   
//void OLED_Display_On(void)
//{
//	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
//	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
//	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
//}
//void OLED_Display_Off(void)
//{
//	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
//	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
//	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
//}
//void OLED_Refresh_Gram(void)
//{  
//	u8 i,n;  
//	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
//	OLED_Refresh_Gram();//更新显示
//}


//void OLED_Init(void)
//{
//	 delay_ms(100); 
//	
//	OLED_WR_Byte( 0xae  , OLED_CMD ) ;
//	OLED_WR_Byte( 0x20  , OLED_CMD ) ;
//	OLED_WR_Byte( 0x10  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xb0  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xc8  , OLED_CMD ) ;
//	
//	OLED_WR_Byte( 0x00  , OLED_CMD ) ;
//	OLED_WR_Byte( 0x10  , OLED_CMD ) ;
//	OLED_WR_Byte( 0x40  , OLED_CMD ) ;
//	OLED_WR_Byte( 0x81  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xff  , OLED_CMD ) ;
//	
//	OLED_WR_Byte( 0xa1  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xa6  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xa8  , OLED_CMD ) ;
//	OLED_WR_Byte( 0x3f  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xa4  , OLED_CMD ) ;
//	
//	OLED_WR_Byte( 0xd3  , OLED_CMD ) ;
//	OLED_WR_Byte( 0x00  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xd5  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xf0  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xd9  , OLED_CMD ) ;
//	
//	OLED_WR_Byte( 0x22  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xda  , OLED_CMD ) ;
//	OLED_WR_Byte( 0x12  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xdb  , OLED_CMD ) ;
//	OLED_WR_Byte( 0x20  , OLED_CMD ) ;
//	
//	OLED_WR_Byte( 0x8d  , OLED_CMD ) ;
//	OLED_WR_Byte( 0x14  , OLED_CMD ) ;
//	OLED_WR_Byte( 0xaf  , OLED_CMD ) ;
//	
//}
//void OLED_Clear(void)
//{  
//	unsigned char m,n;
//    for(m=0;m<8;m++)
//    {
//        OLED_WR_Byte(0xb0+m,OLED_CMD );       //page0-page1
//        OLED_WR_Byte(0x00,OLED_CMD);     //low column start address
//        OLED_WR_Byte(0x10,OLED_CMD);     //high column start address
//        for(n=0;n<128;n++)
//            {
//                OLED_WR_Byte(0x00 , OLED_DATA);
//            }
//    }
//}
//void OLED_DrawPoint(u8 x,u8 y,u8 t)
//{
//	u8 pos,bx,temp=0;
//	if(x>127||y>63)return;//超出范围了.
//	pos=7-y/8;
//	bx=y%8;
//	temp=1<<(7-bx);
//	if(t)OLED_GRAM[x][pos]|=temp;
//	else OLED_GRAM[x][pos]&=~temp;	
//}
//void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)
//{
//	u8 x,y;  
//	for(x=x1;x<=x2;x++)
//	{
//		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
//	}													    
//	OLED_Refresh_Gram();//更新显示
//}
//void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
//{
//	u8 temp,t,t1;
//	u8 y0=y;
//	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
//	chr=chr-' ';//得到偏移后的值		 
//    for(t=0;t<csize;t++)
//    {   
//			if(size==12)temp=asc2_1206[chr][t]; 	 	//调用1206字体
//			else if(size==16)temp=asc2_1608[chr][t];	//调用1608字体
//			else if(size==24)temp=asc2_2412[chr][t];	//调用2412字体
//			else return;								//没有的字库
//					for(t1=0;t1<8;t1++)
//			{
//				if(temp&0x80)OLED_DrawPoint(x,y,mode);
//				else OLED_DrawPoint(x,y,!mode);
//				temp<<=1;
//				y++;
//				if((y-y0)==size)
//				{
//					y=y0;
//					x++;
//					break;
//				}
//			}  	 
//    } 
//}
//void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
//{
//	u8 t,temp;
//	u8 enshow=0;						   
//	for(t=0;t<len;t++)
//	{
//		temp=(num/mypow(10,len-t-1))%10;
//		if(enshow==0&&t<(len-1))
//		{
//			if(temp==0)
//			{
//				OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
//				continue;
//			}else enshow=1; 
//		 	 
//		}
//	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
//	}
//}
//void OLED_ShowString(u8 x,u8 y,unsigned char ch[],u8 size)
//{
//	int i = 0 ;
//	while((*(ch+i)<='~')&&(*(ch+i)>=' '))//判断是不是非法字符!
//    {       
//        if(x>(128-(size/2))){x=0;y+=size;}
//        if(y>(64-size)){y=x=0;OLED_Clear();}
//        OLED_ShowChar(x,y,*(ch+i),size,1);	 
//        x+=size/2;
//        i++;
//    }  
//}	

//u32 mypow(u8 m,u8 n)
//{
//	u32 result=1;	 
//	while(n--)result*=m;    
//	return result;
//}

