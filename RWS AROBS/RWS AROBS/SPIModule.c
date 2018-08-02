/*
 * SPIModule.c
 *
 * Created: 7/30/2018 9:52:49 PM
 *  Author: bruno.sebesi
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "SPIModule.h"

void SPIInit(void)
{
	DDRB |= (1<<5)|(1<<3)|(1<<2);

	//SPCR = 0;
	//SPSR = 0;
	//SPSR |= (1<<SPI2X);
	SPCR |= (1<<SPE)|(1<<MSTR)/*|(1<<CPOL)|(1<<CPHA)|(1<<SPR0)*/|(1<<SPR1);	
}
uint8_t SPISendByte(uint8_t SPISentMessage)
{
		
	SPDR = SPISentMessage;
	while(!(SPSR & (1<<SPIF))){}
	return SPDR;
}
uint8_t SPIRecieveByte(void)
{
	while(!(SPSR & (1<<SPIF))){}
	return SPDR;
}

