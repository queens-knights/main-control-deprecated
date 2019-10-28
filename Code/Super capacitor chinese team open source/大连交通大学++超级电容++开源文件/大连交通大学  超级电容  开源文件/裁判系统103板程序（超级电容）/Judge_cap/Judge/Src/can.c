/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
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
#include "can.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "Judge.h"
#include "capacity.h"
CanTxMsgTypeDef  can_tx;
CanRxMsgTypeDef  can_rx;
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 3;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SJW = CAN_SJW_1TQ;
  hcan.Init.BS1 = CAN_BS1_6TQ;
  hcan.Init.BS2 = CAN_BS2_5TQ;
  hcan.Init.TTCM = DISABLE;
  hcan.Init.ABOM = ENABLE;
  hcan.Init.AWUM = DISABLE;
  hcan.Init.NART = DISABLE;
  hcan.Init.RFLM = DISABLE;
  hcan.Init.TXFP = ENABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();
  
    /**CAN GPIO Configuration    
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_CAN1_2();

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_HP_CAN1_TX_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 1, 2);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */
    hcan.pTxMsg = &can_tx;
    hcan.pRxMsg = &can_rx;
    CAN_FilterConfTypeDef can_filter;
	can_filter.FilterNumber=0;
	can_filter.FilterMode=CAN_FILTERMODE_IDMASK;
	can_filter.FilterScale=CAN_FILTERSCALE_32BIT;
	can_filter.FilterIdHigh=0x0000;
	can_filter.FilterIdLow=0x0000;
	can_filter.FilterMaskIdHigh=0x0000;
	can_filter.FilterMaskIdLow=0x0000;
	can_filter.FilterFIFOAssignment=0;
	can_filter.FilterActivation=ENABLE;
	can_filter.BankNumber = 0;
	HAL_CAN_ConfigFilter(&hcan,&can_filter);
	__HAL_CAN_ENABLE_IT(&hcan,CAN_IT_FMP0);
	__HAL_CAN_ENABLE_IT(&hcan,CAN_IT_TME);
	
  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();
  
    /**CAN GPIO Configuration    
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_HP_CAN1_TX_IRQn);
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan){
#ifdef VERSION17
	switch (can_rx.StdId){
		case 0x300:{
			wl4data tdata;
			tdata.c[0] = can_rx.Data[0];
			tdata.c[1] = can_rx.Data[1];
			tdata.c[2] = can_rx.Data[2];
			tdata.c[3] = can_rx.Data[3];
			ToJudgeData[0] = tdata.f;
			tdata.c[0] = can_rx.Data[4];
			tdata.c[1] = can_rx.Data[5];
			tdata.c[2] = can_rx.Data[6];
			tdata.c[3] = can_rx.Data[7];
			ToJudgeData[1] = tdata.f;
			break;
		}
		case 0x301:{
			wl4data tdata;
			tdata.c[0] = can_rx.Data[0];
			tdata.c[1] = can_rx.Data[1];
			tdata.c[2] = can_rx.Data[2];
			tdata.c[3] = can_rx.Data[3];
			ToJudgeData[2] = tdata.f;	
			JudgeSendFresh = 1;
			break;
		}
	}
#endif
#ifdef VERSION18
	switch (can_rx.StdId){
		case 0x201:{
			chassis_speed[0] = can_rx.Data[2]<<8 | can_rx.Data[3];
			break;
		}
		case 0x202:{
			chassis_speed[1] = can_rx.Data[2]<<8 | can_rx.Data[3];
			break;
		}
		case 0x203:{
			chassis_speed[2] = can_rx.Data[2]<<8 | can_rx.Data[3];
			break;
		}
		case 0x204:{
			chassis_speed[3] = can_rx.Data[2]<<8 | can_rx.Data[3];
			break;
		}
		case 0x300:{
			wl4data tdata;
			tdata.c[0] = can_rx.Data[0];
			tdata.c[1] = can_rx.Data[1];
			tdata.c[2] = can_rx.Data[2];
			tdata.c[3] = can_rx.Data[3];
			ToJudgeData[0] = tdata.f;
			tdata.c[0] = can_rx.Data[4];
			tdata.c[1] = can_rx.Data[5];
			tdata.c[2] = can_rx.Data[6];
			tdata.c[3] = can_rx.Data[7];
			ToJudgeData[1] = tdata.f;
			break;
		}
		case 0x301:{
			wl4data tdata;
			tdata.c[0] = can_rx.Data[0];
			tdata.c[1] = can_rx.Data[1];
			tdata.c[2] = can_rx.Data[2];
			tdata.c[3] = can_rx.Data[3];
			ToJudgeData[2] = tdata.f;	
			ToJudgeMask = can_rx.Data[4];
			usecap = can_rx.Data[5];
			JudgeSendFresh = 1;
			break;
		}
		case 0x401:{
			wl2data t2data;
			t2data.c[0] = can_rx.Data[2];
			t2data.c[1] = can_rx.Data[3];
			imu_gz = -(float)t2data.d / 16.384f;
			break;
		}
	}
#endif
	__HAL_CAN_ENABLE_IT(hcan,CAN_IT_FMP0);
}

void CAN_Send(uint32_t id,int16_t data0,int16_t data1,int16_t data2,int16_t data3){
	hcan.pTxMsg->StdId = id;
	hcan.pTxMsg->IDE = CAN_ID_STD;
	hcan.pTxMsg->RTR = CAN_RTR_DATA;
	hcan.pTxMsg->DLC = 0x08;
	hcan.pTxMsg->Data[0] = (unsigned char)(data0 >> 8);
	hcan.pTxMsg->Data[1] = (unsigned char)data0;
	hcan.pTxMsg->Data[2] = (unsigned char)(data1 >> 8);
	hcan.pTxMsg->Data[3] = (unsigned char)data1;
	hcan.pTxMsg->Data[4] = (unsigned char)(data2 >> 8);
	hcan.pTxMsg->Data[5] = (unsigned char)data2;
	hcan.pTxMsg->Data[6] = (unsigned char)(data3 >> 8);
	hcan.pTxMsg->Data[7] = (unsigned char)data3;
	HAL_CAN_Transmit_IT(&hcan); 
}

void CAN_Send_bytes(uint32_t id,uint8_t data[8]){
	hcan.pTxMsg->StdId = id;
	hcan.pTxMsg->IDE = CAN_ID_STD;
	hcan.pTxMsg->RTR = CAN_RTR_DATA;
	hcan.pTxMsg->DLC = 0x08;
	hcan.pTxMsg->Data[0] = data[0];
	hcan.pTxMsg->Data[1] = data[1];
	hcan.pTxMsg->Data[2] = data[2];
	hcan.pTxMsg->Data[3] = data[3];
	hcan.pTxMsg->Data[4] = data[4];
	hcan.pTxMsg->Data[5] = data[5];
	hcan.pTxMsg->Data[6] = data[6];
	hcan.pTxMsg->Data[7] = data[7];
	HAL_CAN_Transmit_IT(&hcan); 
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
