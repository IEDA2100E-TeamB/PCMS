#include "socket_conn.hpp"
#include "sensor_data.hpp"
#include "config.hpp"

const uint8_t wifiRetryNum = 5;
const uint8_t socketRetryNum = 5;

WiFiClient client;

bool wifi_init(void)
{
	// TODO: currently hardcoded, needs change
	const char *ssid = wifiConfigList[0].ssid;
	const char *password = wifiConfigList[0].password;

	Serial.print("Connecting to WiFi-");
	Serial.println(ssid);
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	for (int i = 0; i < wifiRetryNum; ++i) {
		if (WiFi.status() != WL_CONNECTED) {
			delay(1000);
			Serial.print(".");
			continue;
		}
		Serial.println(WiFi.localIP());
		return true;
	}

	Serial.println("Failed");
	return false;
}

bool socket_connect(void)
{
	// TODO: currently hardcoded, needs change
	const char *host = hostConfigList[0].host;
	uint16_t port = hostConfigList[0].port;

	Serial.print("Connecting to host-");
	Serial.print(host);
	Serial.print(":");
	Serial.println(port);
	for (int i = 0; i < socketRetryNum; ++i) {
		if (!client.connect(host, port)) {
			delay(1000);
			Serial.print(".");
			continue;
		}
		Serial.println("Success!");
		return true;
	}
	Serial.println("Failed");
	return false;
}

void socket_disconnect(void)
{
	client.stop();
	Serial.println("Disconnected from host");
}

void wifi_disconnect(void)
{
	if (client.connected()) {
		client.stop();
	}
	WiFi.disconnect();
	Serial.println("Disconnected from WiFi");
}

bool socket_send_sensor_data(SensorData *sensorData)
{
	if (!client.connected()) {
		if (!socket_connect()) {
			return false;
		}
	}
	String json = sensorData->toJson();
	Serial.println(json);
	client.println(json);
	return true;
}