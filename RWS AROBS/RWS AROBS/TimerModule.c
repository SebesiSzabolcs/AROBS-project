/*
 * TimerModule.c
 *
 * Created: 7/11/2018 9:31:36 PM
 *  Author: bruno.sebesi
 */ 
#include "TimerModule.h"
#include <avr/interrupt.h>
#include <avr/io.h>
volatile uint32_t GlobalMillTimer = 0;
void Timer0Init (void)
{
	TCCR0 = (1<<CS01)|(1<<CS00);
	TCNT0 = (16);
	TIMSK |= (1<<TOIE0);	
}
ISR(TIMER0_OVF_vect)
{
	GlobalMillTimer ++;
	TCNT0 = (16);
}