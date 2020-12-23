/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MF_PWM.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t receive[9] = {0} ;
uint32_t frequency = 1000 ;
uint32_t duty = 50;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void mf_end_uartToHMI(){
	uint8_t end[3] = {0xff,0xff,0xff};
	HAL_UART_Transmit(&huart1,end,3,1000);
}
void MF_HMI_DU(){
	int i;
	uint32_t Dudu = 0;

	Dudu = Dudu | receive[3] ;
	for( i = 2 ; i >= 0 ; i-- ){
		Dudu = Dudu << 8 ;
		Dudu = Dudu | receive[i] ;
	}
	//	printf("Dudu=%d\r\n",Dudu);
		if( Dudu > 180){
			MF_setPWM_du(90);
			printf("t0.txt=\"90\"");
			mf_end_uartToHMI();
		}else{
			MF_setPWM_du(Dudu);
			printf("t0.txt=\"%d\"",Dudu);
			mf_end_uartToHMI();
		}
		HAL_UART_Receive_IT(&huart1,receive,9);
}
void MF_HMI_F(){
	int i;
	frequency = 0;
			duty = 0 ;
			frequency = frequency | receive[3] ;
			duty = duty | receive[7];
			for( i = 2 ; i >= 0 ; i-- ){
				frequency = frequency << 8 ;
				frequency = frequency | receive[i] ;
				duty = duty << 8 ;
				duty = duty | receive[i+4];
			}
			//dc 05 00 00 3c 00 00 00
			//printf("f=%d,duty=%d\r\n",frequency,duty);
			if(frequency > MF_Frequency_Max || frequency < MF_Frequency_Min || duty <=4 || duty >= 96 ){
				frequency = 1000;
				duty = 50 ;
				printf("vis t12,1");
				mf_end_uartToHMI();
			}
				MF_setPWM_Frequency_Duty(frequency,duty);	
				printf("t4.txt=\"%d\"",frequency);
				mf_end_uartToHMI();
				printf("t5.txt=\"%d\"",duty);
				mf_end_uartToHMI();
				printf("t6.txt=\"%.2f\"",1000.0/frequency);
				mf_end_uartToHMI();
				printf("t7.txt=\"%.2f\"",10.0*duty/frequency);
				mf_end_uartToHMI();
			for(i = 0 ; i < 9 ; i++ ){
			 receive[i] = 0x00 ;
			}
			HAL_UART_Receive_IT(&huart1,receive,9);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
		if(huart->Instance == USART1){
			
			switch(receive[8]){
				case 0xaa:
					MF_HMI_F(); //设置频率的
					break;
				case 0xbb:
					MF_HMI_DU();
					//设置角度的
					break;
			}
			
			
		}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
int maindu = 0 ;
	int i = 0 ;
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
#ifndef ZDY
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
#else
  MX_GPIO_Init();
  MX_USART1_UART_Init();
#endif	
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
//MF_setPWM_Frequency_Duty(frequency,duty);
     MF_setPWM_du(120);
		 HAL_Delay(1000);
//	MX_TIM1_Init(320-1,100-1,50);	
//		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
HAL_UART_Receive_IT(&huart1,receive,9);
  while (1)
  {
//		for( i = 0 ; i <= 180 ; i+=18){
//			MF_setPWM_du(i);
//			HAL_Delay(200);
//		}
//		for( i = 180 ; i >= 0 ; i-=18){
//			MF_setPWM_du(i);
//			HAL_Delay(200);
//		}
//		
//		MF_setPWM_du(0);
//		HAL_Delay(500);
//		MF_setPWM_du(180);
//		HAL_Delay(500);
		
//		HAL_Delay(10000);
//		MF_setPWM_Tms_Duty(0.1,6);
//		HAL_Delay(10000);
//		MF_setPWM_Frequency_Duty(500,20);
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
