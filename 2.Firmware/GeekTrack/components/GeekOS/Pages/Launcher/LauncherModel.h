#ifndef __LAUNCHER_MODEL_H
#define __LAUNCHER_MODEL_H


#include "lvgl.h"
#include "Common/DataProc/DataProc.h"

namespace Page
{

class LauncherModel
{
public:
    void Init();
    void Deinit();
    int16_t GetUserStep();
private:
    Account* account;
};

}

#endif
