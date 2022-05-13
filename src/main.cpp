#include <Arduino.h>
#include <WiFi.h>
#include "socket_conn.hpp"
#include "sensor_data.hpp"

bool isWiFiInitSuccess = false;
bool isSocketConnectSuccess = false;

void setup()
{
	Serial.begin(115200);
	isWiFiInitSuccess = wifi_init();

	if (isWiFiInitSuccess) {
		isSocketConnectSuccess = socket_connect();
	}
}

void loop()
{
	if (isSocketConnectSuccess) {
		Serial.println("So far so good");
		delay(1000000);
	}
}
