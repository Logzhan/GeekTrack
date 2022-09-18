#include "HAL\HAL.h"
#include <stdlib.h>
#include "Common/DataProc/DataProc.h"
#include <stdio.h>

static CommitFunc_t CommitFunc;
static void* UserData;

void IMU_SetCommitCallback(CommitFunc_t func, void* userData)
{
    CommitFunc = func;
    UserData = userData;
}

uint8_t IMU_Init()
{
    return 0;
}

void IMU_Update()
{

    static uint16_t steps = 0;

    steps++;
    if (steps > 9999)
    {
        steps = 0;
    }

    IMU_Info_t imu;


    imu.acc[0] = (rand() % 1000 - 500) / 500.0f;
    imu.acc[1] = (rand() % 1000 - 500) / 500.0f;
    imu.acc[2] = (rand() % 1000 - 500) / 500.0f;
    imu.gyr[0] = (rand() % 1000 - 500) / 500.0f;
    imu.gyr[1] = (rand() % 1000 - 500) / 500.0f;
    imu.gyr[2] = (rand() % 1000 - 500) / 500.0f;
                                       
    
    imu.ax = (int16_t)(imu.acc[0] * 2000);
    imu.ay = (int16_t)(imu.acc[1] * 2000);
    imu.az = (int16_t)(imu.acc[2] * 2000);
    imu.gx = rand() % 1000 - 500;
    imu.gy = rand() % 1000 - 500;
    imu.gz = rand() % 1000 - 500;

    imu.steps = steps;

    if (CommitFunc)
    {
        CommitFunc(&imu, UserData);
    }
}

