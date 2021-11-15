const int ledPin = 3;

void setup() 
{
  
}

void loop() 
{
  int i;
  for(i = 0; i < 255; i++)
  {
    analogWrite(ledPin, i);
    delay(5);
  }

  for(i = 255; i > 0; i--)
  {
    analogWrite(ledPin, i);
    delay(5);
  }
}
