#include "esp_event.h"

#define SSID_AP_MODE             "JeheeTest"
#define PASSWORD_AP_MOE          "11122233344455"
#define CHANNEL_AP_MODE          10
#define MAX_CONNECTION_AP_MODE   10

void WiFiInit();
void WiFiAPMode();
void NVSInit();
void WiFiCheckBits();
static void APModeEventHandler(void* arg, esp_event_base_t eventBase, int32_t eventId, void* eventData);
