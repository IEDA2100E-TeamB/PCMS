#include <PCMS_GPS_GPRS.hpp>
#include <Arduino.h>


bool A9G_state = false, disconnected_gateway = true;
String GPS_data="";


void setup()
{
  delay(15000);
  Serial.begin(115200);
  Serial2.begin(115200);
  sendCommandToA9G("AT", 5, "OK");
}
 
void loop()
{
  if(disconnected_gateway==true){
    //when A9G off
    if(A9G_state==false){
      //sendCommandToA9G("AT+SLEEP=0",3,"OK"); //wake A9G up
      //delay(2000);
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

      delay(1000);
    }
  }
  else{
    if(A9G_state==true){
      terminate_GPS();
      terminate_broker_connection();
      //sendCommandToA9G("AT+SLEEP=2",3,"OK"); //low power consumption mode
      A9G_state=false;
    }
    //send data to gateway device
  }
  Serial.println();
  delay(1000);
}