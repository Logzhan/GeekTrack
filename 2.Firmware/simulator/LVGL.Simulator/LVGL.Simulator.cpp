﻿/*
 * PROJECT:   LVGL ported to Windows Desktop
 * FILE:      LVGL.Windows.Desktop.cpp
 * PURPOSE:   Implementation for LVGL ported to Windows Desktop
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Windows.h>
#include <stdio.h>
#include <thread>
#include "resource.h"
#include "System/HAL/HAL.h"
#include "System/GeekOS.h"

#if _MSC_VER >= 1200
 // Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)
#endif

#include "lvgl.h"
#include "lv_drivers/win32drv/win32drv.h"
#include "lv_fs_if/lv_fs_if.h"


#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif

int main()
{
    lv_init();

    lv_fs_if_init();

    if (!lv_win32_init(
        GetModuleHandleW(NULL),
        SW_SHOW,
        240,
        135,
        LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_LVGL))))
    {
        return -1;
    }

    lv_win32_add_all_input_devices_to_group(NULL);

    HAL_Init();

    GeekOS_Init();

    /* LVGL GUI Main Loop. */
    while (!lv_win32_quit_signal)
    {
        lv_timer_handler();
        HAL_Update(lv_tick_get());
        Sleep(1);
    }
    GeekOS_Uninit();

    return 0;
}
