#ifndef TEST_BOARD_H
#define TEST_BOARD_H

#include <Arduino.h>

void testSetup();
void testLoop();
void led_blink(void);
void led_blinkWithoutDelay(void);
void led_fade(void);
void led_dimmer(void);
void printASCII(void);

#endif