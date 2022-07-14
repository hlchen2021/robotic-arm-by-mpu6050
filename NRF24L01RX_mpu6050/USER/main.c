#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "SPI_OLED.h"
#include "key.h"   
#include "usmart.h"   
#include "floatturn.h"
#include "nRF24L01.h"
#include "receieveturn.h"
#include "Servo.h"

unsigned char RxAddr[]={0x0a,0xbc,0xad,0xce,0x2a};//发送地址
unsigned char RXData[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char TranFlag;

int main(void)
{
  float mpudata[3]={0};     //用于存储mpu6050数据
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    	 			//延时函数初始化	  
	uart_init(500000);	 			//串口初始化为9600
	usmart_dev.init(72);			//初始化USMART
	LED_Init();		  					//初始化与LED连接的硬件接口
	KEY_Init();								//初始化按键
	OLED12864_Init();     		//初始化OLED
	Servo_Init();							//舵机初始化
	OLED12864_TurnBias(0x7f);	//OLED亮度设置
	nRF24L01_Setup(RxAddr);		//nrf模块初始化
	SetRxMode();							//配置无线通信模块为接收
	WaitingRX();							//开启接收
	

	OLED12864_DisStr(0,10,0,"link1 :");
	OLED12864_DisStr(0,20,0,"link2 :");
	OLED12864_DisStr(0,30,0,"base	 :");
	
	while(1)
	{
		if(GetIRQStatus()==2)		//判断是否有数据到来
		{
			ClearIRQ();						//清除中断
			nRF24L01_RxDat(RXData,13);
			WaitingRX();
		}
		
		turn_charinto_float(RXData,mpudata);
		OLED12864_Format4(40,10,0,mpudata[0]);
		OLED12864_Format4(40,20,0,mpudata[1]);
		OLED12864_Format4(40,30,0,mpudata[2]);
		
		Servo_SetAngle1(mpudata[2]);
		Servo_SetAngle2(mpudata[0]);
		Servo_SetAngle3(mpudata[1]);
		
	}
}

