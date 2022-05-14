#include "gpio_hall.h"

void my_hall_init()
{
	pinMode(12, INPUT_PULLDOWN);
}

bool my_hall_getData()
{
	if (digitalRead(12) == HIGH) {
		return true;
	} else {
		return false;
	}
}

void my_hall_interrupt_init(){

}

void my_hall_interrupt()
{
}