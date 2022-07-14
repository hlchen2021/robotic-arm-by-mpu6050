#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "delay.h"

void Servo_Init(void)
{
	PWM_Init();
}

void Servo_SetAngle1(float Angle)
{
	PWM_SetCompare1(Angle / 180 * 2000 + 500);
}

void Servo_SetAngle2(float Angle)
{
	PWM_SetCompare2(Angle / 180 * 2000 + 500);
}

void Servo_SetAngle3(float Angle)
{
	PWM_SetCompare3(Angle / 180 * 2000 + 500);
}

/*
	舵机缓慢从angle1转动到angle2
*/
//void Servo_SlowChange(float angle1, float angle2)
//{
//	int i;
//	if(angle1 < angle2)
//	{
//		for(i = angle1;i <= angle2;i=i+2)
//		{
//			Servo_SetAngle1(i);
//			Delay_ms(20);
//		}
//	}
//	else
//	{
//		for(i = angle1;i >= angle2;i=i-2)
//		{
//			Servo_SetAngle(i);
//			Delay_ms(20);			
//		}
//	}
//}
