#include "socket_conn.hpp"
#include "sensor_data.hpp"
#include "unix_time.hpp"

const uint8_t wifiRetryNum = 5;
const uint8_t socketRetryNum = 5;

WiFiClient client;

bool wifi_init(WiFiConfig &config)
{
	// TODO: currently hardcoded, needs change
	const char *ssid = config.ssid;
	const char *password = config.password;

	Serial.print("Connecting to WiFi: ");
	Serial.print(ssid);
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

bool wifi_retry(WiFiConfig &config)
{
	for (int i = 0; i < wifiRetryNum; ++i) {
		if (wifi_init(config)) {
			return true;
		}
		delay(1000);
	}
	return false;
}

bool is_wifi_connected(void)
{
	return WiFi.status() == WL_CONNECTED;
}

bool socket_connect(void)
{
	// TODO: currently hardcoded, needs change
	const char *host = hostConfigList[0].host;
	uint16_t port = hostConfigList[0].port;

	Serial.print("Connecting to host: ");
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
	String json = "{";
	json += "\"parcel_id\":\"" + String(parcelID) + "\",";
	json += "\"message_type\":" + String(MSG_SENSOR_DATA_BASIC) + ",";
	json += "\"timestamp\":" + String(get_time()) + ",";
	json += "\"body\":";
	json += sensorData->to_json();
	json += "}";
	Serial.println(json);
	client.println(json);
	return true;
}

bool socket_send_alarm_message(bool isAlarming)
{
	if (!client.connected()) {
		if (!socket_connect()) {
			return false;
		}
	}
	String json = "{";
	json += "\"parcel_id\":\"" + String(parcelID) + "\",";
	json += "\"message_type\":" + String(MSG_ALARM) + ",";
	json += "\"timestamp\":" + String(get_time()) + ",";
	json += "\"body\":";
	json += "{\"is_alarming\":" + String(isAlarming) + "}";
	json += "}";
	Serial.println(json);
	client.println(json);
	return true;
}