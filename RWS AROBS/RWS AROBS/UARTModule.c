/*
 * UARTModule.c
 *
 * Created: 7/17/2018 9:59:30 PM
 *  Author: bruno.sebesi
 */ 


void UARTInit(uint16_t ubrr){
	UCSRA = (1<<U2X); // to increase precision use U2X
	UBRRH = (uint8_t)(ubrr>>8);
	UBRRL = (uint8_t)(ubrr);
	UCSRB = (1<<TXEN)|(1<<RXEN)|(1<<RXCIE);
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}

void UARTSendChar(uint8_t uartMessage){
	UDR = uartMessage;
}



void UARTSendString(char* myString){
	while(*myString){
		UARTSendChar(*myString);
		myString++;
	}
}