#include "LauncherModel.h"

using namespace Page;

void LauncherModel::Init() {
    account = new Account("SystemInfosModel", DataProc::Center(), 0, this);

    account->Subscribe("IMU");
}

void LauncherModel::Deinit() {
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

int16_t LauncherModel::GetUserStep() {
    IMU_Info_t imu;
    memset(&imu, 0, sizeof(IMU_Info_t));
    account->Pull("IMU", &imu, sizeof(imu));
    return imu.steps;
}


