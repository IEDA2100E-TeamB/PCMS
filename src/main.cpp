#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
// #include "test_board.hpp"
#include "i2c_scanner.h"

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

	// Serial.println(F("BME280 Sensor event test"));
	// if (!bme.begin(BME280_ADDRESS_ALTERNATE)) {
	// 	Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
	// 	while (1)
	// 		delay(10);
	// }

	// bme_temp->printSensorDetails();
	// bme_pressure->printSensorDetails();
	// bme_humidity->printSensorDetails();

	Serial.println("Adafruit MPU6050 test!");
	// Try to initialize!
	if (!mpu.begin()) {
		Serial.println("Failed to find MPU6050 chip");
		while (1) {
			delay(10);
		}
	}
	Serial.println("MPU6050 Found!");

	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
	Serial.print("Accelerometer range set to: ");
	switch (mpu.getAccelerometerRange()) {
	case MPU6050_RANGE_2_G:
		Serial.println("+-2G");
		break;
	case MPU6050_RANGE_4_G:
		Serial.println("+-4G");
		break;
	case MPU6050_RANGE_8_G:
		Serial.println("+-8G");
		break;
	case MPU6050_RANGE_16_G:
		Serial.println("+-16G");
		break;
	}
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);
	Serial.print("Gyro range set to: ");
	switch (mpu.getGyroRange()) {
	case MPU6050_RANGE_250_DEG:
		Serial.println("+- 250 deg/s");
		break;
	case MPU6050_RANGE_500_DEG:
		Serial.println("+- 500 deg/s");
		break;
	case MPU6050_RANGE_1000_DEG:
		Serial.println("+- 1000 deg/s");
		break;
	case MPU6050_RANGE_2000_DEG:
		Serial.println("+- 2000 deg/s");
		break;
	}

	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
	Serial.print("Filter bandwidth set to: ");
	switch (mpu.getFilterBandwidth()) {
	case MPU6050_BAND_260_HZ:
		Serial.println("260 Hz");
		break;
	case MPU6050_BAND_184_HZ:
		Serial.println("184 Hz");
		break;
	case MPU6050_BAND_94_HZ:
		Serial.println("94 Hz");
		break;
	case MPU6050_BAND_44_HZ:
		Serial.println("44 Hz");
		break;
	case MPU6050_BAND_21_HZ:
		Serial.println("21 Hz");
		break;
	case MPU6050_BAND_10_HZ:
		Serial.println("10 Hz");
		break;
	case MPU6050_BAND_5_HZ:
		Serial.println("5 Hz");
		break;
	}

	Serial.println("");
	delay(100);
}

void loop()
{
	// -------- TEST BOARD start --------
	// ledBlinkWithoutDelay();
	// -------- TEST BOARD end --------

	// put your main code here, to run repeatedly:
	// sensors_event_t temp_event, pressure_event, humidity_event;
	// bme_temp->getEvent(&temp_event);
	// bme_pressure->getEvent(&pressure_event);
	// bme_humidity->getEvent(&humidity_event);

	// Serial.print(F("Temperature = "));
	// Serial.print(temp_event.temperature);
	// Serial.println(" *C");

	// Serial.print(F("Humidity = "));
	// Serial.print(humidity_event.relative_humidity);
	// Serial.println(" %");

	// Serial.print(F("Pressure = "));
	// Serial.print(pressure_event.pressure);
	// Serial.println(" hPa");

	// Serial.println();
	// delay(5000);

	/* Get new sensor events with the readings */
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);

	/* Print out the values */
	Serial.print("Acceleration X: ");
	Serial.print(a.acceleration.x);
	Serial.print(", Y: ");
	Serial.print(a.acceleration.y);
	Serial.print(", Z: ");
	Serial.print(a.acceleration.z);
	Serial.println(" m/s^2");

	Serial.print("Rotation X: ");
	Serial.print(g.gyro.x);
	Serial.print(", Y: ");
	Serial.print(g.gyro.y);
	Serial.print(", Z: ");
	Serial.print(g.gyro.z);
	Serial.println(" rad/s");

	Serial.print("Temperature: ");
	Serial.print(temp.temperature);
	Serial.println(" degC");

	Serial.println("");
	delay(500);
}
