#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "WiFiAP.h"

static const char *TAG = "WIFI_SOFTAP";
static int connected_clients = 0;
static bool wifi_initialized = false;

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED)
    {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
        connected_clients++;
        ESP_LOGI(TAG, "station "MACSTR" joined, AID=%d [clients: %d]",
                 MAC2STR(event->mac), event->aid, connected_clients);
    }
    else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
    {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *)event_data;
        connected_clients--;
        ESP_LOGI(TAG, "station "MACSTR" left, AID=%d, reason=%d [clients: %d]",
                 MAC2STR(event->mac), event->aid, event->reason, connected_clients);
    }
}

static esp_err_t wifi_init_softap(void)
{
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = ESP_WIFI_SSID,
            .ssid_len = strlen(ESP_WIFI_SSID),
            .channel = ESP_WIFI_CHANNEL,
            .password = ESP_WIFI_PASS,
            .max_connection = MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA3_PSK,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
            .pmf_cfg = {
                .required = true,
            },
        },
    };

    if (strlen(ESP_WIFI_PASS) == 0)
    {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "SoftAP started — SSID: %s | Channel: %d", ESP_WIFI_SSID, ESP_WIFI_CHANNEL);

    wifi_initialized = true;
    return ESP_OK;
}

void wifi_ap_task(void *pvParameters)
{
    ESP_ERROR_CHECK(wifi_init_softap());

    while (1)
    {
        ESP_LOGI(TAG, "Clients: %d | Free heap: %lu bytes", connected_clients, esp_get_free_heap_size());
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

int wifi_get_connected_clients(void)
{
    return connected_clients;
}

bool wifi_is_initialized(void)
{
    return wifi_initialized;
}