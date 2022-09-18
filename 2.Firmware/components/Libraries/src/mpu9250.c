/*----------------------------------------------------------------------------/
* Description  : MPU9250 diriver for esp32
/----------------------------------------------------------------------------*/
#include <math.h>
#include <stdio.h>
#include "mpu9250.h"
#include "mpu9250_iic.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "geek_shell_api.h"

#define MOUNT_POINT      "/sdcard"
static const char *TAG = "MPU9250";
float q0 = 1.0f; 
float q1 = 0.0f; 
float q2 = 0.0f; 
float q3 = 0.0f;
MPU mpu9250;
FILE* fp = NULL;

/**----------------------------------------------------------------------
* Function    : init_mpu9250
* Description : 初始化配置MPU9250
* Author      : zhanli&719901725@qq.com
* Date        : 2021/10/31 zhanli
*---------------------------------------------------------------------**/
void MPU9250_Init(){
	/* Initalze config mpu9250 i2c gpio. */
    MPU9250_I2CConfig();
	/* Quaternion initialzie. */
	Init_Quaternion();

	uint8_t id = 0;
	while(id != MPU9250_Device_ID)
	{
		id = MPU9250_ReadReg(MPU9250_I2C_ADDR, (MPU9250_WHO_AM_I));
		vTaskDelay(200 / portTICK_PERIOD_MS);
		ESP_LOGI(TAG, "read device id = 0x%x\r\n", id);
	}

    if(id == MPU9250_Device_ID)
	{  
        MPU9250_WriteReg(MPU9250_I2C_ADDR,MPU9250_PWR_MGMT_1,   0x00);			// 唤醒mpu9250
	    MPU9250_WriteReg(MPU9250_I2C_ADDR,MPU9250_CONFIG,       0x06);    	    // 低通滤波5hz				 
	    MPU9250_WriteReg(MPU9250_I2C_ADDR,MPU9250_GYRO_CONFIG,  0x18);			// 不自检，2000deg/s		  
	    MPU9250_WriteReg(MPU9250_I2C_ADDR,MPU9250_ACCEL_CONFIG, 0x00);			// (0x00 +-2g;)  ( 0x08 +-4g;)  (0x10 +-8g;)  (0x18 +-16g)
	    MPU9250_WriteReg(MPU9250_I2C_ADDR,MPU9250_INT_PIN_CFG,  0x02);
	    MPU9250_WriteReg(MPU9250_I2C_ADDR,MPU9250_USER_CTRL,    0x00);			//使能I2C 

		ESP_LOGI(TAG, "read device id sucess.\r\n");

    }else{
		ESP_LOGI(TAG, "read device id fail.0x%.2x\r\n", id);
	}
}

void MPU9250_GetRawData(int16_t *ax,int16_t *ay,int16_t *az,
                        int16_t *gx,int16_t *gy,int16_t *gz,int16_t *temp)
{
	uint8_t buf[20];
	MPU9250_ReadRegs(MPU9250_I2C_ADDR,MPU9250_ACCEL_XOUT_H,
				   buf, 14);
	// 加速度
	*ax = (buf[0] << 8) + buf[1];
	*ay = (buf[2] << 8) + buf[3];
	*az = (buf[4] << 8) + buf[5];
	// 温度
	*temp =(buf[6] <<8) + buf[7];
	// 陀螺仪
	*gx = (buf[8]  << 8) + buf[9];
	*gy = (buf[10] << 8) + buf[11];
	*gz = (buf[12] << 8) + buf[13];
}

void MPU9250_Update(){

	
}

void MPU9250_GetData(float* ax, float* ay, float* az,
					 float* gx, float* gy, float* gz, float* temp)
{
	/*获取加速度计和陀螺仪的数据*/
	MPU9250_GetRawData(&mpu9250.ax,&mpu9250.ay,&mpu9250.az,&mpu9250.gx,
	                   &mpu9250.gy,&mpu9250.gz,&mpu9250.temp);

	/*对加速度计和陀螺仪数据进行缩放以及进行坐标轴变换           */
	*gx = (float) (M_PI*(mpu9250.gx) * GYRO_SCALE / 180.00f);
	*gy = (float) (M_PI*(mpu9250.gy) * GYRO_SCALE / 180.00f);
	*gz = (float) (M_PI*(mpu9250.gz) * GYRO_SCALE / 180.00f);
	
    /* 获取原始的加速度计的数值并按照单位进行缩放*/	
	*ax = (float) (mpu9250.ax * ACC_SCALE); 
	*ay = (float) (mpu9250.ay * ACC_SCALE); 
	*az = (float) (mpu9250.az * ACC_SCALE); 

	*temp = 20.0f;

	AHRSUpdate(*gx, *gy, *gz, *ax, *ay, *az);
}

void MPU9250_GetEulerAngles(float* yaw,float* roll, float* pitch)
{
	mpu9250.pitch = asin((float)(-2.0f*(q3*q1 - q0*q2))); // * (180.0f / 3.141592f);							                                            */
    mpu9250.yaw   = atan2(q2*q1 + q0*q3,0.5f - q2*q2 - q3*q3); // * (180.0f /3.141592f);
    mpu9250.roll  = atan2(q2*q3 + q0*q1,0.5f - q2*q2 - q1*q1); //* (180.0f /3.141592f);

	mpu9250.yaw   = (180.0f / 3.141592f);
	mpu9250.roll  = (180.0f / 3.141592f);
	mpu9250.pitch = (180.0f / 3.141592f);

	*yaw   = mpu9250.yaw;   
	*roll  = mpu9250.roll;  
	*pitch = mpu9250.pitch; 
}

void AHRSUpdate(float gx, float gy, float gz, float ax, float ay, float az) 
{	
	float halfT = 0.5 * (10.0f / 1000.0f);
	float Kp = 2.0f;
	
   	float norm = 1.0 / sqrtf(ax*ax + ay*ay + az*az);	
	
	ax = ax * norm;
	ay = ay * norm;
	az = az * norm;																	 
       	                                                                      
	float vx = 2.0f*(q1*q3 - q0*q2);														 
	float vy = 2.0f*(q0*q1 + q2*q3);															 
	float vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;
	
	float ex = (ay*vz - az*vy);
	float ey = (az*vx - ax*vz);
	float ez = (ax*vy - ay*vx);
		                                                                        
   	if(ex != 0.0f && ey != 0.0f && ez != 0.0f){	
      	gx = gx + Kp * ex;
      	gy = gy + Kp * ey;
      	gz = gz + Kp * ez;
   	}

	float qw = (-q1*gx - q2*gy - q3*gz) * halfT;
	float qx = ( q0*gx + q2*gz - q3*gy) * halfT;
	float qy = ( q0*gy - q1*gz + q3*gx) * halfT;	
	float qz = ( q0*gz + q1*gy - q2*gx) * halfT; 

	q0 = q0 + qw;
   	q1 = q1 + qx;
   	q2 = q2 + qy;
   	q3 = q3 + qz;  

   	norm = 1.0 / sqrtf(q0*q0 + q1*q1 + q2*q2 + q3*q3);	

   	q0 = q0 * norm;       //w
   	q1 = q1 * norm;       //x
   	q2 = q2 * norm;       //y
   	q3 = q3 * norm;       //z																
}

void Init_Quaternion(){
	mpu9250.q[0] = 1.0f;
	mpu9250.q[1] = 0.0f;
	mpu9250.q[2] = 0.0f;
	mpu9250.q[3] = 0.0f;
}
