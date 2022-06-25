#define MQTT_SERVER_ADDRESS         "mqtt://192.168.81.42"

void MQTTInit();
static void MQTTEventHandler(void *args, esp_event_base_t base, int32_t eventId, void* eventData);
static void MQTTStart(void);
