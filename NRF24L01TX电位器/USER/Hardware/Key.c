#include "Key.h"
/*
KEY1=PB11
KEY2=PB10
KEY3=PB1
KEY4=PB0
*/
#define KEY1_APB_GPIO  	RCC_APB2Periph_GPIOB
#define KEY1_Pin		GPIO_Pin_11	
#define KEY1_GPIO       GPIOB

#define KEY2_APB_GPIO  	RCC_APB2Periph_GPIOB
#define KEY2_Pin		GPIO_Pin_10	
#define KEY2_GPIO       GPIOB

#define KEY3_APB_GPIO  	RCC_APB2Periph_GPIOB
#define KEY3_Pin		GPIO_Pin_1	
#define KEY3_GPIO       GPIOB

#define KEY4_APB_GPIO  	RCC_APB2Periph_GPIOB
#define KEY4_Pin		GPIO_Pin_0	
#define KEY4_GPIO       GPIOB

void KeyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;						//定义GPIO结构体	
	RCC_APB2PeriphClockCmd(KEY1_APB_GPIO,ENABLE);				//开启GPIOB模块的时钟
	RCC_APB2PeriphClockCmd(KEY2_APB_GPIO,ENABLE);
	RCC_APB2PeriphClockCmd(KEY3_APB_GPIO,ENABLE);
	RCC_APB2PeriphClockCmd(KEY4_APB_GPIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=KEY1_Pin;						//配置KEY端口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;					//配置端口模式为上拉输入模式
	GPIO_Init(KEY1_GPIO,&GPIO_InitStructure);					//对端口进行初始化

	GPIO_InitStructure.GPIO_Pin=KEY2_Pin;						//配置KEY端口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;					//配置端口模式为上拉输入模式
	GPIO_Init(KEY2_GPIO,&GPIO_InitStructure);					//对端口进行初始化

	GPIO_InitStructure.GPIO_Pin=KEY3_Pin;						//配置KEY端口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;					//配置端口模式为上拉输入模式
	GPIO_Init(KEY3_GPIO,&GPIO_InitStructure);					//对端口进行初始化

	GPIO_InitStructure.GPIO_Pin=KEY4_Pin;						//配置KEY端口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;					//配置端口模式为上拉输入模式
	GPIO_Init(KEY4_GPIO,&GPIO_InitStructure);					//对端口进行初始化
}
unsigned char GetKey1Status(void)
{
	return GPIO_ReadInputDataBit(KEY1_GPIO, KEY1_Pin);
}
unsigned char GetKey2Status(void)
{
	return GPIO_ReadInputDataBit(KEY2_GPIO, KEY2_Pin);
}
unsigned char GetKey3Status(void)
{
	return GPIO_ReadInputDataBit(KEY3_GPIO, KEY3_Pin);
}
unsigned char GetKey4Status(void)
{
	return GPIO_ReadInputDataBit(KEY4_GPIO, KEY4_Pin);
}
#define KeyTime  23000
unsigned char KeyValue=0;//用于存放键值的变量 0代表没有按键被按下
unsigned char GetKeyValue(void)
{
	static unsigned int Key1Count;
	static unsigned int Key2Count;
	static unsigned int Key3Count;
	static unsigned int Key4Count;
	KeyValue=0;
	if(GetKey1Status()==0)
	{
		Key1Count++;
		if(Key1Count>KeyTime)
		{
			KeyValue=1;
			Key1Count=0;
		}
	}
	else
	{
		Key1Count=0;
	}
	
	if(GetKey2Status()==0)
	{
		Key2Count++;
		if(Key2Count>KeyTime)
		{
			KeyValue=2;
			Key2Count=0;
		}
	}
	else
	{
		Key2Count=0;
	}
	if(GetKey3Status()==0)
	{
		Key3Count++;
		if(Key3Count>KeyTime)
		{
			KeyValue=3;
			Key3Count=0;
		}
	}
	else
	{
		Key3Count=0;
	}
	if(GetKey4Status()==0)
	{
		Key4Count++;
		if(Key4Count>KeyTime)
		{
			KeyValue=4;
			Key4Count=0;
		}
	}
	else
	{
		Key4Count=0;
	}
	
	return KeyValue;
}
/********************************************************************
*名    称:unsigned char GetKeyStatus(void)
*功    能:简单的按键状态机函数
*入口参数:无
*出口参数: 
无按键 返回键值0
KEY1被按下   返回键值1
KEY2被按下   返回键值2
KEY3被按下   返回键值3
KEY4被按下   返回键值4
*说    明:无
*调用方法:在定时器中断中每20ms调用一次
********************************************************************/
#define KeyStatusInitial 0 //按键的初始状态
#define KeyStatusDown    1 //单次按键被按下状态
#define KeyStatusLong    2 //按键被长按
#define KeyStatusOpen	 3 //按键被释放

