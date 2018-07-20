/*
 * RWS AROBS.c
 *
 * Created: 7/10/2018 6:36:57 AM
 * Author : bruno.sebesi
 */ 
#define F_CPU 4000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include "TimerModule.h"
#include "UARTModule.h"
#define SETPORTB(PIN) PORTB|=(1<<(PIN))
#define CLEARPORTB(PIN) PORTB &=~ (1<<(PIN))
#define SETPORTC(PIN) PORTC|=(1<<(PIN))
#define CLEARPORTC(PIN) PORTC &=~(1<<PIN)
#define BAUD (38400)
#define MyUBBR ((F_CPU/(8*BAUD))-1)
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
	DDRC = 0xFF;
	PORTC = 0x10;
	DDRB |= 0x18;
	ControlPin(BPort,3,0);
	ControlPin(BPort,4,0);
	UARTSendString("ARDUINO");
	UartSendUdec(GlobalMillTimer);
	UartSendNewLine();
    /* Replace with your application code */
    while (1) 
    {
	
		if ((GlobalMillTimer % 1000) == 0) 
		{
			
			pinstate^=1;
			if (pinstate) {
				//ControlPin(CPort,5,true);
			}
			else {
				//ControlPin(CPort,5,false);
			}
			UARTSendChar(PORTC + 0x30);
			UartSendNewLine();
			UartSendUdec(GlobalMillTimer);
			UartSendNewLine();
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