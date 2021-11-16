/*  Model : HC-SR501
 *  PIR Sensor
 *  VCC, GND, Signal 1ea
 */

int val = 0;

void setup() 
{
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  val = digitalRead(2);
  if(val == HIGH)
  {
    digitalWrite(3, HIGH);
  }

  else
  {
    digitalWrite(3, LOW);
  }

  Seiral.println(val);
}
