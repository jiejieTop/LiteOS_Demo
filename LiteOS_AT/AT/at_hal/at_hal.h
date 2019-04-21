#ifndef __AT_HAL_H__
#define __AT_HAL_H__

#include <stdint.h>
#include <stdio.h>
#include "at_frame/at_main.h"

void at_transmit(uint8_t * cmd, int32_t len,int flag);
int32_t at_usart_init(void);
void at_usart_deinit(void);
int read_resp(uint8_t *buf, recv_buff* recv_buf);
void write_at_task_msg(at_msg_type_e type);



#endif
