#include <Arduino.h>
#include "test_board.h"

// -------- INCLUDES --------
// -------- SENSOR SYSTEM --------
#include "i2c_scanner.h"
#include "peripheral_bme280.h"
#include "peripheral_mpu6050.h"

// ------- GPS MODULE --------
#include "PCMS_GPS_GPRS.hpp"

// -------- DEFINES --------
// please write down the pins used in ascending order:
#define I2C_SDA 21
#define I2C_SCL 22

// -------- VARIABLES --------
bool A9G_state = false, disconnected_gateway = true;
String GPS_data = "";
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
	Serial2.begin(115200);
	delay(15000);


	// -------- SENSOR SYSTEM --------
	// i2cScannerSetup();
	bme280_setup();
	mpu6050_setup();

	// -------- GPS MODULE ---------
	sendCommandToA9G("AT", 5, "OK");
}

void loop()
{
<<<<<<< HEAD
  if(disconnected_gateway==true){
    //when disconnected from gateway turn on A9G
    if(A9G_state==false){
	  Serial.print("ON");
	  //digitalWrite(23, HIGH);
	  
      connect_mqqt_broker();
      start_GPS();
      A9G_state=true;
    }
    //when A9G is already operating
    else{
      get_GPS_data();

      //Serial.print("GPS DATA: ");
     // Serial.println(GPS_data);
      //ShowSerialData();
      Serial.println();
      send_JSON_data();
	  check_new_threshold();
      delay(1000);
    }
  }
  else{
	  Serial.print("OFF");
	  turn_off_A9G();
      A9G_state=false;
    //send data to gateway device
  }
  Serial.println();
  delay(500);
}
	// -------- TEST BOARD start --------
	// led_blinkWithoutDelay();
	// -------- TEST BOARD end --------

	// put your main code here, to run repeatedly:

	// -------- SENSOR SYSTEM --------
	// i2cScannerLoop();
	bme280_print();
	mpu6050_print();

	// -------- GPS MODULE ----------
	if(disconnected_gateway==true){
    //when disconnected from gateway turn on A9G
    	if(A9G_state==false){
			Serial.print("ON");
	  //digitalWrite(23, HIGH);
	  
    		connect_mqqt_broker();
      		start_GPS();
      		A9G_state=true;
    	}
    //when A9G is already operating
    	else{
      		get_GPS_data();

      //Serial.print("GPS DATA: ");
     // Serial.println(GPS_data);
      //ShowSerialData();
      		Serial.println();
      		send_JSON_data();
	  		check_new_threshold();
      		delay(1000);
    	}
  }
	else{
		Serial.print("OFF");
		turn_off_A9G();
    	A9G_state=false;
    //send data to gateway device
  	}
  Serial.println();
  delay(500);
}
