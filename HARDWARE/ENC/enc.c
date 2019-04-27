#include "enc.h"
//每转1外圈增加11
void ENC2_Init(void)                               // PA15---TIM2-1; PB3---TIM2-2 
{ 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct; 
  TIM_ICInitTypeDef TIM_ICInitStruct;  
  GPIO_InitTypeDef GPIO_InitStruct; 
        
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  |  RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);// enable SWD not JTAG
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);          // GPIO_PartialRemap1_TIM2/GPIO_PartialRemap2_TIM2/GPIO_FullRemap_TIM2                         
  GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);      // GPIO_PartialRemap1_TIM2/GPIO_PartialRemap2_TIM2/GPIO_FullRemap_TIM2
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;  
  GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStruct);         
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3; 
  GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IPU;
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //??JTAG,SWD????? 
  GPIO_Init(GPIOB, &GPIO_InitStruct); 
    
  TIM_DeInit(TIM2);  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);   
  TIM_TimeBaseStruct.TIM_Prescaler =650*2-1;          
  TIM_TimeBaseStruct.TIM_Period = 1000*11;   
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;      // TIM_CKD_DIV1/TIM_CKD_DIV2/TIM_CKD_DIV4
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;    
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct); 
    
  // TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);	
  TIM_ICStructInit(&TIM_ICInitStruct);        
  TIM_ICInitStruct.TIM_ICFilter = 5; 
  TIM_ICInit(TIM2, &TIM_ICInitStruct); 
  TIM_ClearFlag(TIM2,TIM_IT_Update);
  // TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);       
  TIM_Cmd(TIM2, ENABLE);  
  TIM_SetCounter(TIM2, 0);
}

void ENC3_Init(void)                               // PB4---TIM3-1; PB5---TIM3-2                        
{ 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct; 
  TIM_ICInitTypeDef TIM_ICInitStruct;  
  GPIO_InitTypeDef GPIO_InitStruct;
        
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3 ,ENABLE);                          
  GPIO_StructInit(&GPIO_InitStruct);        
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; 
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStruct); 
    
  TIM_DeInit(TIM3);  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);    
  TIM_TimeBaseStruct.TIM_Prescaler =650*2-1;          
  TIM_TimeBaseStruct.TIM_Period = 1000*11;   
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;      // TIM_CKD_DIV1/TIM_CKD_DIV2/TIM_CKD_DIV4
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;    
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct); 
    
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
  TIM_ICStructInit(&TIM_ICInitStruct);        
  TIM_ICInitStruct.TIM_ICFilter = 5; 
  TIM_ICInit(TIM3, &TIM_ICInitStruct); 
  TIM_ClearFlag(TIM3,TIM_IT_Update);
  // TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 
  TIM_Cmd(TIM3,ENABLE);  
  TIM_SetCounter(TIM3,0);
} 

void ENC4_Init(void)                               // PB6---TIM4-1; PB7---TIM4-2  
{ 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct; 
  TIM_ICInitTypeDef TIM_ICInitStruct;  
  GPIO_InitTypeDef GPIO_InitStruct; 
        
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStruct); 
    
  TIM_DeInit(TIM4);  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);    
  TIM_TimeBaseStruct.TIM_Prescaler =650*2-1;          
  TIM_TimeBaseStruct.TIM_Period = 1000*11;   
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;      // TIM_CKD_DIV1/TIM_CKD_DIV2/TIM_CKD_DIV4 
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;    
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStruct); 
    
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
  TIM_ICStructInit(&TIM_ICInitStruct);        
  TIM_ICInitStruct.TIM_ICFilter = 5; 
  TIM_ICInit(TIM4, &TIM_ICInitStruct); 
  TIM_ClearFlag(TIM4,TIM_IT_Update);
  // TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); 
  TIM_Cmd(TIM4, ENABLE);  
  TIM_SetCounter(TIM4, 0);
}

void ENC5_Init(void)                               // PA0---TIM5-1; PA1---TIM5-2  
{ 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct; 
  TIM_ICInitTypeDef TIM_ICInitStruct;  
  GPIO_InitTypeDef GPIO_InitStruct; 
        
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);   
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);       
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStruct); 
    
  TIM_DeInit(TIM5);  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);  
  TIM_TimeBaseStruct.TIM_Prescaler =650*2-1;          
  TIM_TimeBaseStruct.TIM_Period = 1000*11;   
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;      // TIM_CKD_DIV1/TIM_CKD_DIV2/TIM_CKD_DIV4	
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;    
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStruct); 
    
  TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
  TIM_ICStructInit(&TIM_ICInitStruct);        
  TIM_ICInitStruct.TIM_ICFilter = 5; 
  TIM_ICInit(TIM5, &TIM_ICInitStruct); 
  TIM_ClearFlag(TIM5,TIM_IT_Update);
  // TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); 
  TIM_Cmd(TIM5, ENABLE);  
  TIM_SetCounter(TIM5, 0);
}

 
