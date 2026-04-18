#include "sleep.h"

void sleep_mode::deep_sleep(int time)
{
    const char *TAG = "SLEEP";

#ifdef DEBUG_LEVEL
    ESP_LOGI(TAG, "Entering in deep sleep mode...");
#endif

    esp_sleep_enable_timer_wakeup(time);
    esp_deep_sleep_start();
}