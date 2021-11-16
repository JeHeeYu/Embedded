/*  Model : HC-SR04
 *  PIR Sensor
 *  VCC, GND, Signal 2ea
 */

int trig = 2;
int echo = 3;

void setup() 
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);

  int distance = pulseIn(echo, HIGH) * 340 / 2 / 10000;
  Serial.print(distance);
  Serial.println("cm");

  delay(100);
}
