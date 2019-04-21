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
#include "button_task.h"

/* �����߳̿��ƿ� */

UINT32 Button_Task_Handle;

/********************************************************************
													   ��������
 *******************************************************************/ 
Button_t Button0;
Button_t Button1;
Button_t Button2; 
Button_t Button3; 

/********************************************************************
													ʵ�ֶ�ȡ������ƽ
 *******************************************************************/ 
static uint8_t Read_Button0_Level(void)
{
  return BUTTON0;
}

static uint8_t Read_Button1_Level(void)
{
  return BUTTON1;
}

static uint8_t Read_Button2_Level(void)
{
  return BUTTON2;
}

static uint8_t Read_Button3_Level(void)
{
  return BUTTON3;
}

/********************************************************************
													ʵ�ֻص�����
 *******************************************************************/ 
void Btn0_Dowm_CallBack(void *btn)
{
  PRINTF_INFO("Button0 ����!");
}
void Btn0_Double_CallBack(void *btn)
{
  PRINTF_INFO("Button0 ˫��!");
}
void Btn0_Long_CallBack(void *btn)
{
  PRINTF_INFO("Button0 ����!");
}
void Btn0_Continuos_CallBack(void *btn)
{
  PRINTF_INFO("Button0 ����!");
}
void Btn0_ContinuosFree_CallBack(void *btn)
{
  PRINTF_INFO("Button0 �����ͷ�!");
}

/********************************************************************
													button1
 *******************************************************************/ 
void Btn1_Dowm_CallBack(void *btn)
{
  PRINTF_INFO("Button1 ����!");
}
void Btn1_Double_CallBack(void *btn)
{
  PRINTF_INFO("Button1 ˫��!");
}
void Btn1_Long_CallBack(void *btn)
{
  PRINTF_INFO("Button1 ����!");
}
void Btn1_Continuos_CallBack(void *btn)
{
  PRINTF_INFO("Button1 ����!");
}
void Btn1_ContinuosFree_CallBack(void *btn)
{
  PRINTF_INFO("Button1 �����ͷ�!");
}

/********************************************************************
													button2
 *******************************************************************/ 
void Btn2_Dowm_CallBack(void *btn)
{
  PRINTF_INFO("Button2 ����!");
}
void Btn2_Double_CallBack(void *btn)
{
  PRINTF_INFO("Button2 ˫��!");
}
void Btn2_Long_CallBack(void *btn)
{
  PRINTF_INFO("Button2 ����!");
}
void Btn2_Continuos_CallBack(void *btn)
{
  PRINTF_INFO("Button2 ����!");
}
void Btn2_ContinuosFree_CallBack(void *btn)
{
  PRINTF_INFO("Button2 �����ͷ�!");
}

/********************************************************************
													button3
 *******************************************************************/ 
void Btn3_Dowm_CallBack(void *btn)
{
  PRINTF_INFO("Button3 ����!");
}
void Btn3_Double_CallBack(void *btn)
{
  PRINTF_INFO("Button3 ˫��!");
}

void Btn3_Long_CallBack(void *btn)
{
  PRINTF_INFO("Button3 ����!");
}

void Btn3_Continuos_CallBack(void *btn)
{
  PRINTF_INFO("Button3 ����!");
}
void Btn3_ContinuosFree_CallBack(void *btn)
{
  PRINTF_INFO("Button3 �����ͷ�!");
}

/********************************************************************
													ע�ᰴ��
 *******************************************************************/ 
static void Register_Button(void)
{
  Button_Create("Button0",
                &Button0, 
                Read_Button0_Level, 
                BUTTON_ON);
  Button_Attach(&Button0,BUTTON_DOWM,Btn0_Dowm_CallBack);                       //����
  Button_Attach(&Button0,BUTTON_DOUBLE,Btn0_Double_CallBack);                   //˫��
  Button_Attach(&Button0,BUTTON_CONTINUOS,Btn0_Continuos_CallBack);             //����  
  Button_Attach(&Button0,BUTTON_CONTINUOS_FREE,Btn0_ContinuosFree_CallBack);    //�����ͷ�  
  Button_Attach(&Button0,BUTTON_LONG,Btn0_Long_CallBack);   

  Button_Create("Button1",
                &Button1, 
                Read_Button1_Level, 
                BUTTON_ON);
  Button_Attach(&Button1,BUTTON_DOWM,Btn1_Dowm_CallBack);                       //����
  Button_Attach(&Button1,BUTTON_DOUBLE,Btn1_Double_CallBack);                   //˫��
  Button_Attach(&Button1,BUTTON_CONTINUOS,Btn1_Continuos_CallBack);             //����  
  Button_Attach(&Button1,BUTTON_CONTINUOS_FREE,Btn1_ContinuosFree_CallBack);    //�����ͷ�  
  Button_Attach(&Button1,BUTTON_LONG,Btn1_Long_CallBack);                       //����
  
  Button_Create("Button2",
                &Button2, 
                Read_Button2_Level, 
                BUTTON_ON);
  Button_Attach(&Button2,BUTTON_DOWM,Btn2_Dowm_CallBack);                       //����
  Button_Attach(&Button2,BUTTON_DOUBLE,Btn2_Double_CallBack);                   //˫��
  Button_Attach(&Button2,BUTTON_CONTINUOS,Btn2_Continuos_CallBack);             //����  
  Button_Attach(&Button2,BUTTON_CONTINUOS_FREE,Btn2_ContinuosFree_CallBack);    //�����ͷ�  
  Button_Attach(&Button2,BUTTON_LONG,Btn2_Long_CallBack);                       //����
  
  Button_Create("Button3",
                &Button3, 
                Read_Button3_Level, 
                BUTTON_OFF);
  Button_Attach(&Button3,BUTTON_DOWM,Btn3_Dowm_CallBack);                       //����
  Button_Attach(&Button3,BUTTON_DOUBLE,Btn3_Double_CallBack);                   //˫��
  Button_Attach(&Button3,BUTTON_CONTINUOS,Btn3_Continuos_CallBack);             //����  
  Button_Attach(&Button3,BUTTON_CONTINUOS_FREE,Btn3_ContinuosFree_CallBack);    //�����ͷ�  
  Button_Attach(&Button3,BUTTON_LONG,Btn3_Long_CallBack);                       //����
  
}


void Button_Task(void* parameter)
{
  
  Register_Button();
  
  while(1)
  {
    Button_Process();     //��Ҫ���ڵ��ð���������
    LOS_TaskDelay(20);
  }
}




UINT32 Creat_Button_Task(void)
{
  UINT32 uwRet = LOS_OK;				/* ����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ */
  TSK_INIT_PARAM_S task_init_param;

  task_init_param.usTaskPrio = 1;								                    /* ���ȼ�����ֵԽС�����ȼ�Խ�� */
  task_init_param.pcName = "Button_Task";						                  /* ���������ַ�����ʽ��������� */
  task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Button_Task;	/* �������� */
  task_init_param.uwStackSize = 512;						                  /* ջ��С����λΪ�֣���4���ֽ� */

  uwRet = LOS_TaskCreate(&Button_Task_Handle, &task_init_param);/* �������� */
  
  return uwRet;
}



