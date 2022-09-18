#include <stdio.h>
#include <stdbool.h>
#include "HAL.h"
/* ESP32 NVS Flash Support.*/
#include "nvs_flash.h"
#include "nvs.h"

static nvs_handle_t nvs_hal;
bool Config_InitFlag = false;
char StringBuff[64]  = {0};

void Config_Init()
{
    printf("Init Config Support.\n");
    /* Init ESP32 NVS Flash. */
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    // err = nvs_open("storage", NVS_READWRITE, &nvs_hal);
    // if (err != ESP_OK) {
    //     printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    //     Config_InitFlag = false;
    // }

    // Config_InitFlag = true;
    // size_t length = 64;
    // /* If load wifi name fail. config the default name. and password */
    // if(Config_GetString("WIFI_NAME", StringBuff, &length) == 0){
    //     Config_SetString("WIFI_NAME", "WIFI_DAFAULT_NAME");
    // }
    // if(Config_GetString("WIFI_NAME", StringBuff, &length) == 0){
    //     Config_SetString("WIFI_PWD", "WIFI_DAFAULT_PWD");
    // }
}


uint8_t Config_GetString(const char* key, char* str, size_t* length)
{
    if(!Config_InitFlag){
        return 0;
    }

    esp_err_t err =  nvs_get_str(nvs_hal, key, str, length);

    if(err != ESP_OK)
    {
        printf("Cofig_GetStrig:: nvs_get_str error\n");
        return 0;
    }
    return 1;
}

uint8_t Config_SetString(const char* key, const char* str){
    if(!Config_InitFlag){
        return 0;
    }
    esp_err_t err = nvs_set_str(nvs_hal, key, str);
    if(err != ESP_OK){
        printf("Cofig_SetStrig:: nvs_set_str error\n");
        return 0;
    }
    return 1;
}

