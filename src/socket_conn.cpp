#include "socket_conn.hpp"
#include "sensor_data.hpp"
#include "config.hpp"

const uint8_t wifiRetryNum = 5;
const uint8_t socketRetryNum = 5;

WiFiClient client;

bool wifi_init(void)
{
	const char* ssid = wifiConfigList[0].ssid;
	const char* password = wifiConfigList[0].password;
	WiFi.begin(ssid, password);
	for (int i = 0; i < wifiRetryNum; ++i) {
		Serial.println(WiFi.status());
		if (WiFi.status() != WL_CONNECTED) {
			delay(1000);
			Serial.println("...");
			continue;
		}
		Serial.print("WiFi ");
		Serial.print(ssid);
		Serial.print(" connected with IP: ");
		Serial.println(WiFi.localIP());
		return true;
	}
	Serial.print("Failed to connect to WiFi ");
	Serial.println(ssid);
	return false;
}

bool socket_connect(void)
{
	const char* host = hostConfigList[0].host;
	uint16_t port = hostConfigList[0].port;
	for (int i = 0; i < socketRetryNum; ++i) {
		if (!client.connect(host, port)) {
			delay(1000);
			Serial.println("...");
			continue;
		}
		Serial.print("Connected to the host: ");
		Serial.print(host);
		Serial.print(":");
		Serial.println(port);
		return true;
	}
	Serial.print("Failed to connect to the host: ");
	Serial.print(host);
	Serial.print(":");
	Serial.println(port);
	return false;
}

void socket_disconnect(void)
{
	client.stop();
	Serial.println("Disconnected from the host");
}

void wifi_disconnect(void)
{
	if (client.connected()) {
		client.stop();
	}
	WiFi.disconnect();
	Serial.println("Disconnected from the WiFi");
}

String make_massage_header(void)
{
	
}

bool socket_send_sensor_data(SensorData* sensorData)
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