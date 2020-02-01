/****************************************************************************
 *  Copyright (C) 2018 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

/**
  *********************** (C) COPYRIGHT 2018 DJI **********************
  * @update
  * @history
  * Version     Date              Author           Modification
  * V1.0.0      Jan-15-2018       ric.luo
  * V1.3.0      Feb-06-2018       ric.luo
  * @verbatim
  *********************** (C) COPYRIGHT 2018 DJI **********************
  */ 
 


#ifndef __RM_LIB_H__
#define __RM_LIB_H__

#include "stm32f4xx_hal.h"

/**
  * @brief     IMU 数据结构体 Data Struct
  */
typedef struct
{
  float acc_x;   //m/s^2
  float acc_y;   //m/s^2
  float acc_z;   //m/s^2
  float gyro_x;  //degree/s
  float gyro_y;  //degree/s
  float gyro_z;  //degree/s
  float angle_x; //degree
  float angle_y; //degree
  float angle_z; //degree
} imu_t;

/**
  * @brief     UART 配置类型枚举 Configuration type enumeration
  */
typedef enum
{
  WORD_LEN_8B = 0,
  WORD_LEN_9B,
  STOP_BITS_1,
  STOP_BITS_2,
  PARITY_NONE,
  PARITY_EVEN,
  PARITY_ODD,
} uart_config_e;

/**
  * @brief     数字 IO 引脚方向枚举 Digital IO pin direction enumeration
  */
typedef enum
{
  IO_INPUT  = 1,
  IO_OUTPUT = 2,
} digital_io_e;

/**
  * @brief     LED IO 状态 LED IO STATUS
  */
typedef enum
{
  LED_ON  = 0,
  LED_OFF = 1,
} led_io_e;

//CAN 设备端口定义 Device Port Definition
#define USER_CAN1         1  //CAN1
#define USER_CAN2         2  //CAN2
#define CHASSIS_CAN       1  //底盘电机使用CAN1 //Chassis Motor Use
#define GIMBAL_CAN        1  //云台电机使用CAN1 //PTZ Motor Use
#define TRIGGER_CAN       1  //拨弹电机使用CAN1 //Dial Wheel Motor Use
//CAN 设备相关函数 //Device Related Functions
/**
  * @brief     CAN 设备初始化 //Device Initialzation
  */
void can_device_init(void);
/**
  * @brief     发送 CAN 数据 //Send CAN Data
  * @param     can_id: CAN 设备 ID，只有 CAN1 或者 CAN2 //CAN Device ID, Only CAN1 OR CAN2
  * @param     send_id: 发送数据 ID //Send Data ID
  * @param     send_data: 发送数据指针，大小为 8 位 //Send Data Pointer, 8-bit Size
  */
void write_can(uint8_t can_id, uint32_t send_id, uint8_t send_data[]);
/**
  * @brief     注册 CAN 接收回调函数 //Register CAN Recieve Callback Function
  * @param     can_id: CAN 设备 ID //CAN Device ID
  * @param     callback: 接收回调函数指针 //Recieve Callback Function Pointer
  */
void can_recv_callback_register(uint8_t can_id, void (* callback)(uint32_t recv_id, uint8_t data[]));
/**
  * @brief     开启 CAN 接收数据中断 //Turn on CAN Recieve Data Interrup
  */
void can_receive_start(void);

