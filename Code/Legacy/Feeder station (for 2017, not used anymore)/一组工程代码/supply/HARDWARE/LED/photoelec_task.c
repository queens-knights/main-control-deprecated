#include "photoelec_task.h"

u8 input_state = 0 ;
void photoelec_detect_circle()
{
	light[0] = GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_0);//KEY_STATE;
  light[1] = GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_1);//KEY_STATE;
	light[2] = GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_2);//KEY_STATE;
  light[3] = GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_3);//KEY_STATE;
}
