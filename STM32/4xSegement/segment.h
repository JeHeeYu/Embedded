#ifndef INC_SEGMENT_H_
#define INC_SEGMENT_H_

#include "main.h"

GPIO_TypeDef *segPort[8] =
{
		SEG_1_GPIO_Port,
		SEG_2_GPIO_Port,
		SEG_3_GPIO_Port,
		SEG_4_GPIO_Port,
		SEG_5_GPIO_Port,
		SEG_6_GPIO_Port,
		SEG_7_GPIO_Port,
		SEG_8_GPIO_Port,
};

GPIO_TypeDef *segComPort[4] =
{
		SEGCOM_1_GPIO_Port,
				SEGCOM_2_GPIO_Port,
				SEGCOM_3_GPIO_Port,
				SEGCOM_4_GPIO_Port,
};

void SegShow(int number, int digit);
void SegInit();

#endif /* INC_SEGMENT_H_ */
