#include <esp_sleep.h>
#include "esp_log.h"

namespace sleep_mode
{
    /**
     * @brief Enter deep sleep mode for a specified time.
     *
     * @param time Wakeup time in microseconds.
     */
    void deep_sleep(int time);
}
