/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "can.h"
#include "Judge.h"
#include "capacity.h"
/* USER CODE END 0 */

TIM_HandleTypeDef htim3;

/* TIM3 init function */
void MX_TIM3_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 72-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* TIM3 interrupt Init */
    HAL_NVIC_SetPriority(TIM3_IRQn, 3, 1);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspInit 1 */
	
  /* USER CODE END TIM3_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
extern int JudgeFresh;
extern int16_t datatype;
uint8_t candata[8];
wl4data  data4bytes;
wl2data  data2bytes;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim3){
		Capacity_Ctrl();
		if(JudgeSendFresh == 1){
#ifdef VERSION17 
			UploadData(ToJudgeData[0],ToJudgeData[1],ToJudgeData[2]);
#endif		
#ifdef VERSION18
			UploadData(ToJudgeData[0],ToJudgeData[1],ToJudgeData[2],ToJudgeMask);
#endif
			JudgeSendFresh = 0;
		}
		if(JudgeFresh != 0){
			JudgeFresh = 0;
#ifdef VERSION17 
			switch(datatype){
				case 0x0001:
				data4bytes.f = Judge_GameInfo.realChassisOutA;
				candata[0] = data4bytes.c[0];
				candata[1] = data4bytes.c[1];
				candata[2] = data4bytes.c[2];
				candata[3] = data4bytes.c[3];
				data4bytes.f = Judge_GameInfo.realChassisOutV;
				candata[4] = data4bytes.c[0];
				candata[5] = data4bytes.c[1];
				candata[6] = data4bytes.c[2];
				candata[7] = data4bytes.c[3];
				CAN_Send_bytes(0x100,candata);
				
				data2bytes.d = Judge_GameInfo.remainLifeValue;
				candata[0] = data2bytes.c[0];
				candata[1] = data2bytes.c[1];
				data4bytes.f = Judge_GameInfo.remainPower;
				candata[2] = data4bytes.c[0];
				candata[3] = data4bytes.c[1];
				candata[4] = data4bytes.c[2];
				candata[5] = data4bytes.c[3];
				candata[6] = 0x00;
				candata[7] = 0x00;
				CAN_Send_bytes(0x101,candata);

				break;
				case 0x0002:
				candata[0] = Judge_BloodData.weakId;
				candata[1] = Judge_BloodData.way;
				data2bytes.d = Judge_BloodData.value;
				candata[2] = data2bytes.c[0];
				candata[3] = data2bytes.c[1];
				memset(&candata[4],0,4);
				CAN_Send_bytes(0x102,candata);
				break;
				case 0x0003:
				data4bytes.f = Judge_ShootData.realBulletShootSpeed;
				candata[0] = data4bytes.c[0];
				candata[1] = data4bytes.c[1];
				candata[2] = data4bytes.c[2];
				candata[3] = data4bytes.c[3];
				data4bytes.f = Judge_ShootData.realBulletShootFreq;
				candata[4] = data4bytes.c[0];
				candata[5] = data4bytes.c[1];
				candata[6] = data4bytes.c[2];
				candata[7] = data4bytes.c[3];
				CAN_Send_bytes(0x103,candata);	
				break;
			}
#endif
			
#ifdef VERSION18
			if(JudgeFreshSignal[0] == 1){
				JudgeFreshSignal[0] = 0;
				candata[0] = Judge_extGameRobotState.gameProgress;
				candata[1] = Judge_extGameRobotState.robotLevel;
				data2bytes.ud = Judge_extGameRobotState.remainHP;
				candata[2] = data2bytes.c[0];
				candata[3] = data2bytes.c[1];
				data2bytes.ud = Judge_extGameRobotState.maxHP;
				candata[4] = data2bytes.c[0];
				candata[5] = data2bytes.c[1];
				candata[6] = 0x00;
				candata[7] = 0x00;
				CAN_Send_bytes(0x101,candata);				
			}
			if(JudgeFreshSignal[1] == 1){
				JudgeFreshSignal[1] = 0;
				candata[0] = Judge_extRobotHurt.armorType;
				candata[1] = Judge_extRobotHurt.hurtType;
				memset(&candata[2],0,6);
				CAN_Send_bytes(0x102,candata);				
			}
			if(JudgeFreshSignal[2] == 1){
				JudgeFreshSignal[2] = 0;
				data4bytes.f = Judge_extShootData.bulletSpeed;
				candata[0] = Judge_extShootData.bulletType;
				candata[1] = Judge_extShootData.bulletFreq;
				candata[2] = data4bytes.c[0];
				candata[3] = data4bytes.c[1];
				candata[4] = data4bytes.c[2];
				candata[5] = data4bytes.c[3];
				candata[6] = 0x00;
				candata[7] = 0x00;
				CAN_Send_bytes(0x103,candata);				
			}
			if(JudgeFreshSignal[3] == 1){
				JudgeFreshSignal[3] = 0;
				data4bytes.f = Judge_extPowerHeatData.chassisPowerBuffer;
				candata[0] = data4bytes.c[0];
				candata[1] = data4bytes.c[1];
				candata[2] = data4bytes.c[2];
				candata[3] = data4bytes.c[3];
				data2bytes.ud = Judge_extPowerHeatData.shooterHeat0;
				candata[4] = data2bytes.c[0];//17mm heat
				candata[5] = data2bytes.c[1];
				data2bytes.ud = Judge_extPowerHeatData.shooterHeat1;
				candata[6] = data2bytes.c[0];//42mm heat
				candata[7] = data2bytes.c[1];
				CAN_Send_bytes(0x104,candata);
			}
			if(JudgeFreshSignal[4] == 1){
				JudgeFreshSignal[4] = 0;
				candata[0] = Judge_extRfidDetect.cardIdx;
				candata[1] = Judge_extRfidDetect.cardType;
				memset(&candata[2],0,6);
				CAN_Send_bytes(0x105,candata);				
			}
			if(JudgeFreshSignal[5] == 1){
				JudgeFreshSignal[5] = 0;
			}
			if(JudgeFreshSignal[6] == 1){
				JudgeFreshSignal[6] = 0;
				candata[0] = Judge_extGetBuff.buffMusk;
				memset(&candata[1],0,6);
				CAN_Send_bytes(0x107,candata);				
			}
			if(JudgeFreshSignal[7] == 1){
				
			}
			if(JudgeFreshSignal[8] == 1){
				JudgeFreshSignal[7] = 0;
			}
#endif
		}
	}
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
