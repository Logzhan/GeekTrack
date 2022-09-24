/******************** (C) COPYRIGHT 2022 GEEKIMU *******************************
* File Name          : app_main.c
* Current Version    : V1.0 & ESP32
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2022.09.17 zhanli : Create for GeekTrack.
* Comments           : GeekTrack主程序
********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "HAL/HAL.h"

// ESP网络相关
#include "esp_log.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <sys/param.h>
#include "esp_netif.h"
#include "lwip/sockets.h"
#include <lwip/netdb.h>
// ESP 串口配置相关
#include "freertos/queue.h"
#include "geek_shell_api.h"

// ADC 配置相关
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"

#include "System/GeekOS.h"
#include "WIFINetwork.h"
#include "mpu9250.h"

#define UDP_PORT            9000
#define TAG                 "main"

static void UdpSendData(void *pvParameters)
{
    struct sockaddr_in saddr = { 0 };

    int sock = -1; 
    int err = 0;
    /* Init the sock. */
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0) {
        ESP_LOGE(TAG, "Failed to create socket. Error %d", errno);
    }

    saddr.sin_family = PF_INET;
    saddr.sin_port = htons(UDP_PORT);
    saddr.sin_addr.s_addr = htonl(IPADDR_BROADCAST);
    
	char line[128] = " ";
    /* Task Send Sensor Data. */
    while (1) {
        float yaw, roll, pitch;
        MPU9250_GetEulerAngles(&yaw, &roll, &pitch);
		sprintf(line, "%f %f %f\n", yaw, roll, pitch);
        err = sendto(sock, line, 256, 0, (struct sockaddr *)&saddr, 
                sizeof(struct sockaddr_in));
        if (err < 0) {
            ESP_LOGE(TAG, "IPV4 sendto failed. errno: %d", errno);
        }   
        vTaskDelay(30 / portTICK_PERIOD_MS);
    }
    close(sock);
}

/**-----------------------------------------------------------------------
* Function    : app_main
* Description : GEEKIMU 程序主入口
* Author      : zhanli&719901725@qq.com
* Date        : 2021/7/20 zhanli
*---------------------------------------------------------------------**/
void app_main(void)
{
    /* HAL init config. */
    HAL_Init();

    // vTaskDelay(1500 / portTICK_PERIOD_MS);
    /* Config serial zero for shell. */
	userShellInit(0);
    xTaskCreate(shellTask, "shell", 4096, GetEsp32Shell(), 12, NULL);

    LIB_WIFIConnect();
    xTaskCreate(UdpSendData, "UdpSend", 4096, NULL, 5, NULL);

    uint32_t tick = 0;
    /* Forever loop. */
    while(1){
        /* Delay 10ms in order to relase cpu. */
        vTaskDelay(10 / portTICK_PERIOD_MS);
        /* Update HAL task. */
        HAL_Update(tick);
        tick += 10;
    }
}
