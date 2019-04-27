#include "control.h"	
#include "motor.h"
#include "led.h"
extern int KDshu;//µãµç»úÒª×ªµÄÈ¦Êı/11
extern u16 motor_pwm1;
int pi_motor_next_enc1 = 0;   //piµ÷ËÙÓÃÀ´¼ÆËãµÄÉÏÒ»´Î±àÂëÆ÷Öµ
int pi_motor_next_enc2 = 0;
int pi_motor_next_enc3 = 0;
int pi_motor_next_enc4 = 0;

int pi_motor_new_enc1 = 0;   //piµ÷ËÙÓÃÀ´¼ÆËãµÄÉÏÒ»´Î±àÂëÆ÷Öµ
int pi_motor_new_enc2 = 0;
int pi_motor_new_enc3 = 0;
int pi_motor_new_enc4 = 0;

int Target_velocity1	= 50;  //Éè¶¨ËÙ¶È¿ØÖÆµÄÄ¿±êËÙ¶ÈÎª50¸öÂö³åÃ¿10ms
int Target_velocity2	= 50;  //Éè¶¨ËÙ¶È¿ØÖÆµÄÄ¿±êËÙ¶ÈÎª50¸öÂö³åÃ¿10ms
int Target_velocity3	= 50;  //Éè¶¨ËÙ¶È¿ØÖÆµÄÄ¿±êËÙ¶ÈÎª50¸öÂö³åÃ¿10ms
int Target_velocity4	= 20;  //Éè¶¨ËÙ¶È¿ØÖÆµÄÄ¿±êËÙ¶ÈÎª50¸öÂö³åÃ¿10ms

int Pwm1 = 0;   //piµ÷ËÙÓÃÀ´¼ÆËãµÄÉÏÒ»´Î±àÂëÆ÷Öµ
int Pwm2 = 0;
int Pwm3 = 0;
int Pwm4 = 150;
int rnm  =0 ;
u16 t;
	float cs =0;
/************»ñµÃËÄÂ·±àÂëÆ÷µÄÂë×Ö²îÖµ*************/
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

void TIM6_IRQHandler(void)   //TIM3ÖĞ¶Ï
{	
	
	
	u16  j=0;

	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //¼ì²éTIM3¸üĞÂÖĞ¶Ï·¢ÉúÓë·ñ
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //Çå³ıTIMx¸üĞÂÖĞ¶Ï±êÖ¾ 
			
			
			if(KDshu!=0)
				{
			
				if(TIM_GetCounter(TIM5)!=0)  j=TIM_GetCounter(TIM5);
					
					
				if(motor_pwm1<255)//ËµÃ÷ÄæÊ±Õë×ª
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
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
						USART_SendData(USART2,'n');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
						USART_SendData(USART2,'s');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
						USART_SendData(USART2,'h');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊ
						USART_SendData(USART2,'\r');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
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
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
						USART_SendData(USART2,'n');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
						USART_SendData(USART2,'s');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
						USART_SendData(USART2,'h');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊ
						USART_SendData(USART2,'\r');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
//						USART_SendData(USART2,'\n');

					}
					
					
					
					
				
				}
					
				
				

				
				
			
			}

			
			
			
			
			
			
			
			
			
			
			
			

		}
}



/**************************************************************************
º¯Êı¹¦ÄÜ£º¸³Öµ¸øPWM¼Ä´æÆ÷
Èë¿Ú²ÎÊı£ºPWM
·µ»Ø  Öµ£ºÎŞ
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
º¯Êı¹¦ÄÜ£ºÏŞÖÆPWM¸³Öµ 
Èë¿Ú²ÎÊı£ºÎŞ
·µ»Ø  Öµ£ºÎŞ
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=200;    //===PWMÂú·ùÊÇ7200 ÏŞÖÆÔÚ7100
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
º¯Êı¹¦ÄÜ£º¾ø¶ÔÖµº¯Êı
Èë¿Ú²ÎÊı£ºint
·µ»Ø  Öµ£ºunsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
º¯Êı¹¦ÄÜ£ºÔöÁ¿PI¿ØÖÆÆ÷
Èë¿Ú²ÎÊı£º±àÂëÆ÷²âÁ¿Öµ£¬Ä¿±êËÙ¶È
·µ»Ø  Öµ£ºµç»úPWM
¸ù¾İÔöÁ¿Ê½ÀëÉ¢PID¹«Ê½ 
pwm+=Kp[e£¨k£©-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)´ú±í±¾´ÎÆ«²î 
e(k-1)´ú±íÉÏÒ»´ÎµÄÆ«²î  ÒÔ´ËÀàÍÆ 
pwm´ú±íÔöÁ¿Êä³ö
ÔÚÎÒÃÇµÄËÙ¶È¿ØÖÆ±Õ»·ÏµÍ³ÀïÃæ£¬Ö»Ê¹ÓÃPI¿ØÖÆ
pwm+=Kp[e£¨k£©-e(k-1)]+Ki*e(k)
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
	 Bias1=pi_motor_new_enc1-Target_velocity1;                //¼ÆËãÆ«²î
	 Pwm1+=Kp1*(Bias1-Last_bias1)+Ki1*Bias1;   //ÔöÁ¿Ê½PI¿ØÖÆÆ÷
	 Last_bias1=Bias1;	                   //±£´æÉÏÒ»´ÎÆ«²î 
	
	 Bias2=pi_motor_new_enc2-Target_velocity2;                //¼ÆËãÆ«²î
	 Pwm2+=Kp2*(Bias2-Last_bias2)+Ki2*Bias2;   //ÔöÁ¿Ê½PI¿ØÖÆÆ÷
	 Last_bias2=Bias2;	                   //±£´æÉÏÒ»´ÎÆ«²î    
	
	 Bias3=pi_motor_new_enc3-Target_velocity3;                //¼ÆËãÆ«²î
	 Pwm3+=Kp3*(Bias3-Last_bias3)+Ki3*Bias3;   //ÔöÁ¿Ê½PI¿ØÖÆÆ÷
	 Last_bias3=Bias3;	                   //±£´æÉÏÒ»´ÎÆ«²î 
	
	 Bias4=pi_motor_new_enc4-Target_velocity4;                //¼ÆËãÆ«²î
		cs=		(float)Kp4*(Bias4-Last_bias4)+(float)Ki4*Bias4;
	rnm = (int)((float)Kp4*(Bias4-Last_bias4)+(float)Ki4*Bias4);
// Pwm4= (int)Pwm4+(int)((float)Kp4*(Bias4-Last_bias4)+(float)Ki4*Bias4);   //ÔöÁ¿Ê½PI¿ØÖÆÆ÷
Pwm4+=	rnm;
	Last_bias4=Bias4;	                   //±£´æÉÏÒ»´ÎÆ«²î 
	 
//	  U2TxBuff[0]=Pwm4/10000+'0';	Pwm4=Pwm4%10000; U2TxBuff[1]=Pwm4/1000+'0'; Pwm4=Pwm4%1000; U2TxBuff[2]=Pwm4/100+'0';	Pwm4=Pwm4%100;
//	  U2TxBuff[3]=Pwm4/10+'0';	U2TxBuff[4]=')';	U2TxBuff[5]='\r';U2TxBuff[6]='\n';		
//		for(t=0;t<7;t++)
//			{
//				USART_SendData(USART2, U2TxBuff[t]);//Ïò´®¿Ú1·¢ËÍÊı¾İ
//				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
//			}
	       
}
