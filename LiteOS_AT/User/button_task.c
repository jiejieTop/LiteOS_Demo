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

/* 定义线程控制块 */

UINT32 Button_Task_Handle;

/********************************************************************
													   变量声明
 *******************************************************************/ 
Button_t Button0;
Button_t Button1;
Button_t Button2; 
Button_t Button3; 

/********************************************************************
													实现读取按键电平
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
													实现回调函数
 *******************************************************************/ 
void Btn0_Dowm_CallBack(void *btn)
{
  PRINTF_INFO("Button0 单击!");
}
void Btn0_Double_CallBack(void *btn)
{
  PRINTF_INFO("Button0 双击!");
}
void Btn0_Long_CallBack(void *btn)
{
  PRINTF_INFO("Button0 长按!");
}
void Btn0_Continuos_CallBack(void *btn)
{
  PRINTF_INFO("Button0 连按!");
}
void Btn0_ContinuosFree_CallBack(void *btn)
{
  PRINTF_INFO("Button0 连按释放!");
}

/********************************************************************
													button1
 *******************************************************************/ 
void Btn1_Dowm_CallBack(void *btn)
{
  PRINTF_INFO("Button1 单击!");
}
void Btn1_Double_CallBack(void *btn)
{
  PRINTF_INFO("Button1 双击!");
}
void Btn1_Long_CallBack(void *btn)
{
  PRINTF_INFO("Button1 长按!");
}
void Btn1_Continuos_CallBack(void *btn)
{
  PRINTF_INFO("Button1 连按!");
}
void Btn1_ContinuosFree_CallBack(void *btn)
{
  PRINTF_INFO("Button1 连按释放!");
}

/********************************************************************
													button2
 *******************************************************************/ 
void Btn2_Dowm_CallBack(void *btn)
{
  PRINTF_INFO("Button2 单击!");
}
void Btn2_Double_CallBack(void *btn)
{
  PRINTF_INFO("Button2 双击!");
}
void Btn2_Long_CallBack(void *btn)
{
  PRINTF_INFO("Button2 长按!");
}
void Btn2_Continuos_CallBack(void *btn)
{
  PRINTF_INFO("Button2 连按!");
}
void Btn2_ContinuosFree_CallBack(void *btn)
{
  PRINTF_INFO("Button2 连按释放!");
}

/********************************************************************
													button3
 *******************************************************************/ 
void Btn3_Dowm_CallBack(void *btn)
{
  PRINTF_INFO("Button3 单击!");
}
void Btn3_Double_CallBack(void *btn)
{
  PRINTF_INFO("Button3 双击!");
}

void Btn3_Long_CallBack(void *btn)
{
  PRINTF_INFO("Button3 长按!");
}

void Btn3_Continuos_CallBack(void *btn)
{
  PRINTF_INFO("Button3 连按!");
}
void Btn3_ContinuosFree_CallBack(void *btn)
{
  PRINTF_INFO("Button3 连按释放!");
}

/********************************************************************
													注册按键
 *******************************************************************/ 
static void Register_Button(void)
{
  Button_Create("Button0",
                &Button0, 
                Read_Button0_Level, 
                BUTTON_ON);
  Button_Attach(&Button0,BUTTON_DOWM,Btn0_Dowm_CallBack);                       //单击
  Button_Attach(&Button0,BUTTON_DOUBLE,Btn0_Double_CallBack);                   //双击
  Button_Attach(&Button0,BUTTON_CONTINUOS,Btn0_Continuos_CallBack);             //连按  
  Button_Attach(&Button0,BUTTON_CONTINUOS_FREE,Btn0_ContinuosFree_CallBack);    //连按释放  
  Button_Attach(&Button0,BUTTON_LONG,Btn0_Long_CallBack);   

  Button_Create("Button1",
                &Button1, 
                Read_Button1_Level, 
                BUTTON_ON);
  Button_Attach(&Button1,BUTTON_DOWM,Btn1_Dowm_CallBack);                       //单击
  Button_Attach(&Button1,BUTTON_DOUBLE,Btn1_Double_CallBack);                   //双击
  Button_Attach(&Button1,BUTTON_CONTINUOS,Btn1_Continuos_CallBack);             //连按  
  Button_Attach(&Button1,BUTTON_CONTINUOS_FREE,Btn1_ContinuosFree_CallBack);    //连按释放  
  Button_Attach(&Button1,BUTTON_LONG,Btn1_Long_CallBack);                       //长按
  
  Button_Create("Button2",
                &Button2, 
                Read_Button2_Level, 
                BUTTON_ON);
  Button_Attach(&Button2,BUTTON_DOWM,Btn2_Dowm_CallBack);                       //单击
  Button_Attach(&Button2,BUTTON_DOUBLE,Btn2_Double_CallBack);                   //双击
  Button_Attach(&Button2,BUTTON_CONTINUOS,Btn2_Continuos_CallBack);             //连按  
  Button_Attach(&Button2,BUTTON_CONTINUOS_FREE,Btn2_ContinuosFree_CallBack);    //连按释放  
  Button_Attach(&Button2,BUTTON_LONG,Btn2_Long_CallBack);                       //长按
  
  Button_Create("Button3",
                &Button3, 
                Read_Button3_Level, 
                BUTTON_OFF);
  Button_Attach(&Button3,BUTTON_DOWM,Btn3_Dowm_CallBack);                       //单击
  Button_Attach(&Button3,BUTTON_DOUBLE,Btn3_Double_CallBack);                   //双击
  Button_Attach(&Button3,BUTTON_CONTINUOS,Btn3_Continuos_CallBack);             //连按  
  Button_Attach(&Button3,BUTTON_CONTINUOS_FREE,Btn3_ContinuosFree_CallBack);    //连按释放  
  Button_Attach(&Button3,BUTTON_LONG,Btn3_Long_CallBack);                       //长按
  
}


void Button_Task(void* parameter)
{
  
  Register_Button();
  
  while(1)
  {
    Button_Process();     //需要周期调用按键处理函数
    LOS_TaskDelay(20);
  }
}




UINT32 Creat_Button_Task(void)
{
  UINT32 uwRet = LOS_OK;				/* 定义一个创建任务的返回类型，初始化为创建成功的返回值 */
  TSK_INIT_PARAM_S task_init_param;

  task_init_param.usTaskPrio = 1;								                    /* 优先级，数值越小，优先级越高 */
  task_init_param.pcName = "Button_Task";						                  /* 任务名，字符串形式，方便调试 */
  task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Button_Task;	/* 任务函数名 */
  task_init_param.uwStackSize = 512;						                  /* 栈大小，单位为字，即4个字节 */

  uwRet = LOS_TaskCreate(&Button_Task_Handle, &task_init_param);/* 创建任务 */
  
  return uwRet;
}



