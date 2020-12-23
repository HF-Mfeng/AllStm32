#include"IIC.h"


void IIC_Init(void)
{
	GPIO_InitTypeDef gpio;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	gpio.GPIO_Pin=GPIO_Pin_11 | GPIO_Pin_12; //11 & 12 for SCL&SDA
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
    gpio.GPIO_Mode=GPIO_Mode_Out_PP;         //tuiwan
	GPIO_Init(GPIOA, &gpio);
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

void IIC_Start(void)
{
	SDA_OUT();     
    
    SDA_H;
    SCL_H;

    delay_us(2);

    SDA_L;
    delay_us(2);
    
    SCL_L;
	delay_us(2);

}
void IIC_Stop(void)
{
    //SDA_OUT();
    
    SCL_H;

    SDA_L;
    
	delay_us(2);
    
    //SCL_H;
    
    SDA_H;
    delay_us(2);                                   
}
u8 IIC_Wait_Ack(void)     
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
 

void IIC_Ack(void)
{
   
    SCL_L;
    
    SDA_OUT();
    
    SDA_L;
    
    delay_us(2);
    
    SCL_H;
    
    delay_us(2);
    
    SCL_L;

}
 

void IIC_NAck(void)
{
    SCL_L;
    SDA_OUT();
    
    SDA_H;
    delay_us(2);
    
    SCL_H;
    delay_us(2);
    
    SCL_L;
}
 
void IIC_Send_Byte(u8 data)
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
 
u8 IIC_Read_Byte(void)
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

