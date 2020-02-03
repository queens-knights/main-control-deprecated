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
  * V1.0.0      January-15-2018   ric.luo
  * @verbatim
  *********************** (C) COPYRIGHT 2018 DJI **********************
  */ 
 



#ifndef __UART_DEVICE_H__
#define __UART_DEVICE_H__

#include "rm_hal_lib.h"

/**
  * @brief     解析后的遥控器数据结构体 Data structure of remote control after parsing
  */
typedef struct 
{
  /* 遥控器的通道数据，数值范围：-660 ~ 660 Channel data of remote control, data range: -660 ~ 660*/
  int16_t ch1;   //右侧左右 right side left and right
  int16_t ch2;   //右侧上下 right side upper and lower
  int16_t ch3;   //左侧左右 left side left and right
  int16_t ch4;   //左侧上下 left side upper and lower
  
  /* 遥控器的拨杆数据，上中下分别为：1、3、2 Remote control lever data, upper, middle, and lower are: 1, 3, and 2, respectively*/
  uint8_t sw1;   //左侧拨杆 left side lever
  uint8_t sw2;   //右侧拨杆 right side lever
  
  /* PC 鼠标数据 PC mouse data*/
  struct
  {
    /* 鼠标移动相关 mouse moving related*/
    int16_t x;   //鼠标平移 mouse x
    int16_t y;   //鼠标上下 mouse y
    /* 鼠标按键相关，1为按下，0为松开 mouse button related, 1 is pressed, 0 is released*/
    uint8_t l;   //左侧按键 left button
    uint8_t r;   //右侧按键 right button
  }mouse;
  
  /* PC 键盘按键数据 PC keyboard key data*/
  union 
  {
    uint16_t key_code;
    struct 
    {
      uint16_t W:1;
      uint16_t S:1;
      uint16_t A:1;
      uint16_t D:1;
      uint16_t SHIFT:1;
      uint16_t CTRL:1;
      uint16_t Q:1;
      uint16_t E:1;
      uint16_t R:1;
      uint16_t F:1;
      uint16_t G:1;
      uint16_t Z:1;
      uint16_t X:1;
      uint16_t C:1;
      uint16_t V:1;
      uint16_t B:1;
    }bit;
  }kb;
  
  /* 遥控器左侧拨轮数据 Remote control left dialwheel data*/
  int16_t wheel;
} rc_type_t;

/**
  * @brief     遥控器拨杆数据枚举 Remote control level data enumerate
  */
enum
{
  RC_UP = 1,
  RC_MI = 3,
  RC_DN = 2,
};

/**
  * @brief     解析遥控器数据 parsing remote control data
  * @param     rc: 解析后的遥控器数据结构体指针 rc: remote control data structure pointer after parsing
  * @param     buff: 串口接收到的遥控器原始数据指针 buff: Remote control original data pointer that serial port received
  */
static void remote_data_handle(rc_type_t *rc, uint8_t *buff);
/**
  * @brief     遥控器中断回调函数，在设置 UART 接收时注册 Remote control interrupt callback function, registered when setting UART reception
  */
void dbus_uart_callback(void);

extern rc_type_t rc;
extern uint8_t   dbus_recv[];

#endif
