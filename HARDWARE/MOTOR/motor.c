#include "motor.h"
#include "sys.h"
#include "timer.h"
#include "motor_config.h"

u8  volatile motor_round_flag1 = 0;   //�����ת�̶�Ȧ����־λ1
u8  volatile motor_round_flag2 = 0;
u8  volatile motor_round_flag3 = 0;
u8  volatile motor_round_flag4 = 0;

extern float motor1_pwm_div ;
extern float motor2_pwm_div ;
extern float motor3_pwm_div ;
extern float motor4_pwm_div ;
u8 motor_dir_flag1 = 0;     //�����ת�����־λ1
u8 motor_dir_flag2 = 0;
u8 motor_dir_flag3 = 0;
u8 motor_dir_flag4 = 0;

u16 motor1_qep_last;				//X�ŵ����Ӧ�������ٿ�ʼ��Ȧ��תʱ�ĳ�ʼ����ֵ
u16 motor2_qep_last;
u16 motor3_qep_last;
u16 motor4_qep_last;

int motor1_round = 0;       //X�ŵ����Ŀ����תȦ������Ϊ��ת����Ϊ��ת������һ����תδ����ʱ���µ�Ŀ��Ȧ����ǿ�ƽ�����֮ǰδ��ɵĶ�����
int motor2_round = 0;
int motor3_round = 0;
int motor4_round = 0;

unsigned char M1XW1_STA=0x00,M1XW2_STA=0x00,M2XW1_STA=0x00,M2XW2_STA=0x00,M3XW1_STA=0x00,M3XW2_STA=0x00,M4XW1_STA=0x00,M4XW2_STA=0x00;
unsigned char M1DIR=0,M2DIR=0,M3DIR=0,M4DIR=0;       
void MOTOR_EN_Init(void)
{
		 GPIO_InitTypeDef  GPIO_InitStructure;
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
			
		 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PB.5 �˿�����
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
		 GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);						 //PB.5 �����

}
void TIM1_PWM_Init(u32 arr,u32 psc)        // PA8---TIM1-1; PA9---TIM1-2; PA10---TIM1-3; PA11---TIM1-4; PA12---TIM1-ETR
{		 					 
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  
  // GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1 ,ENABLE);   // PA8---TIM1-1; PA7---TIM1-1N
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;      	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           // PB13---TIM1-1N; PB14---TIM1-2N; PB15---TIM1-3N    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    
  // GPIO_Init(GPIOB,&GPIO_InitStructure);   	
	
  TIM_TimeBaseStructure.TIM_Prescaler=psc;  
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_CenterAligned1;  // TIM_CounterMode_Up/TIM_CounterMode_Down/TIM_CounterMode_CenterAligned(1~3)
  TIM_TimeBaseStructure.TIM_Period=arr;   
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure); 
        
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; 
  TIM_OCInitStructure.TIM_Pulse = psc;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;            // TIM_OCPolarity_High/TIM_OCPolarity_Low
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;           // TIM_OCPolarity_High/TIM_OCPolarity_Low
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;           // TIM_OCNIdleState_Set
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;       // TIM_OCNIdleState_Reset 
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure.TIM_DeadTime = 0x00; 
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
  TIM_ARRPreloadConfig(TIM1,ENABLE);
  TIM_Cmd(TIM1, ENABLE);
  // TIM_SetCompare1(TIM1,720); TIM_SetCompare2(TIM1,720);                // MOTOR1
  // TIM_SetCompare3(TIM1,720); TIM_SetCompare4(TIM1,720);                // MOTOR2
  TIM_CtrlPWMOutputs(TIM1, ENABLE);       									  
}

