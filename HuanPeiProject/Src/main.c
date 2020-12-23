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
#include "delay.h"
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
int Frequency = 0 ; //Ƶ��
int time = 0 ; //����ʱ�䣬һ����λ��0.1��
int Move = 90 ; //0~360��
int mode = 5 ; // ģʽ0��ʾ���������ģʽ1��ʾ�������״̬��ģʽ2��ʾ����״̬

int Mark = 0 ; //0Ϊ��һ�ν�������жϣ�Ȼ���1����ȶ����ٵ�һ�����,֮���ά��һ���ӵĲ���
								//0��ʾ��Ҫ����ˢ��ģʽ��1��ʾ��Ҫ�������ģʽ��2��ʾ��Ҫ�������ģʽ,3��ʾ���������һ�㲻��ʲô
#define ONESecond 10
#define FOURSecond 1000

#define FIRST 10
#define SECOND 20
#define TFIRD 920
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){ //�ⲿ�жϻص����������벶���
    if(GPIO_Pin == MyEXTI_Pin){
//			if(mode == 5){
//					mode = 1 ;
//					HAL_TIM_Base_Start_IT(&htim3);
//			}
//			if(mode == 1 && Frequency <= 10000)
//          Frequency++ ;
//			}else if(mode == 0){
//					HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_1);
//				//(int)(((double)Move/360)*(1000000.0/Frequency));  //��λ��us΢��,���������
//          MX_TIM2_Init(Frequency);
//					mydelay_us((int)(((double)Move/360)*(1000000.0/Frequency)));
//          HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_1);
//          Frequency = 0 ;
//          mode = 2 ;
//			}
			
//			if(Mark == 0){
//				HAL_TIM_Base_Start_IT(&htim3);
//				Mark = 1 ;
//			}else if(Mark =
			
//			switch(Mark){
//				case 0 :
//					time = 0 ;
//					Frequency = 0;
//					HAL_TIM_Base_Start_IT(&htim3);
//					Mark = 3 ;
//					break ;
//				case 1:
//					Frequency++ ;
//					break ;
//				case 2:
//					Mark = 3 ;
//					MX_TIM2_Init(Frequency);
//					delay_us((int)(((double)Move/360)*(1000000.0/Frequency)) - 2);
//					HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
//					//����Ƶ�ʵ�ֵ�������ֵ������
//					break ;
//			}
			
    }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){ //��ʱ�����жϺ�����������ʱ�ģ�1s������3sˢ��
  if (htim->Instance == TIM3)
  {
//    time++ ;
//    if(time >= FOURSecond){
//      time = 0 ; 
//			mode = 1 ;
//    }else if(time == ONESecond){
//			mode = 0 ;
//		}
		
//		time++ ;
//		switch(time){
//			case FIRST:
//				Mark = 1 ;
//				break ;
//			case SECOND:
//				Mark = 2 ;
//				break ;
//			case TFIRD:
//				Mark = 0 ;
//				HAL_TIM_Base_Stop_IT(&htim3);
//				HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
//				break ;	
//		}
	}
  
    
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  MX_TIM3_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
					MX_TIM2_Init(1000);
				//	delay_us((int)(((double)Move/360)*(1000000.0/Frequency)) - 2);
					HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
  while (1)
  {
//		if(mode == 0){
//			if(ih == 1){
//				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
//			}else ih = 1 ;
//			//(int)(((double)Move/360)*(1000000.0/Frequency));  //��λ��us΢��,���������
//				MX_TIM2_Init(Frequency);
//		//		mydelay_us((int)(((double)Move/360)*(1000000.0/Frequency)) - 2);
//			//delay_us((int)(((double)Move/360)*(1000000.0/Frequency)) - 2);
//			
//				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
//				Frequency = 0 ;
//				mode = 2 ;
//			}
//		switch(Mark){
//			case 0:
//				break ;
//			case 1:
//				break ;
//			case 2:
//				break ;
//		}
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
