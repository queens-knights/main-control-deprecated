#include "adc.h"
#include "dma.h"
//初始化ADC
//开启ADC1的通道0~15,对应关系如下
//ADC1_CH0-->PA0	
//ADC1_CH1-->PA1	
//ADC1_CH2-->PA2
//ADC1_CH3-->PA3	
//ADC1_CH4-->PA4	
//ADC1_CH5-->PA5	
//ADC1_CH6-->PA6 
//ADC1_CH7-->PA7 
//ADC1_CH8-->PB0 
//ADC1_CH9-->PB1 
//ADC1_CH10-->PC0
//ADC1_CH11-->PC1
//ADC1_CH12-->PC2
//ADC1_CH13-->PC3
//ADC1_CH14-->PC4 
//ADC1_CH15-->PC5 
void Adc_Int(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //设置ADC分频因子6  72/6=12  ADC最大时间不超过14M
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;  //模拟输入引脚
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_DeInit(ADC1);//复位ADC1
	
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;  //ADC工作模式：ADC1 ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode=ENABLE;        //扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;  //循环模式
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//转换由软件热不是外部触发
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel=M;     //顺序规则转换通道数
	ADC_Init(ADC1,&ADC_InitStructure);    //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0,  1, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1,  2, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2,  3, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3,  4, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4,  5, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期	

	ADC_Cmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);//使能复位校准
	while(ADC_GetCalibrationStatus(ADC1));//等待复位校准结束
	ADC_StartCalibration(ADC1);//开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件打开ADC转换

}









