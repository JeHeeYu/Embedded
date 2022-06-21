#include "esp_event.h"

#define SSID_STATION_MODE         "AndroidHotspot3373"
#define PASSWORD_STATION_MODE     "11122233344455" 
#define CHANNEL_STATION_MODE      1
#define RETRY_MAXIMUM_COUNT       10

#define WIFI_CONNECTED_BIT        BIT0
#define WIFI_FAIL_BIT             BIT1

void WiFiInit();
void WiFiStationMode();
void NVSInit();
void WiFiCheckBits();

static void StationModeEventHandler(void* arg, esp_event_base_t eventBase, int32_t eventId, void* eventData);
