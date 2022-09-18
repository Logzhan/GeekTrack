#include "DataProc.h"
#include "System/HAL/HAL.h"
#include "lvgl.h"

uint32_t DataProc::GetTick()
{
    return lv_tick_get();
}

uint32_t DataProc::GetTickElaps(uint32_t prevTick)
{
    return lv_tick_elaps(prevTick);
}

const char* DataProc::MakeTimeString(uint64_t ms, char* buf, uint16_t len)
{
    uint64_t ss = ms / 1000;
    uint64_t mm = ss / 60;
    uint32_t hh = (uint32_t)(mm / 60);

    lv_snprintf(
        buf, len,
        "%d:%02d:%02d",
        hh,
        (uint32_t)(mm % 60),
        (uint32_t)(ss % 60)
    );

    return buf;
}

// static bool Clock_Calibrate(Account* account, GPS_Info_t* gpsInfo)
// {
//     bool retval = false;
//     if(gpsInfo->isVaild)
//     {
//         Clock_Info_t clock;
//         if (account->Pull("TzConv", &clock, sizeof(clock)) == Account::RES_OK)
//         {
//             Clock_SetInfo(&clock);
//             retval = true;
//         }
//     }
//     return retval;
// }

// static int onEvent(Account* account, Account::EventParam_t* param)
// {
//     if (param->event == Account::EVENT_PUB_PUBLISH)
//     {
//         if (param->size == sizeof(GPS_Info_t))
//         {
//             if (Clock_Calibrate(account, (GPS_Info_t*)param->data_p))
//             {
//                 account->Unsubscribe("GPS");
//             }
//         }
        
//         return Account::RES_OK;
//     }

//     if (param->event != Account::EVENT_SUB_PULL)
//     {
//         return Account::RES_UNSUPPORTED_REQUEST;
//     }

//     if (param->size != sizeof(Clock_Info_t))
//     {
//         return Account::RES_SIZE_MISMATCH;
//     }

//     // Clock_Info_t* info = (Clock_Info_t*)param->data_p;
//     // Clock_GetInfo(info);

//     return Account::RES_OK;
// }

DATA_PROC_INIT_DEF(Clock)
{
    // account->Subscribe("TzConv");
    // account->Subscribe("GPS");
    // account->SetEventCallback(onEvent);
}
