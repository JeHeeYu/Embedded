#include <PubSubClient.h>
#include <WiFi.h>

#define MSG_BUFFER_SIZE (50)

const char* ssid = "AndroidHotspot3373";
const char* password = "11122233344455";
const char* mqtt_server = "192.168.115.164";
const char* clientName = "D1miniClientA";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;

char msg[MSG_BUFFER_SIZE];

int value = 0;

void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ...");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    Serial.print("WiFi connected");
    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());
  }
}

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  for(int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if((char)payload[0] == '1')
  {
    // led on
    Serial.println("LED On");
  }
  else
  {
    // led of
    Serial.println("LED Off");
  }
}

void reconnect()
{
  while(!client.connected())
  {
    Serial.print("Attempting MQTT Connection..");
    
    if(client.connect(clientName))
    {
      Serial.println("Connected");
      client.publish("outTopic", "hello world");
      client.subscribe("inTopic");
    }
    else
    {
      Serial.print("failed, rc = ");
      Serial.println(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  if(!client.connected())
  {
    reconnect();
  }
  client.loop();
  unsigned long now = millis();
  if(now - lastMsg  > 2000)
  {
    lastMsg = now;
    ++value;
    snprintf(msg, MSG_BUFFER_SIZE, "Hello World #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
}
