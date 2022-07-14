#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"
void KeyInit(void);
unsigned char GetKey1Status(void);
unsigned char GetKey2Status(void);
unsigned char GetKey3Status(void);
unsigned char GetKey4Status(void);
unsigned char GetKeyValue(void);
unsigned char GetKeyStatus(void);

#endif
