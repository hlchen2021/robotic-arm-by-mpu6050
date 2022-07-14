#ifndef __PWM_H__
#define __PWM_H__
#include "stm32f10x.h"
#define CH1 	1					//通道1
#define CH2 	2					//通道2
#define CH3 	3					//通道3
#define CH4 	4					//通道4
#define CH5 	5					//通道5
#define CH6 	6					//通道6
#define CH7 	7					//通道7
#define CH8 	8					//通道8
#define NoRemap 		0			//无重映像
#define PartialRemap1 	1			//部分重映像1
#define PartialRemap2 	3			//部分重映像2
#define FullRemap 		2			//完全映像
void PWM1Init(unsigned int Cycle);
void PWM1IOInit(unsigned char CH,unsigned char remap);
void PWM1Output(unsigned char CH,unsigned int pwmval);
void PWM2Init(unsigned int Cycle);
void PWM2IOInit(unsigned char CH,unsigned char remap);
void PWM2Output(unsigned char CH,unsigned int pwmval);
void PWM3Init(unsigned int Cycle);
void PWM3IOInit(unsigned char CH,unsigned char remap);
void PWM3Output(unsigned char CH,unsigned int pwmval);
void PWM4Init(unsigned int Cycle);
void PWM4IOInit(unsigned char CH,unsigned char remap);
void PWM4Output(unsigned char CH,unsigned int pwmval);
void PWM5Init(unsigned int Cycle);
void PWM5IOInit(unsigned char CH,unsigned char remap);
void PWM5Output(unsigned char CH,unsigned int pwmval);
#endif
