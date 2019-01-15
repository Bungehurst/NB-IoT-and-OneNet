#ifndef __IIC_HTS_H
#define __IIC_HTS_H
#include "sys.h"
#include "delay.h"
#include "led.h"
/****************
SDA----PA5
SCL----PA4
****************/

//IO�������� ���ı�IO������ı����������
#define SDA_HTS_IN()  {GPIOA->CRL&=0XFF0FFFFF; GPIOA->CRL|=(u32)8<<20;}
#define SDA_HTS_OUT() {GPIOA->CRL&=0XFF0FFFFF; GPIOA->CRL|=(u32)3<<20;}

//IO��������	 
#define IIC_HTS_SCL    PAout(4) //SCL
#define IIC_HTS_SDA    PAout(5) //SDA	 
#define READ_SDA_HTS   PAin(5)  //����SDA 

//IIC���в�������
void IIC_HTS_Init(void);                //��ʼ��IIC��IO��				 
void IIC_HTS_Start(void);				//����IIC��ʼ�ź�
void IIC_HTS_Stop(void);	  			//����IICֹͣ�ź�
void IIC_HTS_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_HTS_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_HTS_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_HTS_Ack(void);					//IIC����ACK�ź�
void IIC_HTS_NAck(void);				//IIC������ACK�ź�

#endif
