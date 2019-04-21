#include "at_hal/at_hal.h"

//#include "bsp_usart.h"

extern at_task at;

USART_TypeDef at_usart;

static USART_TypeDef *s_pUSART = USART2;
static uint32_t s_uwIRQn = USART2_IRQn;

//uint32_t list_mux;
uint8_t buff_full = 0;
static uint32_t g_disscard_cnt = 0;

uint32_t wi       = 0;
uint32_t pre_ri   = 0;/*only save cur msg start*/
uint32_t ri       = 0;

#if USE_USART2_DMA_RX 
static void USART2_DMA_Rx_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	// 开启DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// 设置DMA源地址：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)USART2_DR_ADDRESS;
	// 内存地址(要传输的变量的指针)
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)at.recv_buf;
	// 方向：从内存到外设	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	// 传输大小	
	DMA_InitStructure.DMA_BufferSize = USART2_RX_BUFF_SIZE;
	// 外设地址不增	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// 内存地址自增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// 外设数据单位	
	DMA_InitStructure.DMA_PeripheralDataSize = 
	DMA_PeripheralDataSize_Byte;
	// 内存数据单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	// DMA模式，一次或者循环模式
	//DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
	// 优先级：中	
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
	// 禁止内存到内存的传输
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	// 配置DMA通道		   
	DMA_Init(USART2_RX_DMA_CHANNEL, &DMA_InitStructure);		
	// 清除DMA所有标志
	DMA_ClearFlag(DMA1_FLAG_TC6);
	DMA_ITConfig(USART2_RX_DMA_CHANNEL, DMA_IT_TE, ENABLE);
	// 使能DMA
	DMA_Cmd (USART2_RX_DMA_CHANNEL,ENABLE);
}
#endif

#if USE_USART2_DMA_TX 
static void USART2_DMA_Tx_Config(void)
{
		DMA_InitTypeDef DMA_InitStructure;
	
		// 开启DMA时钟
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		// 设置DMA源地址：串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)USART2_DR_ADDRESS;
		// 内存地址(要传输的变量的指针)
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Usart2_Tx_Buf;
		// 方向：从内存到外设	
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		// 传输大小	
		DMA_InitStructure.DMA_BufferSize = USART2_TX_BUFF_SIZE;
		// 外设地址不增	    
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		// 内存地址自增
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		// 外设数据单位	
		DMA_InitStructure.DMA_PeripheralDataSize = 
	  DMA_PeripheralDataSize_Byte;
		// 内存数据单位
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
		// DMA模式，一次或者循环模式
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
//		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
		// 优先级：中	
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 
		// 禁止内存到内存的传输
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		// 配置DMA通道		   
		DMA_Init(USART2_TX_DMA_CHANNEL, &DMA_InitStructure);		
		// 使能DMA
		DMA_Cmd (USART2_TX_DMA_CHANNEL,ENABLE);
}
#endif

static void at_usart_adapter(uint32_t port)
{
    switch ( port )
    {
    case 1 :
        s_pUSART = USART1;
        s_uwIRQn = USART1_IRQn;
        break;
    case 2 :
        s_pUSART = USART2;
        s_uwIRQn = USART2_IRQn;
        break;
    case 3 :
        s_pUSART = USART3;
        s_uwIRQn = USART3_IRQn;
        break;
    default:
        break;
    }
}


void at_transmit(uint8_t * cmd, int32_t len,int flag)
{
  at_config *at_user_conf = at_get_config();
  
  char *line_end = at_user_conf->line_end;
  PRINTF_DEBUG("send:%s,len:%d",cmd,len);
  (void)Usart2_Send_Data(USART2, (uint8_t *)cmd, len);
  if(flag == 1)
  {
      (void)Usart2_Send_Data(USART2, (uint8_t *)line_end, strlen(at_user_conf->line_end));
  }
  
}
    
