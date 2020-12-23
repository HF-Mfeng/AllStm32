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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#define DataLength 14
uint8_t Receive[DataLength];
uint32_t GameData[4][4] = {0};

int max = 2  ;
//是否能继续游戏，比如说，不能继续，能继续 1--能，2--不能




//上 下 左 右
// 0  1  2  3

void Do_Move(void);



int fputc(int ch, FILE *f){
	HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,100);
	return 0;
}
void END_HMI(){
	uint8_t t[3]= { 0xff ,0xff ,0xff } ;
	HAL_UART_Transmit(&huart1,(uint8_t *)&t,3,1000);
}




void Draw_all_data(){
	for(int i = 0 ; i < 16 ; i++){
		if(GameData[i/4][i%4] != 0){
			printf("t%d.txt=\"%d\"",i,GameData[i/4][i%4]);
			END_HMI();
		}else{
			printf("t%d.txt=\"\"",i);
			END_HMI();
		}
	}
	printf("t19.txt=\"%d\"",max);
	END_HMI();
}


void MF_Move(){
	switch(Receive[1]){
		case 0xaa:       //up 上
			for(int i = 0 ; i < 4 ; i++ ){
				for(int j = 0  ; j < 3 ; j++ ){
					if(GameData[j][i] != 0){
						for(int k = j + 1 ; k < 4 ; k++ ){
							if(GameData[k][i] != GameData[j][i] && GameData[k][i] != 0){
								j = k - 1  ;
								break;
							}	
							if( GameData[k][i] == GameData[j][i] ){
								GameData[j][i] += GameData[k][i] ;
								GameData[k][i] = 0 ;
								if(GameData[j][i] > max)
									max = GameData[j][i] ;
								j = k - 1 ;
								break ;
							}		
						}
					}
				}
			}
		break ;
		case 0xbb:      //down
			for(int i = 0 ; i < 4 ; i++ ){
				for(int j = 3  ; j > 0 ; j-- ){
					if(GameData[j][i] != 0){
						for(int k = j - 1 ; k >= 0 ; k-- ){
							if(GameData[k][i] != GameData[j][i] && GameData[k][i] != 0){
								j = k + 1 ;
								break;
							}	
							if( GameData[k][i] == GameData[j][i] ){
								GameData[j][i] += GameData[k][i] ;
								GameData[k][i] = 0 ;
								if(GameData[j][i] > max)
									max = GameData[j][i] ;
								j = k + 1 ;
								break ;
							}		
						}
					}
				}
			}
		break ;
		case 0xcc :      //left
			for(int i = 0 ; i < 4 ; i++ ){
					for(int j = 0  ; j < 3 ; j++ ){
						if(GameData[i][j] != 0){
							for(int k = j + 1 ; k < 4 ; k++ ){
								if(GameData[i][k] != GameData[i][j] && GameData[i][k] != 0){
									j = k - 1 ;
									break;
								}	
								if( GameData[i][k] == GameData[i][j] ){
									GameData[i][j] += GameData[i][k] ;
									GameData[i][k] = 0 ;
									if(GameData[i][j] > max)
										max = GameData[i][j] ;
									j = k - 1 ;
									break ;
								}		
							}
						}
					}
				}
		break ;
		case 0xdd :        //right
		for(int i = 0 ; i < 4 ; i++ ){
					for(int j = 3  ; j > 0 ; j-- ){
						if(GameData[i][j] != 0){
							for(int k = j - 1 ; k >= 0 ; k-- ){
								if(GameData[i][k] != GameData[i][j] && GameData[i][k] != 0){
									j = k + 1 ;
									break;
								}	
								if( GameData[i][k] == GameData[i][j] ){
									GameData[i][j] += GameData[i][k] ;
									GameData[i][k] = 0 ;
									if(GameData[i][j] > max)
										max = GameData[i][j] ;
									j = k + 1 ;
									break ;
								}		
							}
						}
					}
				}
		break ;
	}
}

