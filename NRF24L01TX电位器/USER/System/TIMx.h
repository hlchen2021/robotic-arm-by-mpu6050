#ifndef __TIMX_H__
#define __TIMX_H__
#include "stm32f10x.h"
void TimerConfiguration(void);
void TIM1_Configuration(void);
void TIM2_Configuration(void);
void TIM3_Configuration(void);
void TIM4_Configuration(void);
void TIM5_Configuration(void);
void TIM6_Configuration(void);
void TIM7_Configuration(void);
void TIM8_Configuration(void);
void TIM1_Period(unsigned short TimeLength);
void TIM2_Period(unsigned short TimeLength);
void TIM3_Period(unsigned short TimeLength);
void TIM4_Period(unsigned short TimeLength);
void TIM5_Period(unsigned short TimeLength);
void TIM6_Period(unsigned short TimeLength);
void TIM7_Period(unsigned short TimeLength);
void TIM8_Period(unsigned short TimeLength);
#endif
