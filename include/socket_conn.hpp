#ifndef SOCKET_CONN
#define SOCKET_CONN

#include <WiFi.h>
#include "sensor_data.hpp"
#include "config.hpp"

extern WiFiClient wifiClient;

typedef enum {
	MSG_SENSOR_DATA_BASIC,
	MSG_SENSOR_DATA_PREMIUM,
	MSG_ALARM,
} MessageType;

bool wifi_init(WiFiConfig &config);

bool wifi_retry(WiFiConfig &config);

bool is_wifi_connected(void);

void wifi_disconnect(void);

bool socket_connect(void);

void socket_disconnect(void);

bool socket_send_sensor_data(SensorData *);

bool socket_send_alarm_message(bool isAlarming);

#endif