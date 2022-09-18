#include "HAL\HAL.h"
#include "HAL/HAL_Config.h"
/* print sdmmc info support */

static const char *TAG = "SDCARD";

#define MOUNT_POINT "/sdcard"
/* SDCard DMA CHANNEL select */
#define SPI_DMA_CHAN    2
/* SDcard Pin Config         */
#define PIN_NUM_MISO    2
#define PIN_NUM_MOSI    15
#define PIN_NUM_CLK     14
#define PIN_NUM_CS      13
#define SD_OCR_SDHC_CAP                 (1<<30)

static bool SD_IsReady = false;
/* Win32 Simulate set 16GB. */
static uint64_t SD_CardSize = 16 * 1024;
static SD_CallbackFunction_t SD_EventCallback = nullptr;

/*
 * User provided date time callback function.
 * See SdFile::dateTimeCallback() for usage.
 */
static void SD_GetDateTime(uint16_t* date, uint16_t* time)
{
    // User gets date and time from GPS or real-time
    // clock in real callback function
    // HAL::Clock_Info_t clock;
    // HAL::Clock_GetInfo(&clock);

    // // return date using FAT_DATE macro to format fields
    // *date = FAT_DATE(clock.year, clock.month, clock.day);

    // // return time using FAT_TIME macro to format fields
    // *time = FAT_TIME(clock.hour, clock.minute, clock.second);
}

static bool SD_CheckDir(const char* path)
{
    bool retval = true;
    // if(!SD.exists(path))
    // {
    //     Serial.printf("SD: Auto create path \"%s\"...", path);
    //     retval = SD.mkdir(path);
    //     Serial.println(retval ? "success" : "failed");
    // }
    return retval;
}

const char* SD_GetCardName(){
    if(SD_IsReady){
        return "WIN32Card";
    }
    return "None";
}

float SD_GetCardSizeMB()
{
    float size = (float)SD_CardSize;
    return size;
}


uint8_t SD_Init()
{
    SD_IsReady = true;
    return SD_IsReady;
}



uint8_t SD_GetReady()
{
    return SD_IsReady;
}


const char* SD_GetTypeName()
{
    return "MMC";
}

static void SD_Check(bool isInsert)
{
    // if(isInsert)
    // {
    //     bool ret = HAL::SD_Init();

    //     if(ret && SD_EventCallback)
    //     {
    //         SD_EventCallback(true);
    //     }

    //     HAL::Audio_PlayMusic(ret ? "DeviceInsert" : "Error");
    // }
    // else
    // {
    //     SD_IsReady = false;

    //     if(SD_EventCallback)
    //     {
    //         SD_EventCallback(false);
    //         SD_CardSize = 0;
    //     }

    //     HAL::Audio_PlayMusic("DevicePullout");
    // }
}

void SD_SetEventCallback(SD_CallbackFunction_t callback)
{
    SD_EventCallback = callback;
}

void SD_Update()
{
    // bool isInsert = (digitalRead(CONFIG_SD_CD_PIN) == LOW);

    // CM_VALUE_MONITOR(isInsert, SD_Check(isInsert));
}
