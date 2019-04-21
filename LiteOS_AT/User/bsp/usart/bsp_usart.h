#ifndef __USART1_H
#define	__USART1_H

#include "stm32f1xx.h"
#include <stdio.h>

//串口波特率
#define USART1_BAUDRATE                    115200

//引脚定义
/*******************************************************/
#define USART1_CLK_ENABLE()                __USART1_CLK_ENABLE();

#define RCC_PERIPHCLK_UARTx                RCC_PERIPHCLK_USART1
#define RCC_UARTxCLKSOURCE_SYSCLK          RCC_USART1CLKSOURCE_SYSCLK

#define USART1_RX_GPIO_PORT                GPIOA
#define USART1_RX_GPIO_CLK_ENABLE()        __GPIOA_CLK_ENABLE()
#define USART1_RX_PIN                      GPIO_PIN_10

#define USART1_TX_GPIO_PORT                GPIOA
#define USART1_TX_GPIO_CLK_ENABLE()        __GPIOA_CLK_ENABLE()
#define USART1_TX_PIN                      GPIO_PIN_9


#define USART1_IRQHandler                  USART1_IRQHandler
#define USART1_IRQ                 		    USART1_IRQn
/************************************************************/

void Usart_SendString(uint8_t *str);
void USART1_Config(void);
//int fputc(int ch, FILE *f);
extern UART_HandleTypeDef UartHandle;
#endif /* __USART1_H */
