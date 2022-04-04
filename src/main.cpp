#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
// #include "test_board.h"
// #include "i2c_scanner.h"

// -------- DEFINES --------
// #define BME280_ADDR 0x76
// #define MPU6050_ADDR 0x68

// -------- VARIABLES --------
// Adafruit_BME280 bme; // use I2C interface
// Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
// Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
// Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();
Adafruit_MPU6050 mpu;

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
	Serial.begin(115200);
}

void loop()
{
	// -------- TEST BOARD start --------
	// ledBlinkWithoutDelay();
	// -------- TEST BOARD end --------

	// put your main code here, to run repeatedly:
}
