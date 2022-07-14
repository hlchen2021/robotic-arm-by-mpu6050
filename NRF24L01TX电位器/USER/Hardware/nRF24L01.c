#include "nRF24L01.h"
#include "Delay.h"
#include "SPI_OLED.h"
/*
nRF24L01模块管脚说明
GND：接地
Vcc：电压范围1.9V~3.6V
CE： （发送模式下）置高会启动发送
     （接收模式下）置高会启动接收
CSN：置低使能，SPI片选使能引脚
SCK：时钟信号引脚
MOSI：主机数据输出、从机数据输出
MISO：主机数据输入、从机数据输出

工作模式：
nRF24L01有两种工作模式，一种是ShockBurst模式
一种是 Enhanced ShockBurst模式（即自动应答模式），两种模式
的区别在于Enhanced ShockBurst模式在发送过程中会要求接收设备
产生应答信号，以便发送发检测数据是否丢失，一旦丢失将重发丢失数据
将丢失的数据恢复。注意在自动应答模式下产生应答信号和数据的自动
重发都是自动完成的。

Enhanced ShockBurst发送模式下的流程：
1，配置自动应答通道使能（发送完一包数据后自动进入接收应答信号状态，
每次发送一包数据）。
2，设置自动重发次数不为0。这两步是开启Enhance ShockBurst模式的关键
3，写入发送数据设备和接收数据设备的地址。
4，CE置高启动发送。
5，启动发射以后会遇到两种情况
   a，在有限的时间内收到应答信号，TX_DS置高（发送数据成功标志位），
   并引发IRQ中断（引脚IRQ置低）， 并清除TX_FIFO(此为发送缓冲寄存器，
   自动清除)，IRQ中断需要写状态寄存器进行复位（此处的IRQ由TX_DS引发
   将TX_DS复位即可使IRQ复位）
   b，重发数据超过了设定值，MAX_RT置高（达到最多重发次数标志位），并
   引发IRQ中断（引脚IRQ置低），不清除TX_FIFO，IRQ中断需要写状态寄存器
   进行复位（此处的IQR由MAX_RT引发，将MAX_RT复位即可将IRQ复位）
6，接收到应答信号产生中断或者达到最大重发次数产生中断后，会继续发送
   下一包数据。
7，当TX_FIFO为空时，进入待机模式二

Enhanced ShockBurst接收模式的流程：
1，设置数据通道自动应答使能（EN_AA寄存器设置），此步是开启自动应答的关键
   使能接收数据通道（EN_RXADDR寄存器设置），设置接收模式。
2，CE置高，启动接收状态。
3，接收到一个有效数据包后，数据存储在RX_FIFO并产生RX_DR中断
  （RX_DR为接收数据成功标志位，接收成功置1），中断和发送模式一应
  同样需要复位。
4，接收设备自动向发送设备发送应答确认信号。
5，CE置低，NRF24L01进入待机模式1
6，读取数据


发送流程：
配置nrf:
写入发送地址和接收地址
CE置高，启动发送

接收过程
配置nrg
CE置高，启动接收
读取nrf数据
*/

/*
///////////////////////////引脚定义///////////////////////////////////////
CE 		PA11    推挽输出	
CSN 	PA12   	推挽输出	
SCK 	PC9    	推挽输出	
MISO 	PC7 	上拉输入
MOSI 	PA8		推挽输出
IRQ 	PC8		上拉输入
*/

#define CE_Pin        	GPIO_Pin_11
#define CE_GPIO       	GPIOA
#define CE_APB_GPIO		RCC_APB2Periph_GPIOA

#define CSN_Pin        	GPIO_Pin_12
#define CSN_GPIO       	GPIOA
#define CSN_APB_GPIO	RCC_APB2Periph_GPIOA

#define SCK_Pin        	GPIO_Pin_9
#define SCK_GPIO       	GPIOC
#define SCK_APB_GPIO	RCC_APB2Periph_GPIOC

