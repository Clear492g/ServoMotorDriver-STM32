#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"
void MOTOR_EN_Init(void );
void MOT4RUN(unsigned char per); 
void TIM1_PWM_Init(u32 arr,u32 psc); 
void TIM8_PWM_Init(u32 arr,u32 psc); 
void MOTOR_STOP(unsigned char motor_num);
void MOTOR_RUN_SPEED(unsigned char motor_num,unsigned char motor_speed,unsigned char motor_dir,int motor_round);
void MOTOR_CODE();      
		 				    
#endif
