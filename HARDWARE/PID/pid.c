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
	//���鲻ͬpid��������һ����ڽ������ڶ���Ͽ�
	#if PARA
		pid_setspeed = 0.0;					//�����趨ֵ
		pid_actualspeed = 0.0;			//����ʵ��ֵ
		
		pid_err = 0.0;							//����ƫ��ֵ
		pid_err_last = 0.0;					//��������ǰ��ƫ��ֵ
		pid_err_next = 0.0;					//������һ����ƫ��ֵ
		
		pid_kp = 0.0001;								//����ϵ��
		pid_ki = 0.025;						  //����ϵ��
		pid_kd = 0.2;								//΢��ϵ��
	#else
		pid_setspeed = 0.0;					//�����趨ֵ
		pid_actualspeed = 0.0;			//����ʵ��ֵ
		
		pid_err = 0.0;							//����ƫ��ֵ
		pid_err_last = 0.0;					//��������ǰ��ƫ��ֵ
		pid_err_next = 0.0;					//������һ����ƫ��ֵ
		
		pid_kp = 0.001;								//����ϵ��
		pid_ki = 0.055;						  //����ϵ��
		pid_kd = 0.3;								//΢��ϵ��	
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
//	measure_value = (double)fan.read() * 60.;//��ȡʵ��ת��
	pid_err = set_value - measure_value;//����ƫ��ֵ

	incrementSpeed = pid_kp * (pid_err - pid_err_next) + pid_ki * pid_err;// + pid_kd * (pid_err - 2 * pid_err_next + pid_err_last);//�����ٶ�����
	pwm_duty += incrementSpeed / 120;//���ٶ�����ת��Ϊռ�ձȵ�����
	
	pid_err_last = pid_err_next;//���ϴ�ƫ��ֵ������ǰƫ��
	pid_err_next = pid_err;//�ѵ�ǰƫ�����һ��ƫ��
	if(pwm_duty > 200){//���ȵ����ռ�ձȵ���ֵΪ5000
		pwm_duty = 200;
	}
	else if(pwm_duty < 0){//���ȵ���Сռ�ձȵ���ֵΪ500
		pwm_duty = 0;
	}
	TIM_SetCompare3(TIM1,0);
  TIM_SetCompare4(TIM1,(unsigned char)(pwm_duty));
	//fan.set_pwm(pwm_duty );//ͨ�����õ�ǰ��ռ�ձ�ֵ���ڷ��ȵ�ת��
//	printf("speed:%d",measure_value);
//	printf("ok");
//		test[0]=measure_value/10000+'0';	measure_value=measure_value%10000; test[1]=measure_value/1000+'0'; measure_value=measure_value%1000; test[2]=measure_value/100+'0';	measure_value=measure_value%100;
//	  test[3]=measure_value/10+'0';	measure_value=measure_value%10; test[4]=measure_value/1+'0';	test[5]='\r';test[6]='\n';
//	for(t=0;t<7;t++)
//			{
//				USART_SendData(USART2, test[t]);//�򴮿�1��������
//				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//			}
	return measure_value;//����ʵ���ٶ�
}