#define MISO_Pin        GPIO_Pin_7
#define MISO_GPIO       GPIOC
#define MISO_APB_GPIO	RCC_APB2Periph_GPIOC

#define MOSI_Pin        GPIO_Pin_8
#define MOSI_GPIO       GPIOA
#define MOSI_APB_GPIO	RCC_APB2Periph_GPIOA

#define IRQ_Pin        	GPIO_Pin_8
#define IRQ_GPIO       	GPIOC
#define IRQ_APB_GPIO	RCC_APB2Periph_GPIOC

#define CE_HIGH() 		GPIO_SetBits(CE_GPIO,CE_Pin)			//CE置位
#define CE_LOW() 		GPIO_ResetBits(CE_GPIO,CE_Pin)			//CE清0
#define CSN_HIGH() 		GPIO_SetBits(CSN_GPIO,CSN_Pin)			//CSN置位
#define CSN_LOW() 		GPIO_ResetBits(CSN_GPIO,CSN_Pin)		//CSN清0
#define SCK_HIGH() 		GPIO_SetBits(SCK_GPIO,SCK_Pin)			//SCK置位
#define SCK_LOW() 		GPIO_ResetBits(SCK_GPIO,SCK_Pin)		//SCK清0
#define MOSI_HIGH() 	GPIO_SetBits(MOSI_GPIO,MOSI_Pin)		//MOSI置位
#define MOSI_LOW() 		GPIO_ResetBits(MOSI_GPIO,MOSI_Pin)		//MOSI清0		

unsigned char INIT_ADDR[5]={0x05,0x06,0x0a,0x0b,0x0c};//初始化地址
unsigned char CE_Status=0;

/******************************************************
** 功能：  nRF24L01有关的端口初始化
** 参数：  无
** 返回值：无
******************************************************/
void IOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;						//定义GPIO结构体	
	RCC_APB2PeriphClockCmd(CE_APB_GPIO,ENABLE);						//开启CE_GPIO模块的时钟
	GPIO_InitStructure.GPIO_Pin=CE_Pin;							//配置CE_Pin端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(CE_GPIO,&GPIO_InitStructure);						//对端口进行初始化	
	
	RCC_APB2PeriphClockCmd(CSN_APB_GPIO,ENABLE);					//开启CSN_GPIO模块的时钟
	GPIO_InitStructure.GPIO_Pin=CSN_Pin;						//配置CSN_Pin端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(CSN_GPIO ,&GPIO_InitStructure);					//对端口进行初始化	
	
	RCC_APB2PeriphClockCmd(SCK_APB_GPIO,ENABLE);					//开启SCK_GPIO模块的时钟
	GPIO_InitStructure.GPIO_Pin=SCK_Pin;						//配置SCK_Pin端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(SCK_GPIO ,&GPIO_InitStructure);					//对端口进行初始化	

	RCC_APB2PeriphClockCmd(MISO_APB_GPIO,ENABLE);					//开启MISO_GPIO模块的时钟
	GPIO_InitStructure.GPIO_Pin=MISO_Pin;						//配置MISO_Pin端口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;					//配置端口模式为上拉输入模式
	GPIO_Init(MISO_GPIO ,&GPIO_InitStructure);					//对端口进行初始化	
	
	RCC_APB2PeriphClockCmd(MOSI_APB_GPIO,ENABLE);					//开启MOSI_GPIO模块的时钟
	GPIO_InitStructure.GPIO_Pin=MOSI_Pin;						//配置MOSI_Pin端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;				//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//配置端口模式为推挽输出模式
	GPIO_Init(MOSI_GPIO ,&GPIO_InitStructure);					//对端口进行初始化	
	
	RCC_APB2PeriphClockCmd(IRQ_APB_GPIO,ENABLE);					//开启IRQ_GPIO模块的时钟
	GPIO_InitStructure.GPIO_Pin=IRQ_Pin;						//配置IRQ_Pin端口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;					//配置端口模式为上拉输入模式
	GPIO_Init(IRQ_GPIO ,&GPIO_InitStructure);					//对端口进行初始化	

	CE_LOW();        											// 待机
	CSN_HIGH();      											// SPI禁止
	SCK_LOW();        											// SPI时钟置低
}
/******************************************************
** 功能：  通过spi总线发送一个字节，再读取一个字节
** 参数：  dat:要发送的字节
** 返回值：dat：读取的字节
******************************************************/
unsigned char SPI_ExchangeByte(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(dat&0x80)
		{MOSI_HIGH();}
		else
	    {MOSI_LOW();}
		SCK_HIGH();
		dat<<=1;
		//dat|=MISO;//如果使用avr 这句要改变
		dat|=GPIO_ReadInputDataBit(MISO_GPIO, MISO_Pin);
		SCK_LOW();
	}
	return dat;
}
unsigned char GetCEStatus( void )
{
	return CE_Status;
}
/******************************************************
** 功能：  设定CE引脚的状态
** 参数：  status 1：CE=1 0：CE=0
** 返回值：无
******************************************************/
void SetCE(unsigned char status)
{
    if(status==0)
    {CE_LOW();CE_Status=0;}
    else
    {CE_HIGH();CE_Status=1;}
}
/******************************************************
** 功能：  读取一个寄存器中的数据
** 参数：  寄存器的地址
** 返回值：读取的内容
******************************************************/
unsigned char ReadSingleReg(unsigned char Addr)
{
    unsigned char temp;
	//SetCE(0);
	CSN_LOW();
    SPI_ExchangeByte(nREAD_REG|Addr);
    temp = SPI_ExchangeByte(0x00);
    CSN_HIGH();
    return temp;
}

