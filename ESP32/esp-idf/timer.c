#include <stdio.h>
#include "esp_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "soc/timer_group_struct.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"
#include "./hdr/timer.h"
#define TIMER_DIVIDER   (16)
#define LED_PIN GPIO_NUM_2
    timer_config_t timerConfig = {
    .divider = TIMER_DIVIDER,
    .counter_dir = TIMER_COUNT_UP,
    .counter_en = TIMER_PAUSE,
    .alarm_en = TIMER_ALARM_EN,
    .auto_reload = TIMER_AUTORELOAD_EN,
};

static SemaphoreHandle_t s_timer_sem;
static bool IRAM_ATTR TimerCallback(void *args) 
{
  BaseType_t high_task_awoken = pdFALSE;
  xSemaphoreGiveFromISR(s_timer_sem, &high_task_awoken);

  return high_task_awoken == pdTRUE;
}

void TimerInit()
{
    gpio_set_direction(2, GPIO_MODE_OUTPUT);
    timer_init(TIMER_GROUP_0, TIMER_0, &timerConfig);
    timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0);
    timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, (TIMER_BASE_CLK / TIMER_DIVIDER));
    timer_enable_intr(TIMER_GROUP_0, TIMER_0);
    timer_isr_callback_add(TIMER_GROUP_0, TIMER_0, TimerCallback, NULL, 0);
    timer_start(TIMER_GROUP_0, TIMER_0);
}

void app_main()
{	
    static int led_state = 0;
    s_timer_sem = xSemaphoreCreateBinary();

    TimerInit();
    while(1) {
        if(xSemaphoreTake(s_timer_sem, portMAX_DELAY) == pdPASS) {
            if (led_state == 0) {
                led_state = 1;
                gpio_set_level(LED_PIN, 1);
                }
            else {
                led_state = 0;
                gpio_set_level(LED_PIN, 0);
                }
            }
        }
}
