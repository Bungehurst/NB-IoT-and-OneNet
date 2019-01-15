#ifndef __USART2_SEND_H
#define __USART2_SEND_H
#include "sys.h"
#include "stm32f10x_it.h"
#include "ptc.h"
#include "stdio.h"
#define USART2_REC_LEN 1024
extern uint8_t USART2_RX_BUF[USART2_REC_LEN];
extern uint16_t USART_RX_STA;
extern u8 IS_OK;
void USART2_Send_Data(u8 *buf,u16 len);
void USART2_Send_Init(void);
void Usart_Recv_Handlve(void);	//���ݽ��մ���
void Usart_Cmd_Send(u8 *data,u8 cmd,u8 len);	//�����������෢����Ҫ����
#endif
