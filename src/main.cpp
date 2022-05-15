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

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);

	// ======== gateway communication init ========
	// !!! we init this part first
	// if (wifi_init() != true) {
	// 	return;
	// }
	// if (sync_time() != true) {
	// 	return;
	// }
	// if (socket_connect() != true) {
	// 	return;
	// }

	// ======== local system init ========
	// i2cScannerSetup();
	bme280_setup();
	mpu6050_setup();
	my_aBuzzer_init();

	// ======== server communication init ========
	// !!! we skip server communication init and ONLY init it when neccesary
	Serial2.begin(115200);
	sendCommandToA9G("AT", 5, "OK");

	// ======== threads init ========
	static TaskHandle_t task_system = NULL;
	static TaskHandle_t task_gatewayCommunication = NULL;
	static TaskHandle_t task_serverCommunication = NULL;
	BaseType_t xReturned;

	// ======== local system thread ========
	//create a task that will be executed in the function, with priority 1 and executed on core 0
	xReturned = pdFAIL;
	xReturned = xTaskCreatePinnedToCore(system_task, /* Task function. */
					    "System", /* name of task. */
					    10000, /* Stack size of task */
					    NULL, /* parameter of the task */
					    1, /* priority of the task */
					    &task_system, /* Task handle to keep track of created task */
					    0); /* pin task to core 0 */
	if (xReturned != pdPASS) {
		return;
	}
	delay(500);

	// ======== gateway communication thread ========
	//create a task that will be executed in the function, with priority 1 and executed on core 1
	// xReturned = pdFAIL;
	// xTaskCreatePinnedToCore(gatewayCommunication_task, /* Task function. */
	// 			"Gateway Communication", /* name of task. */
	// 			10000, /* Stack size of task */
	// 			NULL, /* parameter of the task */
	// 			1, /* priority of the task */
	// 			&task_gatewayCommunication, /* Task handle to keep track of created task */
	// 			1); /* pin task to core 1 */
	// if (xReturned != pdPASS) {
	// 	return;
	// }
	// delay(500);

	// ======== server communication thread ========
	// !!! not creating it now
	// create a task that will be executed in the function, with priority 1 and executed on core 1
	xReturned = pdFAIL;
	xReturned = xTaskCreatePinnedToCore(serverCommunication_task, /* Task function. */
					    "Task2", /* name of task. */
					    10000, /* Stack size of task */
					    NULL, /* parameter of the task */
					    1, /* priority of the task */
					    &task_serverCommunication, /* Task handle to keep track of created task */
					    1); /* pin task to core 1 */
	if (xReturned != pdPASS) {
		return;
	}
	delay(500);
}

void loop()
{
	// ======== TEST BOARD start ========
	// led_blinkWithoutDelay();
	// ======== TEST BOARD end ========

	// put your main code here, to run repeatedly:
	// Serial.println("this is loop()");
	// delay(1000);
}

void system_task(void *pvParameters)
{
	for (;;) {
		// --Task application code here.--
		// i2cScannerLoop();
		bme280_print();
		mpu6050_print();
		my_light_print();
		// my_aBuzzer_alarm();
	}

	/* Tasks must not attempt to return from their implementing
        function or otherwise exit.  In newer FreeRTOS port
        attempting to do so will result in an configASSERT() being
        called if it is defined.  If it is necessary for a task to
        exit then have the task call vTaskDelete( NULL ) to ensure
        its exit is clean. */
	vTaskDelete(NULL);
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
