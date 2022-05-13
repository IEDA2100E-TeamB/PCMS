#include "socket_conn.hpp"
#include "wifi_config.hpp"

const uint8_t wifiRetryNum = 5;
const uint8_t socketRetryNum = 5;

WiFiClient client;

bool wifi_init(void)
{
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
	client.stop();
	WiFi.disconnect();
	Serial.println("Disconnected from the WiFi");
}