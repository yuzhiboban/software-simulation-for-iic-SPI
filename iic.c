#include"iic.h"
//IIC总线 PB6:SCL  PB7:SDA
//软件模拟IIC时序可以使用任意两个GPIO口，即使单片机没有IIC功能，也是可以的.
extern void delay_us(__IO uint32_t nTime);
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_OD; //配置为开漏输出
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7);
}

//产生IIC开始信号
//产生IIC开始信号
void IIC_Start(void)
{
	EEPROM_I2C_SCL_1(); 
	EEPROM_I2C_SDA_1(); 
	delay_us(5); 
	EEPROM_I2C_SDA_0();
	delay_us(5); 
	EEPROM_I2C_SCL_0(); 
}
void IIC_Stop(void)
{
	EEPROM_I2C_SCL_0();
	EEPROM_I2C_SDA_0();
	delay_us(5);
	EEPROM_I2C_SCL_1(); 
	delay_us(5);
	EEPROM_I2C_SDA_1();
	delay_us(5);
}

//单片机对设备芯片的应答ACK信号:可以理解为单片机向从设备发送一位值为0的数据
void IIC_ACK(void)
{
	EEPROM_I2C_SCL_0();
	EEPROM_I2C_SDA_0(); //在SCL为0时准备好数据
	delay_us(5);
	EEPROM_I2C_SCL_1();  //SCL的上升沿发送一位数据
	delay_us(5);//在SCL高电平期间保持不变
	EEPROM_I2C_SCL_0();
}
 
//单片机对设备芯片的非应答NADCK信号：可以理解为单片机向从设备发送一位值为1的数据
void IIC_NACK(void)
{
	EEPROM_I2C_SCL_0();
	EEPROM_I2C_SDA_1();  //在SCL为0时准备好数据
	delay_us(5);
	EEPROM_I2C_SCL_0();   //SCL的上升沿发送一位数据
	delay_us(5); //在SCL高电平期间保持不变
	EEPROM_I2C_SCL_0(); 
}
 
//单片机等待接收设备芯片的应答:相当于从设备向单片机发送一位数据
u8 IIC_WaitACK(void)
{
	EEPROM_I2C_SCL_0(); 
	EEPROM_I2C_SDA_1();  //此处是为了让单片机处于高阻态，以便于单片机能读取SDA线上的电平。
                //但是会发现不设置成高阻态程序也能正常运行，原因是即使IIC_SDA=0时单片机不能 
                //读取到外部电平，此时单片机被MOS管拉低，读到的值会总是为0，单片机会误认为是从机 
                //发送的应答信号，因此程序也会正常运行。
	delay_us(5);
	EEPROM_I2C_SCL_1(); 
	delay_us(5); //以上是为了提供给从机一个上升沿时钟信号，从机就会主动发送一位数据
	if(EEPROM_I2C_SDA_READ()==1) //下面判断从机发送过来的是1还是0，也就是判断从机发送的是不应答还是应答信号
	{
		IIC_Stop(); //如果从机发送过来的是不应答就停止传输数据
		return 1;
	}
	else
	{
		EEPROM_I2C_SCL_0(); 
		return 0; //如果从机发送过来的是应答信号就继续传输数据
	}
}

//发送一个字节数据:相当于把8位数据一位一位发送过去
//此函数被用来发送设备芯片地址、数据在设备芯片中的存储地址、以及要发送的8位数据
void IIC_SendByte(u8 txd)
{
	u8 i;
	EEPROM_I2C_SCL_0(); 
	for(i=0;i<8;i++) //先传送高位，再传送低位
	{
		if(txd&0x80) EEPROM_I2C_SDA_1();
    else EEPROM_I2C_SDA_0();
    txd<<=1;
		delay_us(5);
		EEPROM_I2C_SCL_1(); 
		delay_us(5);
		EEPROM_I2C_SCL_0(); 
	}
}

//读取一个字节数据：从设备会在主设备每发送一个时钟上升沿时向主设备发送一位数据
u8 IIC_ReadByte(void)
{
	u8 i;
	u8 receive=0;
	for(i=0;i<8;i++)
	{
		EEPROM_I2C_SCL_0(); 
		delay_us(5);
		EEPROM_I2C_SDA_1();
		EEPROM_I2C_SCL_1(); 
		receive<<=1;
		if(EEPROM_I2C_SDA_READ()==1) receive++;
	}		
	return receive;
}

//模拟完整发送一个字节数据时序
void IIC_SendOneByte(u8 write_addr,u8 write_data)
{
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitACK();
	IIC_SendByte(write_addr);
	IIC_WaitACK();
	IIC_SendByte(write_data);
	IIC_WaitACK();
	IIC_Stop();
  delay_us(5);
}

//模拟完整读取一个数据时序
u16 IIC_ReadOneByte(u8 read_addr)
{
	u8 temp;
	IIC_Start();
  IIC_SendByte(0xA0);
	IIC_WaitACK();
	IIC_SendByte(read_addr);
	IIC_WaitACK();
	IIC_Start();
	IIC_SendByte(0xA1);
	IIC_WaitACK();
	temp=IIC_ReadByte();
	IIC_NACK();
	IIC_Stop();
	return temp;
}
