#include"uart.h"
int fputc(int ch,FILE  *f){
	USART_SendData(USART1,(uint8_t)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}
void usart_initfunction(){
		GPIO_InitTypeDef GPIO_InitStructure;//定义一个GPIO_InitTypeDef类型的结构体
		USART_InitTypeDef usart_tx;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE); //开启GPIOB的外设时钟和AFIO时钟
	
		GPIO_InitStructure.GPIO_Pin   =   GPIO_Pin_9;//选择要控制的GPIOB引脚
		GPIO_InitStructure.GPIO_Speed =   GPIO_Speed_50MHz;//设置引脚速率为50MHz
		GPIO_InitStructure.GPIO_Mode  =   GPIO_Mode_AF_PP;//设置引脚模式为通用推挽输出
		GPIO_Init(GPIOA, &GPIO_InitStructure); //调用库函数，初始化GPIOB
		
		GPIO_InitStructure.GPIO_Pin   =   GPIO_Pin_10;//选择要控制的GPIOB引脚
		GPIO_InitStructure.GPIO_Mode  =   GPIO_Mode_IN_FLOATING;//设置引脚模式为通用推挽输出
		GPIO_Init(GPIOA, &GPIO_InitStructure); //调用库函数，初始化GPIOB

		usart_tx.USART_BaudRate=115200;
		usart_tx.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		usart_tx.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
		usart_tx.USART_WordLength=USART_WordLength_8b;
		usart_tx.USART_Parity=USART_Parity_No;
		usart_tx.USART_StopBits=USART_StopBits_1;
		
		USART_Init(USART1,&usart_tx);
		
		USART_Cmd(USART1,ENABLE);
}
