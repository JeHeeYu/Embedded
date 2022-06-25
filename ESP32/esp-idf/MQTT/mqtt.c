#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_system.h"
#include "esp_netif.h"
#include "mqtt_client.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "../hdr/common.h"
#include "../hdr/mqtt.h"

esp_mqtt_client_config_t mqttConfig = {
    .uri = MQTT_SERVER_ADDRESS,
    .port = 1883,
};

void MQTTInit()
{
    nvs_flash_init();
    tcpip_adapter_init();
    esp_netif_init();
    esp_event_loop_create_default();

    MQTTStart();
}

static void MQTTEventHandler(void *args, esp_event_base_t base, int32_t eventId, void* eventData)
{
    esp_mqtt_event_handle_t event = eventData;
    esp_mqtt_client_handle_t client = event->client;
    int messageId;

    switch((esp_mqtt_event_id_t)eventId) {
        case MQTT_EVENT_CONNECTED:
            printf("MQTT Connect is Success\n");
            int jehee = esp_mqtt_client_publish(client, "/jehee", "{\"mode\":7, \"press\":7}", 0, 1, 0);

            messageId = esp_mqtt_client_publish(client, "/jehee", "{\"mode\":7, \"press\":7}", 0, 0, 0);
            printf("Publish Success, messageId : %d\n", messageId);

            messageId = esp_mqtt_client_subscribe(client, "topic/qos0", 0);
            printf("Subscribe Success, messageId : %d\n", messageId);

            messageId = esp_mqtt_client_subscribe(client, "topic/qos1", 1);
            printf("Subscribe Success, messageId : %d\n", messageId);

            messageId = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
            break;
        case MQTT_EVENT_DISCONNECTED:
            printf("MQTT Connect is Fail\n");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            printf("MQTT_EVENT_SUBSCRIBED messsageId : %d\n", event->msg_id);
            messageId = esp_mqtt_client_publish(client, "/jehee", "{\"mode\":7, \"press\":7}", 0, 0, 0);
            printf("Publish Success messageid : %d", messageId);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            printf("MQTT_EVENT_UNSUBSRIBED messageId : %d\n", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            printf("MQTT_EVENT_PUBLISHED messageid : %d\n", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
        printf("MQTT_EVENT_DATA\n");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        break;
        case MQTT_EVENT_ERROR:
            printf("MQTT_EVENT_ERROR\n");
            if(event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
                printf("MQTT event Error\n");
            }
        default:
            break;
    }
}

static void MQTTStart(void)
{
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqttConfig);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, MQTTEventHandler, NULL);
    esp_mqtt_client_start(client);
    
    int jehee = esp_mqtt_client_publish(client, "/jehee", "{\"mode\":7, \"press\":7}", 0, 1, 0);
    printf("jehee : %d\n", jehee);
}
