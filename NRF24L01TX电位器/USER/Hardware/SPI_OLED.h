#ifndef __SPI_OLED_H__
#define __SPI_OLED_H__
#include "stm32f10x.h"
#include <math.h>
#include <stdio.h>
#define bit unsigned char 
typedef struct
{
	unsigned char x;
	unsigned char y;
}Point;
/*------OLED12864屏幕尺寸和功能宏定义------*/																	//命令
#define LCD_X	128								//液晶屏横坐标宽度
#define LCD_ROW LCD_X							//液晶屏列宽度
#define LCD_Y	64								//液晶屏纵坐标高度
#define LCD_COLUMN LCD_Y / 8					//液晶屏行高度
#define LCD_AREA LCD_X * LCD_Y					//液晶屏面积
#define LCD_AREA_BYTE LCD_COLUMN * LCD_ROW		//液晶屏字节容量
  
void OLED12864_Init(void);
void OLED12864_Location(unsigned char x,unsigned char y);
void OLED12864_Clean(void);//
void OLED12864_TurnBias(unsigned char Vlcd);
//////////////////////////////6*8点阵字符函数(高度8)///////////////////////////////////////////
void OLED12864_DisChar(unsigned char x,unsigned char y,unsigned char value);
void OLED12864_DisRevChar(unsigned char x,unsigned char y,unsigned char value);
void OLED12864_DisOneChar(unsigned char x,unsigned char y,bit Rev,unsigned char value);

void OLED12864_Format1(unsigned char x,unsigned char y,bit Rev,unsigned int temp);//0123
void OLED12864_Format2(unsigned char x,unsigned char y,bit Rev,unsigned int temp);//01
void OLED12864_Format3(unsigned char x,unsigned char y,bit Rev,unsigned int temp);//001
void OLED12864_Format4(unsigned char x,unsigned char y,bit Rev,float);//1.22V
void OLED12864_Format5(unsigned char x,unsigned char y,bit Rev,unsigned int temp);//0xff
unsigned char OLED12864_DisStr(unsigned char x,unsigned char y,bit Rev,char * str);//显示字符串

//////////////////////////////8*12点阵字符函数(高度12)///////////////////////////////////////////
void OLED12864_DisOneBigChar(unsigned char x,unsigned char y,bit Rev,unsigned char value);//显示单个字符
unsigned char OLED12864_DisBigStr(unsigned char x,unsigned char y,bit Rev,char * str);//显示字符串
void OLED12864_DisBigChs(unsigned char x,unsigned char y,bit Rev,unsigned char num,const unsigned char Hanzi[][24]);//显示12*12的汉字
void OLED12864_BigFormat1(unsigned char x,unsigned char y,bit Rev,unsigned int temp);//0123
void OLED12864_BigFormat2(unsigned char x,unsigned char y,bit Rev,unsigned int temp);//01
void OLED12864_BigFormat3(unsigned char x,unsigned char y,bit Rev,float);//12.56V
void OLED12864_BigFormat4(unsigned char x,unsigned char y,bit Rev,float temp);//01.3V
void OLED12864_BigFormat5(unsigned char x,unsigned char y,bit Rev,unsigned int temp);//100%
void OLED12864_DisBigStr1(unsigned char x,unsigned char y,bit Rev,char * str);
//////////////////////////////8*16点阵字符函数(高度16)///////////////////////////////////////////
unsigned char OLED12864_DisLargeStr(unsigned char x,unsigned char y,bit Rev,char * str);//显示8*16字符串
void OLED12864_DisLargeChStr(unsigned char x,unsigned char y,bit Rev,unsigned char num,const unsigned char Hanzi[][32]);//显示16*16汉字字符串
void OLED12864_LargeFormat1(unsigned char x,unsigned char y,bit Rev,unsigned int temp);//01
void OLED12864_LargeFormat2(unsigned char x,unsigned char y,bit Rev,float temp);


//////////////////////////////画图函数///////////////////////////////////////////
void OLED12864_DisLine(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);//画直线
void OLED12864_DisPolyline(const Point *p,unsigned char num);//画折线
void OLED12864_DisSqu(unsigned char x,unsigned char y,unsigned char width,unsigned char height,bit Rev);//画矩形
void OLED12864_DisCircle(unsigned char center_x,unsigned char center_y,unsigned char r);//画园
void OLED12864_DisBmp(unsigned char x,unsigned char y,unsigned char width,unsigned char height,bit Rev,const unsigned char bitmap[]);//画图
void OLED12864_DisPower(unsigned char x,unsigned char y,unsigned char width,unsigned char height,int MaxX,bit Rev,float index);//画幂函数
void OLED12864_DisThro(unsigned char x,unsigned char y,unsigned char width,unsigned char height,int MaxX,float index,float kndex);//画油门曲线

#endif
