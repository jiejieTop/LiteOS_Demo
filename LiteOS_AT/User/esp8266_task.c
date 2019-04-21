/************************************************************
 * @brief   
 * @param[in]   
 * @param[out]  
 * @return    NULL
 * @author    jiejie
 * @github    https://github.com/jiejieTop
 * @date      2018-xx-xx
 * @version   v1.0
 * @note      NULL
 ************************************************************/
#include "esp8266_task.h"
#include "led/bsp_led.h"

#include "at_frame/at_api.h"

/* ���������� */
UINT32 ESP8266_Send_Task_Handle;
UINT32 ESP8266_Recv_Task_Handle;

void ESP8266_Send_Task(void* parameter)
{
  uint8_t abc[20];
  extern at_adaptor_api esp8266_interface;
  printf("\r\n=============USE_ESP8266============================\n");
  
  at_api_register(&esp8266_interface);
  
  at_api_connect("192.168.10.100","8000",0);
  
  while (1)
  {
//    at_api_sendto(0, abc, 6,"192.168.10.100",8000);
//    
    if(at_api_recv(0,abc,20)>0)
    {
      printf("%s",abc);
      memset(abc,0,20);
    }
    LOS_TaskDelay(10);
  }
}

void ESP8266_Recv_Task(void* parameter)
{
  while(1)
  {
    LOS_TaskDelay(2000);
  }
}


UINT32 Creat_ESP8266_Task(void)
{
  UINT32 uwRet = LOS_OK;				/* ����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ */
  TSK_INIT_PARAM_S task_init_param;

  task_init_param.usTaskPrio = 5;								                    /* ���ȼ�����ֵԽС�����ȼ�Խ�� */
  task_init_param.pcName = "Send_Task";						                  /* ���������ַ�����ʽ��������� */
  task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)ESP8266_Send_Task;	/* �������� */
  task_init_param.uwStackSize = 1024;						                  /* ջ��С����λΪ�֣���4���ֽ� */

  uwRet = LOS_TaskCreate(&ESP8266_Send_Task_Handle, &task_init_param);/* �������� */
  
  if(uwRet != LOS_OK )
    return uwRet;
   
  task_init_param.usTaskPrio = 6;								                    /* ���ȼ�����ֵԽС�����ȼ�Խ�� */
  task_init_param.pcName = "Recv_Task";						                  /* ���������ַ�����ʽ��������� */
  task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)ESP8266_Recv_Task;	/* �������� */
  task_init_param.uwStackSize = 512;						                  /* ջ��С����λΪ�֣���4���ֽ� */

  uwRet = LOS_TaskCreate(&ESP8266_Recv_Task_Handle, &task_init_param);/* �������� */
  
  return uwRet;
}



