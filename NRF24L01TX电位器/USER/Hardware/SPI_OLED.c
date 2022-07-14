#include "SPI_OLED.h"
#include "English_Font.h"
#include "Delay.h"

/*
CS =PB12;			//片选
D/C=PB13;			// 命令/数据
RST=PB14;			//复位
SDA=PB15;	(MOSI)	//master out slave in
			 MISO   //master in slave out	
SCL=PC6;	(SCLK)		//总线时钟
*/
#define CS_Pin        	GPIO_Pin_12
#define CS_GPIO       	GPIOB
#define CS_GPIO_CLK		RCC_APB2Periph_GPIOB

#define DC_Pin        	GPIO_Pin_13
#define DC_GPIO       	GPIOB
#define DC_GPIO_CLK		RCC_APB2Periph_GPIOB

#define RST_Pin        	GPIO_Pin_14
#define RST_GPIO       	GPIOB
#define RST_GPIO_CLK	RCC_APB2Periph_GPIOB

#define SDA_Pin        	GPIO_Pin_15
#define SDA_GPIO       	GPIOB
#define SDA_GPIO_CLK	RCC_APB2Periph_GPIOB

#define SCL_Pin        	GPIO_Pin_6
#define SCL_GPIO       	GPIOC
#define SCL_GPIO_CLK	RCC_APB2Periph_GPIOC

#define CS_SET() 			GPIO_SetBits(CS_GPIO,CS_Pin)				//CS置位
#define CS_RESET() 		GPIO_ResetBits(CS_GPIO,CS_Pin)			//CS清0
#define DC_SET() 			GPIO_SetBits(DC_GPIO,DC_Pin)				//DC置位
#define DC_RESET() 		GPIO_ResetBits(DC_GPIO,DC_Pin)			//DC清0
#define RST_SET() 		GPIO_SetBits(RST_GPIO,RST_Pin)			//RST置位
#define RST_RESET() 	GPIO_ResetBits(RST_GPIO,RST_Pin)		//RST清0
#define SDA_SET() 		GPIO_SetBits(SDA_GPIO,SDA_Pin)			//SDA置位
#define SDA_RESET() 	GPIO_ResetBits(SDA_GPIO,SDA_Pin)		//SDA清0
#define SCL_SET() 		GPIO_SetBits(SCL_GPIO,SCL_Pin)			//SCL置位
#define SCL_RESET() 	GPIO_ResetBits(SCL_GPIO,SCL_Pin)		//SCL清0
Point Buff;
Point Start;
unsigned char DisBuff[8][128]={0};//用于显示的缓存
void OLED12864_IoInit(void)				//对OLED的IO初始化
{	
	GPIO_InitTypeDef OLED_InitStructure;									//定义GPIO结构体
	RCC_APB2PeriphClockCmd(CS_GPIO_CLK,ENABLE);						//开启GPIO模块的时钟
	RCC_APB2PeriphClockCmd(DC_GPIO_CLK,ENABLE);						//开启GPIO模块的时钟
	RCC_APB2PeriphClockCmd(RST_GPIO_CLK,ENABLE);					//开启GPIO模块的时钟
	RCC_APB2PeriphClockCmd(SDA_GPIO_CLK,ENABLE);					//开启GPIO模块的时钟
	RCC_APB2PeriphClockCmd(SCL_GPIO_CLK,ENABLE);					//开启GPIO模块的时钟
	
	OLED_InitStructure.GPIO_Pin=CS_Pin;										//配置CS端口
	OLED_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	OLED_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(CS_GPIO,&OLED_InitStructure);								//对端口进行初始化	
	GPIO_SetBits(CS_GPIO, CS_Pin);												//初始输出高电位
	
	OLED_InitStructure.GPIO_Pin=DC_Pin;										//配置DC端口
	OLED_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	OLED_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(DC_GPIO,&OLED_InitStructure);								//对端口进行初始化	
	GPIO_SetBits(DC_GPIO, DC_Pin);												//初始输出高电位	
	
	OLED_InitStructure.GPIO_Pin=RST_Pin;									//配置RST端口
	OLED_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	OLED_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(RST_GPIO,&OLED_InitStructure);							//对端口进行初始化	
	GPIO_SetBits(RST_GPIO, RST_Pin);											//初始输出高电位	
	
	OLED_InitStructure.GPIO_Pin=SDA_Pin;									//配置SDA端口
	OLED_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	OLED_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(SDA_GPIO,&OLED_InitStructure);
	GPIO_SetBits(SDA_GPIO, SDA_Pin);											//初始输出高电位
	
	OLED_InitStructure.GPIO_Pin=SCL_Pin;									//配置SCL端口
	OLED_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	OLED_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(SCL_GPIO,&OLED_InitStructure);							//对端口进行初始化	
	GPIO_SetBits(SCL_GPIO, SCL_Pin);											//初始输出高电位
}

/********************************************************************
* 名称 : OLED12864_SendByte()
* 功能 : 按照液晶的SPI通信协议，发送一个字节的数据
* 输入 : temp:要写入的数据
* 输出 : 无
***********************************************************************/
void OLED12864_SendByte(unsigned char temp)
{
	unsigned int i;
	for(i=0;i<8;i++)
	{
		SCL_RESET();
		if(temp&0x80)//先写入高位
		SDA_SET();
		else 
		SDA_RESET();
		SCL_SET();
		temp=temp<<1;
	}
}

/********************************************************************
* 名称 : OLED12864_SendCom
* 功能 : 写入一个字节的串口指令 串口控制—格式11111ABC 
* 输入 : cmd
* 输出 : 无
***********************************************************************/
void OLED12864_SendCom(unsigned char cmd)
{
	CS_RESET();
	DC_RESET();
	OLED12864_SendByte(cmd);
	CS_SET();
}
/********************************************************************
* 名称 : OLED12864_SendData
* 功能 : 写入一个字节数据
* 输入 : dat
* 输出 : 无
***********************************************************************/
void OLED12864_SendData(unsigned char dat)
{
	CS_RESET();
	DC_SET();
	OLED12864_SendByte(dat);
	CS_SET();
}

