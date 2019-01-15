/**
  ******************************************************************************
  * @file    ADS1115.c 
  * @author  ZTY
  * @version V2.0.0
  * @date    17-November-2018
  * @brief   
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "ads1115.h"
/* constants -----------------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  ��ȡADS1115�ļĴ���
  * @param  u8 devAddr Ҫ��ȡ��ADS1115�ĵ�ַ
			ȡֵ��0 GND
				  1 VDD
				  2 SDA
				  3 SCL
			u8 regAddr Ҫ��ȡ�ļĴ����ĵ�ַ
			ȡֵ��0 Conversion register �洢ת����ɺ���ֵ�ļĴ���
				  1 Config register
				  2 Lo_thresh register
				  3 Hi_thresh register
  * @retval u16 �Ĵ�����ֵ
  */
u16 ADS1115_ReadFromRegister(u8 devAddr, u8 regAddr)
{	
	u16 regValue = 0; // �Ĵ�������
	
	IIC_ADS_Start();
	IIC_ADS_Send_Byte(0x90|(devAddr<<1)); // ���ʹӻ���ַ
	IIC_ADS_Wait_Ack();                   // �ȴ�Ӧ��
	IIC_ADS_Send_Byte(0x00|regAddr);      // ���ͼĴ�����ַ
	IIC_ADS_Wait_Ack();                   // �ȴ�Ӧ��
	IIC_ADS_Start();
	IIC_ADS_Send_Byte(0x91|(devAddr<<1)); // ���ʹӻ���ַ
	IIC_ADS_Wait_Ack();                   // �ȴ�Ӧ��
	regValue = (IIC_ADS_Read_Byte(1)<<8); // ��ȡ�߰�λ���ݲ�����Ӧ��
	regValue |= IIC_ADS_Read_Byte(1);     // ��ȡ�Ͱ�λ���ݲ�����Ӧ��
	IIC_ADS_Stop();
	delay_us(3);                      // ���߿���ʱ��
	
	return regValue;
}


/**
  * @brief  дADS1115�ļĴ���
  * @param  u8 devAddr Ҫд���ADS1115�ĵ�ַ
			ȡֵ��0 GND
				  1 VDD
				  2 SDA
				  3 SCL
			u8 regAddr Ҫд��ļĴ����ĵ�ַ
			ȡֵ��0 Conversion register �洢ת����ɺ���ֵ�ļĴ���
				  1 Config register
				  2 Lo_thresh register
				  3 Hi_thresh register
			u16 RegValue д��Ĵ�����ֵ
  * @retval None
  */
void ADS1115_WriteToRegister(u8 devAddr, u8 regAddr, u16 regValue)
{	
	IIC_ADS_Start();
	IIC_ADS_Send_Byte(0x90|(devAddr<<1)); // ���ʹӻ���ַ
	IIC_ADS_Wait_Ack();                   // �ȴ�Ӧ��
	IIC_ADS_Send_Byte(0x00|regAddr);      // ���ͼĴ�����ַ
	IIC_ADS_Wait_Ack();                   // �ȴ�Ӧ��
	IIC_ADS_Send_Byte((u8)(regValue>>8)); // ���͸߰�λ����
	IIC_ADS_Wait_Ack();                   // �ȴ�Ӧ��
	IIC_ADS_Send_Byte((u8)(regValue));    // ���͵Ͱ�λ����
	IIC_ADS_Wait_Ack();                   // �ȴ�Ӧ��
	IIC_ADS_Stop();
	delay_us(3);                      // ���߿���ʱ��
}


/**
  * @brief  ADS1115��ALERT/RDY�ܽų�ʼ��
  * @param  GPIO_TypeDef *GPIOx GPIO��� GPIOA-GPIOG
			uint16_t GPIO_Pin GPIO�ܽź� GPIO_Pin_0-GPIO_Pin_15
  * @retval None
  */
void ADS1115_ALERTRDYpin_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	switch((u32)GPIOx)
	{
		case (u32)GPIOA:
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ��
			break;
		}
		case (u32)GPIOB:
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOBʱ��
			break;
		}
		case (u32)GPIOC:
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��GPIOCʱ��
			break;
		}
		case (u32)GPIOD:
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	//ʹ��GPIODʱ��
			break;
		}
		case (u32)GPIOE:
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	//ʹ��GPIOEʱ��
			break;
		}
		case (u32)GPIOF:
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	//ʹ��GPIOFʱ��
			break;
		}
		case (u32)GPIOG:
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	//ʹ��GPIOGʱ��
			break;
		}
		default: break;
	}
	   
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;   // ��������
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}


/**
  * @brief  ADS1115��ʼ��
  * @param  u8 devAddr Ҫд���ADS1115�ĵ�ַ
			ȡֵ��0 GND
				  1 VDD
				  2 SDA
				  3 SCL
			u16 confRegValue д�� Config register ��ֵ
			u16 loRegValue д�� Lo_thresh register ��ֵ
			u16 hiRegValue д�� Hi_thresh register ��ֵ
			GPIO_TypeDef *GPIOx GPIO��� ȡֵ��GPIOA-GPIOG
			uint16_t GPIO_Pin GPIO�ܽź� ȡֵ��GPIO_Pin_0-GPIO_Pin_15
  * @retval u8 ���ý��
			ȡֵ��0 ���óɹ�
				  1 ���ó���
  */
