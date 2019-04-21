#ifndef _BSP_BUTTON_H
#define	_BSP_BUTTON_H


#include "stm32f1xx.h"

//  ���Ŷ���

#define     BUTTON0_GPIO_PORT		GPIOE		   
#define     BUTTON0_GPIO_PIN		GPIO_PIN_4
#define     BUTTON0_GPIO_PULL		GPIO_PULLUP


#define     BUTTON1_GPIO_PORT		GPIOE			   
#define     BUTTON1_GPIO_PIN		GPIO_PIN_3
#define     BUTTON1_GPIO_PULL		GPIO_PULLUP


#define     BUTTON2_GPIO_PORT		GPIOE		   
#define     BUTTON2_GPIO_PIN		GPIO_PIN_2
#define     BUTTON2_GPIO_PULL		GPIO_PULLUP


#define     BUTTON3_GPIO_PORT		GPIOA		   
#define     BUTTON3_GPIO_PIN		GPIO_PIN_0
#define     BUTTON3_GPIO_PULL		GPIO_PULLDOWN

//����ķ�ʽ��ͨ��ֱ�Ӳ���HAL�⺯����ʽ��ȡIO
#define     BUTTON0       	HAL_GPIO_ReadPin(BUTTON0_GPIO_PORT,BUTTON0_GPIO_PIN)  //KEY0����PE4
#define     BUTTON1        	HAL_GPIO_ReadPin(BUTTON1_GPIO_PORT,BUTTON1_GPIO_PIN)  //KEY1����PE3
#define     BUTTON2        	HAL_GPIO_ReadPin(BUTTON2_GPIO_PORT,BUTTON2_GPIO_PIN) 	//KEY2����PE2
#define     BUTTON3       	HAL_GPIO_ReadPin(BUTTON3_GPIO_PORT,BUTTON3_GPIO_PIN)  //WKUP����PA0

 /** �������±��ú�
	*  ��������Ϊ�ߵ�ƽ������ BUTTON_ON=1�� BUTTON_OFF=0
	*  ����������Ϊ�͵�ƽ���Ѻ����ó�BUTTON_ON=0 ��BUTTON_OFF=1 ����
	*/
#define BUTTON_ON	0
#define BUTTON_OFF	1

void Button_Config(void);
uint8_t Button_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);


#endif /* __BUTTON_H */