unsigned char GetKeyStatus(void)
{
	static unsigned char KeyStatus1;	//按键状态的中间变量
	static unsigned char KeyStatus2;
	static unsigned char KeyStatus3;
	static unsigned char KeyStatus4;
	unsigned char KeyPress1;			//当前按键的电平状态
	unsigned char KeyPress2;
	unsigned char KeyPress3;
	unsigned char KeyPress4;
	unsigned char KeyNum=0;				//按键的返回值
	KeyPress1=GetKey1Status();			//获取按键引脚的电平
	KeyPress2=GetKey2Status();			//获取按键引脚的电平
	KeyPress3=GetKey3Status();			//获取按键引脚的电平
	KeyPress4=GetKey4Status();			//获取按键引脚的电平
	switch(KeyStatus1)
	{
		case KeyStatusInitial:
		if(!KeyPress1)
		{
			KeyStatus1=KeyStatusDown;
		}
		break;
		case KeyStatusDown:
		if(!KeyPress1)
		{
			KeyNum=1;
			KeyStatus1=KeyStatusOpen;
		}
		else
		{
			KeyStatus1=KeyStatusInitial;
		}
		break;
		case KeyStatusOpen:
		if(KeyPress1)
		{
			KeyStatus1=KeyStatusInitial;
		}
	}
	switch(KeyStatus2)
	{
		case KeyStatusInitial:
		if(!KeyPress2)
		{
			KeyStatus2=KeyStatusDown;
		}
		break;
		case KeyStatusDown:
		if(!KeyPress2)
		{
			KeyNum=2;
			KeyStatus2=KeyStatusOpen;
		}
		else
		{
			KeyStatus2=KeyStatusInitial;
		}
		break;
		case KeyStatusOpen:
		if(KeyPress2)
		{
			KeyStatus2=KeyStatusInitial;
		}
	}
	switch(KeyStatus3)
	{
		case KeyStatusInitial:
		if(!KeyPress3)
		{
			KeyStatus3=KeyStatusDown;
		}
		break;
		case KeyStatusDown:
		if(!KeyPress3)
		{
			KeyNum=3;
			KeyStatus3=KeyStatusOpen;
		}
		else
		{
			KeyStatus3=KeyStatusInitial;
		}
		break;
		case KeyStatusOpen:
		if(KeyPress3)
		{
			KeyStatus3=KeyStatusInitial;
		}
	}
	switch(KeyStatus4)
	{
		case KeyStatusInitial:
		if(!KeyPress4)
		{
			KeyStatus4=KeyStatusDown;
		}
		break;
		case KeyStatusDown:
		if(!KeyPress4)
		{
			KeyNum=4;
			KeyStatus4=KeyStatusOpen;
		}
		else
		{
			KeyStatus4=KeyStatusInitial;
		}
		break;
		case KeyStatusOpen:
		if(KeyPress4)
		{
			KeyStatus4=KeyStatusInitial;
		}
	}
	
	
	
	
	return KeyNum;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


