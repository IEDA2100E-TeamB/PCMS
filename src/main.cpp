#include <Arduino.h>
// #include "socket_conn.hpp"
#include <WiFi.h>
#include "socket_conn.hpp"

bool connectSuccessful = false;

void setup()
{
	connectSuccessful = wifi_init();
}

void loop()
{
}
