#include "PWM.h"
/*
TIM1:4通道PWM 
TIM2:4通道PWM 可端口复用（可完全映像）
TIM3:4通道PWM 可端口复用（可完全映像）
TIM4:4通道PWM 可端口复用
TIM5:4通道PWM 可端口复用(1个端口可复用)
TIM8:7通道PWM 
PWM输出通道配置 详见参考手册 8.3.7 定时器复用功能重映射

*/
/********************************************************************
*名    称:void PWM1Init(unsigned int Cycle)
*功    能:TIM1初始化函数 对分频系数和预装数据的设置
*入口参数:Cycle：PWM周期 最大值65536us
*出口参数:无
*说    明:无
*调用方法:不能与相应的定时器中断初始化函数同时调用
********************************************************************/
void PWM1Init(unsigned int Cycle)
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;				//定义定时器结构体
	TIM_OCInitTypeDef	TIM_OCInitStrue;						//定义比较输出结构体
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//开启APB2时钟 端口复用功能		
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);		//开启APB1时钟 定时器TIM1
	TIM_TimeBaseStructure.TIM_Period = Cycle;					//装载初值即周期值	
	TIM_TimeBaseStructure.TIM_Prescaler = (72-1); 				//定时器时钟的预分频数值 频率72m/72=1m
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00; 			//时钟分割，暂时用不到
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上模式 
	//TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, & TIM_TimeBaseStructure);
	
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        			//PWM模式1:CNT<CCR时输出有效
    TIM_OCInitStrue.TIM_OutputState = TIM_OutputState_Enable;	//正向通道有效
    TIM_OCInitStrue.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStrue.TIM_Pulse = Cycle/2;
	TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;			//设置极性-有效为高电平 两个选项定义输出高电平  
    TIM_OCInitStrue.TIM_OCNPolarity= TIM_OCNPolarity_High;	
    TIM_OCInitStrue.TIM_OCIdleState = TIM_OCIdleState_Set;	
    TIM_OCInitStrue.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM1,&TIM_OCInitStrue);        					//TIM1的通道1 PWM 模式设置
	TIM_OC2Init(TIM1,&TIM_OCInitStrue);        					//TIM1的通道2 PWM 模式设置
	TIM_OC3Init(TIM1,&TIM_OCInitStrue);        					//TIM1的通道3 PWM 模式设置
	TIM_OC4Init(TIM1,&TIM_OCInitStrue);        					//TIM1的通道4 PWM 模式设置
   
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道2开启
	//TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_Cmd(TIM1,ENABLE);        								//使能TIM1
		
}


/********************************************************************
*名    称:void PWM2Init(unsigned int Cycle)
*功    能:TIM2初始化函数 对分频系数和预装数据的设置
*入口参数:Cycle：PWM周期 最大值65536us
*出口参数:无
*说    明:无
*调用方法:不能与相应的定时器中断初始化函数同时调用
********************************************************************/
void PWM2Init(unsigned int Cycle)
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;				//定义定时器结构体
	TIM_OCInitTypeDef	TIM_OCInitStrue;						//定义比较输出结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//开启APB2时钟 端口复用功能		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		//开启APB1时钟 定时器TIM3
	TIM_TimeBaseStructure.TIM_Period = Cycle;					//装载初值即周期值	
	TIM_TimeBaseStructure.TIM_Prescaler = (72-1); 				//定时器时钟的预分频数值 频率72m/72=1m
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 				//时钟分割，暂时用不到
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上模式 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);
	
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        			//PWM模式1:CNT<CCR时输出有效
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;			//设置极性-有效为高电平 两个选项定义输出高电平
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;		//输出使能
    TIM_OC1Init(TIM2,&TIM_OCInitStrue);        					//TIM2的通道1 PWM 模式设置
	TIM_OC2Init(TIM2,&TIM_OCInitStrue);        					//TIM2的通道2 PWM 模式设置
	TIM_OC3Init(TIM2,&TIM_OCInitStrue);        					//TIM2的通道3 PWM 模式设置
	TIM_OC4Init(TIM2,&TIM_OCInitStrue);        					//TIM3的通道4 PWM 模式设置
    //TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道2开启
    TIM_Cmd(TIM2,ENABLE);        								//使能TIM3
}