//UART 设备端口定义 //Device Port Definition
#define DBUS_UART         1 //遥控器接收机串口 //Remote Control Receiver Serial Port
#define USER_UART1        1 //用户串口1，遥控器接收机使用 //User Serial Port 1, For Remote Control Use Purpose
#define USER_UART2        2 //用户串口2 //User Serial Port 2
#define USER_UART3        3 //用户串口3 //User Serial Port 3
#define USER_UART4        4 //用户串口4 //User Serial Port 4
#define USER_UART5        5 //用户串口5，用于和官方上位机通信 //User Serial Port 5, Use for Communication with Upper PC
//UART 设备相关函数 //Device Related Funtions
/**
  * @brief     UART 设备初始化 //Device Initialzation
  * @param     uart_id: UART 设备 ID //UART Device ID
  * @param     baud_rate: 波特率 //Baud Rate
  * @param     word_len: 字长，数据类型为 uart_config_e // Word Length, Data Type is uart_config_e
  * @param     stop_bits: 停止位，数据类型为 uart_config_e //Stop bit, Data Type is uart_config_e
  * @param     parity: 校验位，数据类型为 uart_config_e //Check bit, Data Type is uart_config_e
  */
void uart_init(uint8_t uart_id, uint32_t baud_rate, uart_config_e word_len, \
               uart_config_e stop_bits, uart_config_e parity);
/**
  * @brief     发送 UART 数据 //Send Uart Data
  * @param     uart_id: UART ID
  * @param     send_data: 发送数据指针 //Send Data Pointer
  * @param     size: 发送数据的长度 //length of send data
  */
void write_uart(uint8_t uart_id, uint8_t *send_data, uint16_t size);
/**
  * @brief     注册 UART 接收回调函数 //register uart callback function
  * @param     uart_id: UART ID
  * @param     callback: 接收回调函数指针 //recieve callback function pointer
  */
void uart_recv_callback_register(uint8_t uart_id, void (* callback)(void));
/**
  * @brief     开启 UART 接收数据中断 //turn on uart recieve data interrupt
  * @param     uart_id: UART ID
  * @param     recv_data: 要接收数据的指针 //pointer to recieve data
  * @param     size: 要接收的数据的长度 //length of recieve data
  */
void uart_receive_start(uint8_t uart_id, uint8_t *recv_data, uint16_t size);


//数字 IO 接口定义 //digital IO interface definition
#define DIGI_IO1          1
#define DIGI_IO2          2
#define DIGI_IO3          3
#define DIGI_IO4          4
#define DIGI_IO5          5
#define DIGI_IO6          6
#define DIGI_IO7          7
#define DIGI_IO8          8
#define DIGI_IO9          9
//数字 IO 相关函数 //digital IO related function
/**
  * @brief     设置数字 IO 方向 //set digital IO direction
  * @param     io_id: 数字 IO 的 ID //digital IO ID
  * @param     io_type: IO 方向，数据类型为 digital_io_e
  */
void set_digital_io_dir(uint8_t io_id, digital_io_e io_type);
/**
  * @brief     写数字 IO //write digital IO
  * @param     io_id: 数字 IO 的 ID //digital IO ID
  * @param     value: 写入的数据值，只能为0或1，否则设置不成功 //The written data value either 0 or 1, otherwise setting unsuccessful
  */
void write_digital_io(uint8_t io_id, uint8_t value);
/**
  * @brief     读数字 IO //read digital IO
  * @param     io_id: 数字 IO 的 ID //digital IO ID
  * @param     value: 读取数据值的指针，读取的数据值为0或1 //pointer to read data value (either 0 or 1)
  */
void read_digital_io(uint8_t io_id, uint8_t *value);

//LED IO 接口定义 //port definition
#define LED_IO1           1   //LED1 IO
#define LED_IO2           2   //LED2 IO
#define LED_IO3           3   //LED3 IO
#define LED_IO4           4   //LED4 IO
#define LED_IO5           5   //LED5 IO
#define LED_IO6           6   //LED6 IO
#define LED_IO7           7   //LED7 IO
#define LED_IO8           8   //LED8 IO
#define LED_G             9   //绿色 LED IO //green
#define LED_R             10  //红色 LED IO //red
#define LASER_IO          11  //激光 IO //laser
//LED IO 相关函数 //related function
/**
  * @brief     写 LED IO //write LED IO
  * @param     led_id: LED IO 的 ID
  * @param     value: 写入的数据值，数据类型为 led_io_e，状态为亮或灭 //the written data value's data type is led_op_e, status either on or off
  */
