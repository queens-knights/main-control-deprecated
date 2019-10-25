/****************************************************************************
 *  Copyright (C) 2019 RoboMaster.
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

#include "sys.h"
#include "shoot.h"
#include "dbus.h"
#include "shoot_task.h"
#include "drv_io.h"

int32_t shoot_firction_toggle(shoot_t pshoot);

void shoot_task(void const *argument)
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

  uint32_t shoot_time;

  while (1)
  {
    if (rc_device_get_state(prc_dev, RC_S2_DOWN) != RM_OK)
    {
						LED_G_ON();
						LED_R_OFF();
       shoot_set_cmd(pshoot, SHOOT_CONTINUOUS_CMD, 0);
		}
    else
    {
						LED_G_OFF();
						LED_R_ON();
       shoot_set_cmd(pshoot, SHOOT_STOP_CMD, 0);
    }

    shoot_execute(pshoot);
    osDelayUntil(&period, 5);
  }
}

int32_t shoot_firction_toggle(shoot_t pshoot)
{
  static uint8_t toggle = 0;
  if (toggle)
  {
    shoot_set_fric_speed(pshoot, 1000, 1000);
  }
  else
  {
    shoot_set_fric_speed(pshoot, 1250, 1250);
  }
  toggle = ~toggle;
  return 0;
}