/******************************************************
** 功能：  向一个寄存器中的写入一个字节的数据
** 参数：  Addr：寄存器的地址 Value：写入的字节
** 返回值：无
******************************************************/
void WriteSingleReg(unsigned char Addr,unsigned char Value)
{
    unsigned char temp=GetCEStatus();
	SetCE(0);
	CSN_LOW();
    SPI_ExchangeByte(nWRITE_REG|Addr);//写入地址和写操作命令
    SPI_ExchangeByte(Value);
    CSN_HIGH();
	SetCE(temp);
}
/******************************************************
** 功能：  向一个寄存器中的写入多个字节的数据
** 参数：  StartAddr：寄存器开始地址
           *pBuff：存储数据的缓存
            Value：写入的字节的个数
** 返回值：无
******************************************************/
void WriteMultiReg(unsigned char StartAddr,unsigned char *pBuff,unsigned char Length)
{
    unsigned char i;
	unsigned char temp=GetCEStatus();
	SetCE(0);
    CSN_LOW();
    SPI_ExchangeByte(nWRITE_REG|StartAddr);
    for(i=0;i<Length;i++)
    {
        SPI_ExchangeByte(pBuff[i]);
    }
    CSN_HIGH();
	SetCE(temp);
}
/******************************************************
** 功能：  从寄存器中的读出多个字节的数据
** 参数：  StartAddr：寄存器开始地址
           *pBuff：存储数据的缓存
            Value：写入的字节的个数
** 返回值：无
******************************************************/
void ReadMultiReg(unsigned char StartAddr,unsigned char *pBuff,unsigned char Length)
{
    unsigned char i;
    CSN_LOW();
    SPI_ExchangeByte(nREAD_REG|StartAddr);
	for(i=0;i<Length;i++)
    {
        pBuff[i]=SPI_ExchangeByte(0);
    }
    CSN_HIGH();	
}
/******************************************************
** 功能：  清空TX FIFO寄存器
** 参数：  无
** 返回值：无
******************************************************/
void FlushTX(void)
{
    CSN_LOW();
    SPI_ExchangeByte(FLUSH_TX);
    CSN_HIGH();
}

/******************************************************
** 功能：  清空RX FIFO寄存器
** 参数：  无
** 返回值：无
******************************************************/
void FlushRX(void)
{
	CSN_LOW();
    SPI_ExchangeByte(FLUSH_RX);
    CSN_HIGH();
}

