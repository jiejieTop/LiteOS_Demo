/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   GPIO输出--使用固件库点亮LED灯
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 STM32 F429 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx.h"
 /* LiteOS 头文件 */
#include "los_sys.h"
#include "los_typedef.h"
#include "los_task.ph"
#include "los_queue.h"

#include "led/bsp_led.h"
#include "usart/bsp_usart.h"
#include "button/bsp_button.h"

static void SystemClock_Config(void);
static void GPIO_CLK_Init(void);

void BSP_Init(void)
{
  HAL_Init();    
  GPIO_CLK_Init();
  /* 配置系统时钟为72 MHz */ 
  SystemClock_Config();
  
	/* 初始化LED */ 
  LED_Config();
  
	/* 初始化按键 */ 
  Button_Config();

  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART1_Config();

}

/**
  * @brief  系统时钟配置 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  无
  * @retval 无
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;  	//时钟源为HSE
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;                      //时钟源为HSE
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;		    //HSE预分频
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                  //打开PLL
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;          //PLL时钟源选择HSE
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;                  //主PLL倍频因子

  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
   while(1) {}
  }
 
  /* 选择PLLCLK作为SYSCLK，并配置 HCLK, PCLK1 and PCLK2 的时钟分频因子 
	 * SYSCLK = PLLCLK     = 72M
	 * HCLK   = SYSCLK / 1 = 72M
	 * PCLK2  = SYSCLK / 2 = 36M
	 * PCLK1  = SYSCLK / 4 = 72M
	 */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;		//设置系统时钟时钟源为PLL
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;				  //AHB分频系数为1
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2; 				  //APB1分频系数为2
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1; 				  //APB2分频系数为1
  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    while(1) {}
  }
  
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/LOSCFG_BASE_CORE_TICK_PER_SECOND);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void GPIO_CLK_Init(void)
{
 /* GPIO Ports Clock Enable */
 __HAL_RCC_GPIOA_CLK_ENABLE();
 __HAL_RCC_GPIOB_CLK_ENABLE();
 __HAL_RCC_GPIOC_CLK_ENABLE();
 __HAL_RCC_GPIOD_CLK_ENABLE(); 
 __HAL_RCC_GPIOE_CLK_ENABLE();
 __HAL_RCC_GPIOF_CLK_ENABLE();
 __HAL_RCC_GPIOG_CLK_ENABLE();
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
