/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   GPIO���--ʹ�ù̼������LED��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx.h"
 /* LiteOS ͷ�ļ� */
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
  /* ����ϵͳʱ��Ϊ72 MHz */ 
  SystemClock_Config();
  
	/* ��ʼ��LED */ 
  LED_Config();
  
	/* ��ʼ������ */ 
  Button_Config();

  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART1_Config();

}

/**
  * @brief  ϵͳʱ������ 
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
  * @param  ��
  * @retval ��
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;  	//ʱ��ԴΪHSE
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;                      //ʱ��ԴΪHSE
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;		    //HSEԤ��Ƶ
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                  //��PLL
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;          //PLLʱ��Դѡ��HSE
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;                  //��PLL��Ƶ����

  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
   while(1) {}
  }
 
  /* ѡ��PLLCLK��ΪSYSCLK�������� HCLK, PCLK1 and PCLK2 ��ʱ�ӷ�Ƶ���� 
	 * SYSCLK = PLLCLK     = 72M
	 * HCLK   = SYSCLK / 1 = 72M
	 * PCLK2  = SYSCLK / 2 = 36M
	 * PCLK1  = SYSCLK / 4 = 72M
	 */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;		//����ϵͳʱ��ʱ��ԴΪPLL
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;				  //AHB��Ƶϵ��Ϊ1
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2; 				  //APB1��Ƶϵ��Ϊ2
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1; 				  //APB2��Ƶϵ��Ϊ1
  
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
