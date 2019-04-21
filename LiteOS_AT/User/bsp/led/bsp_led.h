#ifndef __LED_H
#define	__LED_H


#include "stm32f1xx.h"


/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
#define 	LED0_GPIO_PORT		GPIOB			              /* GPIO端口 */
#define 	LED0_GPIO_PIN     GPIO_PIN_5			        /* 连接到SCL时钟线的GPIO */

#define 	LED1_GPIO_PORT		GPIOE			              /* GPIO端口 */
#define 	LED1_GPIO_PIN     GPIO_PIN_5			        /* 连接到SCL时钟线的GPIO */


/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  1
#define OFF 0

#define LED0(a)	if (a)	\
					GPIO_SetBits(LED0_GPIO_PORT,LED0_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED0_GPIO_PORT,LED0_GPIO_PIN)

#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN)
          
/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			{p->BRR=i;}	 	//输出为高电平		
#define digitalLo(p,i)			{p->BSRR=i;}	//输出低电平
#define digitalToggle(p,i)		{p->ODR ^=i;}	//输出反转状态


/* 定义控制IO的宏 */
#define LED0_TOGGLE		 digitalToggle(LED0_GPIO_PORT,LED0_GPIO_PIN)
#define LED0_OFF		   digitalHi(LED0_GPIO_PORT,LED0_GPIO_PIN)
#define LED0_ON			   digitalLo(LED0_GPIO_PORT,LED0_GPIO_PIN)

#define LED1_TOGGLE		 digitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_OFF		   digitalHi(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_ON			   digitalLo(LED1_GPIO_PORT,LED1_GPIO_PIN)

void LED_Config(void);

#endif /* __LED_H */
