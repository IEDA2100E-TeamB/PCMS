#include <Arduino.h>
#include "peripheral_bme280.h"
#include "test_board.h"
#include "i2c_scanner.h"

// -------- DEFINES --------
// please write down the pins used in ascending order:
#define I2C_SDA 21
#define I2C_SCL 22

// -------- VARIABLES --------

// -------- FUNCTION PROTOTYPES --------

void setup()
{
	// -------- TEST BOARD start --------
	// pinMode(LED_BUILTIN, OUTPUT);
	// Serial.begin(115200);
	// Serial.println("serial setup done!");
	// printASCII();
	// -------- TEST BOARD end --------

	// put your setup code here, to run once:
	// i2cScannerSetup();
	Serial.begin(115200);
	bme280_setup();
}

void loop()
{
	// -------- TEST BOARD start --------
	// led_blinkWithoutDelay();
	// -------- TEST BOARD end --------

	// put your main code here, to run repeatedly:
	// i2cScannerLoop();
	bme280_print();
}
