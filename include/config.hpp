#ifndef CONFIG
#define CONFIG

#include <Arduino.h>
#include "sensor_data.hpp"

// array sizes
const uint8_t hostConfigListSize = 10;
const uint8_t ntpServerListSize = 3;
const uint8_t sensorDataRingBufferSize = 50;

extern const char *parcelID;

struct WiFiConfig {
	const char *ssid;
	const char *password;
};

struct HostConfig {
	const char *host;
	uint16_t port;
};

extern WiFiConfig warehouseWiFiConfig;
extern WiFiConfig truckWiFiConfig;
extern HostConfig hostConfigList[hostConfigListSize];
extern SensorData sensorDataRingBuffer[sensorDataRingBufferSize];
extern const char *ntpServerList[3];

#endif

/*
Copy the following content and create config.cpp to initialize 
WiFi and host configuration lists:

#include "config.hpp"

const char * parcelID = "<unique parcel ID>";

WiFiConfig wifiConfigList[wifiConfigListSize] = {
    WiFiConfig{"<ssid>", "<password>"},
};

HostConfig hostConfigList[hostConfigListSize] = {
    HostConfig{"<host IP>", <port>},
};

const char * ntpServerList[ntpServerListSize] = {
    "0.hk.pool.ntp.org",
    "1.hk.pool.ntp.org",
    "2.hk.pool.ntp.org",
};

*/