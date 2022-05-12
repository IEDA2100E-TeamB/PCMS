#ifndef SOCKET_CONN
#define SOCKET_CONN

#include <WiFi.h>

extern WiFiClient wifiClient;

bool wifi_init(void);

bool socket_connect(void);

void socket_disconnect(void);

#endif