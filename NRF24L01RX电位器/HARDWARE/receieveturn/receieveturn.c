#include <stdio.h>
#include "receieveturn.h"

/********************************************************************
*名    称:turn_charinto_float
*功    能:用于将NRF24L01接收到的数据转换成float类型的数据，方便写入舵机和在OLED上显示
*入口参数:unsigned char p 为NRF24L01接收到的数据，flaot zz用于存储转换后的float数据，char sign_plus用于存储符号信息
*出口参数:无
*说    明:无
*调用方法:无
********************************************************************/

void turn_charinto_float(unsigned char* p, float* zz, char* sign_plus) //p[]为nrf24l01 接收到的数据，xx1,yy1,zz1 用于存储 pitch，roll，yaw 的各个位; zz 用于存储float类型的数据
{
    int i;
		unsigned int xx1[4];
		unsigned int yy1[4];
		unsigned int zz1[4];

    switch(p[0])
    {
    case 1:
        sign_plus[0] = '+';
        sign_plus[1] = '+';
        sign_plus[2] = '+';
        break;
    case 2:
        sign_plus[0] = '+';
        sign_plus[1] = '+';
        sign_plus[2] = '-';
        break;
    case 3:
        sign_plus[0] = '+';
        sign_plus[1] = '-';
        sign_plus[2] = '-';
    case 4:
        sign_plus[0] = '+';
        sign_plus[1] = '+';
        sign_plus[2] = '+';
        break;
    case 5:
        sign_plus[0] = '-';
        sign_plus[1] = '-';
        sign_plus[2] = '-';
    case 6:
        sign_plus[0] = '-';
        sign_plus[1] = '+';
        sign_plus[2] = '+';
        break;
    case 7:
        sign_plus[0] = '+';
        sign_plus[1] = '-';
        sign_plus[2] = '+';
        break;
    case 8:
        sign_plus[0] = '-';
        sign_plus[1] = '+';
        sign_plus[2] = '-';
        break;
    }

    for(i=3; i>=0; i--)                                         //将unsigned char类型数据转换成unsigned int数据
    {
        xx1[i] = p[i+1];
        yy1[i] = p[i+5];
        zz1[i] = p[i+9];
    }

    zz[0] = xx1[3]*100 + xx1[2]*10 + xx1[1] + xx1[0]*0.1;       //将接收到的unsigned cahr 类型的数据转换成float类型
    zz[1] = yy1[3]*100 + yy1[2]*10 + yy1[1] + yy1[0]*0.1;
    zz[2] = zz1[3]*100 + zz1[2]*10 + zz1[1] + zz1[0]*0.1;
}

