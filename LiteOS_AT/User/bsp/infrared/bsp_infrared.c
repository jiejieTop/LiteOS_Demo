/**
********************************************************
*
* @file      Hal_infrared.c
* @author    Gizwtis
* @version   V03010100
* @date      2016-07-05
*
* @brief     机智云.只为智能硬件而生
*            Gizwits Smart Cloud  for Smart Products
*            链接|增值ֵ|开放|中立|安全|自有|自由|生态
*            www.gizwits.com
*
*********************************************************/

#include <stm32f10x.h>
#include "infrared/bsp_infrared.h"

void irInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(Infrared_GPIO_CLK,ENABLE);//使能PORTA,PORTE时钟
    GPIO_InitStructure.GPIO_Pin  = Infrared_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init(Infrared_GPIO_PORT, &GPIO_InitStructure);
}

bool irHandle(void)
{
    if(GPIO_ReadInputDataBit(Infrared_GPIO_PORT, Infrared_GPIO_PIN))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
