#include "timer.h"
#include "led.h"
#include "usart.h"
#include "motor_config.h"
#include "motor.h"
#include "command.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!


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










