
#ifndef PCMS_GPS_GPRS
#define PCMS_GPS_GPRS

#include <ArduinoJSON.h>

void sendCommandToA9G(String command, int maxTime, const char readReplay[]);
void ShowSerialData();
void turnOff_A9G();
//GPS
void start_GPS();
void get_GPS_data();
void terminate_GPS();
//GPRS
void connect_mqqt_broker();
void send_JSON_data();
void terminate_broker_connection();

#endif