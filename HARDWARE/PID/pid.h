#ifndef __PID_H
#define __PID_H	 
#include "sys.h"
#define SET_PARA 0     //此处值为1 时：		kp = 0.4;	ki = 0.025; kd = 0.2;  调节速度较慢
											 //此处值为0 时：		kp = 0.9;	ki = 0.055; kd = 0.3;  调节速度较快

//------------------------- Data struct ------------------------//

	
int pid_initialize(void);
int pid_realize(float set_value);//600  //1400  //2205

//----------------------- Extern function ----------------------//

extern int read_speed_flag;
		 				    
#endif
