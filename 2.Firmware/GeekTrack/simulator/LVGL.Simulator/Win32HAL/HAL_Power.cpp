#include <stdlib.h>
#include <stdio.h>
#include "HAL\HAL.h"
#ifdef _WIN32
#  include <windows.h>
#endif


static Power_Info_t Power_Info;


void Power_Init(){
}


void Power_GetInfo(Power_Info_t* info)
{
    /* Current version not support charging detect. */
    info->isCharging = false;
    info->usage = Power_Info.capacity;
    info->voltage = Power_Info.voltage;
    info->capacity = Power_Info.capacity;
}

void Power_GetBatteryVoltage(){
    static uint16_t voltage = 3000;
    voltage += 100;
    if (voltage > 4300) {
        voltage = 3000;
    }
    Power_Info.voltage = voltage;
}


void Power_SetEventCallback(Power_CallbackFunction_t callback)
{

}

static void Power_CalBatteryCapacity(float vol){
    const int   precent[] = {100,   90,   80,  70,    60,   50,   40,   30,   20,  15,   10,   5,   0};
    const float voltage[] = {4.2f, 4.08f, 4.00f, 3.93f, 3.87f, 3.82f, 3.79f, 3.77f, 3.73f, 3.7f, 3.68f, 3.5f, 3.0f};

    int i = 0;
    int LEN = 13;
    for(i = 0; i < LEN; i++){
        if(vol >= voltage[i]){
            break;
        }
    }
    int offset = 0;
    // 对于非关键点的电压数据进行线性拟合
    if(i > 0 && i < LEN){
        float dv = vol - voltage[i];
        offset = (int)((dv / (voltage[i-1] - voltage[i]))*(precent[i-1] - precent[i]));
    }
    Power_Info.capacity = precent[i] + offset;
}

void Power_Update(){
    /* Get Battery voltage form adc. */
    Power_GetBatteryVoltage();
    /* Calculate battery capacity.   */
    Power_CalBatteryCapacity((Power_Info.voltage / 1000.0f));
}
