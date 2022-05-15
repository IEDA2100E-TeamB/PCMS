#ifndef MY_MAIN_H
#define MY_MAIN_H

#include <Arduino.h>
#include "threshold.hpp"
#include "sensor_data.hpp"

// ======== DEFINES ========
typedef enum {
	DISCONNECT,
	WAREHOUSE_WIFI_CONNECTING,
	WAREHOUSE_WIFI_CONNECTED,
	WAREHOUSE_WIFI_RETRY,
	TRUCK_WIFI_CONNECTING,
	TRUCK_WIFI_CONNECTED,
	TRUCK_WIFI_RETRY,
	A9G_CONNECTING,
	A9G_CONNECTED,
	A9G_RETRY,
} system_status;
#define DATA_BUFF_LENGTH 20
// ======== PIN USED ========
// debugging
static const uint8_t SERIAL0_RX = 3;
static const uint8_t SERIAL0_TX = 1;
// sensor
static const uint8_t SENSOR_VOLTAGE = 2;
static const uint8_t ADC_LIGHT_SENSOR = 4;
static const uint8_t DIN_HALL_SENSOR = 12;
static const uint8_t DOU_ACTIVE_BUZZER = 18;
static const uint8_t I2C_SDA = 21;
static const uint8_t I2C_SCL = 22;
// server communication
static const uint8_t SERIAL2_RX = 16;
static const uint8_t SERIAL2_TX = 17;

// ======== VARIABLES ========
// system status
system_status currentStatus = DISCONNECT;
system_status previousStatus = DISCONNECT;
// sensor
SensorData dataBuffer[DATA_BUFF_LENGTH];
uint8_t idx_currRead = 0;
uint8_t idx_currWrite = 0;
Threshold currThreshold{ -10, 50, 20, 90, 850, 1100, true, true };
static uint32_t bme280_prevMillis = 0;
static uint32_t bme280_currMillis = 0;
static uint32_t bme280_delay = 5000;
static uint32_t mpu6050_prevMillis = 0;
static uint32_t mpu6050_currMillis = 0;
static uint32_t mpu6050_delay = 5000;
static uint32_t hall_prevMillis = 0;
static uint32_t hall_currMillis = 0;
static uint32_t hall_delay = 5000;
static uint32_t light_prevMillis = 0;
static uint32_t light_currMillis = 0;
static uint32_t light_delay = 5000;
static uint32_t buzzer_prevMillis = 0;
static uint32_t buzzer_currMillis = 0;
static uint32_t buzzer_delay = 5000;
// gateway communication
static bool isWiFiInitSuccess = false;
static bool isSocketConnectSuccess = false;
static bool isTimeSyncSuccess = false;
// server communication
static bool A9G_state = false;

#endif
