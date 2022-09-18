/*----------------------------------------------------------------------------/
/ LED include file               (C)ChaN, 2019
/----------------------------------------------------------------------------*/
#ifndef _DEF_MPU9250_H_
#define _DEF_MPU9250_H_
/*---------------------------------------------------------------------------*/
/* System Configurations */
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//#define M_PI 3.14159265358979323846F	/*定义pi*/

#define GYRO_SCALE  0.06103515625
#define ACC_SCALE   0.00006103515625

/* ---- MPU9250 Reg In MPU9250 ---------------------------------------------- */

#define MPU9250_I2C_ADDR            ((unsigned char)0xD0)
#define  MPU9250_Device_ID          ((unsigned char)0x71)  // In MPU9250

#define MPU9250_SELF_TEST_XG        ((unsigned char)0x00)
#define MPU9250_SELF_TEST_YG        ((unsigned char)0x01)
#define MPU9250_SELF_TEST_ZG        ((unsigned char)0x02)
#define MPU9250_SELF_TEST_XA        ((unsigned char)0x0D)
#define MPU9250_SELF_TEST_YA        ((unsigned char)0x0E)
#define MPU9250_SELF_TEST_ZA        ((unsigned char)0x0F)
#define MPU9250_XG_OFFSET_H         ((unsigned char)0x13)
#define MPU9250_XG_OFFSET_L         ((unsigned char)0x14)
#define MPU9250_YG_OFFSET_H         ((unsigned char)0x15)
#define MPU9250_YG_OFFSET_L         ((unsigned char)0x16)
#define MPU9250_ZG_OFFSET_H         ((unsigned char)0x17)
#define MPU9250_ZG_OFFSET_L         ((unsigned char)0x18)
#define MPU9250_SMPLRT_DIV          ((unsigned char)0x19)
#define MPU9250_CONFIG              ((unsigned char)0x1A)
#define MPU9250_GYRO_CONFIG         ((unsigned char)0x1B)
#define MPU9250_ACCEL_CONFIG        ((unsigned char)0x1C)
#define MPU9250_ACCEL_CONFIG_2      ((unsigned char)0x1D)
#define MPU9250_LP_ACCEL_ODR        ((unsigned char)0x1E)
#define MPU9250_MOT_THR             ((unsigned char)0x1F)
#define MPU9250_FIFO_EN             ((unsigned char)0x23)
#define MPU9250_I2C_MST_CTRL        ((unsigned char)0x24)
#define MPU9250_I2C_SLV0_ADDR       ((unsigned char)0x25)
#define MPU9250_I2C_SLV0_REG        ((unsigned char)0x26)
#define MPU9250_I2C_SLV0_CTRL       ((unsigned char)0x27)
#define MPU9250_I2C_SLV1_ADDR       ((unsigned char)0x28)
#define MPU9250_I2C_SLV1_REG        ((unsigned char)0x29)
#define MPU9250_I2C_SLV1_CTRL       ((unsigned char)0x2A)
#define MPU9250_I2C_SLV2_ADDR       ((unsigned char)0x2B)
#define MPU9250_I2C_SLV2_REG        ((unsigned char)0x2C)
#define MPU9250_I2C_SLV2_CTRL       ((unsigned char)0x2D)
#define MPU9250_I2C_SLV3_ADDR       ((unsigned char)0x2E)
#define MPU9250_I2C_SLV3_REG        ((unsigned char)0x2F)
#define MPU9250_I2C_SLV3_CTRL       ((unsigned char)0x30)
#define MPU9250_I2C_SLV4_ADDR       ((unsigned char)0x31)
#define MPU9250_I2C_SLV4_REG        ((unsigned char)0x32)
#define MPU9250_I2C_SLV4_DO         ((unsigned char)0x33)
#define MPU9250_I2C_SLV4_CTRL       ((unsigned char)0x34)
#define MPU9250_I2C_SLV4_DI         ((unsigned char)0x35)
#define MPU9250_I2C_MST_STATUS      ((unsigned char)0x36)
#define MPU9250_INT_PIN_CFG         ((unsigned char)0x37)
#define MPU9250_INT_ENABLE          ((unsigned char)0x38)
#define MPU9250_INT_STATUS          ((unsigned char)0x3A)
#define MPU9250_ACCEL_XOUT_H        ((unsigned char)0x3B)
#define MPU9250_ACCEL_XOUT_L        ((unsigned char)0x3C)
#define MPU9250_ACCEL_YOUT_H        ((unsigned char)0x3D)
#define MPU9250_ACCEL_YOUT_L        ((unsigned char)0x3E)
#define MPU9250_ACCEL_ZOUT_H        ((unsigned char)0x3F)
#define MPU9250_ACCEL_ZOUT_L        ((unsigned char)0x40)
#define MPU9250_TEMP_OUT_H          ((unsigned char)0x41)
#define MPU9250_TEMP_OUT_L          ((unsigned char)0x42)
#define MPU9250_GYRO_XOUT_H         ((unsigned char)0x43)
#define MPU9250_GYRO_XOUT_L         ((unsigned char)0x44)
#define MPU9250_GYRO_YOUT_H         ((unsigned char)0x45)
#define MPU9250_GYRO_YOUT_L         ((unsigned char)0x46)
#define MPU9250_GYRO_ZOUT_H         ((unsigned char)0x47)
#define MPU9250_GYRO_ZOUT_L         ((unsigned char)0x48)
#define MPU9250_EXT_SENS_DATA_00    ((unsigned char)0x49)
#define MPU9250_EXT_SENS_DATA_01    ((unsigned char)0x4A)
#define MPU9250_EXT_SENS_DATA_02    ((unsigned char)0x4B)
#define MPU9250_EXT_SENS_DATA_03    ((unsigned char)0x4C)
#define MPU9250_EXT_SENS_DATA_04    ((unsigned char)0x4D)
#define MPU9250_EXT_SENS_DATA_05    ((unsigned char)0x4E)
#define MPU9250_EXT_SENS_DATA_06    ((unsigned char)0x4F)
#define MPU9250_EXT_SENS_DATA_07    ((unsigned char)0x50)
#define MPU9250_EXT_SENS_DATA_08    ((unsigned char)0x51)
#define MPU9250_EXT_SENS_DATA_09    ((unsigned char)0x52)
#define MPU9250_EXT_SENS_DATA_10    ((unsigned char)0x53)
#define MPU9250_EXT_SENS_DATA_11    ((unsigned char)0x54)
#define MPU9250_EXT_SENS_DATA_12    ((unsigned char)0x55)
#define MPU9250_EXT_SENS_DATA_13    ((unsigned char)0x56)
#define MPU9250_EXT_SENS_DATA_14    ((unsigned char)0x57)
#define MPU9250_EXT_SENS_DATA_15    ((unsigned char)0x58)
#define MPU9250_EXT_SENS_DATA_16    ((unsigned char)0x59)
#define MPU9250_EXT_SENS_DATA_17    ((unsigned char)0x5A)
#define MPU9250_EXT_SENS_DATA_18    ((unsigned char)0x5B)
#define MPU9250_EXT_SENS_DATA_19    ((unsigned char)0x5C)
#define MPU9250_EXT_SENS_DATA_20    ((unsigned char)0x5D)
#define MPU9250_EXT_SENS_DATA_21    ((unsigned char)0x5E)
#define MPU9250_EXT_SENS_DATA_22    ((unsigned char)0x5F)
#define MPU9250_EXT_SENS_DATA_23    ((unsigned char)0x60)
#define MPU9250_I2C_SLV0_DO         ((unsigned char)0x63)
#define MPU9250_I2C_SLV1_DO         ((unsigned char)0x64)
#define MPU9250_I2C_SLV2_DO         ((unsigned char)0x65)
#define MPU9250_I2C_SLV3_DO         ((unsigned char)0x66)
#define MPU9250_I2C_MST_DELAY_CTRL  ((unsigned char)0x67)
#define MPU9250_SIGNAL_PATH_RESET   ((unsigned char)0x68)
#define MPU9250_MOT_DETECT_CTRL     ((unsigned char)0x69)
#define MPU9250_USER_CTRL           ((unsigned char)0x6A)
#define MPU9250_PWR_MGMT_1          ((unsigned char)0x6B)
#define MPU9250_PWR_MGMT_2          ((unsigned char)0x6C)
#define MPU9250_FIFO_COUNTH         ((unsigned char)0x72)
#define MPU9250_FIFO_COUNTL         ((unsigned char)0x73)
#define MPU9250_FIFO_R_W            ((unsigned char)0x74)
#define MPU9250_WHO_AM_I            ((unsigned char)0x75)	// ID = 0x71 In MPU9250
#define MPU9250_XA_OFFSET_H         ((unsigned char)0x77)
#define MPU9250_XA_OFFSET_L         ((unsigned char)0x78)
#define MPU9250_YA_OFFSET_H         ((unsigned char)0x7A)
#define MPU9250_YA_OFFSET_L         ((unsigned char)0x7B)
#define MPU9250_ZA_OFFSET_H         ((unsigned char)0x7D)
#define MPU9250_ZA_OFFSET_L         ((unsigned char)0x7E)

