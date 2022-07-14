#include "stm32f10x_it.h"
#include "Key.h"
/********************************************************************
*名    称:NVIC_Configration(void)
*功    能:中断分组函数，包含TIM1~4和USART1
*入口参数:无
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//定时器1优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;			//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//定时器2优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;				//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//定时器3优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;				//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//定时器4优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;				//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//定时器5优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;				//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//定时器6优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;				//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//定时器7优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;				//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//定时器8优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;			//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//串口优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//串口优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;			//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//串口优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;			//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//串口优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;			//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//串口优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//串口优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//串口优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//串口优先级分分组 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//指定的IRQ中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级别 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			//响应优先级别
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
}
/*******************************************************************************
名称：void TIM1_IRQHandler(void)
功能：定时器1的中断服务函数
入口参数：无
出口参数：无
说明：无
***********************************************************************************/
// unsigned short Timer1Counter;//定时器1的执行计数器
// extern unsigned char Beep;//音响效果的变量
// extern unsigned short SoundCounter;//蜂鸣器定时计数器

// void TIM1_UP_IRQHandler(void)
// {
// 	Timer1Counter++;
// 	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);					//清除中断标志
// 	
// 	BuzzerOut();
// 	
// 	
// 	if(Timer1Counter == 100) //100*10ms=1s
// 	{
// 		LED2Reverse();
// 		Timer1Counter=0;
// 	}
// }
/*******************************************************************************
名称：void TIM2_IRQHandler(void)
功能：定时器2的中断服务函数
入口参数：无
出口参数：无
说明：无
************************************************************************************/

unsigned short Timer2Counter=0;
unsigned char TranFlag=0;
extern unsigned char TXData[13];
void TIM2_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);					//清除中断标志
	Timer2Counter++;
// 	switch(GetKeyStatus())
// 	{
// 		case 1: Beep=5;break;
// 		case 2: Beep=6;break;
// 		case 3: Beep=3;break;
// 		case 4: Beep=4;break;
// 		default:break;
// 	}
	if(Timer2Counter==1)
	{
		Timer2Counter=0;
		TranFlag=1;
	}		
}
// /*******************************************************************************
// 名称：void TIM3_IRQHandler(void)
// 功能：定时器3的中断服务函数
// 入口参数：无
// 出口参数：无
// 说明：无
// ***********************************************************************************
// void TIM3_IRQHandler(void)
// {
// 	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);					//清除中断标志
// 	LED1Reverse();
// }*/
// /*******************************************************************************
// 名称：void TIM4_IRQHandler(void)
// 功能：定时器4的中断服务函数
// 入口参数：无
// 出口参数：无
// 说明：无
// ***********************************************************************************
// void TIM4_IRQHandler(void)
// {
// 	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);					//清除中断标志
// 	LED4Reverse();
// }*/
// /*******************************************************************************
// 名称：void TIM5_IRQHandler(void)
// 功能：定时器5的中断服务函数
// 入口参数：无
// 出口参数：无
// 说明：无
// ***********************************************************************************
// void TIM5_IRQHandler(void)
// {
// 	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);					//清除中断标志
// 	LED4Reverse();
// }*/
// /*******************************************************************************
// 名称：void TIM6_IRQHandler(void)
// 功能：定时器6的中断服务函数
// 入口参数：无
// 出口参数：无
// 说明：无
// ***********************************************************************************
// void TIM6_IRQHandler(void)
// {
// 	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);					//清除中断标志
// 	LED4Reverse();
// }*/
// /*******************************************************************************
// 名称：void TIM7_IRQHandler(void)
// 功能：定时器7的中断服务函数
// 入口参数：无
// 出口参数：无
// 说明：无
// ***********************************************************************************/
// void TIM7_IRQHandler(void)
// {
// 	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);					//清除中断标志
// 	LED4Reverse();
// }*/
// /*******************************************************************************
// 名称：void TIM8_IRQHandler(void)
// 功能：定时器8的中断服务函数
// 入口参数：无
// 出口参数：无
// 说明：无
// **********************************************************************************/
// void TIM8_UP_IRQHandler(void)
// {
// 	TIM_ClearITPendingBit(TIM8, TIM_IT_Update);					//清除中断标志
// 	LED4Reverse();
// }*/
// /*******************************************************************************
// 名称：void EXTI15_10_IRQHandler(void)
// 功能：外部中断10-15的中断服务函数
// 入口参数：无
// 出口参数：无
// 说明：无
// ***********************************************************************************/
// void EXTI15_10_IRQHandler(void)
// {
// 	if(EXTI_GetFlagStatus(EXTI_Line11))
// 	{
// 		EXTI_ClearITPendingBit(EXTI_Line11);							//清除EXTI11 标志
// 		LED4Reverse();
// 	}
// }
// */


/*******************************************************************************
名称：void USART1_IRQHandler(void)
功能：串口一的中断服务函数
入口参数：无
出口参数：无
说明：无
***********************************************************************************/

// unsigned char Usart1Data=0;
// unsigned char Usart1Status=0;
// unsigned char ShiWei=0;
// unsigned char GeWei=0;
// unsigned char ShiFenWei=0;
// float Temprature=0.0;
// void AdjustASCII(unsigned char ASCII_dat)
// {
// 	if((ASCII_dat<'0')||(ASCII_dat>0x7f))
// 		ASCII_dat='0';
// }

// void USART1_IRQHandler(void)
// {

// 	
// 	if(USART_GetITStatus(USART1,USART_IT_RXNE))			//判断终端来源是否为接收中断
// 	{
// 		USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清除中断标识位
// 		Usart1Data=USART_ReceiveData(USART1);			//读取串口一接收到的数据
// 		//USART_SendData(USART1,Usart1Data);					//将接收到的数据发送
// 		//while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);//等待数据发送完成
// 		switch(Usart1Status)
// 		{
// 			case 0:
// 				if(Usart1Data=='T')
// 				Usart1Status=1;
// 			break;
// 			case 1:
// 				AdjustASCII(Usart1Data);
// 				ShiWei=Usart1Data-'0';
// 				Usart1Status=2;
// 			break;
// 			case 2:
// 				AdjustASCII(Usart1Data);
// 				GeWei=Usart1Data-'0';
// 				Usart1Status=3;
// 			break;
// 			case 3:
// 				AdjustASCII(Usart1Data);
// 			if(Usart1Data=='.')
// 				Usart1Status=4;
// 			else
// 				Usart1Status=0;
// 			break;
// 			case 4:
// 				AdjustASCII(Usart1Data);
// 				ShiFenWei=Usart1Data-'0';
// 				Usart1Status=0;
// 			Temprature=ShiWei*10+GeWei+ShiFenWei*0.1;
// 			break;
// 			default:break;
// 		}
// 	}
// }






























































































































/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
