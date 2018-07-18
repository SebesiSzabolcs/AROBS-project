/*
 * RWS AROBS.c
 *
 * Created: 7/10/2018 6:36:57 AM
 * Author : bruno.sebesi
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include "TimerModule.h"
#define SETPORTB(PIN) PORTB|=(1<<(PIN))
#define CLEARPORTB(PIN) PORTB &=~ (1<<(PIN))
#define SETPORTC(PIN) PORTC|=(1<<(PIN))
#define CLEARPORTC(PIN) PORTC &=~(1<<PIN)
#define F_PROC (4000000)
#define BAUD (38400)
#define MyUBBR ((F_PROC/(8*BAUD)-1)
extern volatile uint32_t GlobalMillTimer;
typedef enum{
	APort = 0,
	BPort,
	CPort,
	DPort,
	EPort,
	FPort } EN_Port_Type;
	

void ControlPin(EN_Port_Type Port2Control, uint8_t pinNr, bool pinState);

int main(void)
{
	static bool pinstate = true;
	unsigned char i; 
	cli();
	Timer0Init();
	UARTInit(MyUBBR);
	sei();

	DDRC = 0x3F;
	
	UARTSendString("ARDUINO");
	
    /* Replace with your application code */
    while (1) 
		  
    {	
		if ((GlobalMillTimer % 1000) == 0) 
		{
			ControlPin(CPort,1,pinstate);
			pinstate^=1;
		}  
	
}
}
void ControlPin(EN_Port_Type Port2Control, uint8_t pinNr, bool pinState)
{
	static uint16_t counter = 0;
	counter++;
	switch(Port2Control) {
		case (BPort):
			if (pinState) {
				SETPORTB(pinNr);
			} else {
				CLEARPORTB(pinNr);
			}
		break;
		case(CPort):
			if(pinState){
				SETPORTC(pinNr);
			} else {
				CLEARPORTC(pinNr);	
			}
		break;
		default:
		break;
	}
}