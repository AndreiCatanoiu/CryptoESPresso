#ifndef __WIFIAP_H__
#define __WIFIAP_H__

#include "esp_err.h"

#define ESP_WIFI_SSID      "CryptoESPresso"
#define ESP_WIFI_PASS      "AndreiCatanoiu"
#define ESP_WIFI_CHANNEL   1
#define MAX_STA_CONN       4

void wifi_ap_task(void *pvParameters);
int wifi_get_connected_clients(void);
bool wifi_is_initialized(void);

#endif