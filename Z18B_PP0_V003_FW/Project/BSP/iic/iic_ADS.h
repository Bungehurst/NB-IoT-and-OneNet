		//�ļ�ͷ ��ֹ�ظ�����
#ifndef __MYIIC_ADS_H
#define __MYIIC_ADS_H

		//�����ļ�����
#include "sys.h"
#include "delay.h"

		//�궨�岿��

//IO�������� ���ı�IO������ı����������
#define SDA_ADS_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_ADS_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO��������	 
#define IIC_ADS_SCL    PBout(6) //SCL
#define IIC_ADS_SDA    PBout(7) //SDA	 
#define READ_SDA_ADS   PBin(7)  //����SDA 


		//������������

//IIC���в�������
void IIC_ADS_Init(void);                //��ʼ��IIC��IO��				 
void IIC_ADS_Start(void);				//����IIC��ʼ�ź�
void IIC_ADS_Stop(void);	  			//����IICֹͣ�ź�
void IIC_ADS_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_ADS_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_ADS_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_ADS_Ack(void);					//IIC����ACK�ź�
void IIC_ADS_NAck(void);				//IIC������ACK�ź�

#endif