/********************************************************************
*名    称:void PWM3Init(unsigned int Cycle)
*功    能:TIM3初始化函数 对分频系数和预装数据的设置
*入口参数:Cycle：PWM周期 最大值65536us
*出口参数:无
*说    明:无
*调用方法:不能与相应的定时器中断初始化函数同时调用
********************************************************************/
void PWM3Init(unsigned int Cycle)
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;				//定义定时器结构体
	TIM_OCInitTypeDef	TIM_OCInitStrue;						//定义比较输出结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//开启APB2时钟 端口复用功能		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		//开启APB1时钟 定时器TIM3
	TIM_TimeBaseStructure.TIM_Period = Cycle;					//装载初值即周期值	
	TIM_TimeBaseStructure.TIM_Prescaler = (72-1); 				//定时器时钟的预分频数值 频率72m/72=1m
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 				//时钟分割，暂时用不到
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上模式 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);
	
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        			//PWM模式1:CNT<CCR时输出有效
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;			//设置极性-有效为高电平 两个选项定义输出高电平
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;		//输出使能
    TIM_OC1Init(TIM3,&TIM_OCInitStrue);        					//TIM3的通道2 PWM 模式设置
	TIM_OC2Init(TIM3,&TIM_OCInitStrue);        					//TIM3的通道2 PWM 模式设置
	TIM_OC3Init(TIM3,&TIM_OCInitStrue);        					//TIM3的通道2 PWM 模式设置
	TIM_OC4Init(TIM3,&TIM_OCInitStrue);        					//TIM3的通道2 PWM 模式设置
    //TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道2开启
    TIM_Cmd(TIM3,ENABLE);        								//使能TIM3
}
/********************************************************************
*名    称:void PWM4Init(unsigned int Cycle)
*功    能:TIM4初始化函数 对分频系数和预装数据的设置
*入口参数:Cycle：PWM周期 最大值65536us
*出口参数:无
*说    明:无
*调用方法:不能与相应的定时器中断初始化函数同时调用
********************************************************************/
void PWM4Init(unsigned int Cycle)
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;				//定义定时器结构体
	TIM_OCInitTypeDef	TIM_OCInitStrue;						//定义比较输出结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//开启APB2时钟 端口复用功能		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);		//开启APB1时钟 定时器TIM4
	TIM_TimeBaseStructure.TIM_Period = Cycle;					//装载初值即周期值	
	TIM_TimeBaseStructure.TIM_Prescaler = (72-1); 				//定时器时钟的预分频数值 频率72m/72=1m
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 				//时钟分割，暂时用不到
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上模式 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, & TIM_TimeBaseStructure);
	
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        			//PWM模式1:CNT<CCR时输出有效
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;			//设置极性-有效为高电平 两个选项定义输出高电平
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;		//输出使能
    TIM_OC1Init(TIM4,&TIM_OCInitStrue);        					//TIM4的通道1 PWM 模式设置
	TIM_OC2Init(TIM4,&TIM_OCInitStrue);        					//TIM4的通道2 PWM 模式设置
	TIM_OC3Init(TIM4,&TIM_OCInitStrue);        					//TIM4的通道3 PWM 模式设置
	TIM_OC4Init(TIM4,&TIM_OCInitStrue);        					//TIM4的通道4 PWM 模式设置
    //TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道2开启
    TIM_Cmd(TIM4,ENABLE);        								//使能TIM4
}
/********************************************************************
*名    称:void PWM5Init(unsigned int Cycle)
*功    能:TIM5初始化函数 对分频系数和预装数据的设置
*入口参数:Cycle：PWM周期 最大值65536us
*出口参数:无
*说    明:无
*调用方法:不能与相应的定时器中断初始化函数同时调用
********************************************************************/
void PWM5Init(unsigned int Cycle)
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;				//定义定时器结构体
	TIM_OCInitTypeDef	TIM_OCInitStrue;						//定义比较输出结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//开启APB2时钟 端口复用功能		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);		//开启APB1时钟 定时器TIM5
	TIM_TimeBaseStructure.TIM_Period = Cycle;					//装载初值即周期值	
	TIM_TimeBaseStructure.TIM_Prescaler = (72-1); 				//定时器时钟的预分频数值 频率72m/72=1m
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 				//时钟分割，暂时用不到
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上模式 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM5, & TIM_TimeBaseStructure);
	
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        			//PWM模式1:CNT<CCR时输出有效
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;			//设置极性-有效为高电平 两个选项定义输出高电平
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;		//输出使能
    TIM_OC1Init(TIM5,&TIM_OCInitStrue);        					//TIM5的通道1 PWM 模式设置
	TIM_OC2Init(TIM5,&TIM_OCInitStrue);        					//TIM5的通道2 PWM 模式设置
	TIM_OC3Init(TIM5,&TIM_OCInitStrue);        					//TIM5的通道3 PWM 模式设置
	TIM_OC4Init(TIM5,&TIM_OCInitStrue);        					//TIM5的通道4 PWM 模式设置
    //TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道2开启
    TIM_Cmd(TIM5,ENABLE);        								//使能TIM4
}

