#include <PCMS_GPS_GPRS.hpp>
#include <Arduino.h>


bool A9G_state = false, disconnected_gateway = true;



void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial2.println("AT");
  Serial.write(Serial2.read());
  //sendCommandToA9G("AT", 5, "OK");
  /*
  myserial.println("AT");
  delay(500);

  myserial.println("AT+CREG=?");     //Check Network regiistration, wait a while
  delay(1000);
  ShowSerialData();*/
}
 
void loop()
{
  if(disconnected_gateway==true){
    //when A9G off
    if(A9G_state==false){
      //start_GPS();
      start_GPRS();
      A9G_state=true;
    }
      
    //when A9G is already operating
    else{
      send_request_to_server();
      delay(1000);
      
    }
  }
  else{
    if(A9G_state==true){
      terminate_GPS();
      terminate_GPRS();
      A9G_state=false;
    }
    //send data to gateway device
  }
  Serial.println();
  //Serial.print("disconnected_gateway: ");
  //Serial.println(disconnected_gateway);
  //Serial.print("A9G_state: ");
  //Serial.println(A9G_state);
  delay(1000);
}

 

/*
#include <stdio.h>
#include <string.h>
 
#define DEBUG true
 
bool ModuleState=false;


 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    Serial2.println(command);
    long int time = millis();
    while ((time + timeout) > millis())
    {
        while (Serial2.available())
        {
            char c = Serial2.read();
            response += c;
        }
    }
    if (debug)
    {
        Serial.print(response);
    }
    return response;
}

bool moduleStateCheck()
{
    int i = 0;
    bool moduleState=false;
    for (i = 0; i < 5; i++)
    {
        String msg = String("");
        msg = sendData("AT", 1000, DEBUG);
        if (msg.indexOf("OK") >= 0)
        {
            Serial.println("A9/A9G Module had turned on.");
                moduleState=true;
            return moduleState;
        }
        delay(1000);
    }
    return moduleState;
}
 
void setup()
{
	Serial.println("Start Setup");
    Serial2.begin(115200);
    
    Serial.begin(115200);
    //while (!Serial)
    {
        ; // wait for serial port to connect
    }
 
        ModuleState=moduleStateCheck();
        if(ModuleState==false)//if it's off, turn on it.
        {
      		Serial.println("Now turnning the A9/A9G on.");
        }
 
    //sendData("AT+CCID", 3000, DEBUG);
    //sendData("AT+CREG?", 3000, DEBUG);
    //sendData("AT+CGATT=1", 1000, DEBUG);
    //sendData("AT+CGACT=1,1", 1000, DEBUG);
    //sendData("AT+CGDCONT=1,\"IP\",\"CMNET\"", 1000, DEBUG);
    
    //sendData("AT+CIPSTART=\"TCP\",\"www.mirocast.com\",80", 2000, DEBUG);
    Serial.println("Maduino A9/A9G Test Begin!");
}
 
void loop()
{
  Serial.print("Serial 1: ");
  Serial.println(Serial2.available());
  while (Serial2.available() > 0) {
    Serial.write(Serial2.read());
    yield();
  }
  Serial.print("Serial 0: ");
  Serial.println(Serial.available());
  while (Serial.available() > 0) {
    Serial2.write(Serial.read());
    yield();
  }
}
 */