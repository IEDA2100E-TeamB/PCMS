#include <Arduino.h>
#include <Adafruit_BME280.h>
// #include "test_board.hpp"
#include "i2c_scanner.h"

// -------- DEFINES --------
// #define BME280_ADDR 0x76
// #define MPU6050_ADDR 0x68

// -------- VARIABLES --------
Adafruit_BME280 bme; // use I2C interface
Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();

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
	Serial.println(F("BME280 Sensor event test"));

	if (!bme.begin(BME280_ADDRESS_ALTERNATE)) {
		Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
		while (1)
			delay(10);
	}

	bme_temp->printSensorDetails();
	bme_pressure->printSensorDetails();
	bme_humidity->printSensorDetails();
}

void loop()
{
	// -------- TEST BOARD start --------
	// ledBlinkWithoutDelay();
	// -------- TEST BOARD end --------

	// put your main code here, to run repeatedly:
	sensors_event_t temp_event, pressure_event, humidity_event;
	bme_temp->getEvent(&temp_event);
	bme_pressure->getEvent(&pressure_event);
	bme_humidity->getEvent(&humidity_event);

	Serial.print(F("Temperature = "));
	Serial.print(temp_event.temperature);
	Serial.println(" *C");

	Serial.print(F("Humidity = "));
	Serial.print(humidity_event.relative_humidity);
	Serial.println(" %");

	Serial.print(F("Pressure = "));
	Serial.print(pressure_event.pressure);
	Serial.println(" hPa");

	Serial.println();
	delay(1000);
}
