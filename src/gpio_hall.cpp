#include <Arduino.h>
// #include "main.h"
#include "gpio_hall.h"

void my_hall_init()
{
	// pinMode(PIN_GPIO_HALL_SENSOR, INPUT_PULLDOWN);
	pinMode(15, INPUT_PULLDOWN);
}

bool my_hall_getData()
{
	// if (digitalRead(PIN_GPIO_HALL_SENSOR) == HIGH) {
	if (digitalRead(15) == HIGH) {
		return true;
	} else {
		return false;
	}
}

void my_hall_interrupt_init()
{
}

void my_hall_isr()
{
}
