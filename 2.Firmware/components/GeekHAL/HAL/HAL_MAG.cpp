#include "HAL.h"
#include <stdlib.h>
#include "Common/DataProc/DataProc.h"

static CommitFunc_t CommitFunc;
static void* UserData;

void MAG_SetCommitCallback(CommitFunc_t func, void* userData)
{
    CommitFunc = func;
    UserData = userData;
}

uint8_t MAG_Init()
{
    return 0;
}

void MAG_Update()
{
    MAG_Info_t mag;
    mag.x = rand() % 1000 - 500;
    mag.y = rand() % 1000 - 500;
    mag.z = rand() % 1000 - 500;

    if (CommitFunc)
    {
        CommitFunc(&mag, UserData);
    }
}