void OLED12864_Init(void)
{
	OLED12864_IoInit();	//IO初始化
	RST_SET();   				
 	Delayxms(10); 
 	RST_RESET(); 				//低电平复位
 	Delayxms(10); 
 	RST_SET();   				//复位完毕 
 	Delayxms(10); 
 		
	OLED12864_SendCom(0xAE);//命令AE：关闭OLED面板 AF:ON 
	OLED12864_SendCom(0x02);//---set low column address
	OLED12864_SendCom(0x10);//---set high column address
	OLED12864_SendCom(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED12864_SendCom(0x81);//--set contrast control register
	OLED12864_SendCom(0xCF); // Set SEG Output Current Brightness
	OLED12864_SendCom(0xA1);//0xa0左右反置 0xa1正常
	OLED12864_SendCom(0xC8);//0xc0上下反置 0xc8正常
	OLED12864_SendCom(0xA6);//--set normal display
	OLED12864_SendCom(0xA8);//--set multiplex ratio(1 to 64)
	OLED12864_SendCom(0x3f);//--1/64 duty
	OLED12864_SendCom(0x81);//对比度设置
	OLED12864_SendCom(0xFF);//1~255;默认0X7F (亮度设置,越大越亮)
	OLED12864_SendCom(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED12864_SendCom(0x00);//-not offset
	OLED12864_SendCom(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED12864_SendCom(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED12864_SendCom(0xD9);//--set pre-charge period
	OLED12864_SendCom(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED12864_SendCom(0xDA);//--set com pins hardware configuration
	OLED12864_SendCom(0x12);
	OLED12864_SendCom(0xDB);//--set vcomh
	OLED12864_SendCom(0x40);//Set VCOM Deselect Level
	OLED12864_SendCom(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED12864_SendCom(0x02);//
	OLED12864_SendCom(0x8D);//--set Charge Pump enable/disable
	OLED12864_SendCom(0x14);//--set(0x10) disable
	OLED12864_SendCom(0xA4);// Disable Entire Display On (0xa4/0xa5)
	OLED12864_SendCom(0xA6);// Disable Inverse Display On (0xa6/a7) 
	OLED12864_SendCom(0xAF);//--turn on oled panel
	OLED12864_Clean();			//	
}
/*********将光标指向坐标（x，y）*********************
** 功能：  将光标指向坐标（x，y）
** 参数：  X：y:坐标 x 0-127 ,y 0-7
** 返回值：无
******************************************************/
void Location(unsigned char x,unsigned char y)
{
	OLED12864_SendCom(0xb0+y);//设置页
	OLED12864_SendCom(0x10+((x>>4)&0x0f));//设置列高4位
	OLED12864_SendCom(x&0x0f);//设置列低4位	
}
/*********OLED对比度调节************************************
** 功能：OLED对比度调节
** 参数：  vlcd：微调对比度数值 Vlcd：0x00~0xff 中间值：0x7f
** 返回值：无
******************************************************/
void OLED12864_TurnBias(unsigned char Vlcd)
{
	OLED12864_SendCom(0x81); 	//微调对比度命令  
 	OLED12864_SendCom(Vlcd); 	//微调对比度的值，要与命令0x81一起使用 可设置范围 0x00～0xff 	
}
/*********设置缓冲区指针坐标*********************
** 功能：  设置缓冲区指针坐标
** 参数：  x:0~127 y:0~63
** 返回值：无
******************************************************/
void OLED12864_Location(unsigned char x,unsigned char y)
{
	if(y>=LCD_Y) y=0;	//纠正错误纵坐标输入
	if(x>=LCD_X) x=0;	//纠正错误横坐标输入	
	Buff.y=y;			//设置纵坐标
	Buff.x=x;			//设置横坐标
}
/*********将整个缓冲区全部写入液晶*********************
** 功能：  将整个缓冲区全部写入液晶 即显示整个DisBuff的内容 调试用
** 参数：  无
** 返回值：无
******************************************************/
void RefreshAll(void)
{
	unsigned char i,j;
	Location(0,0);
	for(i=0;i<LCD_COLUMN;i++)
	{
		
		for(j=0;j<LCD_X;j++)
		{
			Location(j,i);
			OLED12864_SendData(DisBuff[i][j]);
		}	
	}
}
/*********将指定缓冲区指定区域写入*********************
** 功能：  将整个缓冲区指定区域写入
** 参数：  x:0-127 y:0-63  Width:0-127：长度 Height:0-63：高度		
** 返回值：无
******************************************************/
void Refresh(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height)
{
	unsigned char WidthI,HeightI;
	unsigned char StartRow,StartColumn,EndRow,EndColumn;
	StartRow=y/8;											//刷新起始行
	StartColumn=x;											//刷新起始列
	EndRow=(y+Height-1)/8;									//刷新终止行
	EndColumn=x+Width-1;
										//刷新终止列
	for(HeightI=StartRow;HeightI<=EndRow;HeightI++)			//刷新第height_i行	//刷新指定行
	{
		Location(StartColumn,HeightI);						//刷新该行的width列		//从行首开始刷新
		for(WidthI=StartColumn;WidthI<=EndColumn;WidthI++)	//刷新每行的指定列
		{
			OLED12864_SendData(DisBuff[HeightI][WidthI]);
		}
	}
}
/*********清除缓冲区1字节数据*********************
** 功能：  清除缓冲区1字节数据,x,y为该字节最低位起始坐标
** 参数：  x:0-127 y:0-63 
** 返回值：无
比如 ClearPointofBuf(15,25); 即清除当前点所在字节的坐标点 即清除点：
(15,25)(15,26)(15,27)(15,28)(15,29)(15,30)(15,31)(15,32)
******************************************************/
void ClearPointofBuf(unsigned char x,unsigned char y)
{
	unsigned char Column,ColumnBit;
	OLED12864_Location(x,y);
	Column=Buff.y/8;					//要清除的缓冲区的字节行坐标
	ColumnBit=Buff.y%8;				//坐标在该字节8bit的bit位置
	DisBuff[Column][Buff.x]&=~(0x01<<(ColumnBit));	//清除指向的缓冲区字节
	//if(ColumnBit) 
	//DisBuff[Column+1][Buff.x]&=~(0xff>>(8-ColumnBit));//字节跨两行就清除下一行
}
/*********写一个字节数据到缓冲区*********************
** 功能：  写一个字节数据到缓冲区，写入字节后x会自加
** 参数：  byte:要写入的字节 
** 返回值：无
******************************************************/
void WriteBytetoBuf(unsigned char byte)
{
	unsigned char Column,ColumnBit;	
	Column=Buff.y/8;							//要写的缓冲区的字节行坐标
	ColumnBit=Buff.y%8;						//坐标在该字节8bit的bit位置
	DisBuff[Column][Buff.x]|=byte<<(ColumnBit);	//将1字节数据写入DisBuff指向的缓冲区字节
	if(ColumnBit) DisBuff[Column+1][Buff.x]|=byte>>(8-ColumnBit);//字节跨两行就写下一行
	if(Buff.x>=LCD_X)							//到达行尾缓冲区指针自动跳转到下一行行首
	{
		Buff.x=0;
		Buff.y+=8;
		if(Buff.y>=LCD_Y)				  	//到达页面末尾，缓冲区指针跳到页面开头
		Buff.y=0;
	}
	else 
	Buff.x++;											//缓冲区指针指向下一列
}

void WriteRevBytetoBuf(unsigned char byte)
{
	unsigned char Column,ColumnBit,temp;	
	Column=Buff.y/8;							//要写的缓冲区的字节行坐标
	ColumnBit=Buff.y%8;
	temp=byte<<(ColumnBit);
	temp=~temp;
	temp=temp>>(ColumnBit);				//坐标在该字节8bit的bit位置
	temp=temp<<(ColumnBit);
	DisBuff[Column][Buff.x]|=temp;//将1字节数据写入DisBuff指向的缓冲区字节
	if(ColumnBit) 
	{
		temp=byte>>(8-ColumnBit);
		temp=~temp;
		temp=temp<<(8-ColumnBit);
		temp=temp>>(8-ColumnBit);
		DisBuff[Column+1][Buff.x]|=temp;
	}//字节跨两行就写下一行
	if(Buff.x>=LCD_X)							//到达行尾缓冲区指针自动跳转到下一行行首
	{
		Buff.x=0;
		Buff.y+=8;
		if(Buff.y>=LCD_Y)				  	//到达页面末尾，缓冲区指针跳到页面开头
		Buff.y=0;
	}
	else 
	Buff.x++;											//缓冲区指针指向下一列
}
/*********清空整个缓冲区*********************
** 功能：  清空整个缓冲区
** 参数：  无 
** 返回值：无
******************************************************/
void ClearAllBuf(void)
{
	unsigned char i,j;
	for(j=0;j<LCD_COLUMN;j++)
	{
		for(i=0;i<LCD_ROW;i++)
		DisBuff[j][i]=0x00; 				//写0到缓冲区以清除该字节数据
	}
}
/*********清空整个缓冲区并将缓冲区中数据全部写入*********************
** 功能：  清空整个缓冲区并送入数据
** 参数：  无 
** 返回值：无
******************************************************/
void OLED12864_Clean(void)
{
	ClearAllBuf();								//清除缓冲区
	RefreshAll();									//刷新 送入数据
}
/*********清空缓冲区指定区域*********************
** 功能：  清空缓冲区指定区域
** 参数：  x:0-127 y:0-63  Width:0-127 Height:0-63		
** 返回值：无
******************************************************/
void ClearBuf(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height)
{
	unsigned char i,j;	
	Height=y+Height;							//获得刷新的终止纵坐标
	Width=Width+x;								//获得刷新的终止横坐标
	for(j=y;j<Height;j++)
	{
		for(i=x;i<Width;i++)
		ClearPointofBuf(i,j);				//写0到缓冲区以清除该点
	}
}
/*********清空指定区域*********************
** 功能：  清空指定区域
** 参数：  x:0-127 y:0-63  Width:0-127 Height:0-63		
** 返回值：无
******************************************************/
void ClearArea(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height)
{
   ClearBuf(x,y,Width,Height);
   Refresh(x,y,Width,Height);			//刷新 指定区域
}

////////////////////高度为8的字符显示函数//////////////////////////////////////////////
/*********写一个(6*8)字符到缓冲区(不需要坐标，紧跟上个字符)*********************
** 功能：  写一个(6*8)字符到缓冲区
** 参数：  value:字符		
** 返回值：无
******************************************************/
void WriteChartoBuf(unsigned char value)
{
	unsigned char i;
	for(i=0;i<6;i++)							//连续写六个字节
	WriteBytetoBuf(Font6x8[value-0x20][i]);
}
/*********写一个反白(6*8)*********************
** 功能：  写一个反白(6*8)字符到缓冲区
** 参数：  value:字符		
** 返回值：无
******************************************************/
void WriteRevChartoBuf(unsigned char value)
{
	unsigned char i;
	for(i=0;i<6;i++)							//连续写六个字节
	WriteBytetoBuf(~Font6x8[value-0x20][i]);
}
/*********通过缓冲区写一个ASCII字符(6*8)并刷新(不需要坐标，紧跟上个字符)*********************
** 功能：  通过缓冲区写一个ASCII字符(6*8)并刷新
** 参数：  value:字符		
** 返回值：无
******************************************************/
void OLED12864_DisChar(unsigned char x,unsigned char y,unsigned char value)
{
	OLED12864_Location(x,y);
	Start.x=Buff.x;								//获得开始横坐标
	Start.y=Buff.y;								//获得开始纵坐标
	WriteChartoBuf(value);
	Refresh(Start.x,Start.y,6,8);	//刷新 指定区域
}
/*********刷新显示一个独立的字符*********************
** 功能：  刷新显示一个独立的字符
** 参数：  value:字符		
** 返回值：无
******************************************************/
void OLED12864_DisOneChar(unsigned char x,unsigned char y,bit Rev,unsigned char value)
{
	OLED12864_Location(x,y);
	Start.x=Buff.x;								//获得开始横坐标
	Start.y=Buff.y;								//获得开始纵坐标
	ClearBuf(Start.x,Start.y,6,8);
	OLED12864_Location(x,y); 
	if(Rev)
	WriteRevChartoBuf(value);
	else
	WriteChartoBuf(value);
	Refresh(Start.x,Start.y,6,8);	//刷新 指定区域
}



/*********写一个字符串(高度8)到缓冲区(不需要坐标，紧跟上个字符)*********************
** 功能：  写一个字符串(高度8)到缓冲区
** 参数：  *str：字符串	注意：字符串长度不能超过22	
** 返回值：字符串长度
******************************************************/
unsigned char WriteStrtoBuf(char * str)
{
	unsigned char str_len=0;
	while(*str!='\0')
	{
		WriteChartoBuf(*str++);
		str_len++;
	}
	return str_len;								//返回字符串长度
}
/*********写一个反白字符串(高度8)到缓冲区(不需要坐标，紧跟上个字符)*********************
** 功能：  写一个反白字符串(高度8)到缓冲区
** 参数：  *str：字符串		
** 返回值：字符串长度
******************************************************/
unsigned char WriteRevStrtoBuf(char * str)
{
	unsigned char str_len=0;
	while(*str!='\0')
	{
		WriteRevChartoBuf(*str++);
		str_len++;
	}
	return str_len;									//返回字符串长度
}
/*********写一个字符串(高度8)到缓冲区并刷新(不需要坐标，紧跟上个字符)*********************
** 功能：  写一个字符串(高度8)到缓冲区并刷新 
			注意刷新范围为字符串所在的行 字符串显示不超过一行 对于128*64 最多不超过21个字符
** 参数：  	x:0-127 横坐标 
			y:0-63 纵坐标
			Rev：0：正常显示 1：反白显示
			*str：字符串		
** 返回值：字符串长度
******************************************************/
unsigned char OLED12864_DisStr(unsigned char x,unsigned char y,bit Rev,char * str)
{
	unsigned char Width,Height,str_len;	
	OLED12864_Location(x,y);
	Start.x=Buff.x;								//获得开始横坐标
	Start.y=Buff.y;								//获得开始纵坐标
	if(Rev)
	str_len=WriteRevStrtoBuf(str);
	else
	str_len=WriteStrtoBuf(str);
	Height=8;											//获得刷新高度
	Width=str_len*6;;		          //获得字符串起始纵坐标
	Refresh(Start.x,Start.y,Width,Height);			//刷新显示区域
	return str_len;								//返回字符串长度
}
/*********显示反白字符串*********************
** 功能：  显示反白字符串
			注意刷新范围为字符串所在的行 字符串显示不超过一行
** 参数：  *str：字符串		
** 返回值：字符串长度
******************************************************/
unsigned char OLED12864_DisRevStr(char * str)
{
	unsigned char Width,Height,str_len;	
	Start.x=Buff.x;								//获得开始横坐标
	Start.y=Buff.y;								//获得开始纵坐标
	str_len=WriteRevStrtoBuf(str);
	Height=8;											//获得刷新高度
	Width=str_len*6;;		          //获得字符串起始纵坐标
	Refresh(Start.x,Start.y,Width,Height);			//刷新显示区域
	return str_len;								//返回字符串长度
}
/*-------将一个数字转化为字符串并6*8显示------------------------------------------------
** 功能：将一个数字转化为字符串并显示  
		 如果要改变显示格式 就要改变sprintf函数的命令格式符
		 如果要改变显示长度  就要改变str[]数组的长度
** 参数： temp:要显示的变量 
		   
** 返回值：无 	
-----------------------------------------------------------------------*/
void OLED12864_Format1(unsigned char x,unsigned char y,bit Rev,unsigned int temp)
{
    char str[5];
	unsigned char L;
    //sprintf(str,"%d",temp);  	//产生“123″
    L=sprintf(str,"%04d",temp); //产生“0123″
	ClearBuf(x,y,L*6,8);
    OLED12864_DisStr(x,y,Rev,str);
}
void OLED12864_Format2(unsigned char x,unsigned char y,bit Rev,unsigned int temp)
{
    char str[5];
	unsigned char L;
    L=sprintf(str,"%02x",temp); //产生“01″
	ClearBuf(x,y,L*6,8);
    OLED12864_DisStr(x,y,Rev,str);
}
void OLED12864_Format3(unsigned char x,unsigned char y,bit Rev,unsigned int temp)
{
    char str[4];
	unsigned char L;
    //sprintf(str,"%d",temp);  //产生“123″
    L=sprintf(str,"%02d",temp);//产生“001″
	ClearBuf(x,y,L*6,8);
    OLED12864_DisStr(x,y,Rev,str);
}							 	
void OLED12864_Format4(unsigned char x,unsigned char y,bit Rev,float temp)
{
    char str[10];
	unsigned char L;
    //sprintf(str,"%d",temp);  //产生“123″
    L=sprintf(str,"%04.1f",temp);//产生“1.22V″
	ClearBuf(x,y,L*6,8);
    OLED12864_DisStr(x,y,Rev,str);
}
void OLED12864_Format5(unsigned char x,unsigned char y,bit Rev,unsigned int temp)
{
    char str[4];
	unsigned char L;
    //sprintf(str,"%d",temp);  //产生“123″
    L=sprintf(str,"%02x",temp);//产生“0xff″
	ClearBuf(x,y,L*6,8);
    OLED12864_DisStr(x,y,Rev,str);
}

////////////////高度为12的字符显示函数///////////////////////////////////////////////
/*-------写一个ASCII字符(8*12)到缓冲区------------------------------------------------
** 功能：写一个ASCII字符(8*12)到缓冲区  
** 参数： value:要显示的数字ASCII 		   
** 返回值：无 	
-----------------------------------------------------------------------*/
void WriteBigChar(unsigned char value)
{
	unsigned char i;
	for(i=0;i<8;i++)//写上面一行
	WriteBytetoBuf(Font8x12[value-0x20][i]);
	Buff.x=Buff.x-8;//写下面一行
	Buff.y=Buff.y+8;
	for(i=8;i<16;i++)
	WriteBytetoBuf(Font8x12[value-0x20][i]);
}
/*-------写一个反白ASCII字符(8*12)到缓冲区------------------------------------------------
** 功能：写一个反白ASCII字符(8*12)到缓冲区  
** 参数： value:要显示的数字ASCII 		   
** 返回值：无 	
-----------------------------------------------------------------------*/
void WriteBigRevChar(unsigned char value)
{
	unsigned char i;
	for(i=0;i<8;i++)//写上面一行
	WriteBytetoBuf(~Font8x12[value-0x20][i]);
	Buff.x=Buff.x-8;//写下面一行
	Buff.y=Buff.y+8;
	for(i=8;i<16;i++)
	WriteBytetoBuf((~(Font8x12[value-0x20][i]<<4))>>4);//只反白低4位
}

/*********显示一个8*12字符*********************
** 功能：  刷新显示一个8*12字符串
** 参数：  value:字符ASCIi Rev：是否反白		
** 返回值：无
******************************************************/
void OLED12864_DisBigChar(unsigned char value,bit Rev)
{
	Start.x=Buff.x;							//获得开始横坐标
	Start.y=Buff.y;							//获得开始纵坐标
	if(Rev)
	WriteBigRevChar(value);
	else
	WriteBigChar(value);
	Refresh(Start.x,Start.y,8,12);			//刷新 指定区域
}

/*********写一个8*12字符串到缓冲区*********************
** 功能：  写一个8*12字符串到缓冲区	,每行最多显示128/8个字符
** 参数：  *str：字符串	Rev：1：反白 0：不反白	
** 返回值：字符串长度
******************************************************/
unsigned char WriteBigStr(char * str,bit Rev)
{
	unsigned char str_len=0;
	while(*str!='\0')
	{
		if(Rev)
		WriteBigRevChar(*str++);
		else
		WriteBigChar(*str++);
		Buff.y=Buff.y-8;
		str_len++;
	}
	return str_len;										//返回字符串长度
}
void Write6BigStr(char * str,bit Rev)
{
	unsigned char i=0;
	for(i=0;i<6;i++)
	{
		if(Rev)
		WriteBigRevChar(*str++);
		else
		WriteBigChar(*str++);
		Buff.y=Buff.y-8;
	}
}										//返回字符串长度

/*********刷新显示一个独立8*12的字符*********************
** 功能：  刷新显示一个独立的字符
** 参数：  value:字符		
** 返回值：无
******************************************************/
void OLED12864_DisOneBigChar(unsigned char x,unsigned char y,bit Rev,unsigned char value)
{
	OLED12864_Location(x,y);
	Start.x=Buff.x;								//获得开始横坐标
	Start.y=Buff.y;								//获得开始纵坐标
	ClearBuf(Start.x,Start.y,8,12);
	OLED12864_Location(x,y); 
	if(Rev)
	WriteBigRevChar(value);
	else
	WriteBigChar(value);
	Refresh(Start.x,Start.y,8,12);			     //刷新 指定区域
}
/*********写一个字符串(高度12)到缓冲区并刷新(不需要坐标，紧跟上个字符)*********************
** 功能：  写一个字符串(高度12)到缓冲区并刷新 
			注意刷新范围为字符串所在的行 字符串显示不超过一行 对于128*64 最多不超过21个字符
** 参数：  	x:0-127 横坐标 
			y:0-63 纵坐标
			Rev：0：正常显示 1：反白显示
			*str：字符串		
** 返回值：字符串长度
******************************************************/
unsigned char OLED12864_DisBigStr(unsigned char x,unsigned char y,bit Rev,char * str)
{
	unsigned char Width,Height,str_len;	
	OLED12864_Location(x,y);
	Start.x=Buff.x;								//获得开始横坐标
	Start.y=Buff.y;
	if(Rev)										//获得开始纵坐标
	str_len=WriteBigStr(str,1);
	else
	str_len=WriteBigStr(str,0);
	Height=12;									//获得刷新高度
	Width=str_len*8;;		                 	//获得字符串起始纵坐标
	Refresh(Start.x,Start.y,Width,Height);			//刷新显示区域
	return str_len;								//返回字符串长度
}

void OLED12864_DisBigStr1(unsigned char x,unsigned char y,bit Rev,char * str)
{
	unsigned char Width,Height;	
	OLED12864_Location(x,y);
	Start.x=Buff.x;									//获得开始横坐标
	Start.y=Buff.y;
	if(Rev)											//获得开始纵坐标
	Write6BigStr(str,1);
	else
	Write6BigStr(str,0);
	Height=12;										//获得刷新高度
	Width=6*8;;		                 				//获得字符串起始纵坐标
	Refresh(Start.x,Start.y,Width,Height);			//刷新显示区域								//返回字符串长度
}
/*-------将一个变量转化为字符串并8*12显示------------------------------------------------
** 功能：将一个数字转化为字符串并显示  
		 如果要改变显示格式 就要改变sprintf函数的命令格式符
		 如果要改变显示长度  就要改变str[]数组的长度
** 参数： temp:要显示的变量 
		   
** 返回值：无 	
-----------------------------------------------------------------------*/
void OLED12864_BigFormat1(unsigned char x,unsigned char y,bit Rev,unsigned int temp)
{
    char str[5];
	unsigned char L;
    //L=sprintf(str,"%d",temp);  //产生“1″
    L=sprintf(str,"%04d",temp);  //产生“0123″
	ClearBuf(x,y,L*8,12);
    OLED12864_DisBigStr(x,y,Rev,str);
}
void OLED12864_BigFormat2(unsigned char x,unsigned char y,bit Rev,unsigned int temp)
{
    char str[5];
	unsigned char L;
    //L=sprintf(str,"%d",temp);  //产生“1″
    L=sprintf(str,"%02d",temp);  //产生“01″
	ClearBuf(x,y,L*8,12);
    OLED12864_DisBigStr(x,y,Rev,str);
}
void OLED12864_BigFormat3(unsigned char x,unsigned char y,bit Rev,float temp)
{
    char str[7];
	unsigned char L;
    //L=sprintf(str,"%d",temp);  //产生“1″
    L=sprintf(str,"%05.2fV",temp);  //产生“01.00v″
	ClearBuf(x,y,L*8,12);
    OLED12864_DisBigStr(x,y,Rev,str);
}
void OLED12864_BigFormat4(unsigned char x,unsigned char y,bit Rev,float temp)
{
    char str[10];
	unsigned char L;
    //L=sprintf(str,"%d",temp);  //产生“1″
    L=sprintf(str,"%03.1fV",temp);  //产生“01.1V″
	ClearBuf(x,y,L*8,12);
    OLED12864_DisBigStr(x,y,Rev,str);
}
void OLED12864_BigFormat5(unsigned char x,unsigned char y,bit Rev,unsigned int temp)
{
    char str[10];
	unsigned char L;
    //L=sprintf(str,"%d",temp);  //产生“1″
    L=sprintf(str,"%3d %",temp);  //产生“100%″
	ClearBuf(x,y,L*8,12);
    OLED12864_DisBigStr(x,y,Rev,str);
}
/*********写一个12X12汉字到缓冲区*********************
** 功能： 写一个12X12汉字符到缓冲区 
** 参数：  x:0-127 y:0-63 Hanzi[]:存放汉字数组 单行24个数值  Rev：反白 1：反白 0：正常显示 			
** 返回值：无
******************************************************/
void WriteBigCh(unsigned char x,unsigned char y,const unsigned char Hanzi[],bit Rev)
{
	unsigned char i;
	OLED12864_Location(x,y);//写上面一行
	for(i=0;i<12;i ++)
	{
		if(Rev)
		WriteBytetoBuf(~Hanzi[i]);
		else
		WriteBytetoBuf(Hanzi[i]);
	}
	OLED12864_Location(x,y+8);//写下面一行
	for(i=12;i<24;i++)
	{
		if(Rev)
		WriteBytetoBuf((~(Hanzi[i]<<4))>>4);
		else
		WriteBytetoBuf(Hanzi[i]);
	}
}
/*********显示一个12X12汉字*********************
** 功能： 显示一个12X12汉字 
** 参数：  x:0-83 y:0-48 Hanzi[]:存放汉字数组 Rev：反白  			
** 返回值：无
******************************************************/
void OLED12864_DisBigCh(unsigned char x,unsigned char y,const unsigned char Hanzi[],bit Rev)
{
	WriteBigCh(x,y,Hanzi,Rev);
	Refresh(x,y,12,12);	
}

/*********显示一个12X12汉字字符串*********************
** 功能： 显示一个12X12汉字字符串
** 参数：  x:0-127 y:0-63 Hanzi[][]:存放汉字数组 num:1-10 汉字个数 Rev：反白  			
** 返回值：无
******************************************************/
void OLED12864_DisBigChs(unsigned char x,unsigned char y,bit Rev,unsigned char num,const unsigned char Hanzi[][24])
{														
	unsigned char i;
	OLED12864_Location(x,y);//写上面一行
	for(i=0;i<num;i++)
	{
		WriteBigCh(x+i*12,y,Hanzi[i],Rev);	
	}
	Refresh(x,y,12*num,12);
}
/////////////////高度为16的字符显示函数////////////////////////////////////////////////
/*-------写一个ASCII字符(8*16)到缓冲区------------------------------------------------
** 功能：写一个ASCII字符(8*16)到缓冲区  
** 参数： temp:要显示的数字ASCII 		   
** 返回值：无 	
-----------------------------------------------------------------------*/
void WriteLargeChar(unsigned char value)
{
	unsigned char i;
	for(i=0;i<8;i++)//写上面一行
	WriteBytetoBuf(Font8x16[value-0x20][i]);
	Buff.x=Buff.x-8;//写下面一行
	Buff.y=Buff.y+8;
	for(i=8;i<16;i++)
	WriteBytetoBuf(Font8x16[value-0x20][i]);
}
/*-------写一个反白ASCII字符(8*16)到缓冲区------------------------------------------------
** 功能：写一个反白ASCII字符(8*16)到缓冲区  
** 参数： temp:要显示的数字ASCII 		   
** 返回值：无 	
-----------------------------------------------------------------------*/
void WriteLargeRevChar(unsigned char value)
{
	unsigned char i;
	for(i=0;i<8;i++)//写上面一行
	WriteBytetoBuf(~Font8x16[value-0x20][i]);
	Buff.x=Buff.x-8;//写下面一行
	Buff.y=Buff.y+8;
	for(i=8;i<16;i++)
	WriteBytetoBuf(~Font8x16[value-0x20][i]);
}

/*********显示一个8*16字符串*********************
** 功能：  刷新显示一个8*16字符串
** 参数：  value:字符ASCIi Rev：是否反白		
** 返回值：无
******************************************************/
void OLED12864_DisLargeChar(unsigned char value,bit Rev)
{
	Start.x=Buff.x;							//获得开始横坐标
	Start.y=Buff.y;							//获得开始纵坐标
	if(Rev)
	WriteLargeRevChar(value);
	else
	WriteLargeChar(value);
	Refresh(Start.x,Start.y,8,16);			//刷新 指定区域
}
/*********写一个8X16字符串到缓冲区*********************
** 功能：  写一个8X16字符串到缓冲区	,每行最多显示8个字符
** 参数：  *str：字符串	Rev：反白 0：不反白	
** 返回值：字符串长度
******************************************************/
unsigned char WriteLargeStr(char *str,bit Rev)
{
	unsigned char str_len=0;
	while(*str!='\0')
	{
		if(Rev)
		WriteLargeRevChar(*str++);
		else
		WriteLargeChar(*str++);
		Buff.y=Buff.y-8;
		str_len++;
	}
	return str_len;										//返回字符串长度
}

/*********显示一个8X16字符串*********************
** 功能：  显示一个8X16字符串 
** 参数：  *str：字符串	Rev：反白 0：不反白			
** 返回值：字符串长度
******************************************************/
unsigned char OLED12864_DisLargeStr(unsigned char x,unsigned char y,bit Rev,char *str)
{
	unsigned char Width,Height,str_len;	
	OLED12864_Location(x,y);
	Start.x=Buff.x;								//获得开始横坐标
	Start.y=Buff.y;
	if(Rev)								//获得开始纵坐标
	str_len=WriteLargeStr(str,1);
	else
	str_len=WriteLargeStr(str,0);
	Height=16;									//获得刷新高度
	Width=str_len*8;;		                 	//获得字符串起始纵坐标
	Refresh(Start.x,Start.y,Width,Height);			//刷新显示区域
	return str_len;								//返回字符串长度
}
/*-------将一个变量转化为字符串并8*16显示------------------------------------------------
** 功能：将一个数字转化为字符串并显示  
		 如果要改变显示格式 就要改变sprintf函数的命令格式符
		 如果要改变显示长度  就要改变str[]数组的长度
** 参数： temp:要显示的变量 
		   
** 返回值：无 	
-----------------------------------------------------------------------*/
void OLED12864_LargeFormat1(unsigned char x,unsigned char y,bit Rev,unsigned int temp)
{
    char str[5];
	unsigned char L;
    //L=sprintf(str,"%d",temp);  //产生“123″
    L=sprintf(str,"%04d",temp);  //产生“01″
	ClearBuf(x,y,L*8,16);
    OLED12864_DisLargeStr(x,y,Rev,str);
}
void OLED12864_LargeFormat2(unsigned char x,unsigned char y,bit Rev,float temp)
{
    char str[10];
	unsigned char L;
    //L=sprintf(str,"%d",temp);  //产生“123″
    L=sprintf(str,"%05.2fV",temp);  //产生“01″
	ClearBuf(x,y,L*8,16);
    OLED12864_DisLargeStr(x,y,Rev,str);
}


/*********写一个16X16汉字到缓冲区*********************
** 功能： 写一个16X16汉字符到缓冲区 
** 参数：  x:0-127 y:0-63 Hanzi[]:存放汉字数组 Rev：反白  			
** 返回值：无
******************************************************/
void WriteLargeCh(unsigned char x,unsigned char y,const unsigned char Hanzi[],bit Rev)
{
	unsigned char i;
	OLED12864_Location(x,y);//写上面一行
	for(i=0;i<16;i ++)
	{
		if(Rev)
		WriteBytetoBuf(~Hanzi[i]);
		else
		WriteBytetoBuf(Hanzi[i]);
	}
	OLED12864_Location(x,y+8);//写下面一行
	for(i=16;i<32;i++)
	{
		if(Rev)
		WriteBytetoBuf(~Hanzi[i]);
		else
		WriteBytetoBuf(Hanzi[i]);
	}
}
/*********显示一个16X16汉字*********************
** 功能： 显示一个16X16汉字 
** 参数：  x:0-127 y:0-63 Hanzi[]:存放汉字数组 Rev：反白  			
** 返回值：无
******************************************************/
void OLED12864_DisLargeCh(unsigned char x,unsigned char y,const unsigned char Hanzi[],bit Rev)
{
	WriteLargeCh(x,y,Hanzi,Rev);
	Refresh(x,y,16,16);	
}

/*********显示一个16X16汉字字符串*********************
** 功能： 显示一个16X16汉字字符串
** 参数：  x:0-127 y:0-63 Hanzi[][]:存放汉字数组 num:1-6 汉字个数 Rev：反白  			
** 返回值：无
******************************************************/
void OLED12864_DisLargeChStr(unsigned char x,unsigned char y,bit Rev,unsigned char num,const unsigned char Hanzi[][32])
{
	unsigned char i;
	OLED12864_Location(x,y);//写上面一行
	for(i=0;i<num;i++)
	{
		WriteLargeCh(x+i*16,y,Hanzi[i],Rev);	
	}
	Refresh(x,y,16*num,16);
}
///////////以下为画点，线，折线，矩形，圆，bmp图片函数////////////////////////////////////////////////////
/*********获得一个有符号字符型数的绝对值*********************
** 功能：  获得一个有符号字符型数的绝对值
** 参数：  无
** 返回值：绝对值
******************************************************/
unsigned char CharAbs(char a)
{
	if((unsigned char)a>=128)
	return 256-a;
	else 
	return a;
}
/*********交换两个无符号字符型变量位置*********************
** 功能：  交换两个无符号字符型变量位置
** 参数：  *a *b
** 返回值：绝对值
******************************************************/
void Swap(unsigned char *a,unsigned char *b)
{
	unsigned char temp;	
	temp=*a;
	*a=*b;
	*b=temp;
}
/*********画一个点到缓冲区*********************
** 功能： 画一个点到缓冲区
** 参数：  x:0-127 y:0-63   			
** 返回值：无
******************************************************/
void WritePoint(unsigned char x,unsigned char y)
{
	unsigned char row,line;
	row=y/8;//获得y方向起始坐标
	line=y%8;
	DisBuff[row][x]|=0x01<<(line);
}
/*********显示一个点*********************
** 功能： 显示一个点
** 参数：  x:0-127 y:0-63   			
** 返回值：无
******************************************************/
void DisPoint(unsigned char x,unsigned char y)
{
	WritePoint(x,y);
	Refresh(x,y,1,8);
}
/*********获得最小值*********************
** 功能： 获得最小值
** 参数：  a b  			
** 返回值：a,b中的最小值
******************************************************/
unsigned char Min(unsigned char a,unsigned char b)
{
	return a <= b? a : b;
}
/*********获得划线单位增加的大小*********************
** 功能： 获得划线单位增加的大小
** 参数：  x1 x2  			
** 返回值：
******************************************************/
short GetUnitAdd(unsigned char x1,unsigned char x2)
{
	if(x1 == x2)	
	return 0;
	else if(x2>x1) 
	return 1;
	else 
	return (-1);
}
/*********填充缓冲区指定区域*********************
** 功能：  清空缓冲区指定区域
** 参数：  x:0-127 y:0-63  Width:0-127 Height:0-63		
** 返回值：无
******************************************************/
static void FillBuf(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height)
{
	unsigned char i,j;	
	Height=y+Height;								//获得刷新的终止纵坐标
	Width=Width+x;									//获得刷新的终止横坐标
	for(j=y;j<Height;j++)
	{
		for(i=x;i<Width;i++)
		WritePoint(i,j);					     	//写1到缓冲区以清除该点
	}
}
/*********画一条线到缓冲区*********************
** 功能： 画一条线到缓冲区
** 参数：  x1：0-127 起始点横坐标 
		   y1：0-63 起始点纵坐标
		   x2：0-127 起始点横坐标
		   y2：0-63 起始点纵坐标	  			
** 返回值：无
******************************************************/		
void WriteLine(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2)
{
	unsigned char delt_x,delt_y,flag,i;
	short add_x,add_y,error;
	delt_x=CharAbs(x2-x1);		//计算Δx 取绝对值
	delt_y=CharAbs(y2-y1);		//计算Δy
	if(delt_y>delt_x) 		//如果斜率大于1，置位flag,交换delt_x和delt_y
	{
		flag = 1;										
		Swap(&delt_x,&delt_y);
	}
	else
	flag = 0;
	add_x=GetUnitAdd(x1,x2);	//x轴单位增量(-1,0或1)
	add_y=GetUnitAdd(y1,y2);	//y轴单位增量(-1,0或1)
	error=delt_y<<1-delt_x;		//算法改进后由error=delt_y/delt_x-0.5;变为error=2*delt_x*(delt_y/delt_x-0.5)=2*delt_y-delt_x;
	for(i=0;i<=delt_x;i++)		//横向扫描
	{
		WritePoint(x1,y1);		//画点
		if(error>=0)			//进行error>0时的增量计算
		{
			if(flag)			//斜率大于1的话，x轴进行增量计算
			x1+=add_x;
			else 
			y1+=add_y;			//斜率小于1的话，y轴进行增量计算
			error-=(delt_x<<1);
		}							
		if(flag)				//进行基本增良扑憧，即每次循环都会进行的增量计算//斜率大于1的话，y轴进行增量计算
		y1+=add_y;
		else 					//斜率小于1的话，x轴进行增量计算
		x1+=add_x;
		error+=(delt_y<<1);
	}
}
/*********显示一条线*********************
** 功能： 显示一条线
** 参数：  x1：0-127 起始点横坐标 
		   y1：0-63 起始点纵坐标
		   x2：0-127 起始点横坐标
		   y2：0-63 起始点纵坐标	  			
** 返回值：无
******************************************************/		
void OLED12864_DisLine(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2)
{
	unsigned char x,y,width,height;	
	width=CharAbs(x2-x1)+1;		//获得刷新宽度
	height=CharAbs(y2-y1)+1;	//获得刷新高度
	x=Min(x1,x2);				//获得刷新起始横坐标
	y=Min(y1,y2);				//获得刷新起始纵坐标
	WriteLine(x1,y1,x2,y2);
	Refresh(x,y,width,height);
}
/*********显示折线*********************
** 功能： 显示折线
** 参数：  *p：节点结构体数组
		  例如：PolyLine
		  code Point PolyLine[3]=
			{  
				{0,0},
				{20,30},
				{40,30},
			};	 
		   num：节点个数	  			
** 返回值：无
******************************************************/
void OLED12864_DisPolyline(const Point *p,unsigned char num)
{
	unsigned char i;
	for(i=0;i<num;i++)
	WriteLine(p[i].x,p[i].y,p[i+1].x,p[i+1].y);
	RefreshAll();//全部刷新显示
}



/*********画矩形*********************
** 功能： 画矩形
** 参数：  x1：0-127 矩形左上角横坐标 
		   y1：0-63 矩形左上角纵坐标
		   width：0-127 矩形宽度
		   height：0-63 矩形高度	  			
** 返回值：无
******************************************************/
void OLED12864_DisSqu(unsigned char x,unsigned char y,unsigned char width,unsigned char height,bit Rev)
{
	if(x>127) x=127;
	if(y>63) y=63;
	if(Rev)
	FillBuf(x,y,width,height);//范围内的空间全部显示
	WriteLine(x,y,x+width,y);
	WriteLine(x+width,y,x+width,y+height);
	WriteLine(x,y,x,y+height);
	WriteLine(x,y+height,x+width,y+height);
	Refresh(x,y,width+1,height+1);
}

/*********画圆*********************
** 功能： 画圆
** 参数：  center_x：0-127 圆心横坐标 
		   center_y：0-64 圆心左上角纵坐标
		   r：0-32 半径	  			
** 返回值：无
******************************************************/
void OLED12864_DisCircle(unsigned char center_x,unsigned char center_y,unsigned char r)
{
	unsigned char x=0,y=r;
	short d=5-(r<<2);		//判别式初值4*(1.25-r)				
	while(x <= y)
	{					//将圆分成对称8份分别画
		WritePoint(center_x+x,center_y+y);
		WritePoint(center_x+x,center_y-y);
		WritePoint(center_x-x,center_y+y);
		WritePoint(center_x-x,center_y-y);
		WritePoint(center_x+y,center_y+x);
		WritePoint(center_x+y,center_y-x);
		WritePoint(center_x-y,center_y+x);
		WritePoint(center_x-y,center_y-x);
		x++;
		if(d<0) 		//如果d<0判别式d=d+4*(2*x+3)
		d+=(x<<3)+12;
		else			//如果d>=0判别式d=d+4*(2*(x-y)+5)
		{
			y--;
			d+=(x<<3)-(y<<3)+20;
		}
	}
	Refresh(center_x-r,center_y-r,(r<<1)+1,(r<<1)+1);
}

/*********画Bmp图像*********************
** 功能： 画Bmp图像
** 参数：  x：0-127 图像左上角横坐标 
		   y：0-63 图像左上角纵坐标
		   width：0-128 图像宽度
		   height：0-64 图像高度
		   Rev：   是否反白 0：正常 1：反白
		   bitmap[]：存放图像的数组	  			
** 返回值：无
******************************************************/
/*void OLED12864_DisBmp(unsigned char x,unsigned char y,unsigned char width,unsigned char height,bit Rev,char bitmap[])
{
	unsigned int p=0;
	unsigned char HeightMax;
	unsigned char i,j;
	HeightMax=(height-1)/8+1;
	for(j=0;j<HeightMax;j++)//
	{
		OLED12864_Location(x,y+j*8);
		for(i=0;i<width;i++)//
		{		
			if(Rev)
			WriteRevBytetoBuf(bitmap[p++]);
			else
			WriteBytetoBuf(bitmap[p++]);
		}
	}
	Refresh(x,y,width,height);
}*/
void OLED12864_DisBmp(unsigned char x,unsigned char y,unsigned char width,unsigned char height,bit Rev,const unsigned char bitmap[])
{
	unsigned int p=0;
	unsigned char HeightMax;
	unsigned char i,j,combit,temp=0xff;
	HeightMax=(height-1)/8+1;
	combit=height%8;//有效数据位
	temp<<=combit;
	if(Rev)
	{
		if(combit)
		{
			for(j=0;j<HeightMax-1;j++)//
			{
				OLED12864_Location(x,y+j*8);
				for(i=0;i<width;i++)//
				WriteRevBytetoBuf(bitmap[p++]);
			}
			OLED12864_Location(x,y+(HeightMax-1)*8);
			for(i=0;i<width;i++)//
			WriteRevBytetoBuf(bitmap[p++]|temp);
		}
		else								 //8的整数倍行
		{
		   	for(j=0;j<HeightMax;j++)//
			{
				OLED12864_Location(x,y+j*8);
				for(i=0;i<width;i++)//
				WriteRevBytetoBuf(bitmap[p++]);
			}
		}
		

	}
	else
	{
		for(j=0;j<HeightMax;j++)//
		{
			OLED12864_Location(x,y+j*8);
			for(i=0;i<width;i++)//
			WriteBytetoBuf(bitmap[p++]);
		}
	}
	Refresh(x,y,width,height);
}

/*********画幂函数图像*********************
** 功能： 画B幂函数图像
** 参数：  x：0-127 图像左上角横坐标 
		   y：0-63 图像左上角纵坐标
		   width：0-128 图像宽度
		   height：0-64 图像高度
		   MAxX：x方向的最大值 y方向最大值=x
		   Rev：   正向负向显示 0：负向 1：正向
		   index：幂指数	  			
** 返回值：无
******************************************************/
void OLED12864_DisPower(unsigned char x,unsigned char y,unsigned char width,unsigned char height,int MaxX,bit Rev,float index)
{
	unsigned char i;
	unsigned int DeltaX,DeltaY,LocationY;
	DeltaX=MaxX/width;
	DeltaY=MaxX/height;
	
	if(Rev)
	{
		for(i=0;i<width;i++)
		{
			LocationY=pow(((float)i*DeltaX/512),index)*512;//获取Y方向的坐标
			LocationY=LocationY/DeltaY;
			if(LocationY>height) LocationY=height;
			WritePoint(x+i,y-LocationY);			
		}
		Refresh(x,y-height,width,height);
	}
	else
	{
		for(i=0;i<width;i++)
		{
			LocationY=pow(((float)i*DeltaX/512),index)*512;//获取Y方向的坐标
			LocationY=LocationY/DeltaY;
			if(LocationY>height) LocationY=height;
			WritePoint(x-i,y+LocationY);			
		}
		Refresh(x-width,y,width,height);
	}
}
/*********画油门函数图像*********************
** 功能： 画B幂函数图像
** 参数：  x：0-127 图像左上角横坐标 
		   y：0-63 图像左上角纵坐标
		   width：0-128 图像宽度
		   height：0-64 图像高度
		   MAxX：x方向的最大值 y方向最大值=x
		   Rev： 正向负向显示 0：负向 1：正向
		   index：幂指数
		   kndex：比例指数	  			
** 返回值：无
******************************************************/
void OLED12864_DisThro(unsigned char x,unsigned char y,unsigned char width,unsigned char height,int MaxX,float index,float kndex)
{
	unsigned char i;
	unsigned int DeltaX,DeltaY,LocationY;
	DeltaX=MaxX/width;
	DeltaY=MaxX/height;
	for(i=0;i<width;i++)
	{
		LocationY=1024*kndex*pow(((float)i*DeltaX/1024),index)+(1-kndex)*512;
		LocationY=LocationY/DeltaY;
		if(LocationY>height) LocationY=height;
		WritePoint(x+i,y-LocationY);			
	}
	Refresh(x,y-height,width,height);
}
