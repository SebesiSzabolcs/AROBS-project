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
#include "SPIModule.h"
#define SETPORTB(PIN) PORTB|=(1<<(PIN))
#define CLEARPORTB(PIN) PORTB &=~ (1<<(PIN))
#define SETPORTC(PIN) PORTC|=(1<<(PIN))
#define CLEARPORTC(PIN) PORTC &=~(1<<PIN)
#define SETPORTD(PIN) PORTD|=(1<<(PIN))
#define CLEARPORTD(PIN) PORTD &=~(1<<PIN)
#define BAUD (38400)
#define MyUBBR ((F_CPU/(8*BAUD))-1)
#define ESP_RESET_PORT DPort
#define ESP_RESET_PIN (7)
#define ESP_ENABLE_PORT DPort
#define ESP_ENABLE_PIN (6)
#define STATUS_LED_PORT DPort
#define STATUS_LED_PIN (4)
extern volatile uint32_t GlobalMillTimer;
#define SPI_SS_PORT BPort
#define SPI_SS_PIN (0)
#define SPI_CLEAR_SS ControlPin(SPI_SS_PORT,SPI_SS_PIN, 0)
#define SPI_SET_SS ControlPin(SPI_SS_PORT,SPI_SS_PIN, 1)

typedef enum{
	APort = 0,
	BPort,
	CPort,
	DPort,
	EPort,
	FPort } EN_Port_Type;
	
void ControlPin(EN_Port_Type Port2Control, uint8_t pinNr, bool pinState);
static void PrintStatus(char* MyString, uint8_t Devider, uint32_t MyValue)
{
	UARTSendString(MyString);
	//UARTSendString(": ");
	
	if (Devider == 1)
	{
		UartSendUdec(MyValue);
	} 
	else 
	{
		UARTSendChar((uint8_t)MyValue);
	}
	UartSendNewLine();
}
void EspOff(void)
{
	DDRD |= 0XC0;
	ControlPin(ESP_RESET_PORT,ESP_RESET_PIN,0);
	ControlPin(ESP_ENABLE_PORT,ESP_ENABLE_PIN,0);	
}

int main(void)
{
	
	static char pinstate = true;
	volatile unsigned char i; 
	volatile unsigned char oldi = 0; //to check when the i variable change the value
	DDRD |= (1<< STATUS_LED_PIN);
	DDRB |= (1<< SPI_SS_PIN); //set PB0 to output because the SPI Slave select
	
	cli();
	Timer0Init();
	SPIInit();
	UARTInit(MyUBBR);
	sei();
	EspOff();	
	UartSendUdec(GlobalMillTimer);
	UartSendNewLine();
    /* Replace with your application code */
    while (1) 
    {
		SPI_CLEAR_SS;
		SPISendByte(0x55);
		_delay_ms(10);
		SPI_SET_SS;
#if 1
		if ((GlobalMillTimer % 1000) == 0) 
		{	
			pinstate^=1;
			if(pinstate){ControlPin(STATUS_LED_PORT,STATUS_LED_PIN,true);}
			else{ControlPin(STATUS_LED_PORT,STATUS_LED_PIN,false);}
			PrintStatus("Timer current value: ",1, GlobalMillTimer);
		}
#endif

#if 0
	i = UARTReceiveChar();
	
	if (oldi != i )
	{
		//PrintStatus("",0, i);
		UARTSendChar(i);
		if(i=='F')
		{
			ControlPin(CPort,5,true);
		}
		else if (i== 'G')
		{
			ControlPin(CPort,5,false);
		}

		oldi = i;
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
		case (DPort):
			if(pinState){
				SETPORTD(pinNr);
			}else{
				CLEARPORTD(pinNr);
			}
		break;
		default:
		break;
	
	}
}