#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void timer0_init(void)
{
	TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);/*set fast PWM mode with none-inverting mode*/
	TCCR0B |= (1 << CS00) | (1 << CS01);	//Sets prescaler to 64
}
void timer1_init(void) 
{
    TCNT1 = 62499;
    TCCR1B |= (1 << CS12);
	while ((TIFR1 & (1 << OCF1A)) == 0x00);
	TIFR1 = 0x01;
}
void timer2_init(void)
{
	TCCR2A |= (1 << WGM20) | (1 << WGM21) | (1 << COM2A1); //fast PWM none-inverting
	TCCR2B |= (1 << CS21) | (1<<CS20); //prescale 64
}
