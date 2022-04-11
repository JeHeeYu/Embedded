#ifndef INC_AM2320_H_
#define INC_AM2320_H_

#include "main.h"

#define AM2320_ADDRESS 0x5C<<1

typedef struct {
	I2C_HandleTypeDef* i2c_handle;
	uint8_t device_address;
	uint8_t data[8];
} AM2320_HandleTypeDef;

AM2320_HandleTypeDef AM2320_Init(I2C_HandleTypeDef* i2c_handle,uint8_t device_address);
uint8_t AM2320_SensorRead(AM2320_HandleTypeDef *am2320);
void AM2320_GetSensor(AM2320_HandleTypeDef *am2320, float *temperature, float *humidity);

#endif /* INC_AM2320_H_ */
