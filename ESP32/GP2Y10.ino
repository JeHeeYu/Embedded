#include<DHT.h>

#define DUST_LED_PIN 14
#define DUST_VALUE_PIN 26

void setup() {
  Serial.begin(9600);
  pinMode(DUST_LED_PIN, OUTPUT);
}

void loop() {

  digitalWrite(DUST_LED_PIN, LOW);
  delayMicroseconds(280);
  int value = analogRead(DUST_VALUE_PIN);
  delayMicroseconds(40);
  digitalWrite(DUST_LED_PIN, HIGH);
  delayMicroseconds(9680);
  Serial.println(value);
  delay(100);
}
