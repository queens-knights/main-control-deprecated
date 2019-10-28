#include "dma.h"
#include "usart.h"	
#include "Util.h"

u8 DMA1_MEM_LEN;
u16 value[N][M]={0}; //存储ADC转换后N*M个数字量的数据
u16 aftervalue[M + 1]={0};//存储M个通道数字量的平均值
u16 adc_offset[M + 1]={0};
utilFilter_t adc_f[2];

//DMA1的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从外设模式->存储器/16位数据宽度/存储器增量模式
//DMA_CHx:DMA通道CHx		   //cpar:外设地址 //cmar:存储器地址//cndtr:数据传输量
void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{	  
  DMA_InitTypeDef DMA_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA时钟
	
    DMA_DeInit(DMA_CHx);   //将DMA的通道1寄存器重设为缺省值

	DMA1_MEM_LEN=cndtr;//通道数据长度
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //数据传输方向，从外设发送到内存  DMA_CCRX位4
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //外设数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //内存数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道ADC_DMA_Channel所标识的寄存器	

	
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);	//打开DMA功能
	
}
//#define adc_offset  						3090													//adc测量中间值
#define adc_max									4096													//adc测量最大值
#define adc_range								8000													//ADC量程0-8000mA	
//#define adc_Resolving_power			8.03     //单位adc测量值 即分辨率  3.90  8000/(adc_max-adc_offset)
float adc_Resolving_power[5]={0};
int temp[5]= {0};
void filter(void)
{	
	int sum = 0;//sum 通道采样数值的总和
	u8 count;//
	u8 i=0;
	
	for(i=0;i<M;i++)//每个通道进行循环滤波
	{
		for(count=0;count<N;count++)//采样N次循环
		{
			 sum+=value[count][i];//计算出N次采样值的总和
    }
    aftervalue[i] = sum/N;//求出通道数字量的平均值*3300/4096*4.545
//		aftervalue[i] = utilFilter(adc_f,aftervalue[i]);
		temp[i]	=	aftervalue[i]-adc_offset[i];
		if(temp[i]<=0)	{temp[i] = 0 ;}
		aftervalue[i]	=	temp[i]*adc_Resolving_power[i];
//		aftervalue[i]	=	(aftervalue[i]-adc_offset)*adc_Resolving_power;
    sum=0;
  }
//	for(i=0;i<M;i++){
//	//		temp	=	aftervalue[i]-adc_offset[i];
////		if(temp<=0)	{temp = 0 ;}
////		aftervalue[i]	=	temp*8;
//	}
}

void filter_correct(void)
{	
	int sum = 0;//sum 通道采样数值的总和
	u8 count;//
	u8 i=0;
	float temp;
	for(i=0;i<M;i++)//每个通道进行循环滤波
	{
		for(count=0;count<N;count++)//采样N次循环
		{
			 sum+=value[count][i];//计算出N次采样值的总和
    }
    aftervalue[i] = sum/N;//求出通道数字量的平均值*3300/4096*4.545
		adc_offset[i]	=	aftervalue[i];
//		adc_Resolving_power[i]=(4096-adc_offset[i])
//		if(temp<0)	temp=0;
//		aftervalue[i]	=	temp*adc_Resolving_power;
//		aftervalue[i]	=	(aftervalue[i]-adc_offset)*adc_Resolving_power;
    sum=0;
  }
	adc_Resolving_power[0]=8791.0/(4096.0-adc_offset[0]);
	adc_Resolving_power[1]=8081.0/(4096.0-adc_offset[1]);
	adc_Resolving_power[2]=8696.0/(4096.0-adc_offset[2]);
	adc_Resolving_power[3]=8333.0/(4096.0-adc_offset[3]);
}




