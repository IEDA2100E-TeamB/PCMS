#ifndef UNIX_TIME
#define UNIX_TIME

#include <Arduino.h>

const uint8_t retrySyncNum = 100;   

bool sync_time(void);

unsigned long get_time(void);

#endif