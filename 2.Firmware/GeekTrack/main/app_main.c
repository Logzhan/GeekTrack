/******************** (C) COPYRIGHT 2022 GEEKIMU *******************************
* File Name          : app_main.c
* Current Version    : V1.0 & ESP32
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2022.09.17 zhanli : Create for GeekTrack.
* Comments           : GeekTrack主程序
********************************************************************************/
#include <stdint.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "HAL/HAL.h"
// ESP 串口配置相关
#include "geek_shell_api.h"

void app_main(void)
{
    /* HAL init config. */
    HAL_Init();
    /* Config serial zero for shell. */
	userShellInit(0);
    xTaskCreate(shellTask, "shell", 4096, GetEsp32Shell(), 12, NULL);
    /* Init the wifi and socket connect. */
    Network_Init();
    xTaskCreate(Network_UdpSendData, "NetworkSendData", 4096, NULL, 5, NULL);

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
