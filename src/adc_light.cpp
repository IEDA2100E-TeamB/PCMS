#include <Arduino.h>
// #include "main.h"
#include "adc_light.h"

// extern const uint8_t PIN_ADC_LIGHT_SENSOR;

static uint32_t prevMillis = 0;
static constexpr uint32_t MEASURE_DELAY = 1000;

void my_light_print()
{
	uint32_t currMillis = millis();
	if (currMillis - prevMillis >= MEASURE_DELAY) {
		prevMillis = currMillis;
		uint16_t val;
		// val = analogRead(PIN_ADC_LIGHT_SENSOR);
		val = analogRead(34);
		Serial.println(val, DEC);
	}
}

uint16_t my_light_getData()
{
	// return analogRead(PIN_ADC_LIGHT_SENSOR);
	return analogRead(34);
}

bool my_light_getOpened()
{
	if (my_light_getData() < 2500) {
		return true;
	} else {
		return false;
	}
}