u8 ADS1115_Init(
	u8 devAddr,
	u16 confRegValue, 
	u16 loRegValue, 
	u16 hiRegValue,
	GPIO_TypeDef *GPIOx, 
	uint16_t GPIO_Pin
)
{
	u8 i = 2; // ��������
	
	IIC_ADS_Init(); // ��ʼ��I2C IO�� PB6 SCL  PB7 SDA
	ADS1115_ALERTRDYpin_Init(GPIOx, GPIO_Pin); // ��ʼ��ALERT/RDY�ܽ�
	
	// ��������ļĴ���ֵ���ϵ�Ĭ��ֵ�������򱨴��˳�
	if((ADS1115_ReadFromRegister(devAddr, CVSNREG) != CVSNREG_RESET) ||
		(ADS1115_ReadFromRegister(devAddr, CONFREG) != CONFREG_RESET) ||
		(ADS1115_ReadFromRegister(devAddr, LOREG) != LOREG_RESET) ||
		(ADS1115_ReadFromRegister(devAddr, HIREG) != HIREG_RESET))
	{
		return 1;
	}
	
	// �����ڲ��Ĵ��� ��3������ʧ���򱨴�
	do
	{
		ADS1115_WriteToRegister(devAddr, CONFREG, confRegValue);
		ADS1115_WriteToRegister(devAddr, LOREG, loRegValue);
		ADS1115_WriteToRegister(devAddr, HIREG, hiRegValue);

		if((ADS1115_ReadFromRegister(devAddr, CONFREG) == (confRegValue|0x8000)) && // Config register ���λд��Ͷ�ȡ�ĺ��岻һ��
		(ADS1115_ReadFromRegister(devAddr, LOREG) == loRegValue) &&
		(ADS1115_ReadFromRegister(devAddr, HIREG) == hiRegValue))
		{
			return 0;
		}
	}
	while(i--);
	
	return 1;
}


/**
  * @brief  GasADS1115��ʼ�� оƬ���U1
  * @param  u16 confRegValue д�� Config register ��ֵ
			u16 loRegValue д�� Lo_thresh register ��ֵ
			u16 hiRegValue д�� Hi_thresh register ��ֵ
  * @retval u8 ���ý��
			ȡֵ��0 ���óɹ�
				  1 ���ó���
  */
u8 GasADS1115_Init(
	u16 confRegValue, 
	u16 loRegValue, 
	u16 hiRegValue
)
{
	return ADS1115_Init(DEVADDR_VDD, confRegValue, loRegValue, hiRegValue, GPIOC, GPIO_Pin_3);
}


/**
  * @brief  ��ȡGasADS1115�ļĴ���
  * @param  u8 regAddr Ҫ��ȡ�ļĴ����ĵ�ַ
			ȡֵ��0 Conversion register �洢ת����ɺ���ֵ�ļĴ���
				  1 Config register
				  2 Lo_thresh register
				  3 Hi_thresh register
  * @retval u16 �Ĵ�����ֵ
  */
u16 GasADS1115_ReadFromRegister(u8 regAddr)
{	
	return ADS1115_ReadFromRegister(DEVADDR_VDD, regAddr);
}


/**
  * @brief  дGasADS1115�ļĴ���
  * @param  u8 regAddr Ҫд��ļĴ����ĵ�ַ
			ȡֵ��0 Conversion register �洢ת����ɺ���ֵ�ļĴ���
				  1 Config register
				  2 Lo_thresh register
				  3 Hi_thresh register
			u16 RegValue д��Ĵ�����ֵ
  * @retval None
  */
void GasADS1115_WriteToRegister(u8 regAddr, u16 regValue)
{
	ADS1115_WriteToRegister(DEVADDR_VDD, regAddr, regValue);
}


/**
  * @brief  WindADS1115��ʼ�� оƬ���U2
  * @param  u16 confRegValue д�� Config register ��ֵ
			u16 loRegValue д�� Lo_thresh register ��ֵ
			u16 hiRegValue д�� Hi_thresh register ��ֵ
  * @retval u8 ���ý��
			ȡֵ��0 ���óɹ�
				  1 ���ó���
  */
u8 WindADS1115_Init(
	u16 confRegValue, 
	u16 loRegValue, 
	u16 hiRegValue
)
{
	return ADS1115_Init(DEVADDR_GND, confRegValue, loRegValue, hiRegValue, GPIOC, GPIO_Pin_4);
}


/**
  * @brief  ��ȡWindADS1115�ļĴ���
  * @param  u8 regAddr Ҫ��ȡ�ļĴ����ĵ�ַ
			ȡֵ��0 Conversion register �洢ת����ɺ���ֵ�ļĴ���
				  1 Config register
				  2 Lo_thresh register
				  3 Hi_thresh register
  * @retval u16 �Ĵ�����ֵ
  */
u16 WindADS1115_ReadFromRegister(u8 regAddr)
{	
	return ADS1115_ReadFromRegister(DEVADDR_GND, regAddr);
}


/**
  * @brief  дWindADS1115�ļĴ���
  * @param  u8 regAddr Ҫд��ļĴ����ĵ�ַ
			ȡֵ��0 Conversion register �洢ת����ɺ���ֵ�ļĴ���
				  1 Config register
				  2 Lo_thresh register
				  3 Hi_thresh register
			u16 RegValue д��Ĵ�����ֵ
  * @retval None
  */
void WindADS1115_WriteToRegister(u8 regAddr, u16 regValue)
{
	ADS1115_WriteToRegister(DEVADDR_GND, regAddr, regValue);
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
