#include "TIMx.h"
/*******************************************************************************
名称：void TimerConfiguration(void)
功能：对所有的定时器进行 初始化
入口参数：无
出口参数：无
说明：无
***********************************************************************************/
void TimerConfiguration(void)
{
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);	//开启定时器的APB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	//开启定时器的APB时钟
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	//开启定时器的APB时钟
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	//开启定时器的APB时钟
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	//开启定时器的APB时钟
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);	//开启定时器的APB时钟
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);	//开启定时器的APB时钟
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);	//开启定时器的APB时钟
	
	
	//TIM1_Configuration();								//定时器配置函数
	TIM2_Configuration();								//定时器配置函数
	//TIM3_Configuration();								//定时器配置函数
	//TIM4_Configuration();								//定时器配置函数
	//TIM5_Configuration();								//定时器配置函数
	//TIM6_Configuration();								//定时器配置函数
	//TIM7_Configuration();								//定时器配置函数
	//TIM8_Configuration();								//定时器配置函数
	
	//TIM1_Period(10000);									//单位为us 定时长度10000us=10ms 
	TIM2_Period(20000);									//单位为us 定时长度20000us=20ms 
	//TIM3_Period(10000);									//单位为us 定时长度10000us=10ms 
	//TIM4_Period(10000);									//单位为us 定时长度10000us=10ms 
	//TIM5_Period(10000);									//单位为us 定时长度10000us=10ms 
	//TIM6_Period(10000);									//单位为us 定时长度10000us=10ms 
	//TIM7_Period(10000);									//单位为us 定时长度10000us=10ms 
	
	//TIM_Cmd(TIM1, ENABLE);								//定时器开始工作	
	TIM_Cmd(TIM2, ENABLE);								//定时器开始工作	
	//TIM_Cmd(TIM3, ENABLE);								//定时器开始工作	
	//TIM_Cmd(TIM4, ENABLE);								//定时器开始工作	
	//TIM_Cmd(TIM5, ENABLE);								//定时器开始工作	
	//TIM_Cmd(TIM6, ENABLE);								//定时器开始工作	
	//TIM_Cmd(TIM7, ENABLE);								//定时器开始工作
	//TIM_Cmd(TIM8, ENABLE);								//定时器开始工作	
}
/*******************************************************************************
名称：void TIM1_Configuration(void)
功能：对定时器1进行配置
入口参数：无
出口参数：无
说明：无
***********************************************************************************/
void TIM1_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);					//清除中断标志
	TIM_TimeBaseStructure.TIM_Prescaler = (36-1);				//Timer主频为72M/36=2M 周期为0.5us         
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	//TIM_TimeBaseStructure.TIM_Period = 60000;					//定时器装载初值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;				//时钟分割
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;			//定时器重复的次数
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);				//写入定时器的配置
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE );					//使能TIMx中断 使能以后必须要对应的中断服务函数 否则死机
	TIM_Cmd(TIM1, DISABLE);										//TIMx停止运行
}
/*******************************************************************************
名称：void TIM2_Configuration(void)
功能：对定时器2进行配置
入口参数：无
出口参数：无
说明：无
***********************************************************************************/
void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);					//清除中断标志
	TIM_TimeBaseStructure.TIM_Prescaler = (36-1);				//Timer主频为72M/36=2M 周期为0.5us         
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	//TIM_TimeBaseStructure.TIM_Period = 60000;					//定时器装载初值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;				//时钟分割
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;			//定时器重复的次数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);				//写入定时器的配置
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );					//使能TIMx中断 使能以后必须要对应的中断服务函数 否则死机
	TIM_Cmd(TIM2, DISABLE);										//TIMx停止运行
}

