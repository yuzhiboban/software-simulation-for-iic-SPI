#include <stm32f10x.h>

#ifndef __BSP_I2C_GPIO_H
#define __BSP_I2C_GPIO_H
 
#define EEPROM_I2C_WR	0		/* 写控制bit */
#define EEPROM_I2C_RD	1		/* 读控制bit */
 
 
/* 定义I2C总线连接的GPIO端口, 用户只需要修改下面4行代码即可任意改变SCL和SDA的引脚 */
#define EEPROM_GPIO_PORT_I2C	GPIOB			/* GPIO端口 */
#define EEPROM_RCC_I2C_PORT 	RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define EEPROM_I2C_SCL_PIN		GPIO_Pin_6			/* 连接到SCL时钟线的GPIO */
#define EEPROM_I2C_SDA_PIN		GPIO_Pin_7			/* 连接到SDA数据线的GPIO */
 
 
/* 定义读写SCL和SDA的宏，已增加代码的可移植性和可阅读性 */
/* SCL = 1 */
	#define EEPROM_I2C_SCL_1()  GPIO_SetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SCL_PIN)		
/* SCL = 0 */	
  #define EEPROM_I2C_SCL_0()  GPIO_ResetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SCL_PIN)		
/* SDA = 1 */
	#define EEPROM_I2C_SDA_1()  GPIO_SetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SDA_PIN)		
/* SDA = 0 */	
  #define EEPROM_I2C_SDA_0()  GPIO_ResetBits(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SDA_PIN)		
/* 读SDA口线状态 */	
	#define EEPROM_I2C_SDA_READ()  GPIO_ReadInputDataBit(EEPROM_GPIO_PORT_I2C, EEPROM_I2C_SDA_PIN)	
 
 
 
#endif 

void IIC_Init(void);
u16 IIC_ReadOneByte(u8 read_addr);
void IIC_SendOneByte(u8 write_addr,u8 write_data);
