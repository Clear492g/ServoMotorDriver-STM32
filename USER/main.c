#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "motor.h"
#include "enc.h"
#include "string.h"
#include "timer.h"
#include "command.h"
#include "motor_config.h"
#include "pid.h"

u16 DD =0;
float motor1_pwm_div = 1;
float motor2_pwm_div = 1;
float motor3_pwm_div = 1;
float motor4_pwm_div = 1;
int KDshu =0;//点电机要转的圈数/11
u16 motor_pwm1;
u16 motor_pwm2;
u8 command_success =0;
u16 pid_zhi=0;

 int main(void)
 {		
	u16 cc = 0; 
	u16 j = 0; 
	u16 dd =199; 
 	u16 t;  
	u16 len;	
	u16 times=0;
	u16 code =0;
	char *sp = NULL;
	int  timer = 0;
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
	TIM1_PWM_Init(dd,8);                                                 // 9??:10KHZ
  TIM8_PWM_Init(dd,8);     
	MOTOR_EN_Init();	 
  TIM6_Init();   



 	while(1)
	{

		
		if(USART_RX_STA&0x8000)
		{					   
				timer = 0;
				len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			  motor_travel_fc();
//    		motor_code_debug();
	
		
			if(command_success == 1)
			{
				command_success = 0;
				USART_SendData(USART2,'o');
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
				USART_SendData(USART2,'k');
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
				USART_SendData(USART2,'\r');
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
				USART_SendData(USART2,'\n');

			}
			USART_RX_STA=0;
		}
		

	

	}	 
	
 }

