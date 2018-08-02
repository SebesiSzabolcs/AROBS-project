/*
 * GccApplication1.c
 *
 * Created: 8/2/2018 7:15:47 AM
 * Author : bruno.sebesi
 */ 

#include <avr/io.h>
#define DDR_SPI DDRB
#define DD_MOSI (3)
#define DD_SCK (5)
#define DD_SS (2)
void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR = 0x44;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}

int main(void)
{
	
    /* Replace with your application code */
	SPI_MasterInit();
    while (1) 
    {
		SPI_MasterTransmit(0x55);
    }
}

