#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define AM2320_ADDR 0x5C
#define I2C_DEVICE "/dev/i2c-1"

#define AM2320_HIGH_HUMIDITY 0x00
#define AM2320_LOW_HUMIDITY 0x01
#define AM2320_HIGH_TEMPERATURE 0x02
#define AM2320_LOW_TEMPERATURE 0x03

#define AM2320_READ_REGISTER 0x03


double getTemperature(int fd);
double getHumidity(int fd);



int main(int argc, char * argv[]) 
{
	wiringPiSetup();

	int fd = wiringPiI2CSetup(AM2320_ADDR);
	if(0 > fd)
	{
		fprintf(stderr, "Error : %s\n", strerror(errno));
	}

	while(1) {
		printf("Temp : %5.2f\n", getTemperature(fd));
		printf("Humid : %5.2f\n", getHumidity(fd));
		
		delay(2000);
	}
	
	return 0;
}

double getTemperature(int fd)
{
	unsigned char buf[4];
	wiringPiI2CWrite(fd, AM2320_HIGH_TEMPERATURE);
	delay(100);

	read(fd, buf, 3);
	unsigned int temp = (buf[0] << 8 | buf [1]) & 0xFFFC;

	double tSensorTemp = temp / 65536.0;
	return -46.85 + (175.72 * tSensorTemp);
	// 15 * 16 + 10 = 250
}

double getHumidity(int fd)
{
	unsigned char buf[4];
	wiringPiI2CWrite(fd, AM2320_HIGH_HUMIDITY);
	delay(100);
	read(fd, buf, 3);
	unsigned int humid = (buf [0] << 8 | buf[1]) & 0xFFFC;

	double tSensorHumid = humid / 65536.0;
	return -6.0 + (125.0 * tSensorHumid);
}
