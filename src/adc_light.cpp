#include "adc_light.h"

static uint32_t prevMillis = 0;
static constexpr uint32_t MEASURE_DELAY = 1000;

void my_light_print()
{
	uint32_t currMillis = millis();
	if (currMillis - prevMillis >= MEASURE_DELAY) {
		prevMillis = currMillis;
		int val;
		val = analogRead(4);
		Serial.println(val, DEC);
	}
}
