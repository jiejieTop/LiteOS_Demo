/********************************************************************************
  * @file    bsp_led.c
  * @author  jiejie
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   底板LED驱动
  *******************************************************************************/ 
#include "led/bsp_led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_Init;

	/*开启LED相关的GPIO外设时钟*/
	__HAL_RCC_GPIOB_CLK_ENABLE();           	//开启GPIOB时钟
	__HAL_RCC_GPIOE_CLK_ENABLE();           	//开启GPIOE时钟

	/*设置引脚模式为通用推挽输出*/
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_PULLUP;          	   
	/*设置引脚速率 */   
	GPIO_Init.Speed = GPIO_SPEED_HIGH; 

	/*选择要控制的GPIO引脚*/
	GPIO_Init.Pin = LED0_GPIO_PIN;
	/*调用库函数，初始化GPIO*/
	HAL_GPIO_Init(LED0_GPIO_PORT, &GPIO_Init);

	/*选择要控制的GPIO引脚*/
	GPIO_Init.Pin = LED1_GPIO_PIN;	
	/*调用库函数，初始化GPIO*/
	HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_Init);	
}

/*********************************************END OF FILE**********************/
