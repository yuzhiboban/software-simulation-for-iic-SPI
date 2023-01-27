#ifndef __UART_H
#define __UART_H	


#include "stm32f10x.h"
#include <stdio.h>

void usart_initfunction();
void UART_GPIO_Init(void);
void UART_Config(u32 bound);
void UART_NVIC_Init(void);
void UART_Init(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);


#endif
