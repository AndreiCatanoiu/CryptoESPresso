#include <string.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "HttpServer.h"

static const char *TAG = "HTTP_SERVER";
static httpd_handle_t server = NULL;

extern const uint8_t index_html_start[] asm("_binary_index_html_start");
extern const uint8_t index_html_end[]   asm("_binary_index_html_end");

extern const uint8_t style_css_start[]  asm("_binary_style_css_start");
extern const uint8_t style_css_end[]    asm("_binary_style_css_end");

static esp_err_t root_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, (const char *)index_html_start,
                    index_html_end - index_html_start);
    return ESP_OK;
}

static const httpd_uri_t root_uri = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = root_get_handler,
    .user_ctx  = NULL
};

static esp_err_t css_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/css");
    httpd_resp_send(req, (const char *)style_css_start,
                    style_css_end - style_css_start);
    return ESP_OK;
}

static const httpd_uri_t css_uri = {
    .uri       = "/style.css",
    .method    = HTTP_GET,
    .handler   = css_get_handler,
    .user_ctx  = NULL
};

static esp_err_t process_post_handler(httpd_req_t *req)
{
    char buf[512];
    int received = 0;
    int remaining = req->content_len;

    if (remaining >= sizeof(buf))
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Payload too large");
        return ESP_FAIL;
    }

    while (remaining > 0)
    {
        int ret = httpd_req_recv(req, buf + received, remaining);
        if (ret <= 0)
        {
            if (ret == HTTPD_SOCK_ERR_TIMEOUT)
            {
                continue;
            }
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to receive data");
            return ESP_FAIL;
        }
        received += ret;
        remaining -= ret;
    }
    buf[received] = '\0';

    ESP_LOGI(TAG, "Received POST /process: %s", buf);

    /*
     * TODO: Parse JSON, run crypto, build JSON response.
     */
    const char *response = "{\"result\":\"placeholder — crypto not implemented yet\"}";

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, response, strlen(response));

    return ESP_OK;
}

static const httpd_uri_t process_uri = {
    .uri       = "/process",
    .method    = HTTP_POST,
    .handler   = process_post_handler,
    .user_ctx  = NULL
};

esp_err_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    ESP_LOGI(TAG, "Starting HTTP server on port %d", config.server_port);

    esp_err_t ret = httpd_start(&server, &config);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start HTTP server: %s", esp_err_to_name(ret));
        return ret;
    }

    httpd_register_uri_handler(server, &root_uri);
    httpd_register_uri_handler(server, &css_uri);
    httpd_register_uri_handler(server, &process_uri);

    ESP_LOGI(TAG, "HTTP server started — serving on 192.168.4.1");

    return ESP_OK;
}

void stop_webserver(void)
{
    if (server)
    {
        httpd_stop(server);
        server = NULL;
        ESP_LOGI(TAG, "HTTP server stopped");
    }
}

bool webserver_is_running(void)
{
    return server != NULL;
}