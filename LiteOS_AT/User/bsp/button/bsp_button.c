/************************************************************
 * @brief     bsp_button.c
 * @param[in]   
 * @param[out]  
 * @return    NULL
 * @author    jiejie
 * @github    https://github.com/jiejieTop
 * @date      2018-xx-xx
 * @version   v1.0
 * @note      NULL
 ************************************************************/
#include "button/bsp_button.h"  


/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void Button_Config(void)
{
	GPIO_InitTypeDef GPIO_Init;
	
	/*开启按键端口的时钟*/
    __HAL_RCC_GPIOA_CLK_ENABLE();           //开启GPIOA时钟
    __HAL_RCC_GPIOE_CLK_ENABLE();           //开启GPIOE时钟

	// 设置按键的引脚为输入
	GPIO_Init.Mode = GPIO_MODE_INPUT; 
  GPIO_Init.Speed = GPIO_SPEED_HIGH;     //高速

	//选择按键的引脚
	GPIO_Init.Pin = BUTTON0_GPIO_PIN; 
	GPIO_Init.Pull = BUTTON0_GPIO_PULL;
	//使用结构体初始化按键
	HAL_GPIO_Init(BUTTON0_GPIO_PORT, &GPIO_Init);

	//选择按键的引脚
	GPIO_Init.Pin = BUTTON1_GPIO_PIN; 
	GPIO_Init.Pull = BUTTON1_GPIO_PULL;
	//使用结构体初始化按键
	HAL_GPIO_Init(BUTTON1_GPIO_PORT, &GPIO_Init);

	//选择按键的引脚
	GPIO_Init.Pin = BUTTON2_GPIO_PIN; 
	GPIO_Init.Pull = BUTTON2_GPIO_PULL;
	//使用结构体初始化按键
	HAL_GPIO_Init(BUTTON2_GPIO_PORT, &GPIO_Init);

	//选择按键的引脚
	GPIO_Init.Pin = BUTTON3_GPIO_PIN; 
	GPIO_Init.Pull = BUTTON3_GPIO_PULL;
	//使用结构体初始化按键
	HAL_GPIO_Init(BUTTON3_GPIO_PORT, &GPIO_Init);

}

 /*
 * 函数名：Button_Scan
 * 描述  ：检测是否有按键按下
 * 输入  ：GPIOx：x 可以是 A，B，C，D或者 E
 *		     GPIO_Pin：待读取的端口位 	
 * 输出  ：BUTTON_OFF(没按下按键)、BUTTON_ON（按下按键）
 */
uint8_t Button_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == BUTTON_ON )  
	{	 
		/*等待按键释放 */
		while(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == BUTTON_ON);   
		return 	BUTTON_ON;	 
	}
	else
		return BUTTON_OFF;
}
/*********************************************END OF FILE**********************/
