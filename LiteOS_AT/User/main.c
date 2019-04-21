/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   ����һ��[Ұ��]-STM32F103-�Ե�-LiteOS������Ϣʵ�飡
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� �Ե� ������ STM32 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
 /* LiteOS ͷ�ļ� */
#include "los_sys.h"
#include "los_typedef.h"
#include "los_task.ph"
#include "los_queue.h"
/* �弶����ͷ�ļ� */
#include "stm32f1xx.h"
#include "led/bsp_led.h"
#include "button/bsp_button.h"  

///* ����ͷ�ļ� */
//#include "esp8266_task.h"
#include "button_task.h"

/********************************** ������ *************************************/
/* 
 * ��������һ��ָ�룬����ָ��һ�����񣬵����񴴽���֮�����;�����һ��������
 * �Ժ�����Ҫ��������������Ҫͨ�������������������������������Լ�����ô
 * ����������ΪNULL��
 */

/* ���������� */
UINT32 Receive_Task_Handle;
UINT32 Send_Task_Handle;

/********************************** �ں˶����� *********************************/
/*
 * �ź�������Ϣ���У��¼���־�飬�����ʱ����Щ�������ں˵Ķ���Ҫ��ʹ����Щ�ں�
 * ���󣬱����ȴ����������ɹ�֮��᷵��һ����Ӧ�ľ����ʵ���Ͼ���һ��ָ�룬������
 * �ǾͿ���ͨ��������������Щ�ں˶���
 *
 * �ں˶���˵���˾���һ��ȫ�ֵ����ݽṹ��ͨ����Щ���ݽṹ���ǿ���ʵ��������ͨ�ţ�
 * �������¼�ͬ���ȸ��ֹ��ܡ�������Щ���ܵ�ʵ��������ͨ��������Щ�ں˶���ĺ���
 * ����ɵ�
 * 
 */
 /* ������Ϣ���еľ�� */
UINT32 Test_Queue_Handle;
/* ������Ϣ���г��� */
#define  TEST_QUEUE_LEN  4

/******************************* ȫ�ֱ������� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */


/* �������� */
static UINT32 Creat_Receive_Task(void);
static UINT32 Creat_Send_Task(void);

static void AppTaskCreate(void);

static void Receive_Task(void);
static void Send_Task(void);
extern void BSP_Init(void);



/***************************************************************************
  * @brief  ������
  * @param  ��
  * @retval ��
  * @note   ��һ����������Ӳ����ʼ�� 
			�ڶ���������APPӦ������
			������������LiteOS����ʼ��������ȣ�����ʧ�������������Ϣ
  **************************************************************************/
int main(void)
{	
	UINT32 uwRet = LOS_OK;  //����һ�����񴴽��ķ���ֵ��Ĭ��Ϊ�����ɹ�
	/* �弶��ʼ�������еĸ�������Ӳ����صĳ�ʼ�������Է�������������� */
  BSP_Init();
  
	/* ����һ���ַ��� */
	printf("����һ��[Ұ��]-STM32F103-�Ե�-LiteOS������Ϣʵ�飡\n");
  printf("����K1����K2���Ͷ�����Ϣ\n");
  printf("Receive_Task������յ���Ϣ�ڴ��ڻ���\n\n");
	/* LiteOS ���ĳ�ʼ�� */
	uwRet = LOS_KernelInit();
  if (uwRet != LOS_OK)
   {
	printf("LiteOS ���ĳ�ʼ��ʧ�ܣ�\n");
	return LOS_NOK;
   }
 
	 /* ����APPӦ���������е�Ӧ�����񶼿��Է�������������� */
   AppTaskCreate();
    
   /* ����LiteOS������� */
   LOS_Start();
}


