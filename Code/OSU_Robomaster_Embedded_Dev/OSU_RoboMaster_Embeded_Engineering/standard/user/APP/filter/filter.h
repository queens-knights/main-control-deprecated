/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.5 and Signal Processing Toolbox 8.1.
 * Generated on: 24-Apr-2019 19:12:50
 */

/*
 * Discrete-Time IIR Filter (real)
 * -------------------------------
 * Filter Structure    : Direct-Form II
 * Window Type         : Butterworth
 * Filter Type         : IIR
 * Response Type       : Low Pass
 * Numerator Length    : 9
 * Denominator Length  : 9
 * Stable              : Yes
 * Linear Phase        : Yes
 * F-pass              : 15Hz
 * F-stop              : 40Hz
 * Group Delay         : 50ms
 *
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
#include "arm_math.h"
#include "main.h"
/* 
 * Expected path to tmwtypes.h 
 * D:\MATLAB\R2018b\extern\include\tmwtypes.h 
 */


//#define N 9
//typedef struct{
//	double raw_value;
//	double xbuf[N];
//	double ybuf[N];
//	double filtered_value;
//}IIR_Filter_t;


//typedef struct{
//	double fir_raw_value;
//	double fir_xbuf[361];
//	double fir_ybuf[361];
//	double fir_filtered_value;
//}FIR_Filter_t;


//#define BLACKMAN_LENGTH 101
//typedef struct{
//	double blm_raw_value;
//	double blm_xbuf[BLACKMAN_LENGTH];
//	double blm_ybuf[BLACKMAN_LENGTH];
//	double blm_filtered_value;
//}Blackman_Filter_t;


#define DELAY_MS 200//200 TPU  300 tx2&nano
typedef struct{
	double group_delay_raw_value;
	double group_delay_buffer[DELAY_MS];
}Group_Delay_t;

#define mat         arm_matrix_instance_f32 
#define mat_init    arm_mat_init_f32
#define mat_add     arm_mat_add_f32
#define mat_sub     arm_mat_sub_f32
#define mat_mult    arm_mat_mult_f32
#define mat_trans   arm_mat_trans_f32
#define mat_inv     arm_mat_inverse_f32

#define MATRIX_ORDER 4 //若要更改order，一同更改user_task.c中的矩阵和filter.c中的function的输入signal
typedef struct
{
  fp32 raw_value;
  fp32 filtered_value[MATRIX_ORDER];
  mat xhat, xhatminus, z, A, H, AT, HT, Q, R, P, Pminus, K;
} kalman_filter_t;

typedef struct
{
  fp32 filtered_value[MATRIX_ORDER];
  fp32 xhat_data[MATRIX_ORDER];						//Prior Estimate
	fp32 xhatminus_data[MATRIX_ORDER];			//Last State of Prior Estimate
	fp32 z_data[MATRIX_ORDER];							//Actual Measurement of x
	fp32 Pminus_data[MATRIX_ORDER*MATRIX_ORDER];					//Covariance of the Estimation-Error
	fp32 K_data[MATRIX_ORDER*MATRIX_ORDER];							//Kalman Gain
  fp32 P_data[MATRIX_ORDER*MATRIX_ORDER];							//Initial Covariance of the Estimation-Error
  fp32 AT_data[MATRIX_ORDER*MATRIX_ORDER], HT_data[MATRIX_ORDER*MATRIX_ORDER];	//Transpose Matrix
  fp32 A_data[MATRIX_ORDER*MATRIX_ORDER];							//System Term
  fp32 H_data[MATRIX_ORDER*MATRIX_ORDER];							//Observation Model
  fp32 Q_data[MATRIX_ORDER*MATRIX_ORDER];							//Covariance of the Process Noise
  fp32 R_data[MATRIX_ORDER*MATRIX_ORDER];							//Covariance of the Measurement Noise
} kalman_filter_init_t;
