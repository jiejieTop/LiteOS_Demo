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
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
void Button_Config(void)
{
	GPIO_InitTypeDef GPIO_Init;
	
	/*���������˿ڵ�ʱ��*/
    __HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOAʱ��
    __HAL_RCC_GPIOE_CLK_ENABLE();           //����GPIOEʱ��

	// ���ð���������Ϊ����
	GPIO_Init.Mode = GPIO_MODE_INPUT; 
  GPIO_Init.Speed = GPIO_SPEED_HIGH;     //����

	//ѡ�񰴼�������
	GPIO_Init.Pin = BUTTON0_GPIO_PIN; 
	GPIO_Init.Pull = BUTTON0_GPIO_PULL;
	//ʹ�ýṹ���ʼ������
	HAL_GPIO_Init(BUTTON0_GPIO_PORT, &GPIO_Init);

	//ѡ�񰴼�������
	GPIO_Init.Pin = BUTTON1_GPIO_PIN; 
	GPIO_Init.Pull = BUTTON1_GPIO_PULL;
	//ʹ�ýṹ���ʼ������
	HAL_GPIO_Init(BUTTON1_GPIO_PORT, &GPIO_Init);

	//ѡ�񰴼�������
	GPIO_Init.Pin = BUTTON2_GPIO_PIN; 
	GPIO_Init.Pull = BUTTON2_GPIO_PULL;
	//ʹ�ýṹ���ʼ������
	HAL_GPIO_Init(BUTTON2_GPIO_PORT, &GPIO_Init);

	//ѡ�񰴼�������
	GPIO_Init.Pin = BUTTON3_GPIO_PIN; 
	GPIO_Init.Pull = BUTTON3_GPIO_PULL;
	//ʹ�ýṹ���ʼ������
	HAL_GPIO_Init(BUTTON3_GPIO_PORT, &GPIO_Init);

}

 /*
 * ��������Button_Scan
 * ����  ������Ƿ��а�������
 * ����  ��GPIOx��x ������ A��B��C��D���� E
 *		     GPIO_Pin������ȡ�Ķ˿�λ 	
 * ���  ��BUTTON_OFF(û���°���)��BUTTON_ON�����°�����
 */
uint8_t Button_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*����Ƿ��а������� */
	if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == BUTTON_ON )  
	{	 
		/*�ȴ������ͷ� */
		while(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == BUTTON_ON);   
		return 	BUTTON_ON;	 
	}
	else
		return BUTTON_OFF;
}
/*********************************************END OF FILE**********************/