/********************************************************************
*名    称:void PWM1IOInit(unsigned char CH,unsigned char remap)
*功    能:对PWm1的端口进行初始化 和重映射
*入口参数:CH：通道 1~4 remap：1~4 均为无重映像
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/
/*PWM1的四个通道的无复用设置				 	
CH1		PA8						
CH2		PA9							
CH3		PA10					
CH4		PA11						
*/
void PWM1IOInit(unsigned char CH,unsigned char remap)
{
	GPIO_InitTypeDef PWM_InitStructure;	
	switch(CH)
	{
		case 1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟	
			PWM_InitStructure.GPIO_Pin=GPIO_Pin_8;						//配置PA8端口
			PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
			PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
			GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
			TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道1开启
		break;
		case 2:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
			PWM_InitStructure.GPIO_Pin=GPIO_Pin_9;						//配置PA1端口
			PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
			PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
			GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
			TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道2开启
		break;
		case 3:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
			PWM_InitStructure.GPIO_Pin=GPIO_Pin_10;						//配置PA10端口
			PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
			PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
			GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
			TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道3开启
		break;
		case 4:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
			PWM_InitStructure.GPIO_Pin=GPIO_Pin_11;						//配置PA11端口
			PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
			PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
			GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
			TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道4开启
		break;	
		default:break;				
		}
}
/********************************************************************
*名    称:void PWM2IOInit(unsigned char CH,unsigned char remap)
*功    能:对PWm2的端口进行初始化 和重映射
*入口参数:CH：通道 1~4 remap：0~3 分别对应无重映像 部分重映像1  完全映像和部分重映像2
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/
/*PWM2的四个通道的复用设置
		未重映像0	部分重映像1	 	部分重映像3		完全映像2
CH1		PA0			PA15			PA0	 			PA15		
CH2		PA1			PB3				PA1 			PB3
CH3		PA2			PA2				PB10 			PB10
CH4		PA3			PA3				PB11 			PB11
*/
void PWM2IOInit(unsigned char CH,unsigned char remap)
{
	GPIO_InitTypeDef PWM_InitStructure;
	switch(remap)
	{
		case 0://未重映像	
			switch(CH)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟	
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_0;						//配置PA0端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道1开启
				break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_1;						//配置PA1端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道2开启
				break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_2;						//配置PA2端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道3开启
				break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_3;						//配置PA3端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道4开启
				break;	
				default:break;				
			}
			break;
		case 1://部分重映像1	
			GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
			GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); 			//jtag接口失能，sw有效，释放PB3 PA15	
			switch(CH)
			{		
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_15;						//配置PA15端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道1开启
				break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_3;						//配置PB3端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道2开启
				break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_2;						//配置PA2端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道3开启
				break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_3;						//配置PA3端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道4开启
				break;	
				default:break;				
			}
		break;
		case 2://全部重映像	
			GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);//端口全部重影像
			GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); 	//jtag接口失能，sw有效，释放PB3 PA15	
		switch(CH)
			{		
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOC模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_15;						//配置PA15端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道1开启
				break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_3;						//配置PB3端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道2开启
				break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_10;						//配置PB10端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道3开启
				break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_11;						//配置PB11端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道4开启
				break;	
				default:break;				
			}
		break;
			
		case 3://部分重映像2	
			GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);				//端口全部重影像
			switch(CH)
			{		
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_0;						//配置PA0端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道1开启
				break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_1;						//配置PA1端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道2开启
				break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_10;						//配置PB10端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道3开启
				break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_11;						//配置PB11端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道4开启
				break;	
				default:break;				
			}
		break;
		default:break;
	}
}
/********************************************************************
*名    称:void PWM3IOInit(unsigned char CH,unsigned char remap)
*功    能:对PWm3的端口进行初始化 和重映射
*入口参数:CH：通道 1~4 remap：0~2 分别对应无重映像 部分重映像 和完全映像
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/
/*PWM3的四个通道的复用设置
		未重映像0	部分重映像1	完全映像2
CH1		PA6			PB4			PC6			
CH2		PA7			PB5			PC7
CH3		PB0			PB0			PC8
CH4		PB1			PB1			PC9
*/
void PWM3IOInit(unsigned char CH,unsigned char remap)
{
	GPIO_InitTypeDef PWM_InitStructure;
	switch(remap)
	{
		case 0://未重映像	
			switch(CH)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟	
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_6;						//配置PA6端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道1开启
				break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_7;						//配置PA7端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道2开启
				break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_0;						//配置PB0端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道3开启
				break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_1;						//配置PB1端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道4开启
				break;	
				default:break;				
			}
			break;
		case 1://部分重映像	
			GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
			switch(CH)
			{		
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); 	//jtag接口失能，sw有效，释放PB4
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_4;						//配置PB4端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道1开启
				break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_5;						//配置PB5端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道2开启
				break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_0;						//配置PB0端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道3开启
				break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_1;						//配置PB1端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道4开启
				break;	
				default:break;				
			}
		break;
		case 2://全部重映像	
			GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);//端口全部重影像
			switch(CH)
			{		
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);		//开启GPIOC模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_6;						//配置PC6端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOC,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道1开启
				break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);		//开启GPIOC模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_7;						//配置PC7端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOC,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道2开启
				break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);		//开启GPIOC模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_8;						//配置PC8端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOC,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道3开启
				break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);		//开启GPIOC模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_9;						//配置PC9端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOC,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道4开启
				break;	
				default:break;				
			}
		break;
		default:break;
	}
}
/********************************************************************
*名    称:void PWM4IOInit(unsigned char CH,unsigned char remap)
*功    能:对PWm4的端口进行初始化 和重映射
*入口参数:CH：通道 1~4 remap：0~2 分别对应无重映像 部分重映像 和完全映像
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/
/*PWM4的四个通道的复用设置
		未重映像0	
CH1		PB6				
CH2		PB7			
CH3		PB8			
CH4		PB9			
*/
void PWM4IOInit(unsigned char CH,unsigned char remap)
{
	GPIO_InitTypeDef PWM_InitStructure;
	switch(remap)
	{
		case 0://未重映像
		case 1:
		case 2:
		case 3:	
			switch(CH)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟	
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_6;						//配置PB6端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道1开启
				break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_7;						//配置PB7端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道2开启
				break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_8;						//配置PB8端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道3开启
				break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//开启GPIOB模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_9;						//配置PB9端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOB,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道4开启
				break;	
				default:break;				
			}
			break;
		default:break;
	}
}


