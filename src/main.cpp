#include <Arduino.h>
#include "test_board.h"

// ======== INCLUDES ========
// ======== SENSOR SYSTEM ========
#include "i2c_scanner.h"
#include "i2c_bme280.h"
#include "i2c_mpu6050.h"
#include "adc_light.h"
#include "gpio_hall.h"
#include "gpio_active_buzzer.h"
// ======== GPS MODULE ========
#include "PCMS_GPS_GPRS.hpp"
// ======== GATEWAY ========
#include <WiFi.h>
#include "socket_conn.hpp"
#include "sensor_data.hpp"
#include "unix_time.hpp"

// ======== DEFINES ========
// please write down the pins used in ascending order:
#define ADC_LIGHT_SENSOR 4
#define DIN_HALL_SENSOR 12
#define DOU_ACTIVE_BUZZER 18
#define I2C_SDA 21
#define I2C_SCL 22

// ======== VARIABLES ========
bool A9G_state = false, disconnected_gateway = true;
String GPS_data = "";

bool isWiFiInitSuccess = false;
bool isSocketConnectSuccess = false;
bool isTimeSyncSuccess = false;

// ======== FUNCTION PROTOTYPES ========

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);
	Serial2.begin(115200);

	// ======== SENSOR SYSTEM ========
	// i2cScannerSetup();
	bme280_setup();
	mpu6050_setup();
	my_aBuzzer_init();

	// ======== GPS MODULE ========-
	sendCommandToA9G("AT", 5, "OK");

	// ======== GATEWAY ========
	isWiFiInitSuccess = wifi_init();
	if (!isWiFiInitSuccess) {
		return;
	}
	isTimeSyncSuccess = sync_time();
	if (!isTimeSyncSuccess) {
		return;
	}
	isSocketConnectSuccess = socket_connect();
}

void loop()
{
	// ======== TEST BOARD start ========
	// led_blinkWithoutDelay();
	// ======== TEST BOARD end ========

	// put your main code here, to run repeatedly:

	// ======== SENSOR SYSTEM ========
	// i2cScannerLoop();
	bme280_print();
	mpu6050_print();
	my_light_print();
	// my_aBuzzer_alarm();

	// ======== GPS MODULE ========--
	if (disconnected_gateway == true) {
		//when A9G off
		if (A9G_state == false) {
			//sendCommandToA9G("AT+SLEEP=0",3,"OK"); //wake A9G up
			//delay(2000);
			connect_mqqt_broker();
			start_GPS();
			A9G_state = true;
		}
		//when A9G is already operating
		else {
			get_GPS_data();

			//Serial.print("GPS DATA: ");
			// Serial.println(GPS_data);
			//ShowSerialData();
			Serial.println();
			send_JSON_data();

			delay(1000);
		}
	} else {
		if (A9G_state == true) {
			terminate_GPS();
			terminate_broker_connection();
			//sendCommandToA9G("AT+SLEEP=2",3,"OK"); //low power consumption mode
			A9G_state = false;
		}
		//send data to gateway device
	}
	Serial.println();
	delay(1000);
}
