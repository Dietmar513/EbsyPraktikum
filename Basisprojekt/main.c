#include <stdint.h>
#include <LPC177x_8x.h>
#include "delay.h"


//	LPC_GPIO0->SET = 0xAA00;


/*
int i = 0;

if (i == 0) {
	ledval << 1;
	if (ledval == 0x800) {
		i = 1;
	}
	else {}
else if (i == 1) {
	ledval >> 1;
	if (ledval == 0x000) {
		i = 0;
	}
}
}
*/

static uint32_t led1_value = 0x100;
static uint32_t led2_value = 0x1000;
static uint32_t led1_trigger = 0;
static uint32_t led2_trigger = 0;
static uint32_t led1_freq = 3;
static uint32_t led2_freq = 1;
static uint32_t tickcounter = 0;

void init(void) {
	LPC_GPIO0->DIR = 0xFFFFFFFF;
	LPC_GPIO0->CLR = 0xFFFFFFFF;
}

void blinkLED(int LEDmask) {
	LPC_GPIO0->SET = LEDmask;
	delayms(100);
	LPC_GPIO0->CLR = LEDmask;
	delayms(100);
}

void led1(void) {

	if (led1_trigger == 0) {
		led1_value << 1;
		if (led1_value == 0x800) {
			led1_trigger = 1;
		}
		else 
		{
			//purposely left empty
		}
	else if (led1_trigger == 1) {
		led1_value >> 1;
		if (led1_value == 0x100) {
			led1_trigger = 0;
		}
	}
	}
}


}

void led2(void) {

	if (led2_trigger == 0)
	{
		led2_value << 1;
		if (led2_value == 0x8000)
		{
			led2_trigger = 1;
		}
		else 
		{
			//purposely left empty
		}
	}
	else if (led2_trigger == 1) 
	{
		led2_value >> 1;
		if (led2_value == 0x1000) 
		{
			led2_trigger = 0;
		}
	}
}

int main(void)
{
	init();
	while (1)
	{
		if (led1_freq > led2_freq)
		{

			if (tickcounter % led1_freq == 0)
			{
				blinkLED(led1_value | led2_value);
				led1();
				led2();
			}
			else if (tickcounter % led2_freq == 0)
			{
				blinkLED(led2_value);
				led2();
			}
			tickcounter++;
		}
		else
		{
			if (tickcounter % led2_freq == 0)
			{
				blinkLED(led1_value | led2_value);
				led1();
				led2();
			}
			else if (tickcounter % led1_freq == 0)
			{
				blinkLED(led1_value);
				led1();
			}
			tickcounter++;
		}
	}
}


