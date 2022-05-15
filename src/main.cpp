#include "main.h"
#include "test_board.h"

// ======== INCLUDES ========
// local system
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
// #include "soc/soc.h"
// #include "soc/rtc_cntl_reg.h"
#include "PCMS_GPS_GPRS.hpp"

// ======== FUNCTION PROTOTYPES ========
void sensor_task(void *pvParameters);
void sensor_pollForStatus();
void gatewayCommunication_task(void *pvParameters);
void serverCommunication_task(void *pvParameters);

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);

	// ======== sensor VOUT init ========
	pinMode(SENSOR_VOLTAGE, OUTPUT);
	digitalWrite(SENSOR_VOLTAGE, LOW);

	// ======== gateway communication init ========
	// !!! we init this part first
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
	// !!! we skip server communication init and ONLY init it when neccesary
	Serial2.begin(115200);
	// sendCommandToA9G("AT", 5, "OK");

	// ======== sensor thread init ========
	static TaskHandle_t Task_Sensor = NULL;
	BaseType_t xReturned = pdFAIL;
	//create a task that will be executed in the function, with priority 1 and executed on core 0
	xReturned = xTaskCreatePinnedToCore(sensor_task, /* Task function. */
					    "System", /* name of task. */
					    10000, /* Stack size of task */
					    NULL, /* parameter of the task */
					    1, /* priority of the task */
					    &Task_Sensor, /* Task handle to keep track of created task */
					    0); /* pin task to core 0 */
	if (xReturned != pdPASS) {
		return;
	}
}

void loop()
{
	// ======== TEST BOARD start ========
	// led_blinkWithoutDelay();
	// ======== TEST BOARD end ========

	// put your main code here, to run repeatedly:
	// Serial.println("this is loop()");
	// delay(1000);

	// !!! loop() is for both gateway and server communication
	if (currentStatus == DISCONNECT) {
		// ======== gateway communication ========
		// ======== server communication ========
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
	} else if (currentStatus == A9G_CONNECTED) {
		// ======== gateway communication ========
		// ======== server communication ========
	} else if (currentStatus == A9G_RETRY) {
		// ======== gateway communication ========
		// ======== server communication ========
	}
}

void sensor_task(void *pvParameters)
{
	for (;;) {
		// --Task application code here.--
		// i2cScannerLoop();
		bme280_print();
		mpu6050_print();
		my_light_print();
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
		}

	} else if (currentStatus == WAREHOUSE_WIFI_CONNECTING) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
		}

	} else if (currentStatus == WAREHOUSE_WIFI_CONNECTED) {
		/* code */
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
		}

	} else if (currentStatus == WAREHOUSE_WIFI_RETRY) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
		}

	} else if (currentStatus == TRUCK_WIFI_CONNECTING) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
		}

	} else if (currentStatus == TRUCK_WIFI_CONNECTED) {
		if ((previousStatus != TRUCK_WIFI_CONNECTED) || previousStatus != A9G_CONNECTED) {
			// !!! sensor init
			// i2cScannerSetup();
			bme280_setup();
			mpu6050_setup();
			my_aBuzzer_init();
		}

	} else if (currentStatus == TRUCK_WIFI_RETRY) {
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
		}

	} else if (currentStatus == A9G_CONNECTING) {
		/* code */
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
		}

	} else if (currentStatus == A9G_CONNECTED) {
		if ((previousStatus != TRUCK_WIFI_CONNECTED) || previousStatus != A9G_CONNECTED) {
			// !!! sensor init
			// i2cScannerSetup();
			bme280_setup();
			mpu6050_setup();
			my_aBuzzer_init();
		}

	} else if (currentStatus == A9G_RETRY) {
		/* code */
		if ((previousStatus == TRUCK_WIFI_CONNECTED) || (previousStatus == A9G_CONNECTED)) {
			// turn off the sensor
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

void serverCommunication_task(void *pvParameters)
{
	for (;;) {
		// --Task application code here.--
		SensorData test(0, 0, 0, 0, 0, 0, "test", "test");
		if (currentStatus == DISCONNECT) {
			//when disconnected from gateway turn on A9G
			if (A9G_state == false) {
				connect_mqqt_broker();
				start_GPS();
				A9G_state = true;
			}
			//when A9G is already operating
			else {
				get_GPS_data();
				//Serial.println();
				send_JSON_data(test);
				// check_new_threshold();
				delay(1000);
			}
		} else {
			//Serial.print("OFF");
			turn_off_A9G();
			A9G_state = false;
		}
		Serial.println();
		delay(500);
	}

	/* Tasks must not attempt to return from their implementing
        function or otherwise exit.  In newer FreeRTOS port
        attempting to do so will result in an configASSERT() being
        called if it is defined.  If it is necessary for a task to
        exit then have the task call vTaskDelete( NULL ) to ensure
        its exit is clean. */
	vTaskDelete(NULL);
}