/********************************************************************
*名    称:void PWM5IOInit(unsigned char CH,unsigned char remap)
*功    能:对PWm5的端口进行初始化 和重映射
*入口参数:CH：通道 1~4 remap：0~2 分别对应无重映像 部分重映像 和完全映像
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/
/*PWM5的四个通道的复用设置
		未重映像0	
CH1		PA0				
CH2		PA1			
CH3		PA2			
CH4		PA3			
*/
void PWM5IOInit(unsigned char CH,unsigned char remap)
{
	GPIO_InitTypeDef PWM_InitStructure;
	switch(remap)
	{
		case 0://未重映像
		case 1:
		case 2:
		case 3:	
			switch(CH)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟	
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_0;						//配置PA0端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);        	//使能预装载寄存器 通道1开启
				break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_1;						//配置PA1端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道2开启
				break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_2;						//配置PA2端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC3PreloadConfig(TIM5,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道3开启
				break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIOA模块的时钟
					PWM_InitStructure.GPIO_Pin=GPIO_Pin_3;						//配置PA3端口
					PWM_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
					PWM_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;				//配置端口模式为复用输出模式
					GPIO_Init(GPIOA,&PWM_InitStructure);						//对端口进行初始化
					TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable); 			//使能预装载寄存器 通道4开启
				break;	
				default:break;				
			}
			break;
		default:break;
	}
}

