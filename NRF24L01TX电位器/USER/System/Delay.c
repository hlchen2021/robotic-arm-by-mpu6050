#include "Delay.h"
/********************************************************************
*名    称:Delay_nus(u32 nus)
*功    能:延时n微秒
*入口参数:nus 最大值：1864135
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/

extern void Delayxus(u32 nus)
{
	u32 temp;
	SysTick->LOAD = 9*nus;//Systick时钟源为8分频 72M/8=9M
	SysTick->VAL = 0x00;//计数寄存器清零
	SysTick->CTRL = 0x01;//Systick计数器使能 时钟源为HCLK/8
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01)&&(!(temp&(1<<16))));//判断标志位和使能位
	SysTick->CTRL = 0x00;
	SysTick->VAL = 0x00;
}
/********************************************************************
*名    称:Delay_nms(u32 nms)
*功    能:延时n毫秒 最大值:1864
*入口参数:nms
*出口参数:无
*说    明:无
*调用方法：无
********************************************************************/
/*extern void Delayxms(u32 nms)
{
	u32 temp;
	SysTick->LOAD = 9000*nms;//Systick时钟源为8分频 72M/8=9M
	SysTick->VAL = 0x00;//计数寄存器清零
	SysTick->CTRL = 0x01;//Systick计数器势能 时钟源为HCLK/8
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01)&&(!(temp&(1<<16))));//判断标志位和使能位
	SysTick->CTRL = 0x00;
	SysTick->VAL = 0x00;
}*/
extern void Delayxms(u32 nms)
{
	while(nms--)
	Delayxus(1000);
}

