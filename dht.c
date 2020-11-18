#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>
#include "dht.h"
#define DHT11_PIN		PORTB0
uint8_t c = 0;

void Request() //start pulse/request
{
	DDRB |= (1 << DHT11_PIN);
	PORTB &= ~(1 << DHT11_PIN);	//set to low
	_delay_ms(20);	 //minimum 18ms
	PORTB |= (1 << DHT11_PIN); //set to high
	_delay_us(40);
	DDRB &= ~(1 << DHT11_PIN);
}

int Response()		//receive respons
{
	if (!(PINB & (1 << DHT11_PIN)))
		_delay_us(85); //min 80us
	else
		return 1;
	if ((PINB & (1 << DHT11_PIN)))
		_delay_us(85); //min 80us
	else
	return 1;
}

uint8_t Receive_data() //receive DHT-11 data
{
	for (int i = 0; i < 8; i++)
	{
		while ((PINB & (1 << DHT11_PIN)) == 0);  //check received bit
		_delay_us(30);
		if (PINB & (1 << DHT11_PIN)) //high pulse greater then 30, logic = high
			c = (c << 1) | (0x01);	
		else			//logic low
			c = (c << 1);
		while (PINB & (1 << DHT11_PIN));
	}
	return c;
}