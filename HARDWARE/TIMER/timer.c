#include "timer.h"
#include "led.h"
#include "usart.h"
#include "motor_config.h"
#include "motor.h"
#include "command.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!


extern char motor_dir;
extern u16 motor1_qep_last;
extern u16 motor2_qep_last;
extern u16 motor3_qep_last;
extern u16 motor4_qep_last;


 
void TIM6_Init(void)                    // 1????
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
  NVIC_InitTypeDef NVIC_InitStructure;
    
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);     
  TIM_DeInit(TIM6);
  TIM_TimeBaseStructure.TIM_Prescaler = 1000;
  TIM_TimeBaseStructure.TIM_Period = 7200-1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM6, TIM_FLAG_Update);		
  TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
				
    
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	    	
  NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  			
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 			
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure);    
	
	  TIM_Cmd(TIM6, ENABLE);	
}