void write_led_io(uint8_t led_id, led_io_e value);

//PWM IO 接口定义 // //port definition
#define PWM_GROUP1        1   //第一组 PWM IO //first set
#define PWM_IO1           1
#define PWM_IO2           2
#define PWM_IO3           3
#define PWM_IO4           4

#define PWM_GROUP2        2   //第二组 PWM IO //second set
#define PWM_IO5           5
#define PWM_IO6           6
#define PWM_IO7           7
#define PWM_IO8           8

#define PWM_GROUP3        3   //第三组 PWM IO //third set
#define PWM_IO9           9
#define PWM_IO10          10
#define PWM_IO11          11
#define PWM_IO12          12

#define PWM_GROUP4        4   //第四组 PWM IO //forth set
#define PWM_IO13          13
#define PWM_IO14          14
#define PWM_IO15          15
#define PWM_IO16          16
//PWM IO 相关函数 //related function
/**
  * @brief     开启 PWM 输出 //turn on PWM output
  * @param     pwm_id: PWM IO 的 ID
  */
void start_pwm_output(uint8_t pwm_id);
/**
  * @brief     设置 PWM 组对应参数 //set corresponding parameters of PWM group
  * @param     pwm_group: PWM 组别，目前有 4 组PWM //currently 4 pwm group
  * @param     period:  每组 PWM 对应周期时间，单位是微秒(us) //Corresponding cycle time of each group of PWM(microseconds)
  */
void set_pwm_group_param(uint8_t pwm_group, uint32_t period);
/**
  * @brief     设置 PWM IO 参数 //set PWM IO parameter
  * @param     pwm_id: PWM IO 的 ID
  * @param     pulse: 配置 PWM 的高电平时间，单位是微秒(us) //Configure PWM high time in microseconds
  */
void set_pwm_param(uint8_t pwm_id, uint32_t pulse);


//蜂鸣器 IO //buzzer IO
/* 板子上只有一个蜂鸣器 */ //only one buzzer on board
#define BEEP1_IO        1    //蜂鸣器1 IO //buzzer 1 IO

#define BEEP_FREQ       3000 //默认蜂鸣器频率 //default buzzer frequency
#define BEEP_ON         1    //打开蜂鸣器 //turn on buzzer
#define BEEP_OFF        0    //关闭蜂鸣器 //turn off buzzer
//蜂鸣器 IO 相关函数 //buzzer IO related function
/**
  * @brief     设置蜂鸣器 IO 参数 //set buzzer IO parameter
  * @param     beep_id: 蜂鸣器的 ID //buzzer ID
  * @param     freq: 配置蜂鸣器响的声音的频率(Hz) //configure buzzer sound frequency
  * @param     ctrl: 蜂鸣器开启控制，参数可以为BEEP_ON/BEEP_OFF //buzzer on control, parameter can be Beep_on/off
  */
void set_beep_param(uint8_t beep_id, uint32_t freq, uint8_t ctrl);


//按键 IO 接口定义 //button IO interface definition
#define KEY_IO1          1   //用户按键1 //user button 1
#define KEY_IO2          2   //用户按键2 //user button 2
#define KEY_IO3          3   //用户按键3 //user button 3
#define KEY_IO4          4   //用户按键4 //user button 4
//按键 IO 相关函数 //button IO related function
/**
  * @brief     读按键 IO //read button IO
  * @param     key_id: 按键 IO 的 ID //button IO's ID
  * @param     value: 读取数据值的指针，读取的数据值为0或1，按键没有按下时为1，按下为0 //pointer to read the data value, read data value is 0 or 1.
// key is not pressed, it is 1. pressed, it is 0
  */
void read_key_io(uint8_t key_id, uint8_t *value);


