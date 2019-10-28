
#ifndef __UTIL_H
#define __UTIL_H

#include <stdlib.h>
#include "stm32f10x.h"

#define digitalHi(p)        *p = 1
#define digitalLo(p)        *p = 0
#define digitalSet(p, n)    *p = n
#define digitalGet(p)       (*p)
#define digitalTogg(p)      *p = !(*p)
#define digitalIncreasing(p) *p += 1
#define digitalDecline(p)   *p -= 1
#define digitalClan(p)			*p = 0
#define High	1
#define Low   0

#define constrainInt(v, lo, hi)	    (((int)(v) < (int)(lo)) ? (int)(lo) : (((int)(v) > (int)(hi)) ? (int)(hi) : (int)(v)))
#define constrainFloat(v, lo, hi)   (((float)(v) < (float)(lo)) ? (float)(lo) : (((float)(v) > (float)(hi)) ? (float)(hi) : (float)(v)))

#define ABS(x) ( (x)>0?(x):-(x) )
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define	UTIL_STACK_CHECK	    12

#define UTIL_CCM_HEAP_SIZE	    (0x2800)	// 40KB

#define UTIL_ISR_DISABLE	    __asm volatile ( "CPSID   F\n")
#define UTIL_ISR_ENABLE		    __asm volatile ( "CPSIE   F\n")

#define yield(n)		    vTaskDelay(n)

#define constrainInt(v, lo, hi)	    (((int)(v) < (int)(lo)) ? (int)(lo) : (((int)(v) > (int)(hi)) ? (int)(hi) : (int)(v)))
#define constrainFloat(v, lo, hi)   (((float)(v) < (float)(lo)) ? (float)(lo) : (((float)(v) > (float)(hi)) ? (float)(hi) : (float)(v)))

#define PERIPH2BB(addr, bit)        ((uint32_t *)(PERIPH_BB_BASE + ((addr) - PERIPH_BASE) * 32 + ((bit) * 4)))

// first order filter		一阶滤波器
typedef struct {
    float tc;
    float z1;
} utilFilter_t;

typedef struct {
    const float *window;
    float *data;
    uint8_t n;
    uint8_t i;
} utilFirFilter_t;

//联合体用于转换数据
typedef union
{
	u8 		u8_temp[4];
	float float_temp;
	s32 	s32_temp;
	u32		u32_temp;
} FormatTrans;

typedef struct {
	uint32_t errorCount;
	uint32_t lastErrorCount;
	uint32_t intervalNum;
} errorScanStruct_t; 

//extern void delay(unsigned long t);
extern void delayMicros(unsigned long t);
extern void dumpFloat(unsigned char n, float *floats);
extern void dumpInt(unsigned char n, int *ints);
//extern void info(void);
extern uint16_t *aqStackInit(uint16_t size, char *name);
extern void *aqCalloc(size_t count, size_t size);
extern void aqFree(void *ptr, size_t count, size_t size);
extern void *aqDataCalloc(uint16_t count, uint16_t size);
extern float removeDeadBand(float rcValue,float deadBand);
extern void utilFilterInit(utilFilter_t *f, float dt, float tau, float setpoint);
extern void utilFilterInit2(utilFilter_t *f, float dt, float tau, float setpoint);
extern void utilFilterInit3(utilFilter_t *f, float dt, float tau, float setpoint);
extern float utilFilter(utilFilter_t *f, float signal);
extern float utilFilter2(utilFilter_t *f, float signal);
extern float utilFilter3(utilFilter_t *f, float signal);
extern void utilFilterReset(utilFilter_t *f, float setpoint);
extern void utilFilterReset3(utilFilter_t *f, float setpoint);
extern int ftoa(char *buf, float f, unsigned int digits);
//extern void utilSerialNoString(void);
//extern void utilVersionString(void);
extern float utilFirFilter(utilFirFilter_t *f, float newValue);
extern void utilFirFilterInit(utilFirFilter_t *f, const float *window, float *buffer, uint8_t n);
#ifdef UTIL_STACK_CHECK
//extern void utilStackCheck(void);
extern uint16_t stackFrees[UTIL_STACK_CHECK];
extern uint16_t utilGetStackFree(const char *stackName);
#endif
//void delay_ms(u16 nms);
//void delay_us(u32 nus);

#endif


