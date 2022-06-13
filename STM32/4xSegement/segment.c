#include "segment.h"

uint16_t segPin[8] =
{
		SEG_1_Pin,
		SEG_2_Pin,
		SEG_3_Pin,
		SEG_4_Pin,
		SEG_5_Pin,
		SEG_6_Pin,
		SEG_7_Pin,
		SEG_8_Pin,
};

uint16_t segComPin[4] =
{
		SEGCOM_1_Pin,
		SEGCOM_2_Pin,
		SEGCOM_3_Pin,
		SEGCOM_4_Pin,
};

int segNumber[10][8] =
{
		{ 1, 1, 1, 1, 1, 1, 1, 0 },	// 0
		{ 0, 1, 1, 0, 0, 0, 0, 0 },	// 1
		{ 1, 1, 0, 1, 1, 0, 1, 0 },	// 2
		{ 1, 1, 1, 1, 0, 0, 1, 0 },	// 3
		{ 0, 1, 1, 0, 0, 1, 1, 0 }, 	// 4
		{ 1, 0, 1, 1, 0, 1, 1, 0 }, 	// 5
		{ 1, 0, 1, 1, 1, 1, 1, 0 }, 	// 6
		{ 1, 1, 1, 0, 0, 0, 0, 0 }, 	// 7
		{ 1, 1, 1, 1, 1, 1, 1, 0 }, 	// 8
		{ 1, 1, 1, 0, 0, 1, 1, 0 }	// 9
};



void SegInit()
{
	int i;

	for(i = 0; i < 4; i++)
	{

		HAL_GPIO_WritePin(segComPort[i], segComPin[i], GPIO_PIN_SET);
	}

	for(int i = 0; i < 9; i++)
	{
		HAL_GPIO_WritePin(segPort[i], segPin[i], GPIO_PIN_SET);
	}
}

void SegShow(int number, int digit)
{
	int i;

	for(i = 0 ; i < 4; i++)
	{
		if(i + 1 == digit)
		{
			HAL_GPIO_WritePin(segComPort[i], segComPin[i], GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(segComPort[i], segComPin[i], GPIO_PIN_SET);
		}
	}

	for(i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(segPort[i], segPin[i], segNumber[number][i]);
	}
	HAL_Delay(1000);
}
