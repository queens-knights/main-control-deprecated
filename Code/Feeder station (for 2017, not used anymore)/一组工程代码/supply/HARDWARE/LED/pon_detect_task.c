#include "pon_detect_task.h"

void pon_detect_circle()
{
	key[0]  = GPIO_ReadInputDataBit(GPIOD , GPIO_Pin_12);//KEY_STATE;
  key[1]  = GPIO_ReadInputDataBit(GPIOD , GPIO_Pin_13);//KEY_STATE;
	key[2]  = GPIO_ReadInputDataBit(GPIOD , GPIO_Pin_14);//KEY_STATE;
  key[3]  = GPIO_ReadInputDataBit(GPIOD , GPIO_Pin_15);//KEY_STATE;
	key[4]  = GPIO_ReadInputDataBit(GPIOH , GPIO_Pin_10);//KEY_STATE;
  key[5]  = GPIO_ReadInputDataBit(GPIOH , GPIO_Pin_11);//KEY_STATE;
	key[6]  = GPIO_ReadInputDataBit(GPIOH , GPIO_Pin_12);//KEY_STATE;
  key[7]  = GPIO_ReadInputDataBit(GPIOI , GPIO_Pin_0 );//KEY_STATE;
	key[8]  = GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_8);
	key[9]  = GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_9);
	key[10] = GPIO_ReadInputDataBit(GPIOE , GPIO_Pin_13);
	key[11] = GPIO_ReadInputDataBit(GPIOE , GPIO_Pin_14);
}



