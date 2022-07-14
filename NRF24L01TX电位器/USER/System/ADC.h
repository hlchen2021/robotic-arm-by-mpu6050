#ifndef __ADC_H__
#define __ADC_H__
#include "stm32f10x.h"
void ADC1_Configuration(void);					//ADC1转换器的初始化
void ADC1_CHInit(unsigned char CH);				//ADC1通道初始化
unsigned int GetADC1Result(unsigned char CH);	//获得ADC1的通道数据
unsigned int GetADC1Average(unsigned char CH);	//获得通道平均值
#endif
