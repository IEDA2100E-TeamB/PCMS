
#ifndef PCMS_GPS_GPRS
#define PCMS_GPS_GPRS

#include <ArduinoJSON.h>

void sendCommandToA9G(String command, int maxTime, const char readReplay[]);
void ShowSerialData();
void turnOff_A9G();
//GPS
void start_GPS();
void get_GPS_data();
//GPRS
void connect_mqqt_broker();
void send_JSON_data();
void check_new_threshold();

void turn_off_A9G();

#endif