int32_t at_usart_init(void)
{
  USART_TypeDef *usart = &at_usart;
  at_config *at_user_conf = at_get_config();

  at_usart_adapter(at_user_conf->usart_port);

  USART2_Config();
  
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//  // 串口中断优先级配置
//  NVIC_InitTypeDef NVIC_InitStructure;
//  
//	// 打开串口GPIO的时钟
//	USART2_GPIO_APBxClkCmd(USART2_GPIO_CLK, ENABLE);
//	
//	// 打开串口外设的时钟
//	USART2_APBxClkCmd(USART2_CLK, ENABLE);

//	// 将USART Tx的GPIO配置为推挽复用模式
//	GPIO_InitStructure.GPIO_Pin = USART2_TX_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);

//  // 将USART Rx的GPIO配置为浮空输入模式
//	GPIO_InitStructure.GPIO_Pin = USART2_RX_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
//  
//  USART_TypeDef *usart = &at_usart;
//  
//  at_config *at_user_conf = at_get_config();
//  at_usart_adapter(at_user_conf->usart_port);
//  
//	// 配置串口的工作参数
//	// 配置波特率
//	USART_InitStructure.USART_BaudRate = at_user_conf->buardrate;;
//	// 配置 针数据字长
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	// 配置停止位
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	// 配置校验位
//	USART_InitStructure.USART_Parity = USART_Parity_No ;
//	// 配置硬件流控制
//	USART_InitStructure.USART_HardwareFlowControl = 
//	USART_HardwareFlowControl_None;
//	// 配置工作模式，收发一起
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	// 完成串口的初始化配置
//	USART_Init(s_pUSART, &USART_InitStructure);	

//  /* 配置USART2为中断源 */
//  NVIC_InitStructure.NVIC_IRQChannel = s_uwIRQn; 
//  /* 抢占优先级*/
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
//  /* 子优先级 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  /* 使能中断 */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* 初始化配置NVIC */
//  NVIC_Init(&NVIC_InitStructure);


//#if USE_USART2_DMA_RX 
//	// 开启 串口空闲IDEL 中断
//	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);  
//  // 开启串口DMA接收
//	USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE); 
//	/* 使能串口DMA */
//	USART2_DMA_Rx_Config();
//#else
//	// 使能串口接收中断
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	
//#endif

//#if USE_USART2_DMA_TX 
//	// 开启串口DMA发送
////	USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE); 
//	USART2_DMA_Tx_Config();
//#endif

//	// 使能串口
//	USART_Cmd(USART2, ENABLE);	 

  return AT_OK;

}



void at_usart_deinit(void)
{
  USART_DeInit(USART2);
  
#if USE_USART2_DMA_RX 
	// 开启 串口空闲IDEL 中断
	USART_ITConfig(USART2, USART_IT_IDLE, DISABLE);  
  // 开启串口DMA接收
	USART_DMACmd(USART2, USART_DMAReq_Rx, DISABLE); 
#else
	// 使能串口接收中断
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);	
#endif
}


int read_resp(uint8_t *buf, recv_buff* recv_buf)
{
  uint32_t len = 0;

  uint32_t tmp_len = 0;

  at_config *at_user_conf = at_get_config();

  if (NULL == buf)
  {
      return -1;
  }
  if(1 == buff_full)
  {
      AT_LOG("buf maybe full,buff_full is %d",buff_full);
  }
  
  if (recv_buf->end == recv_buf->ori)
  {
      len = 0;
      goto END;
  }

  if (recv_buf->end > recv_buf->ori)
  {
      len = recv_buf->end - recv_buf->ori;
      memcpy(buf, &at.recv_buf[recv_buf->ori], len);
  }
  else
  {
      tmp_len = at_user_conf->user_buf_len - recv_buf->ori;
      memcpy(buf, &at.recv_buf[recv_buf->ori], tmp_len);
      memcpy(buf + tmp_len, at.recv_buf, recv_buf->end);
      len = recv_buf->end + tmp_len;
  }

  ri = recv_buf->end;
END:
  
  return len;
  
  
}
void write_at_task_msg(at_msg_type_e type)
{
  recv_buff recv_buf;
  int ret;

  memset(&recv_buf,  0, sizeof(recv_buf));
  recv_buf.msg_type = type;

  ret = LOS_QueueWriteCopy(at.rid, &recv_buf, sizeof(recv_buff), 0);
  if(ret != LOS_OK)
  {
      g_disscard_cnt++;
  }
}

void USART2_IRQHandler(void)
{
  recv_buff recv_buf;
  at_config *at_user_conf = at_get_config();

  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
      at.recv_buf[wi++] = USART_ReceiveData( USART2 );
      if(wi == ri)buff_full = 1;
      if (wi >= at_user_conf->user_buf_len)wi = 0;
  }
  else if (USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
  {
      USART_ReceiveData( USART2 );

      recv_buf.ori = pre_ri;
      recv_buf.end = wi;

      pre_ri = recv_buf.end;
      recv_buf.msg_type = AT_USART_RX;

      if(LOS_QueueWriteCopy(at.rid, &recv_buf, sizeof(recv_buff), 0) != LOS_OK)
      {
          g_disscard_cnt++;
      }
  }
}




