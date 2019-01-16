/**
  ******************************************************************************
  * @file    ptc.c 
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  ******************************************************************************
  */  
/* Includes ------------------------------------------------------------------*/
#include "ptc.h"
/* Varibales ------------------------------------------------------------------*/
u8 Tansfer_Buffer[30];
u32 count = 0;
uint8_t RegistrationRequestStatus=0;
/* Functions -----------------------------------------------------------------*/


/********************************************************************
**Function: PTC_Init
**Note 		: Э����ʼ��
**Input 	: None
**Output 	: None
**Use 		: PTC_Init();
*********************************************************************/

void PTC_Init(void)
{
	//IIC_ADS��ʼ��
	IIC_ADS_Init();				
	if(GasADS1115_Init(CONFREG_INIT, LOREG_INIT, HIREG_INIT) == 0 ) 	STM32_LED_ADC1 = 0;				//ADS1115_Gas  ��ʼ��
	else Err_State = IIC_FAULT;
	delay_ms(1);
	if(WindADS1115_Init(CONFREG_INIT, LOREG_INIT, HIREG_INIT) == 0)	 	STM32_LED_ADC2 = 0;			  //ADS1115_Wind ��ʼ��
	else Err_State = IIC_FAULT;
	delay_ms(1);
	
	//IIC_HTS��ʼ��
	IIC_HTS_Init();			 	
	
	for(int i = 0;i < 20;i++) delay_ms(1000);		//�ӳ�20s�ȴ�ģ�鿪��
	
	DMA_Cmd(DMA1_Channel6,ENABLE);	
	USART_Cmd(USART2,ENABLE);	
	
	//BC-35G NB-IoT ��ʼ��
	NB_InitConnectOneNet();											//���ģ��״̬
	if(RegistrationRequestStatus == 0)
	{
		NB_DeleteRegistrationRequest();						//���ע����Ϣ
		delay_ms(1000);delay_ms(1000);						//2s
		RegistrationRequestStatus = NB_SendRegistrationRequest();		//ע��
	}
	delay_ms(1000);															//1s
	if(RegistrationRequestStatus == 2)
	{
		printf("AT+MIPLCLOSE=0\r\n");							//�ر���·
		printf("AT+MIPLCLOSE=0\r\n");
	}

	delay_ms(1000);delay_ms(1000);							//2s
	
	memset(&oneNetDevice,0,sizeof(oneNetDevice));		//��ṹ��
	memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));	//�建��
	
	
	for(int i = 0;i < 10;i++) delay_ms(1000);		//�ӳ�10s
	
	count = 0;																			//��������
}


