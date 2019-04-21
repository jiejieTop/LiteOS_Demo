#ifndef _BSP_BUTTON_H
#define	_BSP_BUTTON_H


#include "stm32f1xx.h"

//  引脚定义

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

//下面的方式是通过直接操作HAL库函数方式读取IO
#define     BUTTON0       	HAL_GPIO_ReadPin(BUTTON0_GPIO_PORT,BUTTON0_GPIO_PIN)  //KEY0按键PE4
#define     BUTTON1        	HAL_GPIO_ReadPin(BUTTON1_GPIO_PORT,BUTTON1_GPIO_PIN)  //KEY1按键PE3
#define     BUTTON2        	HAL_GPIO_ReadPin(BUTTON2_GPIO_PORT,BUTTON2_GPIO_PIN) 	//KEY2按键PE2
#define     BUTTON3       	HAL_GPIO_ReadPin(BUTTON3_GPIO_PORT,BUTTON3_GPIO_PIN)  //WKUP按键PA0

 /** 按键按下标置宏
	*  按键按下为高电平，设置 BUTTON_ON=1， BUTTON_OFF=0
	*  若按键按下为低电平，把宏设置成BUTTON_ON=0 ，BUTTON_OFF=1 即可
	*/
#define BUTTON_ON	0
#define BUTTON_OFF	1

void Button_Config(void);
uint8_t Button_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);


#endif /* __BUTTON_H */

