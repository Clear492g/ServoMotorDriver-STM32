#include "control.h"	
#include "motor.h"
#include "led.h"
extern int KDshu;//����Ҫת��Ȧ��/11
extern u16 motor_pwm1;
int pi_motor_next_enc1 = 0;   //pi���������������һ�α�����ֵ
int pi_motor_next_enc2 = 0;
int pi_motor_next_enc3 = 0;
int pi_motor_next_enc4 = 0;

int pi_motor_new_enc1 = 0;   //pi���������������һ�α�����ֵ
int pi_motor_new_enc2 = 0;
int pi_motor_new_enc3 = 0;
int pi_motor_new_enc4 = 0;

int Target_velocity1	= 50;  //�趨�ٶȿ��Ƶ�Ŀ���ٶ�Ϊ50������ÿ10ms
int Target_velocity2	= 50;  //�趨�ٶȿ��Ƶ�Ŀ���ٶ�Ϊ50������ÿ10ms
int Target_velocity3	= 50;  //�趨�ٶȿ��Ƶ�Ŀ���ٶ�Ϊ50������ÿ10ms
int Target_velocity4	= 20;  //�趨�ٶȿ��Ƶ�Ŀ���ٶ�Ϊ50������ÿ10ms

int Pwm1 = 0;   //pi���������������һ�α�����ֵ
int Pwm2 = 0;
int Pwm3 = 0;
int Pwm4 = 150;
int rnm  =0 ;
u16 t;
	float cs =0;
/************�����·�����������ֲ�ֵ*************/
void Read_Encoder_cha()
{
	int jj1,jj2,jj3,jj4;
			jj1   = TIM_GetCounter(TIM2); 
			jj2		= TIM_GetCounter(TIM3); 
			jj3 	= TIM_GetCounter(TIM4); 
			jj4 	= TIM_GetCounter(TIM5); 
			
			
	
			pi_motor_new_enc1  = jj1 - pi_motor_next_enc1;
			pi_motor_new_enc2  = jj2 - pi_motor_next_enc2;
			pi_motor_new_enc3  = jj3 - pi_motor_next_enc3;
//	if(jj4 - pi_motor_next_enc4<0)
//	{
//		pi_motor_new_enc4  = jj4 - pi_motor_next_enc4+65535;
//	}
//	else
			pi_motor_new_enc4  = jj4 - pi_motor_next_enc4;
	
			pi_motor_next_enc1 = jj1;
			pi_motor_next_enc2 = jj2;
			pi_motor_next_enc3 = jj3;
			pi_motor_next_enc4 = jj4;

}

void TIM6_IRQHandler(void)   //TIM3�ж�
{	
	
	
	u16  j=0;

	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //���TIMx�����жϱ�־ 
			
			
			if(KDshu!=0)
				{
			
				if(TIM_GetCounter(TIM5)!=0)  j=TIM_GetCounter(TIM5);
					
					
				if(motor_pwm1<255)//˵����ʱ��ת
				{  if((j-0)>=KDshu)
					{
							MOTOR_STOP(1); 
							MOTOR_STOP(2);
						TIM_SetCounter(TIM2, 0);
						TIM_SetCounter(TIM3, 0);
						TIM_SetCounter(TIM4, 0);
						TIM_SetCounter(TIM5, 0);
							KDshu=0;
						
						
						if(USART_GetFlagStatus(USART2,USART_FLAG_TC)==SET)  USART_ClearFlag(USART2,USART_FLAG_TC);//
						USART_SendData(USART2,'f');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						USART_SendData(USART2,'n');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						USART_SendData(USART2,'s');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						USART_SendData(USART2,'h');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ��
						USART_SendData(USART2,'\r');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//						USART_SendData(USART2,'\n');
						
					}
					
					
					
					
					
					
					
					
				
				}
				 if(motor_pwm1>255)
				{  if(((11000-j)>=KDshu)&&(j!=0))
					{
							MOTOR_STOP(1); 
							MOTOR_STOP(2); 
						TIM_SetCounter(TIM2, 0);
						TIM_SetCounter(TIM3, 0);
						TIM_SetCounter(TIM4, 0);
						TIM_SetCounter(TIM5, 0);
							KDshu=0;
						
						
						if(USART_GetFlagStatus(USART2,USART_FLAG_TC)==SET)  USART_ClearFlag(USART2,USART_FLAG_TC);//
						USART_SendData(USART2,'f');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						USART_SendData(USART2,'n');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						USART_SendData(USART2,'s');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
						USART_SendData(USART2,'h');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ��
						USART_SendData(USART2,'\r');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//						USART_SendData(USART2,'\n');

					}
					
					
					
					
				
				}
					
				
				

				
				
			
			}

			
			
			
			
			
			
			
			
			
			
			
			

		}
}



