#include <stdlib.h>
#include <stdio.h>
#include "HAL.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#ifdef WIN32
#  include <windows.h>
#endif

#define DEFAULT_VREF    1100        // Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   1           // Multisampling

// ADC的配置
static const adc1_channel_t   channel  = ADC1_CHANNEL_1;     // GPIO34 if ADC1, GPIO14 if ADC2
static const adc_bits_width_t width    = ADC_WIDTH_BIT_12;
static const adc_atten_t      atten    = ADC_ATTEN_DB_11;
static const adc_unit_t       unit     = ADC_UNIT_1;
static esp_adc_cal_characteristics_t adc_chars;
static Power_Info_t Power_Info;


void Power_Init(){
    // 配置ADC基本参数
    adc1_config_width(width);
    adc1_config_channel_atten(channel, atten);
    esp_adc_cal_characterize(unit, atten, width, DEFAULT_VREF, &adc_chars);

    /* Enable Power Pin. */
    gpio_pad_select_gpio(CONFIG_POWER_EN_PIN);
    gpio_set_direction((gpio_num_t)CONFIG_POWER_EN_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)CONFIG_POWER_EN_PIN, 1);

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
    uint32_t adc_reading = 0;
    // 多次采样求均值, 提升采样精度
    for (int i = 0; i < NO_OF_SAMPLES; i++) {
        adc_reading += adc1_get_raw((adc1_channel_t)channel);
    }
    adc_reading /= NO_OF_SAMPLES;
    // 从原始采样结果转换为mV
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, &adc_chars);
    // 转换为V
    Power_Info.voltage = (voltage) * 2;
}


void Power_SetEventCallback(Power_CallbackFunction_t callback)
{

}

static void Power_CalBatteryCapacity(float vol){
    const int   precent[] = {100,   90,   80,  70,    60,   50,   40,   30,   20,  15,   10,   5,   0};
    const float voltage[] = {4.2, 4.08, 4.00, 3.93, 3.87, 3.82, 3.79, 3.77, 3.73, 3.7, 3.68, 3.5, 3.0};

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
        offset = (dv / (voltage[i-1] - voltage[i]))*(precent[i-1] - precent[i]);
    }
    Power_Info.capacity = precent[i] + offset;
}

void Power_Update(){
    /* Get Battery voltage form adc. */
    Power_GetBatteryVoltage();
    /* Calculate battery capacity.   */
    Power_CalBatteryCapacity((Power_Info.voltage / 1000.0f));
}
