#include <Arduino.h>
#include "test_board.hpp"
#include "socket_conn.hpp"

void setup()
{
	Serial.begin(115200);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.println("...");
	}

	Serial.print("WiFi connected with IP: ");
	Serial.println(WiFi.localIP());
}

void loop()
{
	WiFiClient client;

	if (!client.connect(host, port)) {
		Serial.println("Connection to host failed");

		delay(1000);
		return;
	}

	Serial.println("Connected to server successful!");

	client.print("Hello from ESP32!");

	Serial.println("Disconnecting...");
	client.stop();
}
