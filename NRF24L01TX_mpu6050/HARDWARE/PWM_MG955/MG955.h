#ifndef __MG955_H
#define __MG955_H

void PWM_Init(void);
void PWM_SetCompare2(uint16_t Compare);
void Servo_Init(void);
void Servo1_SetAngle(float Angle);
void Servo2_SetAngle(float angle);
void Servo3_SetAngle(float angle);
#endif
