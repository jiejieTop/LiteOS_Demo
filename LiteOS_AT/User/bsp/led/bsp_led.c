/********************************************************************************
  * @file    bsp_led.c
  * @author  jiejie
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   �װ�LED����
  *******************************************************************************/ 
#include "led/bsp_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_Init;

	/*����LED��ص�GPIO����ʱ��*/
	__HAL_RCC_GPIOB_CLK_ENABLE();           	//����GPIOBʱ��
	__HAL_RCC_GPIOE_CLK_ENABLE();           	//����GPIOEʱ��

	/*��������ģʽΪͨ���������*/
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_PULLUP;          	   
	/*������������ */   
	GPIO_Init.Speed = GPIO_SPEED_HIGH; 

	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_Init.Pin = LED0_GPIO_PIN;
	/*���ÿ⺯������ʼ��GPIO*/
	HAL_GPIO_Init(LED0_GPIO_PORT, &GPIO_Init);

	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_Init.Pin = LED1_GPIO_PIN;	
	/*���ÿ⺯������ʼ��GPIO*/
	HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_Init);	
}

/*********************************************END OF FILE**********************/
