#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"

/*************Pin Description************************************
 *            STM32    L298N
 * Motor A + : PA0      IN1
 * Motor A - : PA1      IN2
 * Motor B + : PC0      IN3
 * Motor B + : PC1      IN4
 *
 *****************************************************************/


void MotorOn(GPIO_TypeDef*, uint16_t pinA, uint16_t pinB);
void MotorOff(GPIO_TypeDef*, uint16_t pinA, uint16_t pinB);

#endif /* INC_MOTOR_H_ */
