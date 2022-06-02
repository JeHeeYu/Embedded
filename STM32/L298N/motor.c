#include "main.h"
#include "motor.h"

void MotorOn(GPIO_TypeDef* port, uint16_t pinA, uint16_t pinB)
{
	HAL_GPIO_WritePin(port, pinA, LOW);
	HAL_GPIO_WritePin(port, pinB, HIGH);
	HAL_Delay(100);
}

void MotorOff(GPIO_TypeDef* port, uint16_t pinA, uint16_t pinB)
{
	HAL_GPIO_WritePin(port, pinA, LOW);
	HAL_GPIO_WritePin(port, pinB, LOW);
	HAL_Delay(100);
}
