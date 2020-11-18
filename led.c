#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h> 
#include <stdio.h>
#include <string.h>
#include "led.h"

void led_init() {
    DDRB |= (1 << PB3); //digital pin 11 OC2A, BLUE
    DDRD |= (1 << PD6);//digital pin 6,OC0A RED
}

void TOGGLE_blue_led()
{
    PORTB ^= (1 << PB3);
}
void TOGGLE_red_led()
{
    PORTD ^= (1 << PD6);
}

