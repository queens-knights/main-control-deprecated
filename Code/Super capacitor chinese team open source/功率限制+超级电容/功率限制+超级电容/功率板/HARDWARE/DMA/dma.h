#ifndef __DMA_H
#define __DMA_H
#include "sys.h"
#include "Util.h"
#define N 20 //取20次平均值
#define M 4 //5路AD

void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);
void filter(void);
void filter_correct(void);
extern u16 value[N][M];  //存储ADC转换后M*N个数字量的数据
extern u16 aftervalue[M + 1];//存储M个通道数字量的平均值
extern u16 adc_offset[M + 1];
extern float all_value;
extern utilFilter_t adc_f[2];
#endif




