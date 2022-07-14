#ifndef __LED_H__
#define __LED_H__
#include "stm32f10x.h"
void LED1_ON(void);
void LED2_ON(void);
void LED3_ON(void);
void LED4_ON(void);

void LED1_OFF(void);
void LED2_OFF(void);
void LED3_OFF(void);
void LED4_OFF(void);

void LED1Reverse(void);
void LED2Reverse(void);
void LED3Reverse(void);
void LED4Reverse(void);

void LEDInit(void);
#endif
