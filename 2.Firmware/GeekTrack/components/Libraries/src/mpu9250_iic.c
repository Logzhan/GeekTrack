/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : mpu9250_iic.c
* Current Version    : V2.0  & EPS-IDF v4.3
* Author             : zhanli 719901725@qq.com.
* Date of Issued     : 2021.10.26 zhanli : Create
* Comments           : MPU9250 i2c驱动   
********************************************************************************/

#include "mpu9250_iic.h"
// ESP32 IO操作支持
#include "driver/gpio.h"
// 用于支持i2c延时函数
#include "esp32/rom/ets_sys.h"
#include "driver/i2c.h"
#include "mpu9250.h"
#include "esp_log.h"

static const char *TAG = "MPU9250_IIC";

#define MPU9250_SDA_PIN  32
#define MPU9250_SCL_PIN  33

#define I2C_MASTER_SCL_IO MPU9250_SCL_PIN       /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO MPU9250_SDA_PIN       /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM 1                        /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 100000               /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0             /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0             /*!< I2C master doesn't need buffer */

#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */


// MPU9250的IIC端口初始化
int MPU9250_I2CConfig(){

    int i2c_master_port = I2C_MASTER_NUM;
	i2c_config_t conf = {
		.mode          = I2C_MODE_MASTER,
		.sda_io_num    = I2C_MASTER_SDA_IO,        
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_io_num    = I2C_MASTER_SCL_IO,         
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
		.master.clk_speed = 100000,  
		.clk_flags = 0,          
	};
	/* Check IIC Param. */
 	esp_err_t ret = i2c_param_config(i2c_master_port, &conf);

	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "MPU9250 i2c param config failed. code: 0x%.2X", ret);
	}
	/* Install i2c drver. */
	ret = i2c_driver_install(i2c_master_port, I2C_MODE_MASTER, 0, 0, 0);

	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "MPU9250 i2c driver install failed. code: 0x%.2X", ret);
	}

	ESP_LOGI(TAG, "MPU9250 i2c driver install sucess.");

	return 0;
}

void MPU9250_WriteReg(unsigned char slave_addr,unsigned char reg_addr,unsigned char reg_data)
{
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, slave_addr, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, reg_addr, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, reg_data, ACK_CHECK_EN);
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 10/portTICK_PERIOD_MS);
	i2c_cmd_link_delete(cmd);
	if (ret == ESP_OK) {
		ESP_LOGI(TAG, "write dev:0x%.2X reg:0x%.2X data:0x%.2X\r\n", 
			slave_addr,reg_addr, reg_data);
	} else {
		ESP_LOGE(TAG, "IIC Write OneByte failed. code: 0x%.2X", ret);
	}
}

unsigned char MPU9250_ReadReg(unsigned char slave_addr,unsigned char reg_addr)
{
	unsigned char reg_data = 0;
 	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, slave_addr, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, reg_addr, ACK_CHECK_EN);
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, slave_addr | I2C_MASTER_READ, ACK_CHECK_EN);
	i2c_master_read_byte(cmd, &reg_data, I2C_MASTER_LAST_NACK );
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 10 / portTICK_PERIOD_MS);
	i2c_cmd_link_delete(cmd);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "IIC Read Byte failed. code: 0x%.2X", ret);
	}
	return reg_data;
}

void MPU9250_ReadRegs(uint8_t slave_addr,uint8_t reg_addr,
					uint8_t *data, uint8_t len)
{
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, slave_addr, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, reg_addr, ACK_CHECK_EN);
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, slave_addr | I2C_MASTER_READ, ACK_CHECK_EN);
	i2c_master_read(cmd, data, len, I2C_MASTER_LAST_NACK );
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 10/portTICK_PERIOD_MS);
	i2c_cmd_link_delete(cmd);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "IIC Read Bytes failed. code: 0x%.2X\r\n", ret);
	}
}








