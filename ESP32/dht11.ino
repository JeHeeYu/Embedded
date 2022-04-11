#include<DHT.h>
DHT dht(13, DHT11);

void setup() {
  Serial.begin(9600);

}

void loop() {
  delay(1000);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.print("Temperlature : ");
  Serial.print(temperature);
  Serial.println("C ");
  Serial.print("Humidity : ");
  Serial.print(humidity);
  Serial.println("%");
}