/*********************************************************************************
  * @ ������  �� AppTaskCreate
  * @ ����˵���� ���񴴽���Ϊ�˷���������е����񴴽����������Է��������������
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  ********************************************************************************/
static void AppTaskCreate(void)
{
	UINT32 uwRet = LOS_OK;/* ����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ */
  
//	/* ����һ�����Զ���*/
//	uwRet = LOS_QueueCreate("Test_Queue",			/* ���е����� */
//							TEST_QUEUE_LEN,			  /* ���еĳ��� */
//							&Test_Queue_Handle,		/* ���е�ID(���) */
//							0,						        /* ����ģʽ���ٷ���ʱδʹ�� */
//							sizeof(UINT32));      /* �ڵ��С */
//	if (uwRet != LOS_OK)
//  {
//    printf("Test_Queue���д���ʧ�ܣ�\n");
//  }
    
//	uwRet = Creat_Receive_Task();
//  if (uwRet != LOS_OK)
//    printf("Receive_Task���񴴽�ʧ�ܣ�\n");
//  

	uwRet = Creat_Send_Task();
  if (uwRet != LOS_OK)
    printf("Send_Task���񴴽�ʧ�ܣ�\n");
  
  uwRet = Creat_Button_Task();
  if (uwRet != LOS_OK)
    printf("Button_Task���񴴽�ʧ�ܣ�\n");
  
//  uwRet = Creat_ESP8266_Task();
//  if (uwRet != LOS_OK)
//    printf("ESP8266_Task���񴴽�ʧ�ܣ�\n");
//  
  printf("ok\n");
}
/*********************************************************************************
  * @ ������  �� Receive_Task
  * @ ����˵���� Receive_Task����ʵ��
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************************/
static void Receive_Task(void)
{  
	UINT32 uwRet = LOS_OK;
	UINT32 *r_queue = NULL;
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		/* ���ж�ȡ�����գ����ȴ�ʱ��Ϊһֱ�ȴ� */
		uwRet = LOS_QueueRead(Test_Queue_Handle,	/* ��ȡ�����գ����е�ID(���) */
								&r_queue,			/* ��ȡ�����գ������ݱ���λ�� */
								sizeof(r_queue),		/* ��ȡ�����գ������ݵĳ��� */
								LOS_WAIT_FOREVER); 	/* �ȴ�ʱ�䣺һֱ�� */
		if(LOS_OK == uwRet)
		{
			printf("���ν��յ��������ǣ�%d\n",*r_queue);
		}
		else
		{
			printf("���ݽ��ճ���,�������: %x\n",uwRet);
		}
    LOS_TaskDelay(20);  	  
	}
}
/*********************************************************************************
  * @ ������  �� Send_Task
  * @ ����˵���� �ȴ��¼�����
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************************/
static void Send_Task(void)
{
//	UINT32 uwRet = LOS_OK;				/* ����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ */
//	UINT32 send_data1 = 1;
//	UINT32 send_data2 = 2;
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
    LED0_TOGGLE;
		/* 20msɨ��һ�� */
		LOS_TaskDelay(2000);  
    LED1_TOGGLE;
	}
}

/*********************************************************************************
  * @ ������  �� Creat_Receive_Task
  * @ ����˵���� ����Receive_Task����
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************************/
static UINT32 Creat_Receive_Task()
{
    UINT32 uwRet = LOS_OK;				/* ����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ */
    TSK_INIT_PARAM_S task_init_param;

    task_init_param.usTaskPrio = 5;								/* ���ȼ�����ֵԽС�����ȼ�Խ�� */
    task_init_param.pcName = "Receive_Task";						/* ���������ַ�����ʽ��������� */
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Receive_Task;	/* �������� */
    task_init_param.uwStackSize = 512;						/* ջ��С����λΪ�֣���4���ֽ� */

    uwRet = LOS_TaskCreate(&Receive_Task_Handle, &task_init_param);/* �������� */
    return uwRet;
}
/*********************************************************************************
  * @ ������  �� Creat_Send_Task
  * @ ����˵���� ����Send_Task����
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************************/
static UINT32 Creat_Send_Task()
{
    UINT32 uwRet = LOS_OK;				/* ����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ */
    TSK_INIT_PARAM_S task_init_param;

    task_init_param.usTaskPrio = 4;								/* ���ȼ�����ֵԽС�����ȼ�Խ�� */
    task_init_param.pcName = "Send_Task";						/* ���������ַ�����ʽ��������� */
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Send_Task;	/* �������� */
    task_init_param.uwStackSize = 512;						/* ջ��С����λΪ�֣���4���ֽ� */

    uwRet = LOS_TaskCreate(&Send_Task_Handle, &task_init_param);/* �������� */

    return uwRet;
}

/*********************************************END OF FILE**********************/

