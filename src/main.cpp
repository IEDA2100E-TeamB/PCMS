#include "main.h"
#include "test_board.h"

// ======== INCLUDES ========
// system
// #include "soc/soc.h"
// #include "soc/rtc_cntl_reg.h"
// sensor
#include "sensor_data.hpp"
#include "i2c_scanner.h"
#include "i2c_bme280.h"
#include "i2c_mpu6050.h"
#include "adc_light.h"
#include "gpio_hall.h"
#include "gpio_active_buzzer.h"
// gateway communication
#include <WiFi.h>
#include "socket_conn.hpp"
#include "unix_time.hpp"
// server communication
#include "PCMS_GPS_GPRS.hpp"

// ======== FUNCTION PROTOTYPES ========
void sensor_task(void *pvParameters);
void sensor_pollForStatus();
void gatewayCommunication_task(void *pvParameters);
void serverCommunication_task(void *pvParameters);

void setup()
{
	// put your setup code here, to run once:
	// for debugging
	Serial.begin(115200);

	// ======== system status init ========
	currentStatus = WAREHOUSE_WIFI_CONNECTING;
	currentStatus = WAREHOUSE_WIFI_CONNECTING;
	idx_currRead = 0;
	idx_currWrite = 0;
	currThreshold.update(-10, 50, 20, 90, 850, 1100, true, true);

	// ======== sensor voltage pin init ========
	pinMode(PIN_SENSOR_VOLTAGE, OUTPUT);
	digitalWrite(PIN_SENSOR_VOLTAGE, LOW);

	// for testing
	// delay(50);
	// bme280_setup();
	// mpu6050_setup();
	// my_hall_init();
	// my_aBuzzer_init();
	// Serial.println("sensor inited!");

	// ======== gateway communication init ========
	if (wifi_init() != true) {
		return;
	}
	if (sync_time() != true) {
		return;
	}
	if (socket_connect() != true) {
		return;
	}

	// ======== server communication init ========
	Serial2.begin(115200);

	// ======== sensor thread init ========
	static TaskHandle_t Task_Sensor = NULL;
	BaseType_t xReturned = pdFAIL;
	//create a task that will be executed in the function, with priority 1 and executed on core 0
	xReturned = xTaskCreatePinnedToCore(sensor_task, /* Task function. */
					    "Sensor", /* name of task. */
					    10000, /* Stack size of task */
					    NULL, /* parameter of the task */
					    1, /* priority of the task */
					    &Task_Sensor, /* Task handle to keep track of created task */
					    0); /* pin task to core 0 */
	if (xReturned != pdPASS) {
		return;
	}
	// Serial.println("sensor thread inited!");
}

void loop()
{
	// ======== TEST BOARD start ========
	// led_blinkWithoutDelay();
	// i2cScannerLoop();
	// ======== TEST BOARD end ========

	// put your main code here, to run repeatedly:
	// Serial.println("this is loop()");
	// delay(1000);

	// !!! loop() is for both gateway and server communication
	// Serial.println("Current Status: " + String(currentStatus) + " / Previous Status: " + String(previousStatus));
	if (currentStatus == DISCONNECT) {
		// ======== gateway communication ========

		// ======== server communication ========
		turn_off_A9G();
		disconnect_currMillis = millis();
		if (previousStatus != DISCONNECT) {
			disconnect_prevMillis = millis();
		}
		if (disconnect_currMillis - disconnect_prevMillis >= TIMEOUT_TIME) {
			previousStatus = currentStatus;
			currentStatus = A9G_CONNECTING;
		}

	} else if (currentStatus == WAREHOUSE_WIFI_CONNECTING) {
		// ======== gateway communication ========

		// ======== server communication ========

	} else if (currentStatus == WAREHOUSE_WIFI_CONNECTED) {
		// ======== gateway communication ========

		// ======== server communication ========

	} else if (currentStatus == WAREHOUSE_WIFI_RETRY) {
		// ======== gateway communication ========

		// ======== server communication ========

	} else if (currentStatus == TRUCK_WIFI_CONNECTING) {
		// ======== gateway communication ========

		// ======== server communication ========

	} else if (currentStatus == TRUCK_WIFI_CONNECTED) {
		// ======== gateway communication ========

		// ======== server communication ========

	} else if (currentStatus == TRUCK_WIFI_RETRY) {
		// ======== gateway communication ========

		// ======== server communication ========

	} else if (currentStatus == A9G_CONNECTING) {
		// ======== gateway communication ========

		// ======== server communication ========
		Serial.println("===BOOTING A9G===");
		delay(15000);
		if (connect_mqqt_broker()) {
			Serial.println("SUCCESSFULLY CONNECTED TO THE SERVER");
			start_GPS();
			previousStatus = currentStatus;
			currentStatus == A9G_CONNECTED;
		} else {
			Serial.println("FAILED TO CONNECT TO THE SERVER");
			previousStatus = currentStatus;
			currentStatus == A9G_RETRY;
		}

	} else if (currentStatus == A9G_CONNECTED) {
		// ======== gateway communication ========

		// ======== server communication ========
		get_GPS_data();
		send_JSON_data(dataBuffer[idx_currRead]);
		idx_currRead = (idx_currRead + 1) % DATA_BUFF_LENGTH;

	} else if (currentStatus == A9G_RETRY) {
		// ======== gateway communication ========

		// ======== server communication ========
		turn_off_A9G();
		previousStatus = currentStatus;
		currentStatus == A9G_CONNECTING;
	}
}

