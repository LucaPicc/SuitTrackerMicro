/*
*   USART
*   Author: Luca Piccinini
*/

#include <avr/io.h>
#include "./USART.h"

void USART_init(void)
{
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = ((1<<UCSZ00)|(1<<UCSZ01));
}

void USART_send( unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

unsigned char USART_receive(void)
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void USART_putstring(char* StringPtr)
{
	while(*StringPtr != 0x00)
	{	//Aca se chequea si no hay mas caracteres para enviar, esto se hace chequeando el caracter actual y viendo si es diferente de NULL
		USART_send(*StringPtr);//usando esta simple funcion se envia de a un caracter
		StringPtr++;
	} //se incrementa el puntero para leer el praximo caracter
}