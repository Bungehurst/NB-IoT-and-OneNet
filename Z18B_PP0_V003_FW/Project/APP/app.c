/**
  ******************************************************************************
  * @file    app.c 
  * @author  DPL
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  ******************************************************************************
  */  
/* Includes ------------------------------------------------------------------*/
#include "app.h"
/* Varibales -----------------------------------------------------------------*/
const u16 REG[]={0xC380,0xD380,0xE380,0xF380};				//ADS1115�ĸ�ͨ���Ĵ�����ַ
u16 RegValue[8] = {0}; 
float Voltage[8] = {0};																//�ĸ�ͨ���Ĵ���ֵ
u8 Version[13] = {'Z','1','8','B','_','P','P'					//�汾��Ϣ
									,'1','_','V','0','0','0'};
									
//����������
char tem = 0;
u8 hum = 0;
float Degree = 0,Vel = 0;
u32 Press = 0;
u16 Pm2 = 0;
u16 Pm10 = 0;
float O3 = 0;
float SO2 = 0;
float CO = 0;
float NO2 = 0;
float NB_Buffer[11]={0};
char T_varible[4] = {0};
/* Functions -----------------------------------------------------------------*/

/********************************************************************
**Function: APP_Start
**Note 		: Ӧ�ò����
**Input 	: None
**Output 	: None
**Use 		: APP_Start();
*********************************************************************/
void APP_Start(void)
{
	if(Err_State == NONE)																//ϵͳ������
	STM32_LED_SDCARD = !STM32_LED_SDCARD;							  //SDCard LED ��ʱ����ϵͳ����ָʾ��
	switch(State)
	{
		case NB_TEST:
			for(int i = 0;i < 4;i++)													
				{	
					WindADS1115_WriteToRegister(CONFREG, REG[i]); 	//��ʼ��д
					if(WINDADS1115_RDYPIN) 													//���ת����� PinΪ�ߵ�ƽ
					{
						RegValue[i] = WindADS1115_ReadFromRegister(CVSNREG);//��ȡ�Ĵ���ֵ
						Voltage[i] = (RegValue[i]*4.096/32768.0);			//ת����ʵ�ʵ�ѹ
						if(i==0)
						{
							STM32_LED_WS=!STM32_LED_WS;
							if (Voltage[0]>0&&Voltage[0]<3.0)
								Vel = Voltage[0]*3.67782;										//ת��Ϊ�ٶ�  ������μ���Ʒ�ĵ�
							else Vel = 0;
						}							
						if(i==1)
						{
							STM32_LED_WD=!STM32_LED_WD;
							if(Voltage[1]>0&&Voltage[1]<3.0)
								Degree = Voltage[1]*165.1376;											//ת��Ϊ�Ƕ�  ������μ���Ʒ�ĵ�
						}						
						if(i==2) 
						{
							STM32_LED_SO2=!STM32_LED_SO2;
							SO2 = Voltage[2];
						}
						if(i==3) 
						{
							STM32_LED_O3=!STM32_LED_O3;
							O3 = Voltage[3];
						}
					}
					delay_ms(10);																		//ͨ���л�ʱ��10ms (����)
				}

				//ADC2
				for(int i = 4;i < 8;i++)													
				{	
					GasADS1115_WriteToRegister(CONFREG, REG[i-4]); 		//��ʼ��д
					if(GASADS1115_RDYPIN) 														//���ת����� PinΪ�ߵ�ƽ
					{
						RegValue[i] = GasADS1115_ReadFromRegister(CVSNREG); //��ȡ�Ĵ���ֵ
						Voltage[i] = (RegValue[i]*4.096/32768.0);				//ת����ʵ�ʵ�ѹ
						if(i==4)
						{
							//��
						}
						if(i==5)
						{
							STM32_LED_NO2=!STM32_LED_NO2;
							NO2 = Voltage[5];
						}
						if(i==6) 
						{
							STM32_LED_CO=!STM32_LED_CO;
							CO = Voltage[6];
						}
						if(i==7)
						{
							//PH
						}
					}
					delay_ms(10);																			//ͨ���л�ʱ��10ms (����)
				}
				
			SHT31_Read(&tem,&hum);																//��ȡSHT31
			Press = (u32)BMP180_Update();	
			
			NB_Buffer[0] = tem;
			NB_Buffer[1] = hum;
			NB_Buffer[2] = Press;
			NB_Buffer[3] = CO;
			NB_Buffer[4] = SO2;
			NB_Buffer[5] = NO2;
			NB_Buffer[6] = O3;
			NB_Buffer[7] = Pm2;
			NB_Buffer[8] = Pm10;
			NB_Buffer[9] = Vel;
			NB_Buffer[10] = Degree;
				
			//���³�ʼ��DMA��ʹ���ݴ�BUFFERͷ����
			USART_Cmd(USART2,DISABLE);											//ʧ�ܴ���
			DMA_Cmd(DMA1_Channel6,DISABLE);									//ʧ��DMA
			memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));	//�建��
			DMA_InitTypeDef dma;
			DMA_DeInit(DMA1_Channel6);
			dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->DR);
			dma.DMA_MemoryBaseAddr = (uint32_t)USART2_RX_BUF;
			dma.DMA_DIR = DMA_DIR_PeripheralSRC;
			dma.DMA_BufferSize = USART2_REC_LEN;
			dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
			dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
			dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
			dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
			dma.DMA_Mode = DMA_Mode_Circular;
			dma.DMA_Priority = DMA_Priority_VeryHigh;
			dma.DMA_M2M = DMA_M2M_Disable;
			DMA_Init(DMA1_Channel6,&dma);
			DMA_Cmd(DMA1_Channel6,ENABLE);
			USART_Cmd(USART2,ENABLE);	
			
			delay_ms(1000);
			if(err_stat == 0)															//���ģ��û������ err_stat == 0
			{																							//��ɾ��ע����Ϣ��ֻ����·
				RegistrationRequestStatus = NB_SendRegistrationRequest_2();
			}else if(err_stat == 1)												//���ģ�������� err_stat == 1
			{																							//ɾ��ע����Ϣ����������
				NB_DeleteRegistrationRequest();
				delay_ms(1000);delay_ms(1000);
				NB_SendRegistrationRequest();
				delay_ms(1000);
				printf("AT+MIPLCLOSE=0\r\n");
				printf("AT+MIPLCLOSE=0\r\n");
				delay_ms(1000);
				memset(&oneNetDevice,0,sizeof(oneNetDevice));
				delay_ms(1000);
				err_stat = 0;
				RegistrationRequestStatus = 0;
			}
			delay_ms(1000);
			if(RegistrationRequestStatus == 2) 
			{
				sprintf(T_varible,"%4.1f",NB_Buffer[0]);
				NB_NotifyOneNetMsg((char *)oneNetDevice.observeMsgId_3303_0,(char *)"3303",(char *)"0",(uint8_t *)"5700",(uint8_t *)T_varible);

				sprintf(T_varible,"%4.1f",NB_Buffer[1]);
				NB_NotifyOneNetMsg((char *)oneNetDevice.observeMsgId_3304_0,(char *)"3304",(char *)"0",(uint8_t *)"5700",(uint8_t *)T_varible);

				sprintf(T_varible,"%4.1f",NB_Buffer[2]);
				NB_NotifyOneNetMsg((char *)oneNetDevice.observeMsgId_3323_0,(char *)"3323",(char *)"0",(uint8_t *)"5700",(uint8_t *)T_varible);

				sprintf(T_varible,"%4.1f",NB_Buffer[3]);
				NB_NotifyOneNetMsg((char *)oneNetDevice.observeMsgId_3315_0,(char *)"3315",(char *)"0",(uint8_t *)"5700",(uint8_t *)T_varible);

				sprintf(T_varible,"%4.1f",NB_Buffer[4]);
				NB_NotifyOneNetMsg((char *)oneNetDevice.observeMsgId_3315_1,(char *)"3315",(char *)"1",(uint8_t *)"5700",(uint8_t *)T_varible);

				sprintf(T_varible,"%4.1f",NB_Buffer[5]);
				NB_NotifyOneNetMsg((char *)oneNetDevice.observeMsgId_3315_2,(char *)"3315",(char *)"2",(uint8_t *)"5700",(uint8_t *)T_varible);

				sprintf(T_varible,"%4.1f",NB_Buffer[6]);
				NB_NotifyOneNetMsg((char *)oneNetDevice.observeMsgId_3315_3,(char *)"3315",(char *)"3",(uint8_t *)"5700",(uint8_t *)T_varible);

				sprintf(T_varible,"%4.1f",NB_Buffer[7]);
				NB_NotifyOneNetMsg((char *)oneNetDevice.observeMsgId_3316_0,(char *)"3316",(char *)"0",(uint8_t *)"5700",(uint8_t *)T_varible);

				sprintf(T_varible,"%4.1f",NB_Buffer[8]);
				NB_NotifyOneNetMsg((char *)oneNetDevice.observeMsgId_3316_1,(char *)"3316",(char *)"1",(uint8_t *)"5700",(uint8_t *)T_varible);

				sprintf(T_varible,"%4.1f",NB_Buffer[9]);
				NB_NotifyOneNetMsg((char *)oneNetDevice.observeMsgId_3316_2,(char *)"3316",(char *)"2",(uint8_t *)"5700",(uint8_t *)T_varible);

				sprintf(T_varible,"%4.1f",NB_Buffer[10]);
				NB_NotifyOneNetMsg((char *)oneNetDevice.observeMsgId_3316_3,(char *)"3316",(char *)"3",(uint8_t *)"5700",(uint8_t *)T_varible);
				delay_ms(1000);
				memset(&oneNetDevice,0,sizeof(oneNetDevice));
				delay_ms(1000);
				printf("AT+MIPLCLOSE=0\r\n");
				printf("AT+MIPLCLOSE=0\r\n");
				RegistrationRequestStatus = 0;
				break;
			}
			if(RegistrationRequestStatus == 0) err_stat = 1;
			break;
		default: break;
		}
}
