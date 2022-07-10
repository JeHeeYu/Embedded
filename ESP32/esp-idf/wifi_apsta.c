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
#include "esp_log.h"
#include "esp_http_server.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "../inc/wifi.h"
#include "../inc/http.h"

static const char* TAG = "WIFI";

static EventGroupHandle_t wifiEventGroupHandler;
static int wifiRetryCount = 0;

static void WiFiAPModeEventHandler(void* arg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
{
    if(eventId == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) eventData;
        ESP_LOGI(TAG, "AID : %d", event->aid);
    }
    else if(eventId == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) eventData;
        ESP_LOGI(TAG, "AID : %d", event->aid);
    }
}

static void WiFiStationModeEventHandler(void* arg, esp_event_base_t eventBase, int32_t eventId, void* eventData)
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

void WiFiModeInit()
{
    wifi_config_t stationModeConfig = {
        .sta = {
            .ssid = WIFI_STATION_MODE_SSID,
            .password = WIFI_STATION_MODE_PASSWORD,
        },
    };

    wifi_config_t apModeConfig = {
        .ap = {
            .ssid = WIFI_AP_MODE_SSID,
            .password = WIFI_AP_MODE_PASSWORD,
            .max_connection = WIFI_AP_MODE_MAX_CONNECTION,
            .ssid_len = strlen(WIFI_AP_MODE_SSID),
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
            .max_connection = WIFI_AP_MODE_MAX_CONNECTION,
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &apModeConfig));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &stationModeConfig));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "AP Mode SSID : %s, Password : %s", WIFI_AP_MODE_SSID, WIFI_AP_MODE_PASSWORD);
    
    ESP_ERROR_CHECK(esp_wifi_connect());

    WiFiCheckBits();
}

void WiFiNVSInit()
{
    ESP_LOGI(TAG, "WiFiNVSInit");

    esp_err_t nvs = nvs_flash_init();
    if((nvs == ESP_ERR_NVS_NO_FREE_PAGES) || (nvs == ESP_ERR_NVS_NEW_VERSION_FOUND)) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvs = nvs_flash_init();
    }
    ESP_ERROR_CHECK(nvs);
}

void WiFiInit()
{
    ESP_LOGI(TAG, "WiFiInit");

    WiFiInitializeSet();
    WiFiModeInit();
}

void WiFiInitializeSet()
{
    WiFiNVSInit();
    ESP_ERROR_CHECK(esp_netif_init());

    wifiEventGroupHandler = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_t* apNetIf = esp_netif_create_default_wifi_ap();
    assert(apNetIf);

    esp_netif_t* stationNetIf = esp_netif_create_default_wifi_sta();
    assert(stationNetIf);

    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &WiFiStationModeEventHandler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &WiFiAPModeEventHandler, NULL));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void WiFiCheckBits()
{
    EventBits_t bits = xEventGroupWaitBits(wifiEventGroupHandler, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdFALSE, pdFALSE, portMAX_DELAY);

    if(bits & WIFI_CONNECTED_BIT) {
        printf("WiFi Connected to SSID : %s, Password : %s\n", WIFI_STATION_MODE_SSID, WIFI_STATION_MODE_PASSWORD);
    }
    else if(bits & WIFI_FAIL_BIT) {
        printf("WiFi Fail to SSID : %s, Password : %s\n", WIFI_STATION_MODE_SSID, WIFI_STATION_MODE_PASSWORD);
    }
    else {
        printf("WiFI is Null\n");
    }
}
