#include "socket_conn.hpp"
#include "wifi_config.hpp"

const uint8_t retryNum = 5;

bool wifi_init(void)
{
	Serial.begin(115200);
	WiFi.begin(ssid, password);
	for (int i = 0; i < retryNum; ++i) {
		if (WiFi.status() != WL_CONNECTED) {
			delay(500);
			Serial.println("...");
			continue;
		}
		Serial.print("WiFi connected with IP: ");
		Serial.println(WiFi.localIP());
		return true;
	}
    Serial.println("Failed to connect to WiFi");
    return false;
}

bool socket_connect(void)
{
	
}