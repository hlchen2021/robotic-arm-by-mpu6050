#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "RCC.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "SPI_OLED.h"
#include "OLED_Font.h"
#include "EXTI.h"
#include "TIMX.h"
#include "PWM.h"
#include "ADC.h"
#include "USART.h"
#include "BUZZER.h"
#include "nRF24L01.h"
#include "AD.h"
#include "floatturn.h"

uint16_t AD0, AD1, AD2;														//用于存储ADC值
float servo[3];																		//用于将AD值转换成对应的角度信息
float storage[3];																	//

unsigned char TxAddr[]={0x0a,0xbc,0xad,0xce,0x2a};//发送地址
unsigned char TXData[13]={0};
extern unsigned char TranFlag;										//通过中断来实现定时发送数据
void System_Init(void)
{
	RCC_HSE_Configuration();												//系统时钟设置为72M
	NVIC_Configuration();
	LEDInit();																			//LED初始化
	KeyInit();																			//Key初始化
	OLED12864_Init();																//OLED初始化
	OLED12864_TurnBias(0x7f);												//OLED亮度设置
	TimerConfiguration();
	USART1_Configuration(0);												//串口一未重映射 初始化
	nRF24L01_Setup(TxAddr);													//nrf模块初始化
	AD_Init();
}


int main(void)
{ 
	System_Init();	

	while(1)
	{
		OLED12864_DisStr(0,0,0,"TXData:");
		OLED12864_DisStr(0,10,0,"Base: ");
		OLED12864_DisStr(0,20,0,"Link1:");
		OLED12864_DisStr(0,30,0,"Link2:");
		
		AD0 = AD_GetValue(ADC_Channel_0);
		AD1 = AD_GetValue(ADC_Channel_1);
		AD2 = AD_GetValue(ADC_Channel_2);
		
		servo[0] = (float)AD0/4096*180;
		servo[1] = (float)AD1/4096*180;
		servo[2] = (float)AD2/4096*180;
	
		OLED12864_Format4(40,10,0,servo[0]);
		OLED12864_Format4(40,20,0,servo[1]);
		OLED12864_Format4(40,30,0,servo[2]);
		
		floatturn(servo,TXData,storage);  //将servo的float类型的数据转换成unsigned char类型的数据存入TXData中
		
		if(TranFlag)
		{
			nRF24L01_TxDat(TXData,13);
			TranFlag=0;			
		}
	}
}
