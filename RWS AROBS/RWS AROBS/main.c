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
	
	sei();
//	DDRB = 0x02;
	DDRC = 0x3F;
	
    /* Replace with your application code */
    while (1) 
		  
    {	
		if ((GlobalMillTimer % 1000) == 0) 
		{
			ControlPin(CPort,1,pinstate);
			pinstate^=1;
		}  
/*
		ControlPin(BPort,1,pinstate);
		ControlPin(CPort,4,pinstate);
		_delay_ms(1000);
		pinstate^=1;*/
	#if 0
	for (i=0; i<=5; i++)
	{
		ControlPin(CPort,i,pinstate);
		_delay_ms(1000);
	}
		pinstate^=1;
    }	  
	#endif
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