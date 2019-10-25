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
/** @file judgement_info.c
 *  @version 1.0
 *  @date June 2017
 *
 *  @brief the information from judgement system
 *
 *  @copyright 2017 DJI RoboMaster. All rights reserved.
 *
 */

#include "judgement_info.h"
#include "communicate.h"
#include "comm_task.h"
#include "protocol.h"
#include "bsp_uart.h"
#include "data_fifo.h"
#include "string.h"

/* data send (forward) */
/* data receive */
receive_judge_t judge_rece_mesg;
uint16_t cmd_id_test;
/**
  * @brief    get judgement system message
  */
extern TaskHandle_t pc_unpack_task_t;
void judgement_data_handler(uint8_t *p_frame)
{
  frame_header_t *p_header = (frame_header_t*)p_frame;
  memcpy(p_header, p_frame, HEADER_LEN);

  uint16_t data_length = p_header->data_length;
  uint16_t cmd_id      = *(uint16_t *)(p_frame + HEADER_LEN);
  uint8_t *data_addr   = p_frame + HEADER_LEN + CMD_LEN;
  uint8_t  invalid_cmd = 0;
  
	cmd_id_test = cmd_id;
  switch (cmd_id)
  {
    case Competition_status_ID:
      memcpy(&judge_rece_mesg.game_status, data_addr, data_length);
    break;

		case Competition_result_ID:
      memcpy(&judge_rece_mesg.game_result, data_addr, data_length);
    break;
		
		case Competition_robots_servival_ID:
      memcpy(&judge_rece_mesg.game_robot_survivors, data_addr, data_length);
    break;
		
		case Battlefield_event_ID:
      memcpy(&judge_rece_mesg.event_data, data_addr, data_length);
    break;
		
		case Battlefield_Projectile_Supplier_ID:
      memcpy(&judge_rece_mesg.supply_projectile_action, data_addr, data_length);
    break;
		
		case Request_projectile_supply_ID:
      memcpy(&judge_rece_mesg.supply_projectile_booking, data_addr, data_length);
    break;
		
		case Robot_status_ID:
      memcpy(&judge_rece_mesg.robot_state, data_addr, data_length);
    break;
		
		case Power_heat_ID:
      memcpy(&judge_rece_mesg.power_heat, data_addr, data_length);
    break;
		
		case Robot_position_ID:
      memcpy(&judge_rece_mesg.game_robot_pos, data_addr, data_length);
    break;
		
		case Robot_gain_ID:
      memcpy(&judge_rece_mesg.buff_musk, data_addr, data_length);
    break;
		
		case Aerial_energy_ID:
      memcpy(&judge_rece_mesg.aerial_robot_energy, data_addr, data_length);
    break;
		
		case Damage_status_ID:
      memcpy(&judge_rece_mesg.robot_hurt_t, data_addr, data_length);
    break;
		
		case Real_time_shooting_ID:
      memcpy(&judge_rece_mesg.shoot_data, data_addr, data_length);
    break;
		
		case Interaction_data_ID:
      memcpy(&judge_rece_mesg.student_interactive_header, data_addr, data_length);
    break;
		
    default:
      invalid_cmd = 1;
    break;
  }
  
  /* valid forward data */
  if (!invalid_cmd)
  {
    data_packet_pack(cmd_id, data_addr, data_length, UP_REG_ID);
    osSignalSet(pc_unpack_task_t, PC_UART_TX_SIGNAL);
  }
}

