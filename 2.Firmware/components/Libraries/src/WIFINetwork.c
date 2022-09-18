#include <stdint.h>
#include <stdio.h>
#include "esp_wifi.h"
#include "WIFINetwork.h"
/* ESP32 Library support. */
#include "esp_event.h"
#include "esp_log.h"
/* FreeRTOS Support. */
#include "freertos/event_groups.h"



/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */

#define CFG_MAXIMUM_RETRY   1000                  /* 配置最大重新连接次数 */
#define CFG_WIFI_SSID       "logzhan"             // 配置默认连接的WIFI的SSID
#define CFG_WIFI_PASS       "19931203"            // 配置默认连接的WIFI的密码
#define WIFI_CONNECTED_BIT  BIT0
#define WIFI_FAIL_BIT       BIT1

static EventGroupHandle_t   s_wifi_event_group;   /* FreeRTOS event group to signal when we are connected*/
static const char           *TAG = "WIFINetwork";
static int                  s_retry_num = 0;

wifi_config_t wifi_config = {
    .sta = {
        .ssid = CFG_WIFI_SSID,
        .password = CFG_WIFI_PASS,
        .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        .pmf_cfg = {
            .capable = true,
            .required = false
        },
    },
};

static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < CFG_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            printf("retry to connect to the AP\r\n");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        printf("connect to the AP fail\r\n");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

/**
 * @brief  Initializing the esp32 wifi network by gaving wifi ssid and
 *         password.
 * @param  ssid     : Wifi name which you want to connect.
 * @param  password : The wifi's password which you want to connect.
 * @return
 * @date   2022-09-04
 * @author zhanli 
 */
uint8_t Library_WIFI_Init(char* ssid, char* password){
    return 0;
}


uint8_t LIB_WIFIConnect(){

    ESP_LOGI(TAG, "LIB_WIFIConnect");

    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_LOGI(TAG, "esp_wifi_init");

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));
    /* Config esp32 wifi station mode. */
    ESP_LOGI(TAG, "esp_wifi_set_mode");
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    /* Config esp32 ssid password and authmode. */
    ESP_LOGI(TAG, "esp_wifi_set_config");
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    /* Start run the esp32 wifi. */
    ESP_LOGI(TAG, "esp_wifi_start");
    ESP_ERROR_CHECK(esp_wifi_start());

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) 
       or connection failed for the maximum number of re-tries (WIFI_FAIL_BIT). 
       The bits are set by event_handler() (see above) 
    */
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, hence we 
       can test which event actually* happened. 
    */
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 CFG_WIFI_SSID, CFG_WIFI_PASS);
        // xTaskCreate(create_multicast_ipv4_socket, "udp_client", 4096, NULL, 5, NULL);
        // xTaskCreate(udp_send_data, "udp_send", 4096, NULL, 5, NULL);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 CFG_WIFI_SSID, CFG_WIFI_PASS);
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }

    /* The event will not be processed after unregister */
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, 
        IP_EVENT_STA_GOT_IP, instance_got_ip));

    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, 
        ESP_EVENT_ANY_ID, instance_any_id));

    vEventGroupDelete(s_wifi_event_group);

    return 0;
}