/*******************************************************************************
名称：void TIM3_Configuration(void)
功能：对定时器3进行配置
入口参数：无
出口参数：无
说明：无
***********************************************************************************/
void TIM3_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);					//清除中断标志
	TIM_TimeBaseStructure.TIM_Prescaler = (36-1);				//Timer主频为72M/36=2M 周期为0.5us         
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	//TIM_TimeBaseStructure.TIM_Period = 60000;					//定时器装载初值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;				//时钟分割
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;			//定时器重复的次数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);				//写入定时器的配置
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );					//使能TIMx中断 使能以后必须要对应的中断服务函数 否则死机
	TIM_Cmd(TIM3, DISABLE);										//TIMx停止运行
}
/*******************************************************************************
名称：void TIM4_Configuration(void)
功能：对定时器4进行配置
入口参数：无
出口参数：无
说明：无
***********************************************************************************/
void TIM4_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);					//清除中断标志
	TIM_TimeBaseStructure.TIM_Prescaler = (36-1);				//Timer主频为72M/36=2M 周期为0.5us         
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	//TIM_TimeBaseStructure.TIM_Period = 60000;					//定时器装载初值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;				//时钟分割
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;			//定时器重复的次数
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);				//写入定时器的配置
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE );					//使能TIMx中断 使能以后必须要对应的中断服务函数 否则死机
	TIM_Cmd(TIM4, DISABLE);										//TIMx停止运行
}
/*******************************************************************************
名称：void TIM5_Configuration(void)
功能：对定时器5进行配置
入口参数：无
出口参数：无
说明：无
***********************************************************************************/
void TIM5_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);					//清除中断标志
	TIM_TimeBaseStructure.TIM_Prescaler = (36-1);				//Timer主频为72M/36=2M 周期为0.5us         
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	//TIM_TimeBaseStructure.TIM_Period = 60000;					//定时器装载初值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;				//时钟分割
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;			//定时器重复的次数
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);				//写入定时器的配置
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE );					//使能TIMx中断 使能以后必须要对应的中断服务函数 否则死机
	TIM_Cmd(TIM5, DISABLE);										//TIMx停止运行
}
/*******************************************************************************
名称：void TIM6_Configuration(void)
功能：对定时器6进行配置
入口参数：无
出口参数：无
说明：无
***********************************************************************************/
void TIM6_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);					//清除中断标志
	TIM_TimeBaseStructure.TIM_Prescaler = (36-1);				//Timer主频为72M/36=2M 周期为0.5us         
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	//TIM_TimeBaseStructure.TIM_Period = 60000;					//定时器装载初值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;				//时钟分割
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;			//定时器重复的次数
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);				//写入定时器的配置
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE );					//使能TIMx中断 使能以后必须要对应的中断服务函数 否则死机
	TIM_Cmd(TIM6, DISABLE);										//TIMx停止运行
}
/*******************************************************************************
名称：void TIM7_Configuration(void)
功能：对定时器7进行配置
入口参数：无
出口参数：无
说明：无
***********************************************************************************/
void TIM7_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);					//清除中断标志
	TIM_TimeBaseStructure.TIM_Prescaler = (36-1);				//Timer主频为72M/36=2M 周期为0.5us         
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	//TIM_TimeBaseStructure.TIM_Period = 60000;					//定时器装载初值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;				//时钟分割
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;			//定时器重复的次数
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);				//写入定时器的配置
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE );					//使能TIMx中断 使能以后必须要对应的中断服务函数 否则死机
	TIM_Cmd(TIM7, DISABLE);										//TIMx停止运行
}
/*******************************************************************************
名称：void TIM8_Configuration(void)
功能：对定时器7进行配置
入口参数：无
出口参数：无
说明：无
***********************************************************************************/
void TIM8_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ClearITPendingBit(TIM8, TIM_IT_Update);					//清除中断标志
	TIM_TimeBaseStructure.TIM_Prescaler = (36-1);				//Timer主频为72M/36=2M 周期为0.5us         
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	//TIM_TimeBaseStructure.TIM_Period = 60000;					//定时器装载初值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;				//时钟分割
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;			//定时器重复的次数
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);				//写入定时器的配置
	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE );					//使能TIMx中断 使能以后必须要对应的中断服务函数 否则死机
	TIM_Cmd(TIM8, DISABLE);										//TIMx停止运行
}
/*******************************************************************************
名称：void TIM1_Period(unsigned short TimeLength)
功能：设置定时器定时时长
入口参数：TimeLength：定时时长 最大值不能超过65536/2=32768
出口参数：无
说明：无
***********************************************************************************/
void TIM1_Period(unsigned short TimeLength)
{
	TIM1->ARR = TimeLength*2;
}
/*******************************************************************************
名称：void TIM2_Period(unsigned short TimeLength)
功能：设置定时器定时时长
入口参数：TimeLength：定时时长 最大值不能超过65536/2=32768
出口参数：无
说明：无
***********************************************************************************/
void TIM2_Period(unsigned short TimeLength)
{
	TIM2->ARR = TimeLength*2;
}
/*******************************************************************************
名称：void TIM3_Period(unsigned short TimeLength)
功能：设置定时器定时时长
入口参数：TimeLength：定时时长 最大值不能超过65536/2=32768
出口参数：无
说明：无
***********************************************************************************/
void TIM3_Period(unsigned short TimeLength)
{
	TIM3->ARR = TimeLength*2;
}
/*******************************************************************************
名称：void TIM4_Period(unsigned short TimeLength)
功能：设置定时器定时时长
入口参数：TimeLength：定时时长 最大值不能超过65536/2=32768
出口参数：无
说明：无
***********************************************************************************/
void TIM4_Period(unsigned short TimeLength)
{
	TIM4->ARR = TimeLength*2;
}
/*******************************************************************************
名称：void TIM5_Period(unsigned short TimeLength)
功能：设置定时器定时时长
入口参数：TimeLength：定时时长 最大值不能超过65536/2=32768
出口参数：无
说明：无
***********************************************************************************/
void TIM5_Period(unsigned short TimeLength)
{
	TIM5->ARR = TimeLength*2;
}
/*******************************************************************************
名称：void TIM6_Period(unsigned short TimeLength)
功能：设置定时器定时时长
入口参数：TimeLength：定时时长 最大值不能超过65536/2=32768
出口参数：无
说明：无
***********************************************************************************/
void TIM6_Period(unsigned short TimeLength)
{
	TIM6->ARR = TimeLength*2;
}
/*******************************************************************************
名称：void TIM7_Period(unsigned short TimeLength)
功能：设置定时器定时时长
入口参数：TimeLength：定时时长 最大值不能超过65536/2=32768
出口参数：无
说明：无
***********************************************************************************/
void TIM7_Period(unsigned short TimeLength)
{
	TIM7->ARR = TimeLength*2;
}
/*******************************************************************************
名称：void TIM8_Period(unsigned short TimeLength)
功能：设置定时器定时时长
入口参数：TimeLength：定时时长 最大值不能超过65536/2=32768
出口参数：无
说明：无
***********************************************************************************/
void TIM8_Period(unsigned short TimeLength)
{
	TIM8->ARR = TimeLength*2;
}
