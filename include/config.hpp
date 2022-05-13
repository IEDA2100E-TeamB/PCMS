#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

const uint8_t wifiConfigListSize = 10;
const uint8_t hostConfigListSize = 10;

struct WiFiConfig {
	const char *ssid;
	const char *password;
};

struct HostConfig {
	const char *host;
	uint16_t port;
};

extern WiFiConfig wifiConfigList[wifiConfigListSize];
extern HostConfig hostConfigList[hostConfigListSize];

#endif

/*
Copy the following content and create config.cpp to initialize 
WiFi and host configuration lists:

#include "config.hpp"

WiFiConfig wifiConfigList[wifiConfigListSize] = {
    WiFiConfig{"<ssid>", "<password>"},
};

HostConfig hostConfigList[hostConfigListSize] = {
    HostConfig{"<host IP>", <port>},
};

*/