/******************************************************
** 功能：  空操作
** 参数：  无
** 返回值：无
******************************************************/
void Nopp(void)
{
	CSN_LOW();
    SPI_ExchangeByte(NOPP);
    CSN_HIGH();
}

/******************************************************
** 功能：  清除IRQ标志：RX_DR，TX_DS，MAX_RT ,即清除所有的中断标志
** 参数：  无			手册规定：将1写入中断标志位 中断被清除
** 返回值：状态寄存器内容
******************************************************/
void ClearIRQ(void)
{
    unsigned char temp = 0;
    //中断产生 IRQ低电平
    SetCE(0);
	CSN_LOW();
	temp = ReadSingleReg(STATUS); 
	WriteSingleReg(STATUS,temp);
    CSN_HIGH();
}

/******************************************************
** 功能：  读取IRQ标志，判断哪个中断生效
** 参数：  无
** 返回值：状态寄存器IRQ配置
******************************************************/
unsigned char ReadIRQSource( void )
{
	return ( ReadSingleReg(STATUS) & ( ( 1<<RX_DR ) | ( 1<<TX_DS ) | ( 1<<MAX_RT ) ) );
}

/******************************************************
** 功能：  写入TX地址
** 参数：  *pAddr:用于存放本机地址的缓存
            Addr_Length：地址长度
** 返回值：无
******************************************************/
void SetTXAddr(unsigned char *pAddr,unsigned char Addr_Length )
{
    unsigned char Length=(Addr_Length>5)?5:Addr_Length;
	WriteMultiReg(TX_ADDR,pAddr,Length);
}

/******************************************************
** 功能：  写入一个接收地址到一个通道0
** 参数：  PipeNum：通道号 0~5
            *pAddr:用于存放接受地址的缓存
            Addr_Length：地址长度
** 返回值：无
******************************************************/
void SetRXAddr(unsigned char PipeNum,unsigned char *pAddr,unsigned char Addr_Length )
{
    unsigned char Length=(Addr_Length>5)?5:Addr_Length;
    unsigned char pipe=(PipeNum>5)?5:PipeNum;
    WriteMultiReg(RX_ADDR_P0 + pipe, pAddr, Length );
}

