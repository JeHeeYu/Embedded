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

wifi_config_t apModeConfig = {
    .ap = {
      .ssid = SSID_AP_MODE,
      .ssid_len = strlen(SSID_AP_MODE),
      .password = PASSWORD_AP_MOE,
      .channel = CHANNEL_AP_MODE,
      .authmode = WIFI_AUTH_WPA_WPA2_PSK,
      .max_connection = MAX_CONNECTION_AP_MODE,
    },
};

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
    WiFiAPMode();
}

void WiFiAPMode()
{
    NVSInit();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &APModeEventHandler, NULL, NULL));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &apModeConfig));
    ESP_ERROR_CHECK(esp_wifi_start());
}

static void APModeEventHandler(void* arg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
{
    if(eventId == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) eventData;
    }
    else if(eventId == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) eventData;
    }
    else {
        printf("WiFI Is Null\n");
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
