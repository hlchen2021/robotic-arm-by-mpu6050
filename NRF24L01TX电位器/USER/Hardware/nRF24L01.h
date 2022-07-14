#ifndef __NRF24L01_H__
#define __NRF24L01_H__
#include "stm32f10x.h"
#include "Delay.h"

// nRF24L01指令格式：
#define nREAD_REG            0x00 // 读寄存器
#define nWRITE_REG           0x20 // 写寄存器
#define RD_RX_PLOAD         0x61 // 读RX FIFO有效数据，1-32字节，当读数据完成后，数据被清除，应用于接收模式
#define R_RX_PL_WID         0x60 //	RX_FIFO中有效数据的长度
#define WR_TX_PLOAD         0xA0 // 写TX FIFO有效数据，1-32字节，写操作从字节0开始，应用于发射模式
#define FLUSH_TX            0xE1 // 清除TX FIFO寄存器，应用于发射模式
#define FLUSH_RX            0xE2 // 清除RX FIFO寄存器，应用于接收模式
#define REUSE_TX_PL         0xE3 // 重新使用上一包有效数据，当CE为高过程中，数据包被不断的重新发射
#define W_ACK_PAYLOAD       0xA8 // 
#define W_TX_PAYLOAD_NOACK  0xB0 //	TX模式中关闭自动应答
#define NOPP                0xFF // 空操作，可以用来读状态寄存器

// nRF24L01寄存器地址
#define CONFIG          0x00    // 配置寄存器
                                //reserved: bit7, only '0' allowed
    #define MASK_RX_DR   6      //RW, Mask interrupt caused by RX_DR
    #define MASK_TX_DS   5      //RW, Mask interrupt caused by TX_DS
    #define MASK_MAX_RT  4      //RW, Mask interrupt caused by MAX_RT
    #define EN_CRC       3      //RW, Enable CRC.
    #define CRCO         2      //RW, CRC encoding scheme, 0: 1 byte, 1: 2 bytes
    #define PWR_UP       1      //RW, Power up, 1: power up, 0: power down
    #define PRIM_RX      0      //RW, RX/TX control, 1: PRX, 0: PTX
#define EN_AA           0x01    // “自动应答”功能寄存器
                                //reserved: bit7-bit6:only '00' allowed
    #define ENAA_P5      5      //RW, Enable auto acknowledgement data pipe 5
    #define ENAA_P4      4      //RW, Enable auto acknowledgement data pipe 4
    #define ENAA_P3      3      //RW, Enable auto acknowledgement data pipe 3
    #define ENAA_P2      2      //RW, Enable auto acknowledgement data pipe 2
    #define ENAA_P1      1      //RW, Enable auto acknowledgement data pipe 1
    #define ENAA_P0      0      //RW, Enable auto acknowledgement data pipe 0
#define EN_RXADDR       0x02    // 接收通道使能寄存器
                                //reserved: bit7-bit6:only '00' allowed
    #define ERX_P5       5      //RW, Enable data pipe 5
    #define ERX_P4       4      //RW, Enable data pipe 4
    #define ERX_P3       3      //RW, Enable data pipe 3
    #define ERX_P2       2      //RW, Enable data pipe 2
    #define ERX_P1       1      //RW, Enable data pipe 1
    #define ERX_P0       0      //RW, Enable data pipe 0
#define SETUP_AW        0x03    // 地址宽度设置寄存器
#define SETUP_RETR      0x04    // 自动重发设置寄存器
#define RF_CH           0x05    // 射频通道频率设置寄存器
#define RF_SETUP        0x06    // 射频设置寄存器
#define STATUS          0x07    // 状态寄存器
                                //reserved, bit7, only '0' allowed
    #define RX_DR         6     //RW, Data ready RX FIFO interrupt
    #define TX_DS         5     //RW, Data sent TX FIFO interrupt
    #define MAX_RT        4     //RW, Maximum number of TX retransmits interrupt
                                //for bit3-bit1, R, Data pipe number for the payload available for reading from
                                //RX_FIFO, 000-101, Data pipe number, 110, not used, 111, RX FIFO empty
    #define TX_FULL_0     0     //R, TX FIFO full flag
