#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "WiFiAP.h"
#include "HttpServer.h"

static const char *TAG = "MAIN";

void init_app(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_LOGI(TAG, "System init done");
}

void app_main(void)
{
    init_app();
    xTaskCreate(wifi_ap_task, "wifi_ap", 8192, NULL, 5, NULL);
    while (!wifi_is_initialized())
    {
        ESP_LOGI(TAG, "Waiting for WiFi to initialize...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    start_webserver();
}