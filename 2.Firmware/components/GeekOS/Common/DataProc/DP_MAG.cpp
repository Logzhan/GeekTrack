#include "DataProc.h"
#include "HAL/HAL.h"

DATA_PROC_INIT_DEF(MAG)
{
    MAG_SetCommitCallback([](void* info, void* userData){
        Account* account = (Account*)userData;
        return account->Commit(info, sizeof(MAG_Info_t));
    }, account);
}
