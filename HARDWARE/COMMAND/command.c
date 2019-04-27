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
extern u8 command_success;
extern float motor1_pwm_div ;
extern float motor2_pwm_div ;
extern float motor3_pwm_div ;
extern float motor4_pwm_div ;
extern u16 pid_zhi;
extern int Target_velocity4;
extern int KDshu;//点电机要转的圈数*11
extern u16 motor_pwm1;
extern u16 motor_pwm2;

/*************************CRC校验********************************/
//功能描述：生成CRC值
//形参：   1：想要计算CRC的原始数据值地址   2：数据个数
//返回值：	生成的crc值
/**********************************************************************/
unsigned char get_crc7(const unsigned char *buff,int len)
{
			int i;
			unsigned char crc7_accum = 0;
			for(i=0; i<len; i++)
			{
					crc7_accum = crc7_table[(crc7_accum << 1) ^ buff[i]];
			}
			
			return crc7_accum;
}
void   motor_travel_fc()
{
	char *sp = NULL;

	u8 dir1 = 1;
	u8 dir2 = 1;
	u16 motor_pwm3;
	u8 dir3 = 1;
	if(strstr((const char *)USART_RX_BUF,"@DJ") != 0x00000000)
			{
				
	ENC2_Init();
	ENC3_Init();
	ENC4_Init();
	ENC5_Init();
				
				
				
				
			  sp = strstr((const char *)USART_RX_BUF,"@DJ");
						if((*(sp+3) == ',')&&(*(sp+7)== ',')&&(*(sp+11) == ',')&&(*(sp+15) == ',')&&(*(sp+17) == '#'))
						{
							
							KDshu=(*(sp+12)-0x30)*100+(*(sp+13)-0x30)*10+(*(sp+14)-0x30);
							
							

										{
												motor_pwm1 = (*(sp+4)-0x30)*100+(*(sp+5)-0x30)*10+(*(sp+6)-0x30);
												if(motor_pwm1<=255)
												{
													
													dir1 = 1;
													MOTOR_RUN_SPEED(1,255-motor_pwm1,!dir1,0);
												}
												else 
												{
												
													dir1 = 0;
													MOTOR_RUN_SPEED(1,motor_pwm1-255,!dir1,0);
												}
											
										
											
												motor_pwm2 = (*(sp+8)-0x30)*100+(*(sp+9)-0x30)*10+(*(sp+10)-0x30);
												
												if(motor_pwm2<=255)
												{
													
													dir1 = 1;
													MOTOR_RUN_SPEED(3,255-motor_pwm2,!dir1,0);
												}
												else 
												{
												
													dir1 = 0;
													MOTOR_RUN_SPEED(3,motor_pwm2-255,!dir1,0);
												}
											

									

									}
						}
							command_success = 1;			
			}

}	
void   motor_start_debug()
{
		if(strstr((const char *)USART_RX_BUF,"@START#") != 0x00000000)
		{
	 	      MOTOR_RUN_SPEED(1,100,1,0);         //右前轮向前  - 1号编码器递减
	 	      MOTOR_RUN_SPEED(2,100,0,0);         //左前轮向后  - 2号编码器递增
   	     	MOTOR_RUN_SPEED(3,100,0,0);         //左后轮向后  - 3号编码器递增
	 		    MOTOR_RUN_SPEED(4,100,1,0);					//右后轮向前  - 4号编码器递减
				command_success = 1;
		}
}	
void   motor_init_debug()
{
			u16 motor1_qep_new;			//X号电机对应编码值
			u16 motor2_qep_new;
			u16 motor3_qep_new;
			u16 motor4_qep_new;
		if(strstr((const char *)USART_RX_BUF,"@INIT#") != 0x00000000)
		{
				MOTOR_RUN_SPEED(1,50,1,0);
				MOTOR_RUN_SPEED(2,50,1,0);
				MOTOR_RUN_SPEED(3,50,1,0);
				MOTOR_RUN_SPEED(4,50,1,0);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				MOTOR_STOP(1); 
				MOTOR_STOP(2); 
				MOTOR_STOP(3);
			MOTOR_STOP(4); 	
				motor1_qep_new= TIM_GetCounter(TIM2); 
				motor2_qep_new= TIM_GetCounter(TIM3); 
				motor3_qep_new= TIM_GetCounter(TIM4); 
				motor4_qep_new= TIM_GetCounter(TIM5); 
			
				if(motor1_qep_new>motor2_qep_new)
				{
				   motor1_pwm_div = (float) motor1_qep_new/ motor2_qep_new;
				}
			  if(motor1_qep_new<motor2_qep_new)
				{
				   motor2_pwm_div = (float)  motor2_qep_new /motor1_qep_new;
				}
				if(motor3_qep_new>motor4_qep_new)
				{
				   motor3_pwm_div = (float)  motor3_qep_new/ motor4_qep_new;
				}
			  if(motor3_qep_new<motor4_qep_new)
				{
				   motor4_pwm_div = (float)  motor4_qep_new /motor3_qep_new;
				}
				command_success = 1;
		}
}	
void   motor_round_debug2()
{
		if(strstr((const char *)USART_RX_BUF,"@ROUND2#") != 0x00000000)
		{
			
			
				MOTOR_RUN_SPEED(1,50,0,500);
				MOTOR_RUN_SPEED(2,50,0,500);
				MOTOR_RUN_SPEED(3,50,0,500);
				MOTOR_RUN_SPEED(4,50,0,500);
				command_success = 1;
		}
}
void   motor_round_debug1()
{
		if(strstr((const char *)USART_RX_BUF,"@ROUND1#") != 0x00000000)
		{
				MOTOR_RUN_SPEED(1,50,1,1600);
				MOTOR_RUN_SPEED(2,50,1,1600);
				MOTOR_RUN_SPEED(3,50,1,1600);
				MOTOR_RUN_SPEED(4,50,1,1600);
				command_success = 1;
		}
}
void   motor_stop_debug()
{
		if(strstr((const char *)USART_RX_BUF,"@STOP#") != 0x00000000)
		{
				MOTOR_STOP(1); 
				MOTOR_STOP(2); 
				MOTOR_STOP(3);
				MOTOR_STOP(4); 	
				command_success = 1;
		}
}	
void   pid_debug()
{
	char *sp;

		if(strstr((const char *)USART_RX_BUF,"@PID") != 0x00000000)
		{
		sp =	strstr((const char *)USART_RX_BUF,"@PID");
		Target_velocity4 =atoi(sp+4);
			
			
		}
}	
void   motor_code_debug()
{
		u8  U2TxBuff[50] ={0};
		u16 j = 0;
		u8  t = 0;
		if(strstr((const char *)USART_RX_BUF,"@CODE#") != 0x00000000)
		{
			j   = TIM_GetCounter(TIM2);     
		U2TxBuff[0]='C'; U2TxBuff[1]='O'; U2TxBuff[2]='D';		
		U2TxBuff[3]='E'; U2TxBuff[4]='1'; U2TxBuff[5]='(';
	  U2TxBuff[6]=j/10000+'0';	j=j%10000; U2TxBuff[7]=j/1000+'0'; j=j%1000; U2TxBuff[8]=j/100+'0';	j=j%100;
	  U2TxBuff[9]=j/10+'0';	j=j%10; U2TxBuff[10]=j/1+'0'; U2TxBuff[11]=')';	U2TxBuff[12]='\r';U2TxBuff[13]='\n';		
		for(t=0;t<14;t++)
			{
				USART_SendData(USART2, U2TxBuff[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
			}
				j   = TIM_GetCounter(TIM3);     
			U2TxBuff[0]='C'; U2TxBuff[1]='O'; U2TxBuff[2]='D';		
		U2TxBuff[3]='E'; U2TxBuff[4]='2'; U2TxBuff[5]='(';
	  U2TxBuff[6]=j/10000+'0';	j=j%10000; U2TxBuff[7]=j/1000+'0'; j=j%1000; U2TxBuff[8]=j/100+'0';	j=j%100;
	  U2TxBuff[9]=j/10+'0';	j=j%10; U2TxBuff[10]=j/1+'0'; U2TxBuff[11]=')';	U2TxBuff[12]='\r';U2TxBuff[13]='\n';		
		for(t=0;t<14;t++)
			{
				USART_SendData(USART2, U2TxBuff[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
			}
				j   = TIM_GetCounter(TIM4);     
			U2TxBuff[0]='C'; U2TxBuff[1]='O'; U2TxBuff[2]='D';		
		U2TxBuff[3]='E'; U2TxBuff[4]='3'; U2TxBuff[5]='(';
	  U2TxBuff[6]=j/10000+'0';	j=j%10000; U2TxBuff[7]=j/1000+'0'; j=j%1000; U2TxBuff[8]=j/100+'0';	j=j%100;
	  U2TxBuff[9]=j/10+'0';	j=j%10; U2TxBuff[10]=j/1+'0'; U2TxBuff[11]=')';	U2TxBuff[12]='\r';U2TxBuff[13]='\n';		
		for(t=0;t<14;t++)
			{
				USART_SendData(USART2, U2TxBuff[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
			}
				j   = TIM_GetCounter(TIM5);     
		U2TxBuff[0]='C'; U2TxBuff[1]='O'; U2TxBuff[2]='D';		
		U2TxBuff[3]='E'; U2TxBuff[4]='4'; U2TxBuff[5]='(';
	  U2TxBuff[6]=j/10000+'0';	j=j%10000; U2TxBuff[7]=j/1000+'0'; j=j%1000; U2TxBuff[8]=j/100+'0';	j=j%100;
	  U2TxBuff[9]=j/10+'0';	j=j%10; U2TxBuff[10]=j/1+'0'; U2TxBuff[11]=')';	U2TxBuff[12]='\r';U2TxBuff[13]='\n';		
		for(t=0;t<14;t++)
			{
				USART_SendData(USART2, U2TxBuff[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
			}
				command_success = 1;
		}
}	