/*----------------------------------------------------------------------------/
/ MPU9250 IIC include file            
/----------------------------------------------------------------------------*/
#ifndef _DEF_MPU9250_IIC_H_
#define _DEF_MPU9250_IIC_H_
/*---------------------------------------------------------------------------*/

#include <stdint.h>

/* System Configurations */
int MPU9250_I2CConfig(void);

/**----------------------------------------------------------------------
* Function    : i2c_start
* Description : 产生IIC起始信号
* Author      : zhanli&719901725@qq.com
* Date        : 2021/10/26 zhanli
*---------------------------------------------------------------------**/
void i2c_start(void);

/**----------------------------------------------------------------------
* Function    : i2c_stop
* Description : 产生IIC停止信号
* Author      : zhanli&719901725@qq.com
* Date        : 2021/10/26 zhanli
*---------------------------------------------------------------------**/
void i2c_stop(void);

/**----------------------------------------------------------------------
* Function    : i2c_ack
* Description : 产生ACK应答
* Author      : zhanli&719901725@qq.com
* Date        : 2021/10/26 zhanli
*---------------------------------------------------------------------**/
void i2c_ack(void);

/**----------------------------------------------------------------------
* Function    : i2c_send_byte
* Description : IIC发送一个字节	  
* Author      : zhanli&719901725@qq.com
* Date        : 2021/10/26 zhanli
*---------------------------------------------------------------------**/  
void i2c_send_byte(unsigned char txd);

unsigned char i2c_read_byte(unsigned char ack);

unsigned char i2c_wait_ack();

// 往I2C设备写一个字节
void MPU9250_WriteReg(unsigned char slave_addr,unsigned char reg_addr,unsigned char reg_data);

/**----------------------------------------------------------------------
* Function    : i2c_read_one_byte
* Description : i2c读一个字节
* Author      : zhanli&719901725@qq.com
* Date        : 2021/10/26 zhanli
*---------------------------------------------------------------------**/ 
unsigned char MPU9250_ReadReg(unsigned char slave_addr,unsigned char reg_addr);

/**----------------------------------------------------------------------
* Function    : i2c_read_one_byte
* Description : i2c读多个字节
* Author      : zhanli&719901725@qq.com
* Date        : 2021/10/26 zhanli
*---------------------------------------------------------------------**/ 
void MPU9250_ReadRegs(uint8_t slave_addr,uint8_t reg_addr,
					uint8_t *data, uint8_t len);

#endif /* MPU9250 */
