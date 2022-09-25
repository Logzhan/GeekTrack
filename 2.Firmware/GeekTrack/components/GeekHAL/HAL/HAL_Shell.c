#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include "HAL.h"
#include "esp_system.h"
#include "geek_shell_api.h"


void ShellSupport_Init(){
    printf("Init Shell Support.\n");
}

int SystemReboot(){
    esp_restart();
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)|
                 SHELL_CMD_PARAM_NUM(0), reboot, SystemReboot, reboot system);

int GetBateryInfo(){
    Power_Info_t info;
    memset(&info, 0, sizeof(Power_Info_t));
    Power_GetInfo(&info);
    printf("Battery voltage = %dmV\n", info.voltage);
    printf("Battery capacity = %d%%\n", info.capacity);
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)|
                 SHELL_CMD_PARAM_NUM(0), battery_info, GetBateryInfo, show battery info);


int PrintWifiConfig(){
    char StringBuff[64] = {0};
    size_t length = 64;
    uint8_t ret = Config_GetString("WIFI_NAME", StringBuff, 64);
    if(ret){
        printf("Config WIFI Name = %s\n", StringBuff);
    }
    ret = Config_GetString("WIFI_PWD", StringBuff, 64);
    if(ret){
        printf("Config WIFI Password = %s\n", StringBuff);
    }

    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)|
                 SHELL_CMD_PARAM_NUM(0), print_wifi_cfg, PrintWifiConfig, print wifi ssid and password);

int SetWifiConfigName(char* SSID, char* PWD){
    if(SSID == NULL || PWD == NULL){
        return 0;
    }
    Config_SetString("WIFI_NAME", SSID);
    Config_SetString("WIFI_PWD", PWD);
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)|
                 SHELL_CMD_PARAM_NUM(2), set_wifi_cfg, SetWifiConfigName, set wifi ssid and password);

int SetDevIndx(char* idx){
    Config_SetString("DEV_IDX", idx);
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)|
                 SHELL_CMD_PARAM_NUM(1), set_dev_idx, SetDevIndx, set device idx type);

int PrintDevIndex(){
    char StringBuff[64] = {0};
    uint8_t ret = Config_GetString("DEV_IDX", StringBuff, 64);
    if(ret){
        printf("Config device idx = %s \n", StringBuff);
    }else{
        printf("No config dev idx\n");
    }
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)|
                 SHELL_CMD_PARAM_NUM(0), print_dev_idx, PrintDevIndex, print GeekTrack device type);