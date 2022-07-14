#include "ADC.h"
/********************************************************************
*ADC1的通道关系
CH0：PA0
CH1：PA1
CH2：PA2
// CH3：PA3
// CH4：PA4
// CH5：PA5
// CH6：PA6
// CH7：PA7
// CH8：PB0
// CH9：PB1
CH10：PC0
CH11：PC1
CH12：PC2
CH13：PC3
// CH14：PC4
// CH15：PC5

Mini板
CH0 CH1 CH2 CH10 CH11 CH12 CH13
********************************************************************/
unsigned char ADC_CalibrationFlag=1;//ADC校准标志位
/********************************************************************
*名    称:void ADC1_Configuration(void)
*功    能:ADC1配置函数 
*入口参数:无
*出口参数:无
*说    明:单次独立转换 
*调用方法:无
********************************************************************/
void ADC1_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);					//开启ADC1模块的时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);									//ADC时钟6分频为12M
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					//独立工作模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						//设置扫描模式为单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					//工作方式设置为单次工作模式
	ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;	//触发方式为软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				//数据对齐方式为右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;								//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);
}
/********************************************************************
*名    称:void ADC1_CHInit(unsigned char CH)
*功    能:ADC1 通道配置函数 包括io设置
*入口参数:CH：ADC1的通道 0~15
*出口参数:无
*说    明:无 
*调用方法:无
********************************************************************/
void ADC1_CHInit(unsigned char CH)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	if(ADC_CalibrationFlag==1)							//只在开机时运行一次
	{
		ADC_Cmd(ADC1, ENABLE);							//ADC1转换器启动
		ADC_ResetCalibration(ADC1);						//重置ADC1的校准寄存器
		while(ADC_GetResetCalibrationStatus(ADC1));		//检测校准寄存器的状态
		ADC_StartCalibration(ADC1);						//ADC1开始校准
		while(ADC_GetCalibrationStatus(ADC1));			//校准完成
	}	
	switch(CH)
	{
		case 0:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;							//配置PA0端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;											//ADC校准标志位清0
		break;
		case 1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;							//配置PA1端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;				
		break;
		case 2:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;							//配置PA2端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;			
		break;
		case 3:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;							//配置PA3端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;				
		break;
		case 4:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;							//配置PA4端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;	
		break;
		case 5:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;							//配置PA5端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;	
		break;
		case 6:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;							//配置PA6端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;	
		break;
		case 7:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;							//配置PA7端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOA,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;	
		break;
		case 8:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;							//配置PB0端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOB,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;	
		break;
		case 9:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;							//配置PB1端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOB,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;	
		break;
		case 10:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;							//配置PC0端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOC,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;											//ADC校准标志位清0
		break;
		case 11:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;							//配置PC1端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOC,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;											//ADC校准标志位清0
		break;
		case 12:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;							//配置PC2端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOC,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;											//ADC校准标志位清0
		break;
		case 13:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;							//配置PC3端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOC,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;											//ADC校准标志位清0
		break;
		case 14:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;							//配置PC4端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOC,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;											//ADC校准标志位清0
		break;
		case 15:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);			//开启GPIOC模块的时钟
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;							//配置PC5端口
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;						//配置端口模式为模拟输入模式
			GPIO_Init(GPIOC,&GPIO_InitStructure);							//对端口进行初始化	
			ADC_CalibrationFlag=0;											//ADC校准标志位清0
		break;
		default:break;	
	}

}
/********************************************************************
*名    称:unsigned int GetADC1Value(unsigned char CH)
*功    能:获取ADC1通道数据
*入口参数:CH：ADC1的通道 0~15
*出口参数:ADC1通道数据
*说    明:无 
*调用方法:无
********************************************************************/
unsigned int GetADC1Result(unsigned char CH)
{
	unsigned int ADCValue=0;
	ADC_RegularChannelConfig(ADC1,CH, 1,ADC_SampleTime_1Cycles5);	//设置ADC1通道0的采样循序为1,采样时间为7.5个周期
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);							//ADC1的软件转换启动功能
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));					//判断是否转换完成
	ADCValue = ADC_GetConversionValue(ADC1);
	return ADCValue;
}
/********************************************************************
*名    称:unsigned int GetADC1Average(unsigned char CH)
*功    能:中间值滤波算法
*入口参数:CH：ADC1的通道 0~15
*出口参数:ADC1通道数据
*说    明:采样若干次 舍弃较大数据和较小的数据 然后将中间值平均 
*调用方法:无
********************************************************************/
#define N 300													//采样次数
#define BAN 100													//舍弃数据的个数
unsigned int GetADC1Average(unsigned char CH)  					//获得通道平均值
{ 
	uint16_t  AdcValueBuf[N]={0},AdcValuetemp=0; 
	unsigned int count=0,i=0,j=0;
	uint32_t sum=0;
	for(count=0;count<N;count++) 
	AdcValueBuf[count]=GetADC1Result(CH); 
	for(j=0;j<N-1;j++) 
	{ 
		for(i=0;i<N-j-1;i++) 
		{ 
			if(AdcValueBuf[i]>AdcValueBuf[i+1]) 
			{ 
				AdcValuetemp=AdcValueBuf[i]; 
				AdcValueBuf[i]=AdcValueBuf[i+1]; 
				AdcValueBuf[i+1]=AdcValuetemp; 
			} 
		} 
	}
	for(count=BAN;count<N-BAN;count++) 
	sum+=AdcValueBuf[count]; 
	return ((unsigned int)((float)sum/(N-BAN*2))); 
}

