//#include "uart.h"
#include "iic.h"
#include "at24c02.h"
#include"uart.h"
#include"delay.h"
int main(void)
{
	
	u16 ch;
	delay_config();
	// 串口初始化
	usart_initfunction();
	// I2C GPIO 初始化
	IIC_Init();
	
	printf("\r\n 这是一个I2C外设(AT24C02)读写测试例程 \r\n");
	delay_us(1000000);
	printf("\r\n 这是一个I2C外设(AT24C02)读写测试例程 \r\n");
	//测试 I2C 通讯是否正常
	IIC_SendOneByte(3,'m');
	delay_us(1000000);
	ch=IIC_ReadOneByte(3);
	printf("%c ", ch);
}
