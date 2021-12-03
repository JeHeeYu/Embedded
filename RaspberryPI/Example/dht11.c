#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXTIMINGS    85
#define DHTPIN        7  // RPI DHT11 Pin number

int dht11Data[5] = { 0, };

void ReadDHT11()
{
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t i, j = 0;
	
	float f;
	
	for(i = 0; i < 5; i++)
	{
		dht11Data[i] = 0;
	}
	
	pinMode(DHTPIN, OUTPUT);
	digitalWrite(DHTPIN, LOW);
	delay(18);
	digitalWrite(DHTPIN, HIGH);
	delayMicroseconds(40);
	pinMode(DHTPIN, INPUT);
	
	for(i = 0; i < MAXTIMINGS; i++)
	{
		counter = 0;
		while(digitalRead(DHTPIN) == laststate)
		{
			counter ++;
			delayMicroseconds(1);
			
			if(counter == 255)
			{
				break;
			}
		}
		
		laststate = digitalRead(DHTPIN);

		if(counter == 255)
		{
			break;
		}
		
		if ((i >= 4) && (i % 2 == 0))
		{
			dht11Data[j / 8] <<= 1;
			
			if (counter > 16)
			{
				dht11Data[j / 8] |= 1;
			}
			
			j++;
		}
	}
	
	if ((j >= 40) && (dht11Data[4] == ( (dht11Data[0] + dht11Data[1] + dht11Data[2] + dht11Data[3]) & 0xFF)))
	{
		f = dht11Data[2] * 9. / 5. + 32;
		printf("Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n", dht11Data[0], dht11Data[1], dht11Data[2], dht11Data[3], f);
	}
		
	else  
	{
		printf("Data not good, skip\n");
	}
}

int main()
{
    printf("Raspberry Pi wiringPi DHT11 Temperature test program\n");
 
    if (wiringPiSetup() == -1)
    {
			exit( 1 );
	}
 
    while (1)
    {
        ReadDHT11();
        delay(1000); 
    }
 
    return(0);
}
