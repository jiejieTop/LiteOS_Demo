#ifndef __LED_H
#define	__LED_H


#include "stm32f1xx.h"


/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
#define 	LED0_GPIO_PORT		GPIOB			              /* GPIO�˿� */
#define 	LED0_GPIO_PIN     GPIO_PIN_5			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define 	LED1_GPIO_PORT		GPIOE			              /* GPIO�˿� */
#define 	LED1_GPIO_PIN     GPIO_PIN_5			        /* ���ӵ�SCLʱ���ߵ�GPIO */


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
          
/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)			{p->BRR=i;}	 	//���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)			{p->BSRR=i;}	//����͵�ƽ
#define digitalToggle(p,i)		{p->ODR ^=i;}	//�����ת״̬


/* �������IO�ĺ� */
#define LED0_TOGGLE		 digitalToggle(LED0_GPIO_PORT,LED0_GPIO_PIN)
#define LED0_OFF		   digitalHi(LED0_GPIO_PORT,LED0_GPIO_PIN)
#define LED0_ON			   digitalLo(LED0_GPIO_PORT,LED0_GPIO_PIN)

#define LED1_TOGGLE		 digitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_OFF		   digitalHi(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_ON			   digitalLo(LED1_GPIO_PORT,LED1_GPIO_PIN)

void LED_Config(void);

#endif /* __LED_H */