/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ�����PWM
����  ֵ����
**************************************************************************/
void Set_Pwm()
{							
			if(Pwm1<0)		
			{
							TIM_SetCompare1(TIM8,0);
							TIM_SetCompare2(TIM8,(unsigned char)Pwm1);
			}
			else 
			{
							TIM_SetCompare1(TIM8,(unsigned char)Pwm1);
							TIM_SetCompare2(TIM8,0);
			}
			if(Pwm2<0)		
			{
							TIM_SetCompare3(TIM8,0);
							TIM_SetCompare4(TIM8,(unsigned char)Pwm2);
			}
			else 
			{
							TIM_SetCompare3(TIM8,(unsigned char)Pwm2);
							TIM_SetCompare4(TIM8,0);
			}
			if(Pwm1<0)		
			{
							TIM_SetCompare1(TIM1,0);
							TIM_SetCompare2(TIM1,(unsigned char)Pwm3);
			}
			else 
			{
							TIM_SetCompare1(TIM1,(unsigned char)Pwm3);
							TIM_SetCompare2(TIM1,0);
			}
			if(Pwm1<0)		
			{
							TIM_SetCompare3(TIM1,0);
							TIM_SetCompare4(TIM1,(unsigned char)Pwm4);
			}
			else 
			{
							TIM_SetCompare3(TIM1,(unsigned char)Pwm4);
							TIM_SetCompare4(TIM1,0);
			}

}

/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=200;    //===PWM������7200 ������7100
    if(Pwm1<-Amplitude) Pwm1=-Amplitude;	
		if(Pwm1>Amplitude)  Pwm1=Amplitude;	
	  if(Pwm2<-Amplitude) Pwm2=-Amplitude;	
		if(Pwm2>Amplitude)  Pwm2=Amplitude;	
	  if(Pwm3<-Amplitude) Pwm3=-Amplitude;	
		if(Pwm3>Amplitude)  Pwm3=Amplitude;	
	  if(Pwm4<-Amplitude) Pwm4=-Amplitude;	
		if(Pwm4>Amplitude)  Pwm4=Amplitude;	
}

/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
void Incremental_PI ()
{ 	
   float Kp1=100,Ki1=100;	
	 float Kp2=100,Ki2=100;	
	 float Kp3=100,Ki3=100;	
	 float Kp4=0.5,Ki4=0.01;	

	 static int Bias1,Pwm1,Last_bias1;
	 static int Bias2,Pwm2,Last_bias2;
	 static int Bias3,Pwm3,Last_bias3;
	 static int Bias4,Last_bias4;
	u8  U2TxBuff[50] ={0};
	 Bias1=pi_motor_new_enc1-Target_velocity1;                //����ƫ��
	 Pwm1+=Kp1*(Bias1-Last_bias1)+Ki1*Bias1;   //����ʽPI������
	 Last_bias1=Bias1;	                   //������һ��ƫ�� 
	
	 Bias2=pi_motor_new_enc2-Target_velocity2;                //����ƫ��
	 Pwm2+=Kp2*(Bias2-Last_bias2)+Ki2*Bias2;   //����ʽPI������
	 Last_bias2=Bias2;	                   //������һ��ƫ��    
	
	 Bias3=pi_motor_new_enc3-Target_velocity3;                //����ƫ��
	 Pwm3+=Kp3*(Bias3-Last_bias3)+Ki3*Bias3;   //����ʽPI������
	 Last_bias3=Bias3;	                   //������һ��ƫ�� 
	
	 Bias4=pi_motor_new_enc4-Target_velocity4;                //����ƫ��
		cs=		(float)Kp4*(Bias4-Last_bias4)+(float)Ki4*Bias4;
	rnm = (int)((float)Kp4*(Bias4-Last_bias4)+(float)Ki4*Bias4);
// Pwm4= (int)Pwm4+(int)((float)Kp4*(Bias4-Last_bias4)+(float)Ki4*Bias4);   //����ʽPI������
Pwm4+=	rnm;
	Last_bias4=Bias4;	                   //������һ��ƫ�� 
	 
//	  U2TxBuff[0]=Pwm4/10000+'0';	Pwm4=Pwm4%10000; U2TxBuff[1]=Pwm4/1000+'0'; Pwm4=Pwm4%1000; U2TxBuff[2]=Pwm4/100+'0';	Pwm4=Pwm4%100;
//	  U2TxBuff[3]=Pwm4/10+'0';	U2TxBuff[4]=')';	U2TxBuff[5]='\r';U2TxBuff[6]='\n';		
//		for(t=0;t<7;t++)
//			{
//				USART_SendData(USART2, U2TxBuff[t]);//�򴮿�1��������
//				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//			}
	       
}
