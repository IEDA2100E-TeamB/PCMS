#include <time.h>
#include "unix_time.hpp"
#include "config.hpp"

unsigned long unixTime = 0;

bool sync_time(void)
{
	// use 3 ntp server addresses
	configTime(0, 0, ntpServerList[0], ntpServerList[1], ntpServerList[2]);
    Serial.print("Sync time");
    for (int i = 0; i < retrySyncNum; i++) {
        Serial.print(".");
        if (get_time() > 0) {
            Serial.println(get_time());
            return true;
        }
    }

    Serial.println("Failed");
    return false;
}

unsigned long get_time()
{
	time_t now;
	struct tm timeinfo;
	if (!getLocalTime(&timeinfo)) {
		//Serial.println("Failed to obtain time");
		return (0);
	}
	time(&now);
	return now;
}