void Do_Move(){

	MF_Move();

	switch(Receive[1]){
		case 0xcc:         //left
			for(int i = 0 ; i < 4 ; i++ ){
				for( int j = 0 ; j < 3 ; j++ ){
					if(GameData[i][j] == 0 ){
						for(int k = j + 1 ; k < 4 ; k++ ){
							if(GameData[i][k] != 0){
								GameData[i][j] = GameData[i][k];
								GameData[i][k] = 0 ;
								break ;
							}
						}
					}
				}
			}
			break ;
		case 0xdd:      //right
			for(int i = 0 ; i < 4 ; i++ ){
				for( int j = 3 ; j > 0 ; j-- ){
					if(GameData[i][j] == 0 ){
						for(int k = j - 1 ; k >= 0 ; k-- ){
							if(GameData[i][k] != 0){
								GameData[i][j] = GameData[i][k];
								GameData[i][k] = 0 ;
								break ;
							}
						}
					}
				}
			}
			break ;
		case 0xaa:       //up
			for(int i = 0 ; i < 4 ; i++ ){
				for( int j = 0 ; j < 3 ; j++ ){
					if(GameData[j][i] == 0 ){
						for(int k = j + 1 ; k < 4 ; k++ ){
							if(GameData[k][i] != 0){
								GameData[j][i] = GameData[k][i];
								GameData[k][i] = 0 ;
								break ;
							}
						}
					}
				}
			}
			break ;
		case 0xbb:         //down
			for(int i = 0 ; i < 4 ; i++ ){
				for( int j = 3 ; j > 0 ; j-- ){
					if(GameData[j][i] == 0 ){
						for(int k = j - 1 ; k >= 0 ; k-- ){
							if(GameData[k][i] != 0){
								GameData[j][i] = GameData[k][i];
								GameData[k][i] = 0 ;
								break ;
							}
						}
					}
				}
			}
			break ;
	}
}


//模式A,按键
void Mode_A(){
	Do_Move();
	
//生成下个随机数
	uint8_t row = Receive[2] ;
	uint8_t col = Receive[6] ;
	uint8_t val ;
	//限制初始化的值 2：4的比例
	if(Receive[10] > 4 )
		val = 2 ;
	else
		val = 4 ;
	if(GameData[row%4][col%4] == 0){
		GameData[row%4][col%4] = val ;
		printf("t%d.pic=9",4*(row%4)+(col%4));
		END_HMI();
	}else{
		for(int i = 0 ; i < 4 ; i++){
			for(int j = 0 ; j < 4 ; j++){
				if(GameData[i][j] == 0){
					GameData[i][j] = val ;
					printf("t%d.pic=9",4*i+j);
					END_HMI();
					return ;
				}
			}
		}
		printf("g0.txt=\"Game Over!!!\"");
		END_HMI();
	}
}

//模式B,初始化
void Mode_B(){
	uint8_t row , col;
	//先给它赋值为0，方便按重新开始按钮
	for(int i = 0 ; i < 4 ; i++ )
		for(int j = 0 ; j < 4 ; j++ )
				GameData[i][j] = 0 ;
	row = Receive[2]  ;
	col = Receive[6]  ;
	if(row == col){
		col = (row+1)%16 ;
	}
	//初始化 MCU 的数据
	GameData[row/4][row%4] = 2 ;
	GameData[col/4][col%4] = 2 ; 
	max = 2 ;   
}


//解析数据并执行
void DoThings(){
	switch(Receive[0]){
		case 0xaa:
			Mode_A();
			break ;
		case 0xbb:
			Mode_B();
			break ;
	}
	Draw_all_data();
	//重置接收缓冲区的数据
	for(int i = 0 ; i < DataLength ; i++ ){
		Receive[i] = 0 ;
	}
}

//中断回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART1){
		DoThings();	
		HAL_UART_Receive_IT(&huart1,Receive,DataLength);
	}
}
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_UART_Receive_IT(&huart1,Receive,DataLength);
  while (1)
  {
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
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
