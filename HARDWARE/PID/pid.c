#include "pid.h"
#include "usart.h"
	int pid_flag;
	float pid_setspeed;
	float pid_actualspeed;
	float pid_err;
	float pid_err_next;
	float pid_err_last;
	float pid_kp,pid_ki,pid_kd;
int read_speed_flag;


	 int pwm_duty = 100;
	 double incrementSpeed;
	int measure_value;
	 int motor_qep_next = 0;
	int    motor_qep_new  =0 ;
int pid_initialize(void)
{
	//两组不同pid参数，第一组调节较慢，第二组较快
	#if PARA
		pid_setspeed = 0.0;					//定义设定值
		pid_actualspeed = 0.0;			//定义实际值
		
		pid_err = 0.0;							//定义偏差值
		pid_err_last = 0.0;					//定义最上前的偏差值
		pid_err_next = 0.0;					//定义上一个的偏差值
		
		pid_kp = 0.0001;								//比例系数
		pid_ki = 0.025;						  //积分系数
		pid_kd = 0.2;								//微分系数
	#else
		pid_setspeed = 0.0;					//定义设定值
		pid_actualspeed = 0.0;			//定义实际值
		
		pid_err = 0.0;							//定义偏差值
		pid_err_last = 0.0;					//定义最上前的偏差值
		pid_err_next = 0.0;					//定义上一个的偏差值
		
		pid_kp = 0.001;								//比例系数
		pid_ki = 0.055;						  //积分系数
		pid_kd = 0.3;								//微分系数	
	#endif
	
	return 0;
} 

int pid_realize(float set_value)//600  //1400  //2205
{	
	char  test [15];
	char t=0;
	motor_qep_new= TIM_GetCounter(TIM5);
		measure_value	= -(motor_qep_new-motor_qep_next);
	if(-(motor_qep_new-motor_qep_next)<0)
	{measure_value=65535-(motor_qep_new-motor_qep_next);}
	motor_qep_next = motor_qep_new;
//	measure_value = (double)fan.read() * 60.;//读取实际转速
	pid_err = set_value - measure_value;//计算偏差值

	incrementSpeed = pid_kp * (pid_err - pid_err_next) + pid_ki * pid_err;// + pid_kd * (pid_err - 2 * pid_err_next + pid_err_last);//计算速度增量
	pwm_duty += incrementSpeed / 120;//将速度增量转换为占空比的增量
	
	pid_err_last = pid_err_next;//把上次偏差值给最上前偏差
	pid_err_next = pid_err;//把当前偏差赋给上一个偏差
	if(pwm_duty > 200){//风扇的最大占空比调节值为5000
		pwm_duty = 200;
	}
	else if(pwm_duty < 0){//风扇的最小占空比调节值为500
		pwm_duty = 0;
	}
	TIM_SetCompare3(TIM1,0);
  TIM_SetCompare4(TIM1,(unsigned char)(pwm_duty));
	//fan.set_pwm(pwm_duty );//通过设置当前的占空比值调节风扇的转速
//	printf("speed:%d",measure_value);
//	printf("ok");
//		test[0]=measure_value/10000+'0';	measure_value=measure_value%10000; test[1]=measure_value/1000+'0'; measure_value=measure_value%1000; test[2]=measure_value/100+'0';	measure_value=measure_value%100;
//	  test[3]=measure_value/10+'0';	measure_value=measure_value%10; test[4]=measure_value/1+'0';	test[5]='\r';test[6]='\n';
//	for(t=0;t<7;t++)
//			{
//				USART_SendData(USART2, test[t]);//向串口1发送数据
//				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
//			}
	return measure_value;//返回实际速度
}