#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "dht.h"

uint8_t I_RH, D_RH, I_Temp, D_Temp, CheckSum;

void set_brightness_red(uint8_t data)
{
	OCR2A = data;
}
void set_brightness_blue(uint8_t data)
{
	OCR0A = data;
}

int main(void)
{
	uint8_t brightness[4] = { 10,80,160,254};
	led_init();
	timer0_init();
	timer2_init();
    uart_init();
	while (1)
	{
		_delay_ms(2000); 
		Request();		
		Response();		
		I_RH = Receive_data();	/* store first eight bit in I_RH */
		D_RH = Receive_data();	/* store next eight bit in D_RH */
		I_Temp = Receive_data();	/* store next eight bit in I_Temp */
		D_Temp = Receive_data();	/* store next eight bit in D_Temp */
		CheckSum = Receive_data(); /* store next eight bit in CheckSum */
		int RH = I_RH + D_RH;
		int TEMP = I_Temp;

		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum) // check if correct measurement
		{
			printf("Error\r\n");
		}
		else
		{
			printf("Humidity = %d %%\n", RH);
			printf("Temperature = %d.%d C\n", I_Temp, D_Temp);

			if (RH >= 60)
			{
				for (int count = 0; count < 4; count++)
				{
					set_brightness_red(brightness[3]);
					_delay_ms(50);
					set_brightness_red(brightness[0]);
					_delay_ms(50);
					set_brightness_red(brightness[3]);
				}
			}

			else if (RH >= 53 && RH <= 59)
			{
				set_brightness_red(brightness[2]);
			}

			else if (RH >=44 && RH <= 52)
			{
				set_brightness_red(brightness[1]);
			}

			else if (RH <= 43)
			{
				for (int count = 0; count < 4; count++)
				{
					set_brightness_red(brightness[0]);
					_delay_ms(50);
					set_brightness_red(brightness[3]);
					_delay_ms(50);
					set_brightness_red(brightness[0]);
				}
			}

			if (TEMP >= 35)
			{
				for (int i = 0; i < 4; i++)
				{
					set_brightness_blue(brightness[3]);
					_delay_ms(50);
					set_brightness_blue(brightness[0]);
					_delay_ms(50);
					set_brightness_blue(brightness[3]);
				}
			}

			else if (TEMP >= 26 && TEMP <= 34)
			{
				set_brightness_blue(brightness[2]);
			}

			else if (TEMP >= 17 && TEMP <= 25)
			{
				set_brightness_blue(brightness[1]);
			}

			else if (TEMP <= 16)
			{
				for (int i = 0; i < 10; i++)
				{
					set_brightness_blue(brightness[0]);
					_delay_ms(50);
					set_brightness_blue(brightness[3]);
					_delay_ms(50);
					set_brightness_blue(brightness[0]);
				}
			}
		}
	}
    return 0;
}

