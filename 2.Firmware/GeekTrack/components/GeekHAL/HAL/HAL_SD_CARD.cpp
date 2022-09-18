#include "HAL.h"
#include "HAL/HAL_Config.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
/* print sdmmc info support */
#include "sdmmc_cmd.h"
static const char *TAG = "SDCARD";

#define MOUNT_POINT "/sdcard"
/* SDCard DMA CHANNEL select */
#define SPI_DMA_CHAN    2
/* SDcard Pin Config         */
#define PIN_NUM_MISO    26
#define PIN_NUM_MOSI    13
#define PIN_NUM_CLK     14
#define PIN_NUM_CS      15
#define SD_OCR_SDHC_CAP                 (1<<30)

static bool SD_IsReady = false;
static uint64_t SD_CardSize = 0;
static SD_CallbackFunction_t SD_EventCallback = nullptr;

sdmmc_card_t* card;

/*
 * User provided date time callback function.
 * See SdFile::dateTimeCallback() for usage.
 */
// static void SD_GetDateTime(uint16_t* date, uint16_t* time)
// {
//     // User gets date and time from GPS or real-time
//     // clock in real callback function
//     // HAL::Clock_Info_t clock;
//     // HAL::Clock_GetInfo(&clock);

//     // // return date using FAT_DATE macro to format fields
//     // *date = FAT_DATE(clock.year, clock.month, clock.day);

//     // // return time using FAT_TIME macro to format fields
//     // *time = FAT_TIME(clock.hour, clock.minute, clock.second);
// }

// static bool SD_CheckDir(const char* path)
// {
//     bool retval = true;
//     // if(!SD.exists(path))
//     // {
//     //     Serial.printf("SD: Auto create path \"%s\"...", path);
//     //     retval = SD.mkdir(path);
//     //     Serial.println(retval ? "success" : "failed");
//     // }
//     return retval;
// }

const char* SD_GetCardName(){
    if(SD_IsReady){
        return card->cid.name;
    }
    return "None SDcard";
}

float SD_GetCardSizeMB()
{
    if(SD_IsReady == false){
        SD_CardSize = 0;
        return 0.0f;
    }
    SD_CardSize = ((uint64_t) card->csd.capacity) * card->
            csd.sector_size / (1024 * 1024);
    float size = (float)SD_CardSize;
    return size;
}


uint8_t SD_Init()
{
    bool retval = true;
    const char mount_point[] = MOUNT_POINT;

    ESP_LOGI(TAG, "SDCard Init bus. ");

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
        .flags = 0,
        .intr_flags = 0
    };
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();

    /* Init SPI Bus */
    esp_err_t ret = spi_bus_initialize(SDSPI_DEFAULT_HOST, &bus_cfg, SPI_DMA_CHAN);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize bus.");
        return false;
    }

    ESP_LOGI(TAG, "SDCard Mount System. ");
    /* Configration mount SDSPI FAT System. */
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    
    slot_config.gpio_cs = (gpio_num_t)PIN_NUM_CS;
    slot_config.host_id = (spi_host_device_t)host.slot;
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s).", esp_err_to_name(ret));
        }
        return false;
    }

    SD_IsReady = true;
    /* Print sdcard infomation. */
    //sdmmc_card_print_info(stdout, card);

    FILE* stream = stdout;

    fprintf(stream, "Name: %s\n", SD_GetCardName());
    fprintf(stream, "Size: %.2fMB\n", SD_GetCardSizeMB());
    fprintf(stream, "Type: %s\n", SD_GetTypeName());
    return retval;
}



uint8_t SD_GetReady()
{
    return (uint8_t)SD_IsReady;
}


const char* SD_GetTypeName()
{
    const char* type = "Unknown";
    /* Check card Size. */
    if(!SD_CardSize){
        goto failed;
    }
    /* Check card type. */
    if (card->is_sdio) {
        type = "SDIO";
    }else if (card->is_mmc) {
        type = "MMC";
    }else{
        type = (card->ocr & SD_OCR_SDHC_CAP) ? "SDHC/SDXC" : "SDSC";
    }
failed:
    return type;
}

// static void SD_Check(bool isInsert)
// {
//     // if(isInsert)
//     // {
//     //     bool ret = HAL::SD_Init();

//     //     if(ret && SD_EventCallback)
//     //     {
//     //         SD_EventCallback(true);
//     //     }

//     //     HAL::Audio_PlayMusic(ret ? "DeviceInsert" : "Error");
//     // }
//     // else
//     // {
//     //     SD_IsReady = false;

//     //     if(SD_EventCallback)
//     //     {
//     //         SD_EventCallback(false);
//     //         SD_CardSize = 0;
//     //     }

//     //     HAL::Audio_PlayMusic("DevicePullout");
//     // }
// }

void SD_SetEventCallback(SD_CallbackFunction_t callback)
{
    SD_EventCallback = callback;
}

void SD_Update()
{
    // bool isInsert = (digitalRead(CONFIG_SD_CD_PIN) == LOW);

    // CM_VALUE_MONITOR(isInsert, SD_Check(isInsert));
}