/********************************************************************
*名    称:void PWM1Output(unsigned char CH,unsigned int pwmval)
*功    能:设置PWM1输出通道 和占空比数值
*入口参数:CH：通道 取值1~4
		  pwmval：高电平时间 最大不能超过周期值
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/
void PWM1Output(unsigned char CH,unsigned int pwmval)
{
	switch(CH)
	{
		case 1:TIM_SetCompare1(TIM1,pwmval);break;//PWM2通道1有效输出
		case 2:TIM_SetCompare2(TIM1,pwmval);break;//PWM2通道2有效输出
		case 3:TIM_SetCompare3(TIM1,pwmval);break;//PWM2通道3有效输出
		case 4:TIM_SetCompare4(TIM1,pwmval);break;//PWM2通道4有效输出
		default:break;
	}
}
/********************************************************************
*名    称:void PWM2Output(unsigned char CH,unsigned int pwmval)
*功    能:设置PWM2输出通道 和占空比数值
*入口参数:CH：通道 取值1~4
		  pwmval：高电平时间 最大不能超过周期值
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/
void PWM2Output(unsigned char CH,unsigned int pwmval)
{
	switch(CH)
	{
		case 1:TIM_SetCompare1(TIM2,pwmval);break;//PWM2通道1有效输出
		case 2:TIM_SetCompare2(TIM2,pwmval);break;//PWM2通道2有效输出
		case 3:TIM_SetCompare3(TIM2,pwmval);break;//PWM2通道3有效输出
		case 4:TIM_SetCompare4(TIM2,pwmval);break;//PWM2通道4有效输出
		default:break;
	}
}
/********************************************************************
*名    称:void PWM3Output(unsigned char CH,unsigned int pwmval)
*功    能:设置PWM3输出通道 和占空比数值
*入口参数:CH：通道 取值1~4
		  pwmval：高电平时间 最大不能超过周期值
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/
void PWM3Output(unsigned char CH,unsigned int pwmval)
{
	switch(CH)
	{
		case 1:TIM_SetCompare1(TIM3,pwmval);break;//PWM3通道1有效输出
		case 2:TIM_SetCompare2(TIM3,pwmval);break;//PWM3通道2有效输出
		case 3:TIM_SetCompare3(TIM3,pwmval);break;//PWM3通道3有效输出
		case 4:TIM_SetCompare4(TIM3,pwmval);break;//PWM3通道4有效输出
		default:break;
	}
}
/********************************************************************
*名    称:void PWM3Output(unsigned char CH,unsigned int pwmval)
*功    能:设置PWM4输出通道 和占空比数值
*入口参数:CH：通道 取值1~4
		  pwmval：高电平时间 最大不能超过周期值
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/
void PWM4Output(unsigned char CH,unsigned int pwmval)
{
	switch(CH)
	{
		case 1:TIM_SetCompare1(TIM4,pwmval);break;//PWM4通道1有效输出
		case 2:TIM_SetCompare2(TIM4,pwmval);break;//PWM4通道2有效输出
		case 3:TIM_SetCompare3(TIM4,pwmval);break;//PWM4通道3有效输出
		case 4:TIM_SetCompare4(TIM4,pwmval);break;//PWM4通道4有效输出
		default:break;
	}
}
/********************************************************************
*名    称:void PWM5Output(unsigned char CH,unsigned int pwmval)
*功    能:设置PWM5输出通道 和占空比数值
*入口参数:CH：通道 取值1~4
		  pwmval：高电平时间 最大不能超过周期值
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/
void PWM5Output(unsigned char CH,unsigned int pwmval)
{
	switch(CH)
	{
		case 1:TIM_SetCompare1(TIM5,pwmval);break;//PWM5通道1有效输出
		case 2:TIM_SetCompare2(TIM5,pwmval);break;//PWM5通道2有效输出
		case 3:TIM_SetCompare3(TIM5,pwmval);break;//PWM5通道3有效输出
		case 4:TIM_SetCompare4(TIM5,pwmval);break;//PWM5通道4有效输出
		default:break;
	}
}
