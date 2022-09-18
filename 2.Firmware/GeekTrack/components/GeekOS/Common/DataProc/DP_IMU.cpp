#include "DataProc.h"
#include "HAL/HAL.h"

DATA_PROC_INIT_DEF(IMU)
{
    IMU_SetCommitCallback([](void* info, void* userData){
        Account* account = (Account*)userData;
        return account->Commit(info, sizeof(IMU_Info_t));
    }, account);
}
