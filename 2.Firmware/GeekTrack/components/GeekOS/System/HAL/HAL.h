/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __HAL_H
#define __HAL_H

#include <stddef.h>
#include <stdint.h>
#include "HAL_Def.h"

#ifdef __cplusplus
extern "C" {
#endif
    
typedef bool (*CommitFunc_t)(void* info, void* userData);
    
void HAL_Update(uint32_t tick);
void HAL_Init();

/* Shell */
void ShellSupport_Init(void);

/* Backlight */
void Backlight_Init();
uint16_t Backlight_GetValue();
void Backlight_SetValue(int16_t val);
// void Backlight_SetGradual(uint16_t target, uint16_t time = 500);
void Backlight_ForceLit(bool en);

/* Display */
void Display_Init();
void Display_DumpCrashInfo(const char* info);
void Display_SetAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void Display_SendPixels(const uint16_t* pixels, uint32_t len);
    
typedef void(*Display_CallbackFunc_t)(void);
void Display_SetSendFinishCallback(Display_CallbackFunc_t func);
    
/* FaultHandle */
void FaultHandle_Init();

/* I2C */
int I2C_Scan();

/* IMU */
uint8_t IMU_Init();
void IMU_SetCommitCallback(CommitFunc_t func, void* userData);
void IMU_Update();
    
/* MAG */
uint8_t MAG_Init();
void MAG_SetCommitCallback(CommitFunc_t func, void* userData);
void MAG_Update();

/* SD */
uint8_t  SD_Init();
void SD_Update();
uint8_t  SD_GetReady();
float SD_GetCardSizeMB();
const char* SD_GetCardName();
const char* SD_GetTypeName();
typedef void(*SD_CallbackFunction_t)(bool insert);
void SD_SetEventCallback(SD_CallbackFunction_t callback);

/* Power */
void Power_Init();
void Power_HandleTimeUpdate();
void Power_SetAutoLowPowerTimeout(uint16_t sec);
uint16_t Power_GetAutoLowPowerTimeout();
void Power_SetAutoLowPowerEnable(bool en);
void Power_Shutdown();
void Power_Update();
void Power_EventMonitor();
void Power_GetInfo(Power_Info_t* info);
typedef void(*Power_CallbackFunction_t)(void);
void Power_SetEventCallback(Power_CallbackFunction_t callback);

/* Clock */
void Clock_Init();
void Clock_GetInfo(Clock_Info_t* info);
void Clock_SetInfo(const Clock_Info_t* info);
const char* Clock_GetWeekString(uint8_t week);

/* GPS */
void GPS_Init();
void GPS_Update();
// bool GPS_GetInfo(GPS_Info_t* info);
// bool GPS_LocationIsValid();
double GPS_GetDistanceOffset(GPS_Info_t* info, double preLong, double preLat);

/* Buzzer */
void Buzz_init();
void Buzz_SetEnable(bool en);

/* Encoder */
void Encoder_Init();
void Encoder_Update();
int32_t Encoder_GetDiff();
uint8_t  Encoder_GetIsPush();
void Encoder_SetEnable(bool en);

/* Button */
void Button_Init();
void Button_Update();
void Button_GetInfo(Button_Info_t* info);
void Button_Update_Task();

/* Audio */
void Audio_Init();
void Audio_Update();
uint8_t  Audio_PlayMusic(const char* name);

/* Memory */
void Memory_DumpInfo();

/* Config */
void Config_Init();
uint8_t Config_GetString(const char* key, char* str, size_t* length);
void Config_SetInt();
void Config_GetInt();
uint8_t Config_SetString(const char* key, const char* str);

/* Network. */
void Network_Init();
void Network_UdpSendData();

#ifdef __cplusplus
}
#endif

#endif
