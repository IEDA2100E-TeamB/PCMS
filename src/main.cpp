#include <Arduino.h>
#include "test_board.hpp"

void setup()
{
	// put your setup code here, to run once:
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
	Serial.println("serial setup done!");
	printASCII();
}

void loop()
{
	// put your main code here, to run repeatedly:
	ledBlinkWithoutDelay();
}
