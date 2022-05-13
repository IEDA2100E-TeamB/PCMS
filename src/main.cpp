#include <Arduino.h>
#include <WiFi.h>
#include "socket_conn.hpp"
#include "sensor_data.hpp"
#include "unix_time.hpp"

bool isWiFiInitSuccess = false;
bool isSocketConnectSuccess = false;
bool isTimeSyncSuccess = false;

void setup()
{
	Serial.begin(115200);
	isWiFiInitSuccess = wifi_init();
	if (!isWiFiInitSuccess) {
		return;
	}

	isTimeSyncSuccess = sync_time();
	if (!isTimeSyncSuccess) {
		return;
	}
	isSocketConnectSuccess = socket_connect();
}

void loop()
{
	if (isSocketConnectSuccess) {
		Serial.println("So far so good");
		delay(1000000);
	}
}