/******************************************************
** 功能：  向TX——FIFO中写入有效数据
** 参数：  *pBuff:用于存放发送数据的缓存 最多可以写入32个字节
            nByte：数据包长度
** 返回值：无
******************************************************/
void WriteTXPayload(unsigned char *pBuff,unsigned char nBytes)
{
    unsigned char temp;
    //判断句式 为真执行32 非真执行nByte
    unsigned char length=(nBytes>32)?32:nBytes;
    FlushTX();
    CSN_LOW();
    SPI_ExchangeByte(WR_TX_PLOAD);
    for(temp=0;temp<length;temp++)
    {
        SPI_ExchangeByte(*(pBuff+temp));
    }
    CSN_HIGH();
}
/******************************************************
** 功能： nRF24L01模块初始化函数 发射和接收通用	 非自动应答模式
** 参数： 无
** 返回值：无
******************************************************/
void nRF24L01_InitNoAck(void)
{
	IOInit();
	SetCE(0);
	SetTXAddr(INIT_ADDR,5);  						//写入TX节点地址 接收模式无需配置
	SetRXAddr(0,INIT_ADDR,5);						//写入RX_ADDR地址
	WriteSingleReg(EN_AA,0x00);						//关闭自动应答
	WriteSingleReg(EN_RXADDR,(1<<ERX_P0));			//通道0接收数据使能
	WriteSingleReg(SETUP_RETR,0x00);				//关闭自动重发间隔时间
	WriteSingleReg(RF_CH,0x02);						//设置发射频率 最大值125
	WriteSingleReg(RF_SETUP,0x0f);					//设置发射功率0db,速率：2MBPS，低噪声增益开启
	WriteSingleReg(RX_PW_P0,20);					//写入通道0 RX——FIFO的有效地址宽度 接收模式无需配置 
	WriteSingleReg(CONFIG,0x0e);					//未配置 发送和接收模式PRIM_RX
	//配置基本工作模式参数，PWR_UP：上电 CRCO：16位CRC校验 EN_CRC:CRC使能
}
/******************************************************
** 功能： nRF24L01模块初始化函数 发射和接收通用	 自动应答模式
** 参数： 无
** 返回值：无
******************************************************/
void nRF24L01_InitAck(void)
{
	IOInit();
	SetCE(0);
	SetTXAddr(INIT_ADDR,5);  						//写入TX节点地址 接收模式无需配置
	SetRXAddr(0,INIT_ADDR,5);						//写入RX_ADDR地址
	WriteSingleReg(EN_AA,(1<<ENAA_P0));				//使能通道0自动应答
	WriteSingleReg(EN_RXADDR,(1<<ERX_P0));			//通道0接收数据使能
	WriteSingleReg(SETUP_RETR,0x1a);				//设置自动重发间隔时间：4000us+86us  最大自动重发次数：10次	 接收模式无需配置
	WriteSingleReg(RF_CH,0x02);						//设置发射频率 最大值125
	WriteSingleReg(RF_SETUP,0x0f);					//设置发射功率0db,速率：2MBPS，低噪声增益开启
	WriteSingleReg(RX_PW_P0,20);						//写入通道0 RX——FIFO的有效地址宽度 接收模式无需配置 
	WriteSingleReg(CONFIG,0x0e);					//未配置 发送和接收模式PRIM_RX
	//配置基本工作模式参数，PWR_UP：上电 CRCO：16位CRC校验 EN_CRC:CRC使能
}
/******************************************************
** 功能： 设置通道0有效地址宽度
** 参数： Length：有效地址字节数
** 返回值：无
******************************************************/
void SetPipe0Length(unsigned char Length)
{
	unsigned char len=(Length>32)?32:Length;//判断句式 为真执行32
	SetCE(0);
	WriteSingleReg(RX_PW_P0,len);
} 
/******************************************************
** 功能： 设置发射频率
** 参数： Frequency：发射频率跳变值 真正发射频率为2.4G+Frequency Frequency：0-125
** 返回值：无
******************************************************/
void SetFrequency(unsigned char Frequency)
{
	SetCE(0);
	WriteSingleReg(RF_CH,Frequency);		//设置发射频率 最大值125
} 
/******************************************************
** 功能： 设置发射功率
** 参数： Pow：0-3 3对应0db
** 返回值：无
******************************************************/
void SetPower(unsigned char Pow)
{
	SetCE(0);
	WriteSingleReg(RF_SETUP,Pow|0x08);		//设置发射频率 最大值125
}	
/******************************************************
** 功能： nRF24L01模块设置为发射模式
** 参数： 无
** 返回值：无
******************************************************/
void SetTxMode(void)
{
	unsigned char controlreg; 
	controlreg=ReadSingleReg(CONFIG);
	controlreg&=~(1<<PRIM_RX); 
	WriteSingleReg(CONFIG,controlreg);	
}
/******************************************************
** 功能： nRF24L01模块设置为接收模式
** 参数： 无
** 返回值：无
******************************************************/
void SetRxMode(void)
{
	unsigned char controlreg; 
	controlreg=ReadSingleReg(CONFIG);
	controlreg|=(1<<PRIM_RX); 
	WriteSingleReg(CONFIG,controlreg);	
}

