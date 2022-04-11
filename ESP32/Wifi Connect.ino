#include <WiFi.h>

const char* ssid     = "User ID";    // 연결할 SSID
const char* password = "Password";     // 연결할 SSID의 비밀번호

void setup()
{
    Serial.begin(9600);
    delay(10);
    
    WiFi.begin(ssid, password);

    // 와이파이망에 연결
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}

// 연결 여부 로그 출력
void loop()
{
    if(WiFi.status() == WL_CONNECTED)
        Serial.println("WiFi connected");
    else 
        Serial.println("WiFi not connected");
    delay(1000);
}