//ADC IO 接口定义 //interface definition
#define ADC_IO1          1   //ADC接口1 //ADC interface 1
//ADC IO 相关函数 //related function
/**
  * @brief     读 ADC IO 数据 //read ADC IO data
  * @param     adc_id: ADC IO 的 ID
  * @param     value: 读取数据值的指针，读取的数据值为 uint32_t 类型的正整数， //pointer to read data value, the read data value is a positive integer of type uint32_t
  *            数据范围为 0 ~ 65535 //data range is 0-65535
  *            目前只有一个 ADC 接口，用于拓展版上的霍尔传感器 //currently only one ADC interface, used for Hall sensor on the extension version
  */
void read_adc_io(uint8_t adc_id, uint32_t *value);


//数码管接口定义 //digital tube interface definition
#define DIG_TUBE1        1
#define DIG_TUBE2        2
#define DIG_TUBE3        3
#define DIG_TUBE4        4
#define DIG_TUBE5        5
#define DIG_TUBE6        6
#define DIG_TUBE7        7
#define DIG_TUBE8        8

#define TUBE_ALL_ON      255  //数码管全亮 //digital tube all on
#define TUBE_ALL_OFF     0    //数码管全灭 //digital tube all off
//数码管接口相关函数 //digital tube interface related function
/**
  * @brief     数码管初始化 //digital tube initialization
  * @usage     在使用数码管显示前使用，配置数码管各个控制引脚的功能， //Use before the digital tube display, configure the function of each control pin of the digital tube
  * @attention 因为数码管控制接口和用户接口复用，在使用数码管时 9 个用户数字 IO 不能再被使用 //Because digital tube control interface and user interface are multiplexed
//9 user digital IO can no longer be used when using digital tube

  */
void digital_tube_init(void);
/**
  * @brief     刷新所有数码管 //update all digital tube
  * @usage     数码管需要显示新的数据时使用 //use when digital tube needs to display the new data
  */
void refresh_digital_tube(void);
/**
  * @brief     第几个数码管显示具体数字 //Number of digital tubes display specific numbers
  * @param     pos: 从左到右第几个数码管 //number of digital tube from left to right
  * @param     code: 数码管需要显示的数据，数据类型为 uint8_t 用 10 进制表示的范围为 0 ~ 255
  *                  8位数据由高到低分别对应每段的：A B C D E F G P
  *                  数码管的段和数据代码的对应位置1即可点亮，例如显示数字1，数据代码为96
  *                  每位的具体位置见说明书，其中 P 为小数点
		     //the data type that the digital tube needs to display is uint8_t decimal rangle between 0-255
		     //8-bit data corresponding to each segment: A B C D E F G P, from high to low
		     //The corresponding position of the segment of the digital tube and the data code can be lit. For example, the number 1 is displayed. The specific position of the data code is 96. 
		     //See the manual for the specific position, where P is the decimal point.

  */ 
void switch_display_num(uint8_t pos, uint8_t code);



//其他外设接口相关函数 //other device interface related function
//flash
/**
  * @brief     写 FLASH 设备 //write FLASH device
  * @param     write_data: 写入数据的指针 //read data pointer
  * @param     len: 写入数据的长度 //read data length
  */
void write_flash(uint8_t *write_data, uint32_t len);
/**
  * @brief     读 FLASH 设备 //read FLASH device
  * @param     read_data: 读取数据的指针 //read data pointer
  * @param     len: 读取数据的长度 //read data length
  */
void read_flash(uint8_t *read_data, uint32_t len);

//imu
/**
  * @brief     读取 IMU 数据 //read IMU data
  * @param     imu_data: 接收 IMU 数据的结构体指针 //recieve IMU data struct pointer
  * @usage     需要在循环任务中调用，用来刷新 IMU 数据 //Need to be called in a cyclic task to refresh IMU data

  */
void get_imu_data(imu_t *imu_data);

#endif
