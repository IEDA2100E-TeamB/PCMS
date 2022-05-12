#include <Arduino.h>
#include "socket_conn.hpp"

bool connectSuccessful = false;

void setup()
{
	connectSuccessful = wifi_init();
}

void loop()
{
	WiFiClient client;

	// if (!client.connect(host, port)) {
	// 	Serial.println("Connection to host failed");

	// 	delay(1000);
	// 	return;
	// }

	Serial.print("Time: ");
	unsigned long myTime = millis();

	Serial.println(myTime); // prints time since program started
	delay(1000);

	Serial.println("Connected to server successful!");

	client.print("Hello from ESP32!");

	Serial.println("Disconnecting...");
	client.stop();
}
