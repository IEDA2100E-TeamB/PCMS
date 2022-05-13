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
	if (!isSocketConnectSuccess)
	{
		return;
	}

	SensorData sensorData(1.1, 1.1, 1.1, 1.1, 1.1, 1.1, String("test"), String(get_time()));
	socket_send_sensor_data(&sensorData);
	delay(10000);
}
