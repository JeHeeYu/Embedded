const int ledPin = 2;
const int btnPin = 4;
int btnState;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
}

void loop() 
{
  btnState = digitalRead(btnPin);
  digitalWrite(ledPin, btnState);
}
