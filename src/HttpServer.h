#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include "esp_err.h"
#include "esp_http_server.h"

esp_err_t start_webserver(void);
void stop_webserver(void);
bool webserver_is_running(void);

#endif