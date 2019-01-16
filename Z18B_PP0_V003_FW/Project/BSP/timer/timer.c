/**
  ******************************************************************************
  * @file    timer.c 
  * @author  DPL
  * @version V1.0.0
  * @date    
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
  * 										COPYRIGHT 2011 STMicroelectronics
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "timer.h"
/********************************************************************
**Function: TIMER_Init
**Note 		: ��ʱ��5��ʼ��
**Input 	: u16 arr	��װ��ֵ
						u16 psc Ԥ��Ƶϵ��
**Output 	: None
**Use 		:	TIMER_Init();
*********************************************************************/
void TIMER_Init(u16 arr,u16 psc)
{	 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);						//ʹ��TIM5ʱ��

	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; 												//�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 											//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 				//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	 	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 								//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 								//TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  			//��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  						//�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 								//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  																//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 

	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);												//��������ж�
	
	TIM_Cmd(TIM2,ENABLE ); 													//ʹ�ܶ�ʱ��5

}

/********************************************************************
**Function: TIM2_IRQHandler
**Note 		: ��ʱ��5�жϷ������	
**Input 	: None
**Output 	: None
**Use 		: 
*********************************************************************/
void TIM2_IRQHandler(void)
{ 
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)	
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 			//����жϱ�־λ

		//kalman_tem.predict = kalman1_filter(&kalman_tem,tem);					//�¶ȿ������˲�
		//kalman_hum.predict = kalman1_filter(&kalman_hum,hum);					//ʪ�ȿ������˲�
		IWDG_Feed();
		count++;
	}
}

