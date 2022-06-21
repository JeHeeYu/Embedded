#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "../hdr/common.h"
#include "../hdr/wifi.h"

wifi_config_t stationModeConfig = {
    .sta = {
      .ssid = SSID_STATION_MODE,
      .password = PASSWORD_STATION_MODE,
    },
};

static EventGroupHandle_t wifiEventGroupHandler;
static int wifiRetryCount = 0;

void NVSInit()
{
  esp_err_t ret = nvs_flash_init();
  if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    nvs_flash_erase();
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
}

void WiFiInit()
{
  WiFiStationMode();
  //WiFiAPMode();
}

void WiFiStationMode()
{
  NVSInit();
  wifiEventGroupHandler = xEventGroupCreate();
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  esp_netif_create_default_wifi_sta();

  wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&config));

  esp_event_handler_instance_t instanceId;
  esp_event_handler_instance_t instanceIp;
  ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &StationModeEventHandler, NULL, &instanceId));
  ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &StationModeEventHandler, NULL, &instanceIp));

  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &stationModeConfig));
  ESP_ERROR_CHECK(esp_wifi_start());

  WiFiCheckBits();
}

static void StationModeEventHandler(void* arg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
{
  if(eventBase == WIFI_EVENT && eventId == WIFI_EVENT_STA_START) {
    esp_wifi_connect();
  }
  else if(eventBase == WIFI_EVENT && eventId == WIFI_EVENT_STA_DISCONNECTED) {
    if(wifiRetryCount < RETRY_MAXIMUM_COUNT) {
      esp_wifi_connect();
      wifiRetryCount++;
      printf("WiFi Disconnected and Retry Count : %d\n", wifiRetryCount);
    }
    else {
      xEventGroupSetBits(wifiEventGroupHandler, WIFI_FAIL_BIT);
      }
    }
    else if(eventBase == IP_EVENT && eventId == IP_EVENT_STA_GOT_IP) {
      ip_event_got_ip_t* event = (ip_event_got_ip_t*) eventData;
      wifiRetryCount = 0;
      xEventGroupSetBits(wifiEventGroupHandler, WIFI_CONNECTED_BIT);
    }
    else {
      printf("WiFi is Null\n");
    }
}

void WiFiCheckBits()
{
  EventBits_t bits = xEventGroupWaitBits(wifiEventGroupHandler, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdFALSE, pdFALSE, portMAX_DELAY);

  if(bits & WIFI_CONNECTED_BIT) {
    printf("WiFi Connected to SSID : %s, Password : %s\n", SSID_STATION_MODE, PASSWORD_STATION_MODE);
  }
  else if(bits & WIFI_FAIL_BIT) {
    printf("WiFi Fail to SSID : %s, Password : %s\n", SSID_STATION_MODE, PASSWORD_STATION_MODE);
  }
  else {
    printf("WiFI is Null\n");
  }
}