/******************************************************
** 功能： 发送一包数据
** 参数： *pBuff:用于数据发送的数据缓存 长度应于nByte保持一致
		  nBytes:要发送的字节个数
** 返回值：无
******************************************************/
void nRF24L01_TxDat(unsigned char *pBuff,unsigned char nBytes)
{	
	unsigned char temp=0;
    unsigned char length=(nBytes>32)?32:nBytes;//判断句式 为真执行32 非真执行nByte
    SetCE(0);
	FlushTX();//清空txfifo
    CSN_LOW();
    SPI_ExchangeByte(WR_TX_PLOAD);
    for(temp=0;temp<length;temp++)
    {
        SPI_ExchangeByte(pBuff[temp]);
    }
    CSN_HIGH();
	SetCE(1);//CE置高，txfifo非空，开启发射	RF_SETUP
	Delayxus(200);
}
void nRF24L01_TxDat2(unsigned char *pBuff,unsigned char nBytes)	//避免产生重入
{	
	unsigned char temp=0;
    unsigned char length=(nBytes>32)?32:nBytes;//判断句式 为真执行32 非真执行nByte
    SetCE(0);
	FlushTX();//清空txfifo
    CSN_LOW();
    SPI_ExchangeByte(WR_TX_PLOAD);
    for(temp=0;temp<length;temp++)
    {
        SPI_ExchangeByte(pBuff[temp]);
    }
    CSN_HIGH();
	SetCE(1);//CE置高，txfifo非空，开启发射	RF_SETUP
	Delayxus(200);
}
/******************************************************
** 功能： 从缓存中读出一包数据
** 参数： *pBuff:用于数据发送的数据缓存 长度应于nByte保持一致
		  nBytes:要发送的字节个数
** 返回值：无
******************************************************/
void nRF24L01_RxDat(unsigned char *pBuff,unsigned char nBytes)
{	
	unsigned char temp;
    unsigned char length=(nBytes>32)?32:nBytes;//判断句式 为真执行32 非真执行nByte
	SetCE(0);	//ce=0才能操作寄存器
	CSN_LOW();
    SPI_ExchangeByte(RD_RX_PLOAD);
    for(temp=0;temp<length;temp++)
    {
       	pBuff[temp]=SPI_ExchangeByte(0);
    }
    CSN_HIGH();
	FlushRX();//清空txfifo
	Delayxus(20);
}
void nRF24L01_RxDat2(unsigned char *pBuff,unsigned char nBytes)
{	
	unsigned char temp;
    unsigned char length=(nBytes>32)?32:nBytes;//判断句式 为真执行32 非真执行nByte
	SetCE(0);	//ce=0才能操作寄存器
	CSN_LOW();
    SPI_ExchangeByte(RD_RX_PLOAD);
    for(temp=0;temp<length;temp++)
    {
       	pBuff[temp]=SPI_ExchangeByte(0);
    }
    CSN_HIGH();
	FlushRX();//清空txfifo
	Delayxus(20);
}
/******************************************************
** 功能： 在初始化后检测SPI功能是否正常
** 参数： 无
** 返回值：1：SPI不正常 0：SPI正常工作
******************************************************/
unsigned char nRF24L01_Test(void)
{
	unsigned char Temp;
	if(ReadSingleReg(CONFIG)!=0x2e)
	Temp=1;
	else Temp=0;
	return Temp;	
}
/******************************************************
** 功能： 初始设置函数
** 参数： 发送地址和接收得知
** 返回值：无
******************************************************/
void nRF24L01_Setup(unsigned char *ADDRp)
{
	nRF24L01_InitNoAck();					//无应答模式初始化 只有接受中断 没有发射中断
	WriteSingleReg(CONFIG,0x2e);			//关闭发射中断 未配置发送和接收模式PRIM_RX
	SetTXAddr(ADDRp,5);  					//写入TX节点地址 接收模式无需配置
	SetRXAddr(0,ADDRp,5);					//写入RX_ADDR地址
	SetPipe0Length(13);						//设置通道0有效数据位长度
	SetFrequency(77);						//设置频率2.4G+77mhz
	SetPower(3);							//设置发射功率0db  
	SetTxMode();							//设置为发送模式
}
/******************************************************
** 功能：读取IRQ引脚的状态，然后判断中断源
** 参数：无
** 返回值：0：无中断
1：发送中断
2：接收中断
3：最大发送中断
******************************************************/
unsigned char GetIRQStatus(void)
{
	unsigned char IRQStatus=0;
	if(GPIO_ReadInputDataBit(IRQ_GPIO, IRQ_Pin)==0)//IRQ引脚降为低电平 有中断产生
	{
		switch(ReadIRQSource())//判断中断
		{
			case (1<<TX_DS):IRQStatus=1; break;//发送中断
			case (1<<RX_DR): IRQStatus=2;break;//接收中断
			case (1<<MAX_RT): IRQStatus=3;break;//最大发送中断中断
		}
	}
	else IRQStatus=0;
	return IRQStatus;
}
/******************************************************
** 功能：CE置高等待接收收据的到来
** 参数：无
** 返回值：无
******************************************************/
void WaitingRX(void)
{
	SetCE(1);
}
/******************************************************
** 功能：nRF24L01调试函数
** 参数：无
** 返回值：无
******************************************************/
void nRF24L01_Debug(void)
{
	unsigned char nRF24L01_Dbug[16]={0};
	unsigned char DbugTemp[5],i;
	ReadMultiReg(TX_ADDR,nRF24L01_Dbug,5);		//读取发送地址
	ReadMultiReg(RX_ADDR_P0+0,DbugTemp,5);		//读取P0接收地址
	for(i=0;i<5;i++)
	nRF24L01_Dbug[i+5]=DbugTemp[i];
	nRF24L01_Dbug[10]=ReadSingleReg(EN_AA);		//0x00
	nRF24L01_Dbug[11]=ReadSingleReg(EN_RXADDR);	//0x01
	nRF24L01_Dbug[12]=ReadSingleReg(SETUP_RETR);//0x00
	nRF24L01_Dbug[13]=ReadSingleReg(RF_CH);		//0x6d
	nRF24L01_Dbug[14]=ReadSingleReg(RX_PW_P0);	//0x05
	nRF24L01_Dbug[15]=ReadSingleReg(CONFIG);	//0x2e
	
	OLED12864_DisStr(0,0,0,"Status:");			//检测模块工作状态
	if(nRF24L01_Test()==0)
	OLED12864_DisStr(42,0,0,"Normal");			//正常工作显示Normal
	else
	OLED12864_DisStr(42,0,0,"Error!");			//非正常显示Error！
	OLED12864_DisStr(0,8,0,"TX_add:");
	OLED12864_Format2(42,8,0,nRF24L01_Dbug[0]);
	OLED12864_Format2(60,8,0,nRF24L01_Dbug[1]);
	OLED12864_Format2(78,8,0,nRF24L01_Dbug[2]);
	OLED12864_Format2(96,8,0,nRF24L01_Dbug[3]);
	OLED12864_Format2(114,8,0,nRF24L01_Dbug[4]);
	OLED12864_DisStr(0,16,0,"RX_add:");
	OLED12864_Format2(42,16,0,nRF24L01_Dbug[5]);
	OLED12864_Format2(60,16,0,nRF24L01_Dbug[6]);
	OLED12864_Format2(78,16,0,nRF24L01_Dbug[7]);
	OLED12864_Format2(96,16,0,nRF24L01_Dbug[8]);
	OLED12864_Format2(114,16,0,nRF24L01_Dbug[9]);
	OLED12864_DisStr(0,24,0,"EN_AA:");
	OLED12864_Format2(36,24,0,nRF24L01_Dbug[10]);
	OLED12864_DisStr(54,24,0,"EN_RXADDR:");
	OLED12864_Format2(114,24,0,nRF24L01_Dbug[11]);
	OLED12864_DisStr(0,32,0,"SETUP_RETR:");
	OLED12864_Format2(66,32,0,nRF24L01_Dbug[12]);
	OLED12864_DisStr(0,40,0,"RF_CH:");
	OLED12864_Format2(36,40,0,nRF24L01_Dbug[13]);
	OLED12864_DisStr(54,40,0,"RX_PW_P0:");
	OLED12864_Format2(108,40,0,nRF24L01_Dbug[14]);
	OLED12864_DisStr(0,48,0,"CONFIG:");
	OLED12864_Format2(42,48,0,nRF24L01_Dbug[15]);
}

