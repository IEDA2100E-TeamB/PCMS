#include "i2c_mpu6050.h"

#define MPU6050_ADDR 0x68

static Adafruit_MPU6050 mpu6050;
static Adafruit_Sensor *mpu6050A;
static Adafruit_Sensor *mpu6050G;
static Adafruit_Sensor *mpu6050T;
static uint32_t prevMillis = 0;
static constexpr uint32_t MEASURE_DELAY = 1000;

bool mpu6050_setup()
{
	if (!mpu6050.begin(MPU6050_ADDR, &Wire)) {
		Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
		// TODO generate software interupt
		// while (1)
		// 	;
		return false;
	}

	mpu6050A = mpu6050.getAccelerometerSensor();
	mpu6050G = mpu6050.getGyroSensor();
	mpu6050T = mpu6050.getTemperatureSensor();

	mpu6050A->printSensorDetails();
	mpu6050G->printSensorDetails();
	mpu6050T->printSensorDetails();

	return true;
}

sensors_vec_t mpu6050_getAcceleration()
{
	sensors_event_t eventAcceleration;
	mpu6050A->getEvent(&eventAcceleration);
	return eventAcceleration.acceleration;
}

float mpu6050_getAcceleration_x()
{
	sensors_event_t eventAcceleration;
	mpu6050A->getEvent(&eventAcceleration);
	return eventAcceleration.acceleration.x;
}
float mpu6050_getAcceleration_y()
{
	sensors_event_t eventAcceleration;
	mpu6050A->getEvent(&eventAcceleration);
	return eventAcceleration.acceleration.y;
}
float mpu6050_getAcceleration_z()
{
	sensors_event_t eventAcceleration;
	mpu6050A->getEvent(&eventAcceleration);
	return eventAcceleration.acceleration.z;
}

sensors_vec_t mpu6050_getGyro()
{
	sensors_event_t eventGyro;
	mpu6050G->getEvent(&eventGyro);
	return eventGyro.gyro;
}

float mpu6050_getGyro_x()
{
	sensors_event_t eventGyro;
	mpu6050G->getEvent(&eventGyro);
	return eventGyro.gyro.x;
}
float mpu6050_getGyro_y()
{
	sensors_event_t eventGyro;
	mpu6050G->getEvent(&eventGyro);
	return eventGyro.gyro.y;
}
float mpu6050_getGyro_z()
{
	sensors_event_t eventGyro;
	mpu6050G->getEvent(&eventGyro);
	return eventGyro.gyro.z;
}

float mpu6050_getTemperature()
{
	sensors_event_t eventTemperature;
	mpu6050T->getEvent(&eventTemperature);
	return eventTemperature.temperature;
}

void mpu6050_print()
{
	uint32_t currMillis = millis();
	if (currMillis - prevMillis >= MEASURE_DELAY) {
		sensors_event_t eventAcceleration;
		sensors_event_t eventGyro;
		sensors_event_t eventTemperature;
		mpu6050A->getEvent(&eventAcceleration);
		mpu6050G->getEvent(&eventGyro);
		mpu6050T->getEvent(&eventTemperature);

		Serial.print("Accel (m/s^2):\t X: ");
		Serial.print(eventAcceleration.acceleration.x);
		Serial.print("\t Y: ");
		Serial.print(eventAcceleration.acceleration.y);
		Serial.print("\t Z: ");
		Serial.print(eventAcceleration.acceleration.z);
		Serial.println();

		Serial.print("Gyro (rad/s):\t X: ");
		Serial.print(eventGyro.gyro.x);
		Serial.print("\t Y: ");
		Serial.print(eventGyro.gyro.y);
		Serial.print("\t Z: ");
		Serial.print(eventGyro.gyro.z);
		Serial.println();

		// not using this
		// Serial.print("Temperature (*C): ");
		// Serial.print(eventTemperature.temperature);
		// Serial.println();

		Serial.println();
		prevMillis = currMillis;
	}
}
