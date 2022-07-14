#include "BUZZER.h"

/*
Beep=PA7
*/
#define BEEP_APB_GPIO  	RCC_APB2Periph_GPIOA
#define BEEP_Pin		GPIO_Pin_7	
#define BEEP_GPIO       GPIOA



void BuzzerInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;						//定义GPIO结构体	
	RCC_APB2PeriphClockCmd(BEEP_APB_GPIO,ENABLE);				//开启GPIOA模块的时钟

	
	GPIO_InitStructure.GPIO_Pin=BEEP_Pin;						//配置LED端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(BEEP_GPIO,&GPIO_InitStructure);					//对端口进行初始化

}

void BEEPON(void)
{
	GPIO_ResetBits(BEEP_GPIO,BEEP_Pin);
}

void BEEPOFF(void)
{
	GPIO_SetBits(BEEP_GPIO,BEEP_Pin);
}
unsigned char Beep;//音响效果的变量
unsigned short SoundCounter;//蜂鸣器定时计数器
void BuzzerOut(void)
{
	SoundCounter++;
	switch(Beep)
	{
	case 0:										//不发声
		SoundCounter=0;
		BEEPOFF();
	break;
	case 1:										//发短音
		BEEPON();
		if(SoundCounter>1)
		{
			Beep=0;
			BEEPOFF();
			SoundCounter=0;
		}
	break;
	case 2:										//发长音
		BEEPON();
		if(SoundCounter>100)
		{
			Beep=0;
			BEEPOFF();
			SoundCounter=0;
		}
	break;
	case 3:									//短长
		if(SoundCounter<10) BEEPON();//100ms
		if(SoundCounter>10) BEEPOFF();
		if(SoundCounter>60)
		{
			Beep=0;
			BEEPON();
			SoundCounter=0;
		}
	break;
	case 4:									//滴滴
		if(SoundCounter<10) BEEPON();//100ms
		if(SoundCounter>10) BEEPOFF();
		if(SoundCounter>20) BEEPON();
		if(SoundCounter>30) BEEPOFF();
		if(SoundCounter>80)
		{
			Beep=0;
			SoundCounter=0;
		}
	break;
	case 5:									//滴滴滴
		BEEPON();
		if(SoundCounter>10) BEEPOFF();//100ms
		if(SoundCounter>20) BEEPON();
		if(SoundCounter>30) BEEPOFF();
		if(SoundCounter>40) BEEPON();
		if(SoundCounter>50) BEEPOFF();
		if(SoundCounter>100)
		{
			Beep=0;
			SoundCounter=0;
		}
	break;
	case 6:										//持续滴滴
		if(SoundCounter%40>25) BEEPON();//100ms
		else BEEPOFF();
	break;
	default:break;
}
}