void sensor_task(void *pvParameters)
{
	for (;;) {
		// --Task application code here.--

		// for testing
		// bme280_print();
		// mpu6050_print();
		// my_light_print();
		// my_aBuzzer_alarm();

		sensor_pollForStatus();
	}

	/* Tasks must not attempt to return from their implementing
        function or otherwise exit.  In newer FreeRTOS port
        attempting to do so will result in an configASSERT() being
        called if it is defined.  If it is necessary for a task to
        exit then have the task call vTaskDelete( NULL ) to ensure
        its exit is clean. */
	vTaskDelete(NULL);
}

void sensor_pollForStatus()
{
	if (currentStatus == DISCONNECT) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
			digitalWrite(PIN_SENSOR_VOLTAGE, LOW);
		} else {
			// do nothing
		}

	} else if (currentStatus == WAREHOUSE_WIFI_CONNECTING) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
			digitalWrite(PIN_SENSOR_VOLTAGE, LOW);
		} else {
			// do nothing
		}

	} else if (currentStatus == WAREHOUSE_WIFI_CONNECTED) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
			digitalWrite(PIN_SENSOR_VOLTAGE, LOW);
		} else {
			// do nothing
		}

	} else if (currentStatus == WAREHOUSE_WIFI_RETRY) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
			digitalWrite(PIN_SENSOR_VOLTAGE, LOW);
		} else {
			// do nothing
		}

	} else if (currentStatus == TRUCK_WIFI_CONNECTING) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
			digitalWrite(PIN_SENSOR_VOLTAGE, LOW);
		} else {
			// do nothing
		}

	} else if (currentStatus == TRUCK_WIFI_CONNECTED) {
		if ((previousStatus != TRUCK_WIFI_CONNECTED) && previousStatus != A9G_CONNECTED) {
			// !!! sensor init
			digitalWrite(PIN_SENSOR_VOLTAGE, HIGH);
			delay(10);
			// i2cScannerSetup();
			bme280_setup();
			mpu6050_setup();
			my_hall_init();
			my_aBuzzer_init();
		} else {
			// we keep updating the data buffer
		}

	} else if (currentStatus == TRUCK_WIFI_RETRY) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
			digitalWrite(PIN_SENSOR_VOLTAGE, LOW);
		} else {
			// do nothing
		}

	} else if (currentStatus == A9G_CONNECTING) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
			digitalWrite(PIN_SENSOR_VOLTAGE, LOW);
		} else {
			// do nothing
		}

	} else if (currentStatus == A9G_CONNECTED) {
		if ((previousStatus != TRUCK_WIFI_CONNECTED) && previousStatus != A9G_CONNECTED) {
			// !!! sensor init
			digitalWrite(PIN_SENSOR_VOLTAGE, HIGH);
			delay(10);
			// i2cScannerSetup();
			bme280_setup();
			mpu6050_setup();
			my_hall_init();
			my_aBuzzer_init();
		} else {
			// we keep updating the data buffer
		}

	} else if (currentStatus == A9G_RETRY) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
			digitalWrite(PIN_SENSOR_VOLTAGE, LOW);
		} else {
			// do nothing
		}
	}
}

void gatewayCommunication_task(void *pvParameters)
{
	for (;;) {
		// --Task application code here.--
		SensorData sensorData(1.1, 1.1, 1.1, 1.1, 1.1, 1.1, String("test"), String(get_time()));
		socket_send_sensor_data(&sensorData);
		delay(10000);
	}

	/* Tasks must not attempt to return from their implementing
        function or otherwise exit.  In newer FreeRTOS port
        attempting to do so will result in an configASSERT() being
        called if it is defined.  If it is necessary for a task to
        exit then have the task call vTaskDelete( NULL ) to ensure
        its exit is clean. */
	vTaskDelete(NULL);
}

// void serverCommunication_task(void *pvParameters)
// {
// 	for (;;) {
// 		// --Task application code here.--
// 		SensorData test(0, 0, 0, 0, 0, 0, "test", "test");
// 		if (currentStatus == DISCONNECT) {
// 			//when disconnected from gateway turn on A9G
// 			if (A9G_state == false) {
// 				connect_mqqt_broker();
// 				start_GPS();
// 				A9G_state = true;
// 			}
// 			//when A9G is already operating
// 			else {
// 				get_GPS_data();
// 				//Serial.println();
// 				send_JSON_data(test);
// 				// check_new_threshold();
// 				delay(1000);
// 			}
// 		} else {
// 			//Serial.print("OFF");
// 			turn_off_A9G();
// 			A9G_state = false;
// 		}
// 		Serial.println();
// 		delay(500);
// 	}

// 	/* Tasks must not attempt to return from their implementing
//         function or otherwise exit.  In newer FreeRTOS port
//         attempting to do so will result in an configASSERT() being
//         called if it is defined.  If it is necessary for a task to
//         exit then have the task call vTaskDelete( NULL ) to ensure
//         its exit is clean. */
// 	vTaskDelete(NULL);
// }
