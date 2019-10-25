//Init
#include "dbus.h"
#include "chassis_task.h"
#include "timer_task.h"
#include "infantry_cmd.h"
#include "drv_io.h"
#include "rc_light.h"
#include "shoot.h"
#include "test.h"
#include "tim.h"
float chan_1,chan_2,chan_3,chan_4;
int switch_1,switch_2;

int Left, Right;
float mouse_y;

int isBoxOpen, isGripUp, isGripClose, isGripForward;
int servo_position,open_pos;
int tim8_1, tim8_2, tim8_3, tim8_4;
int tim4_2, tim4_3;
int tim1;
int Grip_UD_flag;


void rc_light(void const *argument)
{
  uint32_t period = osKernelSysTick();

  rc_device_t prc_dev = NULL;
  rc_info_t prc_info = NULL;

  shoot_t pshoot = NULL;
  pshoot = shoot_find("shoot");

  prc_dev = rc_device_find("uart_rc");

  if (prc_dev != NULL)
  {
    prc_info = rc_device_get_info(prc_dev);
  }
  else
  {
  }

	Grip_UD_flag = 0;
	servo_position = 420;
  while (1)
  {

		chan_1 = prc_info->ch1;
		chan_2 = prc_info->ch2;
		chan_3 = prc_info->ch3;
		chan_4 = prc_info->ch4;

		switch_1 = prc_info->sw1;
		switch_2 = prc_info->sw2;

		

  }
}
