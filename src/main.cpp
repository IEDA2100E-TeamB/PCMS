#include <PCMS_GPS_GPRS.hpp>
#include <Arduino.h>


bool A9G_state = false, disconnected_gateway = false;
String GPS_data="";


void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  delay(15000);
  

}
 
void loop()
{
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