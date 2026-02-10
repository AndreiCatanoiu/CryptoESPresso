#include <esp_log.h>
#include <esp_task.h>

void app_main() {
    while (1) {
        ESP_LOGI("APP_MAIN", "Hello, ESP32!");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}