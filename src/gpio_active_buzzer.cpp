#include "gpio_active_buzzer.h"

bool triggerAlarm = false;

static bool isAlarming = false;
static uint32_t startMillis = 0;
static constexpr uint32_t ALARM_DELAY = 5000;

void my_aBuzzer_init()
{
	pinMode(18, OUTPUT);
}

void my_aBuzzer_alarm()
{
	if (triggerAlarm) {
		if (isAlarming != true) {
			// trigger alarm
			isAlarming = true;
			startMillis = millis();
			digitalWrite(18, HIGH);
		} else {
			uint32_t currMillis = millis();
			if (currMillis - startMillis >= ALARM_DELAY) {
				// stop alarm
				isAlarming = false;
				digitalWrite(18, LOW);
			}
		}
	}
}
