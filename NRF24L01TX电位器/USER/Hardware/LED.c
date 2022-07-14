#include "LED.h"
/*
LED1=PA3
LED2=PA4
LED3=PA5
LED4=PA6
*/
#define LED1_APB_GPIO  	RCC_APB2Periph_GPIOA
#define LED1_Pin		GPIO_Pin_3	
#define LED1_GPIO       GPIOA

#define LED2_APB_GPIO  	RCC_APB2Periph_GPIOA
#define LED2_Pin		GPIO_Pin_4	
#define LED2_GPIO       GPIOA

#define LED3_APB_GPIO  	RCC_APB2Periph_GPIOA
#define LED3_Pin		GPIO_Pin_5	
#define LED3_GPIO       GPIOA

#define LED4_APB_GPIO  	RCC_APB2Periph_GPIOA
#define LED4_Pin		GPIO_Pin_6	
#define LED4_GPIO       GPIOA

void LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;						//定义GPIO结构体	
	RCC_APB2PeriphClockCmd(LED1_APB_GPIO,ENABLE);				//开启GPIOA模块的时钟
	RCC_APB2PeriphClockCmd(LED2_APB_GPIO,ENABLE);
	RCC_APB2PeriphClockCmd(LED3_APB_GPIO,ENABLE);
	RCC_APB2PeriphClockCmd(LED4_APB_GPIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=LED1_Pin;						//配置LED端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(LED1_GPIO,&GPIO_InitStructure);					//对端口进行初始化

	GPIO_InitStructure.GPIO_Pin=LED2_Pin;						//配置LED端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(LED2_GPIO,&GPIO_InitStructure);					//对端口进行初始化

	GPIO_InitStructure.GPIO_Pin=LED3_Pin;						//配置LED端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(LED3_GPIO,&GPIO_InitStructure);					//对端口进行初始化

	GPIO_InitStructure.GPIO_Pin=LED4_Pin;						//配置LED端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(LED4_GPIO,&GPIO_InitStructure);					//对端口进行初始化
	
	LED1_OFF();
	LED2_OFF();
	LED3_OFF();
	LED4_OFF();

}

void LED1_ON(void)
{
	GPIO_ResetBits(LED1_GPIO, LED1_Pin);	//LED亮
}
void LED2_ON(void)
{
	GPIO_ResetBits(LED2_GPIO, LED2_Pin);	//LED亮
}
void LED3_ON(void)
{
	GPIO_ResetBits(LED3_GPIO, LED3_Pin);	//LED亮
}
void LED4_ON(void)
{
	GPIO_ResetBits(LED4_GPIO, LED4_Pin);	//LED亮
}

void LED1_OFF(void)
{
	GPIO_SetBits(LED1_GPIO, LED1_Pin);		//LED灭
}
void LED2_OFF(void)
{
	GPIO_SetBits(LED2_GPIO, LED2_Pin);		//LED灭
}
void LED3_OFF(void)
{
	GPIO_SetBits(LED3_GPIO, LED3_Pin);		//LED灭
}
void LED4_OFF(void)
{
	GPIO_SetBits(LED4_GPIO, LED4_Pin);		//LED灭
}

void LED1Reverse(void)
{
	if(GPIO_ReadInputDataBit(LED1_GPIO, LED1_Pin) == 1)
	GPIO_ResetBits(LED1_GPIO, LED1_Pin);
	else
	GPIO_SetBits(LED1_GPIO, LED1_Pin);
}
void LED2Reverse(void)
{
	if(GPIO_ReadInputDataBit(LED2_GPIO, LED2_Pin) == 1)
	GPIO_ResetBits(LED2_GPIO, LED2_Pin);
	else
	GPIO_SetBits(LED2_GPIO, LED2_Pin);
}
void LED3Reverse(void)
{
	if(GPIO_ReadInputDataBit(LED3_GPIO, LED3_Pin) == 1)
	GPIO_ResetBits(LED3_GPIO, LED3_Pin);
	else
	GPIO_SetBits(LED3_GPIO, LED3_Pin);
}
void LED4Reverse(void)
{
	if(GPIO_ReadInputDataBit(LED4_GPIO, LED4_Pin) == 1)
	GPIO_ResetBits(LED4_GPIO, LED4_Pin);
	else
	GPIO_SetBits(LED4_GPIO, LED4_Pin);
}



