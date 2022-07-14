#include "EXTI.h"
/*
KEY1=PB11;

EXTI11=PB11;
*/

#define EXTI11_APB_GPIO   	RCC_APB2Periph_GPIOB
#define EXTI11_Pin			GPIO_Pin_11
#define EXTI11_GPIO			GPIOB

void EXTI11_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;						//定义GPIO结构体	
	RCC_APB2PeriphClockCmd(EXTI11_APB_GPIO,ENABLE);				//开启GPIOB模块的时钟

	GPIO_InitStructure.GPIO_Pin=EXTI11_Pin;						//配置EXTI11端口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;					//配置端口模式为上拉输入模式
	GPIO_Init(EXTI11_GPIO,&GPIO_InitStructure);					//对端口进行初始化
}

void EXTI11_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				//开启端口的复用功能
	EXTI11_GPIO_Init();												//端口模式配置
	
	EXTI_ClearITPendingBit(EXTI_Line11);							//清除EXTI11 标志
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);	//中断来源为PB11
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;						//配置外部中断来源为管脚11
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;				//配置为触发进入中断
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;			//配置触发方式为下降沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//外部中断使能
	EXTI_Init(&EXTI_InitStructure);									//写入中断配置
}
