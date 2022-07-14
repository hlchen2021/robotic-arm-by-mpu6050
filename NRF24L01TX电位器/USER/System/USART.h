#ifndef __USART_H__
#define __USART_H__
#include "stm32f10x.h"
#define NoRemap 0
#define Remap 	1
extern void USART1_Configuration(unsigned char State);
extern void USART2_Configuration(unsigned char State);
extern void USART3_Configuration(unsigned char State);
extern void USART4_Configuration(void);
extern void USART5_Configuration(void);
#endif
