#ifndef __PID_H
#define __PID_H	 
#include "sys.h"
#define SET_PARA 0     //�˴�ֵΪ1 ʱ��		kp = 0.4;	ki = 0.025; kd = 0.2;  �����ٶȽ���
											 //�˴�ֵΪ0 ʱ��		kp = 0.9;	ki = 0.055; kd = 0.3;  �����ٶȽϿ�

//------------------------- Data struct ------------------------//

	
int pid_initialize(void);
int pid_realize(float set_value);//600  //1400  //2205

//----------------------- Extern function ----------------------//

extern int read_speed_flag;
		 				    
#endif
