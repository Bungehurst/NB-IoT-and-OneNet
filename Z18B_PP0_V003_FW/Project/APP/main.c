/**
  ******************************************************************************
  * @file    main.c 
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
#include "main.h"
/* Main function -------------------------------------------------------------*/
int main(void)
{
	BSP_Init();																			//�弶��ʼ��
	PTC_Init();																			//Э����ʼ��
	while(1)
	{
		State = NB_TEST ;
		APP_Start();																	//Ӧ�ò����
		//��ʱ60s

		if(err_stat==0)
		{
			count=0;
			while(count<30) 
			{	
				
			}
		}else
		{
			count=0;
			while(count<15) 
			{	
				
			}
		}
		count=0;
	}
	
}
