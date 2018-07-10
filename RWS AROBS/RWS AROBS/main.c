/*
 * RWS AROBS.c
 *
 * Created: 7/10/2018 6:36:57 AM
 * Author : bruno.sebesi
 */ 

#include <avr/io.h>
#define SETPORTB(PIN) PORTB|=(1<<(PIN))
#define CLEARPORTB(PIN) PORTB &=~ (1<<(PIN))

typedef enum{
	APort = 0,
	BPort,
	CPort,
	DPort,
	EPort,
	FPort } EN_Port_Type;
	

void CONTROLPIN(unsigned char pinNr, unsigned char pinState, EN_Port_Type Port2Control);

int main(void)
{
	DDRB = 0x06;
	SETPORTB(1);
	SETPORTB(2);
	CONTROLPIN(3,0,APort);
    /* Replace with your application code */
    while (1) 
		  
    {	  
		CLEARPORTB(1);
    }	  
}

void CONTROLPIN(unsigned char pinNr, unsigned char pinState, EN_Port_Type Port2Control)
{
	
}