#define OBSERVE_TX      0x08    // 发送检测寄存器
#define CD              0x09    // 载波检测寄存器
#define RX_ADDR_P0      0x0A    // 数据通道0接收地址寄存器
#define RX_ADDR_P1      0x0B    // 数据通道1接收地址寄存器
#define RX_ADDR_P2      0x0C    // 数据通道2接收地址寄存器
#define RX_ADDR_P3      0x0D    // 数据通道3接收地址寄存器
#define RX_ADDR_P4      0x0E    // 数据通道4接收地址寄存器
#define RX_ADDR_P5      0x0F    // 数据通道5接收地址寄存器
#define TX_ADDR         0x10    // 发送地址寄存器
#define RX_PW_P0        0x11    // 数据通道0有效数据宽度设置寄存器
#define RX_PW_P1        0x12    // 数据通道1有效数据宽度设置寄存器
#define RX_PW_P2        0x13    // 数据通道2有效数据宽度设置寄存器
#define RX_PW_P3        0x14    // 数据通道3有效数据宽度设置寄存器
#define RX_PW_P4        0x15    // 数据通道4有效数据宽度设置寄存器
#define RX_PW_P5        0x16    // 数据通道5有效数据宽度设置寄存器
#define FIFO_STATUS     0x17    // FIFO状态寄存器
                                //bit7, reserved, only '0' allowed
    #define TX_REUSE      6     //R,
    #define TX_FULL_1     5     //R, TX FIFO 满
    #define TX_EMPTY      4     //R, TX FIFO 空
                                //bit3-bit2, reserved, only '00'
    #define RX_FULL       1     //R, RX FIFO 满
    #define RX_EMPTY      0     //R, RX FIFO 空
#define     DYNPD      0x1C     //
                                //reserved, bit7-bit6, only '00' allowed
    #define DPL_P5        5     //RW, Enable dynamic payload length data pipe 5
    #define DPL_P4        4     //RW, Enable dynamic payload length data pipe 4
    #define DPL_P3        3     //RW, Enable dynamic payload length data pipe 3
    #define DPL_P2        2     //RW, Enable dynamic payload length data pipe 2
    #define DPL_P1        1     //RW, Enable dynamic payload length data pipe 1
    #define DPL_P0        0     //RW, Enable dynamic payload length data pipe 0
#define     FEATRUE    0x1D     //
                                //reserved, bit7-bit3, only '0000' allowed
    #define EN_DPL        2     //RW, Enables Dynamic payloard length
    #define EN_ACK_PAY    1     //RW, Enable Payload with ACK
    #define EN_DYN_ACK    0     //RW, Enables the W_TX_PAYLOAD_NOACK command

#define IRQ_ALL  ( (1<<RX_DR) | (1<<TX_DS) | (1<<MAX_RT) )

/////////////////////////函数声明///////////////////////////////////////
void IOInit(void);
unsigned char SPI_ExchangeByte(unsigned char dat);
unsigned char GetCEStatus(void);
void SetCE(unsigned char status);
unsigned char ReadSingleReg(unsigned char Addr);
void WriteSingleReg(unsigned char Addr,unsigned char Value);
void WriteMultiReg(unsigned char StartAddr,unsigned char *pBuff,unsigned char Length);
void ReadMultiReg(unsigned char StartAddr,unsigned char *pBuff,unsigned char Length);
void FlushTX(void);
void FlushRX(void);
void Nopp(void);
void ClearIRQ(void);
unsigned char ReadIRQSource(void);
void SetTXAddr(unsigned char *pAddr,unsigned char Addr_Length );
void SetRXAddr(unsigned char PipeNum,unsigned char *pAddr,unsigned char Addr_Length);
void WriteTXPayload(unsigned char *pBuff,unsigned char nBytes);

void SetTxMode(void);
void SetRxMode(void);
void nRF24L01_TxDat(unsigned char *pBuff,unsigned char nBytes);
void nRF24L01_RxDat(unsigned char *pBuff,unsigned char nBytes);
void nRF24L01_TxDat2(unsigned char *pBuff,unsigned char nBytes);
void nRF24L01_RxDat2(unsigned char *pBuff,unsigned char nBytes);
unsigned char nRF24L01_Test(void);
void nRF24L01_InitNoAck(void);
void nRF24L01_InitAck(void);
void SetPipe0Length(unsigned char Length);
void SetFrequency(unsigned char Frequency);
void SetPower(unsigned char Pow);
void nRF24L01_Setup(unsigned char *ADDRp);
unsigned char GetIRQStatus(void);
void WaitingRX(void);
void nRF24L01_Debug(void);
#endif