void TIM8_PWM_Init(u32 arr,u32 psc)        // PC6---TIM8-1; PA7---TIM8-1N; PC7---TIM8-2; PB0---TIM8-2N; PC8---TIM8-3; PB1---TIM8-3N
{		 					 
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
     
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE);  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;          
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    
  // GPIO_Init(GPIOA,&GPIO_InitStructure); 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;          
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    
  // GPIO_Init(GPIOB,&GPIO_InitStructure); 
        
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;          
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    
  GPIO_Init(GPIOC,&GPIO_InitStructure);     
         
  TIM_TimeBaseStructure.TIM_Prescaler=psc;  
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_CenterAligned1;  // TIM_CounterMode_Up/TIM_CounterMode_Down/TIM_CounterMode_CenterAligned(1~3)
  TIM_TimeBaseStructure.TIM_Period=arr;   
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
  TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure); 
        
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; 
  TIM_OCInitStructure.TIM_Pulse = psc;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;        // TIM_OCPolarity_High/TIM_OCPolarity_Low
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;       // TIM_OCPolarity_High/TIM_OCPolarity_Low
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;       // TIM_OCNIdleState_Set
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;   // TIM_OCNIdleState_Reset      
  TIM_OC1Init(TIM8, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM8, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
  TIM_OC3Init(TIM8, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
  TIM_OC4Init(TIM8, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  //TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure.TIM_DeadTime = 0x00; 
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);

  TIM_ARRPreloadConfig(TIM8,ENABLE);
  TIM_Cmd(TIM8, ENABLE);
  // TIM_SetCompare1(TIM8,720); TIM_SetCompare2(TIM8,720);          // MOTOR3
  // TIM_SetCompare3(TIM8,720); TIM_SetCompare4(TIM8,720);          // MOTOR4
  TIM_CtrlPWMOutputs(TIM8, ENABLE);           
}
/*************************��������**********************************/
/*��ʽ���� 1 �����ŵ����1��2��3��4�� 2 �� ����ٶ�  3 �� �������  4�� ���Ȧ�� */
void MOTOR_RUN_SPEED(unsigned char motor_num,unsigned char motor_speed,unsigned char motor_dir,int motor_round)
{
	u16 test =0;
		test= (unsigned char)(motor_speed/motor1_pwm_div);
		test= (unsigned char)(motor_speed/motor2_pwm_div);
		test= (unsigned char)(motor_speed/motor3_pwm_div);
		test= (unsigned char)(motor_speed/motor4_pwm_div);
	if(motor_dir ==1)
	{
					if(motor_num==1)
					{
							TIM_SetCompare1(TIM8,(unsigned char)(motor_speed/motor1_pwm_div));
							TIM_SetCompare2(TIM8,0);
							if(motor_round != 0)			//���Ҫ����Ȧ��
							{
									motor_dir_flag1 =1;
									motor1_qep_last= TIM_GetCounter(TIM2); 
									motor1_round =	motor_round;		
									motor_round_flag1 =1;								
							}
					}
					else if(motor_num==2)
					{
							TIM_SetCompare3(TIM8,(unsigned char)(motor_speed/motor2_pwm_div));
							TIM_SetCompare4(TIM8,0);
							if(motor_round != 0)
							{
									motor_dir_flag2 =1;
									motor2_qep_last= TIM_GetCounter(TIM3);  
									motor2_round = motor2_round	+	motor_round;	
									motor_round_flag2 =1;								
							}
					}
					else if(motor_num== 3)
					{
							TIM_SetCompare1(TIM1,(unsigned char)(motor_speed/motor3_pwm_div));
							TIM_SetCompare2(TIM1,0);
							if(motor_round != 0)
								{
										motor_dir_flag3 =1;
								  	motor3_qep_last= TIM_GetCounter(TIM4); 
										motor3_round = motor3_round	+	motor_round;
										motor_round_flag3 =1;									
								}
					}
					else if(motor_num== 4)
					{
							TIM_SetCompare3(TIM1,(unsigned char)(motor_speed/motor4_pwm_div));
							TIM_SetCompare4(TIM1,0);
							if(motor_round != 0)
							{
									motor_dir_flag4 =1;
									motor4_qep_last= TIM_GetCounter(TIM5);  
									motor4_round = motor4_round	+	motor_round;	
									motor_round_flag4 =1;									
							}
					}
	}
	else if(motor_dir ==0)
	{
					if(motor_num==1)
					{
							TIM_SetCompare1(TIM8,0);
							TIM_SetCompare2(TIM8,(unsigned char)(motor_speed/motor1_pwm_div));
							if(motor_round != 0)
							{
									motor_dir_flag1 =0;
									motor1_qep_last= TIM_GetCounter(TIM2);  
									motor1_round = motor1_round	-	motor_round;	
									motor_round_flag1 =1;								
							}
					}
					else if(motor_num==2)
					{
							TIM_SetCompare3(TIM8,0);
							TIM_SetCompare4(TIM8,(unsigned char)(motor_speed/motor2_pwm_div));
							if(motor_round != 0)
							{
									motor_dir_flag2 =0;
									motor2_qep_last= TIM_GetCounter(TIM3);
									motor2_round = motor2_round	-	motor_round;	
									motor_round_flag2 =1;								
							}
					}
					else if(motor_num== 3)
					{
							TIM_SetCompare1(TIM1,0);
							TIM_SetCompare2(TIM1,(unsigned char)(motor_speed/motor3_pwm_div));
							if(motor_round != 0)
							{
									motor_dir_flag3 =0;
									motor3_qep_last= TIM_GetCounter(TIM4);  
									motor3_round = motor3_round	-	motor_round;
									motor_round_flag3 =1;
							}
					}
					else if(motor_num== 4)
					{
							TIM_SetCompare3(TIM1,0);
							TIM_SetCompare4(TIM1,(unsigned char)(motor_speed/motor4_pwm_div));
							if(motor_round != 0)
							{
									motor_dir_flag4 =0;
									motor4_qep_last= TIM_GetCounter(TIM5);
									motor4_round = motor4_round	-	motor_round;	
									motor_round_flag4 =1;								
							}
					}
	}
}
/*******************��������*******************/
 /**********��Ŀ����ֹͣ************/
void MOTOR_STOP(unsigned char motor_num)                                           // per=[0,100] 
{
				if(motor_num==1)
				{
						TIM_SetCompare1(TIM8,0);
						TIM_SetCompare2(TIM8,0);
						motor_round_flag1 = 0; 
					 motor_dir_flag1 = 0;
					motor1_round = 0;     
				}
				else if(motor_num==2)
				{
						TIM_SetCompare3(TIM8,0);
						TIM_SetCompare4(TIM8,0);
					motor_round_flag2 = 0; 
					 motor_dir_flag2 = 0;
					motor2_round = 0;     
				}
				else if(motor_num== 3)
				{
						TIM_SetCompare1(TIM1,0);
						TIM_SetCompare2(TIM1,0);
					motor_round_flag3 = 0; 
					 motor_dir_flag3 = 0;
					motor3_round = 0;     
				}
				else if(motor_num== 4)
				{
						TIM_SetCompare3(TIM1,0);
						TIM_SetCompare4(TIM1,0);
					motor_round_flag4 = 0; 
					 motor_dir_flag4 = 0;
					motor4_round = 0;     
				}
		
}
/*******************��������*******************/
 /**********���ϼ�⵱ǰ�Ƿ�Ϊ�̶�Ȧ��ģʽ�������Ƿ񵽴�Ŀ��Ȧ************/
void MOTOR_CODE()                                   
{
			u16 motor1_qep_new;			//X�ŵ����Ӧ����ֵ
			u16 motor2_qep_new;
			u16 motor3_qep_new;
			u16 motor4_qep_new;
		
				if(motor_round_flag1 == 1)
				{
							motor1_qep_new= TIM_GetCounter(TIM2);  
							if(motor_dir_flag1 == 1)    //�������ת������������
							{	
								
									if(motor1_qep_new-motor1_qep_last>=motor1_round*MOTOR_DIV)   //����Ԥ��λ
									{
													MOTOR_STOP(1);
													motor_round_flag1 =	0;		
													motor1_round = 0;										
									}
									else if(motor1_qep_new-motor1_qep_last<0)                //�߽�ֵ����
									{
											if(motor1_qep_new-motor1_qep_last+65535>=motor1_round*MOTOR_DIV)   //����Ԥ��λ
											{
													MOTOR_STOP(1);	
													motor_round_flag1 =	0;	
													motor1_round = 0;
											}
									}
							}
				else if(motor_dir_flag1 == 0)    //����Ƿ�ת������������
							{
									
									if(motor1_qep_last-motor1_qep_new>=(-motor1_round*MOTOR_DIV))   //����Ԥ��λ
									{
													MOTOR_STOP(1);
													motor_round_flag1 =	0;	
													motor1_round = 0;
								
									}
									else if(motor1_qep_last-motor1_qep_new<0)                //�߽�ֵ����
									{
											if(motor1_qep_last-motor1_qep_new+65535>=(-motor1_round*MOTOR_DIV))  //����Ԥ��λ
											{
													MOTOR_STOP(1);	
													motor_round_flag1 =	0;	
													motor1_round = 0;
											}
									}
							}
							
				}
				
				if(motor_round_flag2 == 1)
				{
							motor2_qep_new= TIM_GetCounter(TIM3);  
							if(motor_dir_flag2 == 1)    //�������ת������������
							{	
								
									if(motor2_qep_new-motor2_qep_last>=motor2_round*MOTOR_DIV)   //����Ԥ��λ
									{
													MOTOR_STOP(2);
													motor_round_flag2 =	0;		
													motor2_round = 0;										
									}
									else if(motor2_qep_new-motor2_qep_last<0)                //�߽�ֵ����
									{
											if(motor2_qep_new-motor2_qep_last+65535>=motor2_round*MOTOR_DIV)   //����Ԥ��λ
											{
													MOTOR_STOP(2);	
													motor_round_flag2 =	0;	
													motor2_round = 0;
											}
									}
							}
				else if(motor_dir_flag2 == 0)    //����Ƿ�ת������������
							{
									
									if(motor2_qep_last-motor2_qep_new>=(-motor2_round*MOTOR_DIV))   //����Ԥ��λ
									{
													MOTOR_STOP(2);
													motor_round_flag2 =	0;	
													motor2_round = 0;
								
									}
									else if(motor2_qep_last-motor2_qep_new<0)                //�߽�ֵ����
									{
											if(motor2_qep_last-motor2_qep_new+65535>=(-motor2_round*MOTOR_DIV))  //����Ԥ��λ
											{
													MOTOR_STOP(2);	
													motor_round_flag2 =	0;	
													motor2_round = 0;
											}
									}
							}
							
				}
				
				if(motor_round_flag3 == 1)
				{
							motor3_qep_new= TIM_GetCounter(TIM4);  
							if(motor_dir_flag3 == 1)    //�������ת������������
							{	
								
									if(motor3_qep_new-motor3_qep_last>=motor3_round*MOTOR_DIV)   //����Ԥ��λ
									{
													MOTOR_STOP(3);
													motor_round_flag3 =	0;		
													motor3_round = 0;										
									}
									else if(motor3_qep_new-motor3_qep_last<0)                //�߽�ֵ����
									{
											if(motor3_qep_new-motor3_qep_last+65535>=motor3_round*MOTOR_DIV)   //����Ԥ��λ
											{
													MOTOR_STOP(3);	
													motor_round_flag3 =	0;	
													motor3_round = 0;
											}
									}
							}
				else if(motor_dir_flag3 == 0)    //����Ƿ�ת������������
							{
									
									if(motor3_qep_last-motor3_qep_new>=(-motor3_round*MOTOR_DIV))   //����Ԥ��λ
									{
													MOTOR_STOP(3);
													motor_round_flag3 =	0;	
													motor3_round = 0;
								
									}
									else if(motor3_qep_last-motor3_qep_new<0)                //�߽�ֵ����
									{
											if(motor3_qep_last-motor3_qep_new+65535>=(-motor3_round*MOTOR_DIV))  //����Ԥ��λ
											{
													MOTOR_STOP(3);	
													motor_round_flag3 =	0;	
													motor3_round = 0;
											}
									}
							}
							
				}
				
				if(motor_round_flag4 == 1)
				{
							motor4_qep_new= TIM_GetCounter(TIM5);  
							if(motor_dir_flag4 == 1)    //�������ת������������
							{	
								
										if(motor4_qep_new-motor4_qep_last>=motor4_round*MOTOR_DIV)   //����Ԥ��λ
										{
														MOTOR_STOP(4);
														motor_round_flag4 =	0;		
														motor4_round = 0;										
										}
									else if(motor4_qep_new-motor4_qep_last<0)                //�߽�ֵ����
									{
											if(motor4_qep_new-motor4_qep_last+65535>=motor4_round*MOTOR_DIV)   //����Ԥ��λ
											{
													MOTOR_STOP(4);	
													motor_round_flag4 =	0;	
													motor4_round = 0;
											}
									}
							}
				else if(motor_dir_flag4 == 0)    //����Ƿ�ת������������
							{
									
									if(motor4_qep_last-motor4_qep_new>=(-motor4_round*MOTOR_DIV))   //����Ԥ��λ
									{
													MOTOR_STOP(4);
													motor_round_flag4 =	0;	
													motor4_round = 0;
								
									}
									else if(motor4_qep_last-motor4_qep_new<0)                //�߽�ֵ����
									{
											if(motor4_qep_last-motor4_qep_new+65535>=(-motor4_round*MOTOR_DIV))  //����Ԥ��λ
											{
													MOTOR_STOP(4);	
													motor_round_flag4  =	0;	
													motor4_round = 0;
											}
									}
							}			
				}		
}

 
