#ifndef SOCKET_CONN
#define SOCKET_CONN

#include <WiFi.h>
#include "sensor_data.hpp"

extern WiFiClient wifiClient;

typedef enum {
	MSG_SENSOR_DATA_BASIC,
	MSG_SENSOR_DATA_PREMIUM,
} MessageType;

bool wifi_init(void);

void wifi_disconnect(void);

bool socket_connect(void);

void socket_disconnect(void);

bool socket_send_sensor_data(SensorData *);

#endif