/*
 * UARTModule.c
 *
 * Created: 7/17/2018 9:59:30 PM
 *  Author: bruno.sebesi
 */ 
#include <stdint.h>
#include "UARTModule.h"
#include <avr/io.h>
void UARTInit(uint16_t ubrr){
	UCSRA = 0x00; // turn everything off
	UCSRB = 0x00;
	UCSRC = 0x00;
	UCSRA = (1<<U2X); // to increase precision use U2X
	UBRRH = 0;//(uint8_t)(ubrr>>8);
	UBRRL = 12;//(uint8_t)(ubrr);
	UCSRB = (1<<TXEN)/*|(1<<RXEN)|(1<<RXCIE)*/;
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}

void UARTSendChar(uint8_t uartMessage){
	while (!(UCSRA & (1<<UDRE))){}
	UDR = uartMessage;
	
}



void UARTSendString(char* myString){
	while(*myString){
		UARTSendChar(*myString);
		myString++;
	}
}