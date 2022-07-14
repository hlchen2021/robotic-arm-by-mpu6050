#include "USART.h"

/********************************************************************
*名    称:void USART1_Configuration(void)
*功    能:USART1配置函数 对应的IO初始化
*入口参数:State：0端口未重映射
				 1端口重映射
*出口参数:无
*说    明:	未映射TX:PA9  RX:PA10
			重映射TX:PB6  RX:PB7
*调用方法:无
********************************************************************/
extern void USART1_Configuration(unsigned char State)
{
	USART_InitTypeDef USART_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;							//定义GPIO结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			//开启APB2时钟 端口复用功能	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);			//开启APB1 USATR1时钟
	
	switch(State)
	{
		case 0://USART1 未重映射
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//配置TX	//开启 GPIOA模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;							//配置PA9
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;					//配置端口的速度	
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;					//配置端口模式为复用推挽输出模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化	
						
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//配置RX				//配置PA10端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;				//配置端口模式为浮空输出模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化
		break;
		case 1://USART1 重映射
			GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE); 
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//配置TX	//开启 GPIOA模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;							//配置PB6
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;					//配置端口的速度	
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;					//配置端口模式为复用推挽输出模式
			GPIO_Init(GPIOB,&GPIO_InitStructure);							//对端口进行初始化	
						
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;//配置RX					//配置PB7端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;				//配置端口模式为浮空输出模式
			GPIO_Init(GPIOB,&GPIO_InitStructure);							//对端口进行初始化
		break;
		default:
		break;	
	}
	USART_InitStructure.USART_BaudRate = 9600; 						//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 	//数据位8
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 			//停止位1
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验 
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;  								//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//使能接收和发送  
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);					//接收中断标志使能
	USART_Cmd(USART1, ENABLE);										//串口外设使能
	USART_ClearFlag(USART1,USART_FLAG_TC);							//清除发送使能标志位
}
/********************************************************************
*名    称:void USART2_Configuration(void)
*功    能:USART2配置函数 对应的IO初始化
*入口参数:State 0：端口未重映射
				1：端口重映射
*出口参数:无
*说    明:未重映射 TX:PA2  RX:PA3
		  端口重映射 TX:PD5  RX:PD6
*调用方法:无
********************************************************************/
extern void USART2_Configuration(unsigned char State)
{
	USART_InitTypeDef USART_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;							//定义GPIO结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			//开启APB2时钟 端口复用功能	(不用于GOPIO需打开)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);			//开启APB2 USATR2时钟
	
	switch(State)
	{
		case 0://USART2 未重映射
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//配置TX	//开启 GPIOA模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;							//配置PA2
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;					//配置端口的速度	
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;					//配置端口模式为复用推挽输出模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化	
						
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;//配置RX					//配置PA3端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;				//配置端口模式为浮空输出模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化
		break;
		case 1://USART2 重映射
			GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE); 
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//配置TX	//开启 GPIOD模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;							//配置PD5
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;					//配置端口的速度	
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;					//配置端口模式为复用推挽输出模式
			GPIO_Init(GPIOD,&GPIO_InitStructure);							//对端口进行初始化	
						
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;//配置RX					//配置PD6端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;				//配置端口模式为浮空输出模式
			GPIO_Init(GPIOD,&GPIO_InitStructure);							//对端口进行初始化
		break;
		default:
		break;	
	}
	
	USART_InitStructure.USART_BaudRate = 9600; 						//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 	//数据位8
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 			//停止位1
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验 
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;  								//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//使能接收和发送  
	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE,ENABLE);					//接收中断标志使能
	USART_Cmd(USART2, ENABLE);										//串口外设使能
	USART_ClearFlag(USART2,USART_FLAG_TC);							//清除发送使能标志位
}
/********************************************************************
*名    称:void USART3_Configuration(void)
*功    能:USART2配置函数 对应的IO初始化
*入口参数:State 0：端口未重映射
				1：端口部分重映射
*出口参数:无
*说    明:端口未重映射 TX:PB10  RX:PB11
		  部分重映射   TX:PC10  RX:PC11
*调用方法:无
********************************************************************/
extern void USART3_Configuration(unsigned char State)
{
	USART_InitTypeDef USART_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;							//定义GPIO结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			//开启APB2时钟 端口复用功能	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);			//开启APB2 USATR3时钟
		
	switch(State)
	{
		case 0://USART3 未重映射
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//配置TX	//开启 GPIOA模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;						//配置PB10端口
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;					//配置端口的速度	
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;					//配置端口模式为复用推挽输出模式
			GPIO_Init(GPIOB,&GPIO_InitStructure);							//对端口进行初始化	
						
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//配置RX				//配置PB11端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;				//配置端口模式为浮空输出模式
			GPIO_Init(GPIOB,&GPIO_InitStructure);							//对端口进行初始化	
		break;
		case 1://USART3 部分重映射
			GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);          
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//配置TX	//开启 GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;						//配置PC10
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;					//配置端口的速度	
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;					//配置端口模式为复用推挽输出模式
			GPIO_Init(GPIOC,&GPIO_InitStructure);							//对端口进行初始化	
						
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//配置RX				//配置PC11端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;				//配置端口模式为浮空输出模式
			GPIO_Init(GPIOC,&GPIO_InitStructure);							//对端口进行初始化
		break;
		default:
		break;	
	}
	USART_InitStructure.USART_BaudRate = 9600; 						//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 	//数据位8
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 			//停止位1
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验 
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;  								//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//使能接收和发送  
	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE,ENABLE);					//接收中断标志使能
	USART_Cmd(USART3, ENABLE);										//串口外设使能
	USART_ClearFlag(USART3,USART_FLAG_TC);							//清除发送使能标志位
}
/********************************************************************
*名    称:void USART4_Configuration(void)
*功    能:USART4配置函数 对应的IO初始化
*入口参数:无
*出口参数:无
*说    明:TX:PC10  RX:PC11
*调用方法:无
********************************************************************/
extern void USART4_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;							//定义GPIO结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			//开启APB2时钟 端口复用功能	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);			//开启APB2 USATR4时钟

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//配置TX	//开启 GPIOA模块的时钟
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;						//配置PC10端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;					//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;					//配置端口模式为复用推挽输出模式
	GPIO_Init(GPIOC,&GPIO_InitStructure);							//对端口进行初始化	
						
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//配置RX				//配置PC11端口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;				//配置端口模式为浮空输出模式
	GPIO_Init(GPIOC,&GPIO_InitStructure);							//对端口进行初始化	
	
	USART_InitStructure.USART_BaudRate = 9600; 						//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 	//数据位8
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 			//停止位1
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验 
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;  								//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//使能接收和发送  
	USART_Init(UART4, &USART_InitStructure);
	USART_ITConfig(UART4, USART_IT_RXNE,ENABLE);					//接收中断标志使能
	USART_Cmd(UART4, ENABLE);										//串口外设使能
	USART_ClearFlag(UART4,USART_FLAG_TC);							//清除发送使能标志位
}
/********************************************************************
*名    称:void USART4_Configuration(void)
*功    能:USART5配置函数 对应的IO初始化
*入口参数:无
*出口参数:无
*说    明:TX:PC12  RX:PD2
*调用方法:无
********************************************************************/
extern void USART5_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;							//定义GPIO结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			//开启APB2时钟 端口复用功能	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);			//开启APB2 USATR5时钟

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//配置TX	//开启 GPIOC模块的时钟
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;						//配置PC12端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;					//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;					//配置端口模式为复用推挽输出模式
	GPIO_Init(GPIOC,&GPIO_InitStructure);							//对端口进行初始化	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;//配置RX					//配置PD2端口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;				//配置端口模式为浮空输出模式
	GPIO_Init(GPIOD,&GPIO_InitStructure);							//对端口进行初始化	
	
	USART_InitStructure.USART_BaudRate = 9600; 						//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 	//数据位8
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 			//停止位1
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验 
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;  								//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//使能接收和发送  
	USART_Init(UART5, &USART_InitStructure);
	USART_ITConfig(UART5, USART_IT_RXNE,ENABLE);					//接收中断标志使能
	USART_Cmd(UART5, ENABLE);										//串口外设使能
	USART_ClearFlag(UART5,USART_FLAG_TC);							//清除发送使能标志位
}