/* ---- AK8963 Reg In MPU9250 ----------------------------------------------- */

#define AK8963_I2C_ADDR             ((unsigned char)0x18)
#define AK8963_Device_ID            ((unsigned char)0x48)

// Read-only Reg
#define AK8963_WIA                  ((unsigned char)0x00)
#define AK8963_INFO                 ((unsigned char)0x01)
#define AK8963_ST1                  ((unsigned char)0x02)
#define AK8963_ST1_DOR                   0x02
#define AK8963_ST1_DRDY                  0x01 //Data Ready
#define AK8963_HXL                  ((unsigned char)0x03)
#define AK8963_HXH                  ((unsigned char)0x04)
#define AK8963_HYL                  ((unsigned char)0x05)
#define AK8963_HYH                  ((unsigned char)0x06)
#define AK8963_HZL                  ((unsigned char)0x07)
#define AK8963_HZH                  ((unsigned char)0x08)
#define AK8963_ST2                  ((unsigned char)0x09)
#define AK8963_ST2_HOFL             ((unsigned char)0x08)
// Write/Read Reg
#define AK8963_CNTL1                ((unsigned char)0x0A)
#define AK8963_CNTL2                ((unsigned char)0x0B)
#define AK8963_ASTC                 ((unsigned char)0x0C)
#define AK8963_TS1                  ((unsigned char)0x0D)
#define AK8963_TS2                  ((unsigned char)0x0E)
#define AK8963_I2CDIS               ((unsigned char)0x0F)
// Read-only Reg ( ROM )
#define AK8963_ASAX                 ((unsigned char)0x10)
#define AK8963_ASAY                 ((unsigned char)0x11)
#define AK8963_ASAZ                 ((unsigned char)0x12)
typedef struct MPU
{
	int16_t ax;
	int16_t ay;
	int16_t az;
	int16_t temp;
	int16_t gx;
	int16_t gy;
	int16_t gz;
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
	float   acc[3];
	float   gyr[3];
	float   yaw;
	float   roll;
	float   pitch;
	float   q[4];
}MPU;

void MPU9250_Init(void);

void Init_Quaternion(void);

void MPU9250_GetData(float* ax, float* ay, float* az,
					 float* gx, float* gy, float* gz, 
					 float* temp);

void AHRSUpdate(float gx, float gy, float gz, 
				float ax, float ay, float az);

void MPU9250_GetEulerAngles(float* yaw,float* roll, float* pitch);


#ifdef __cplusplus
}
#endif

#endif /* MPU9250 */
