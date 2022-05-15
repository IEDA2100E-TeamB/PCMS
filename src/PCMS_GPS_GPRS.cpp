#ifndef PCMS_GPS_GPRS
#define PCMS_GPS_GPRS

#include <PCMS_GPS_GPRS.hpp>
#include <sensor_data.hpp>
#include <threshold.hpp>
#include <main.h>

int countTrueCommand=0;
int countTimeCommand=0;
bool found = false;
String saved_serial_buffer="",gpsLocation="";

void sendCommandToA9G(String command, int maxTime, const char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while (countTimeCommand < (maxTime * 1))
  {
    Serial2.println(command);
    if (Serial2.find(readReplay))
    {
      found = true;
      break;
    }

    countTimeCommand++;
  }

  if (found == true)
  {
    Serial.println("Success");
    countTrueCommand++;
    countTimeCommand = 0;
  }

  if (found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }

  found = false;
}

void ShowSerialData(){
  while (Serial2.available() > 0)
  {
    Serial.write(Serial2.read());
  }
}

//-------------------------GPS---------------------------

void start_GPS(){
    sendCommandToA9G("AT+GPS=1",3,"OK"); //turns on GPS
    //sendCommandToA9G("AT+GPSRD=2",3,"OK"); //Display location data every 2seconds
}

void get_GPS_data(){
    String serial_buffer="";
    saved_serial_buffer="";
    
    Serial2.println("AT+LOCATION=2");
    serial_buffer=Serial2.readString();
    Serial.print(serial_buffer+'\n');
    if(serial_buffer.indexOf("minTemperature")>-1) saved_serial_buffer=serial_buffer.substring(serial_buffer.indexOf("minTemperature"));
    if(serial_buffer.indexOf(".")>-1){
      gpsLocation=serial_buffer.substring(serial_buffer.indexOf(".")-2,serial_buffer.indexOf(".")+17);
      Serial.print(gpsLocation+'\n');
    }
    else Serial.write("UNABLE TO LOCATE");
    
}


//-------------------------GPRS---------------------------
bool connect_mqqt_broker(){
    sendCommandToA9G("AT+CGDCONT=1,\"IP\",\"pccw\"", 3, "OK");
    if(found==true) sendCommandToA9G("AT+CGACT=1,1", 3, "OK");
    else return false;

    if(found==true) sendCommandToA9G("AT+MQTTCONN=\"broker.hivemq.com\",1883,\"PCMS\",120,0", 5, "OK");
    else return false;

    if(found==true) sendCommandToA9G("AT+MQTTSUB=\"IEDA_test\",1,0", 3, "OK");
    else return false;
    
    if(found==true) return true;
    else return false;
}

void check_new_threshold(){
  String serial_buffer="", string_serial_buffer="";
  String string_minTemperature="", string_maxTemperature="", string_minHumidity="", string_maxHumidity="";
  String string_minPressure="", string_maxPressure="", string_allowMagneticField="", sring_allowOrientationChange="";
  Serial.print("----checking for new threshold----\n");
  serial_buffer=Serial2.readString();
  Serial.print(serial_buffer+'\n');
  if(saved_serial_buffer.indexOf("minTemperature")>-1){
    Serial.print("found somewhere else\n");
    string_serial_buffer=saved_serial_buffer.substring(saved_serial_buffer.indexOf("minTemperature"));

    string_minTemperature=string_serial_buffer.substring(string_serial_buffer.indexOf(":")+1,string_serial_buffer.indexOf("/"));

    string_maxTemperature=string_serial_buffer.substring(string_serial_buffer.indexOf("maxTemperature"));
    string_maxTemperature=string_maxTemperature.substring(string_maxTemperature.indexOf(":")+1,string_maxTemperature.indexOf("/"));

    string_minHumidity=string_serial_buffer.substring(string_serial_buffer.indexOf("minHumidity"));
    string_minHumidity=string_minHumidity.substring(string_minHumidity.indexOf(":")+1,string_minHumidity.indexOf("/"));

    string_maxHumidity=string_serial_buffer.substring(string_serial_buffer.indexOf("maxHumidity"));
    string_maxHumidity=string_maxHumidity.substring(string_maxHumidity.indexOf(":")+1,string_maxHumidity.indexOf("/"));

    string_minPressure=string_serial_buffer.substring(string_serial_buffer.indexOf("minPressure"));
    string_minPressure=string_minPressure.substring(string_minPressure.indexOf(":")+1,string_minPressure.indexOf("/"));

    string_maxPressure=string_serial_buffer.substring(string_serial_buffer.indexOf("maxPressure"));
    string_maxPressure=string_maxPressure.substring(string_maxPressure.indexOf(":")+1,string_maxPressure.indexOf("/"));

    string_allowMagneticField=string_serial_buffer.substring(string_serial_buffer.indexOf("allowMagneticFeild"));
    string_allowMagneticField=string_allowMagneticField.substring(string_allowMagneticField.indexOf(":")+1,string_allowMagneticField.indexOf("/"));

    sring_allowOrientationChange=string_serial_buffer.substring(string_serial_buffer.indexOf("allowOrientationChange"));
    sring_allowOrientationChange=sring_allowOrientationChange.substring(sring_allowOrientationChange.indexOf(":")+1,sring_allowOrientationChange.indexOf("/"));

    bool tempMagneticField, tempOrientation;
    if(string_allowMagneticField.toInt()>0) tempMagneticField = true;
    else tempMagneticField = false;
    if(sring_allowOrientationChange.toInt()>0) tempOrientation=true;
    else tempOrientation=false;

    currThreshold.update(string_minTemperature.toDouble(),string_maxTemperature.toDouble(),string_minHumidity.toDouble(),string_maxHumidity.toDouble(),
                      string_minPressure.toDouble(), string_maxPressure.toDouble(), tempMagneticField, tempOrientation);

    //Serial.print("NEW THRESHOLD DETECTED: "+ string_minTemperature+" "+string_maxTemperature+" "+string_minHumidity+" "+string_maxHumidity+" "+string_minPressure+" "+
    //string_maxPressure+" "+string_allowMagneticField+" "+sring_allowOrientationChange+'\n');
    //return;
  }


  if(serial_buffer.indexOf("minTemperature")==-1) Serial.print("NO_THRESHOLD");
  else{
    string_serial_buffer=serial_buffer.substring(serial_buffer.indexOf("minTemperature"));

    string_minTemperature=string_serial_buffer.substring(string_serial_buffer.indexOf(":")+1,string_serial_buffer.indexOf("/"));

    string_maxTemperature=string_serial_buffer.substring(string_serial_buffer.indexOf("maxTemperature"));
    string_maxTemperature=string_maxTemperature.substring(string_maxTemperature.indexOf(":")+1,string_maxTemperature.indexOf("/"));

    string_minHumidity=string_serial_buffer.substring(string_serial_buffer.indexOf("minHumidity"));
    string_minHumidity=string_minHumidity.substring(string_minHumidity.indexOf(":")+1,string_minHumidity.indexOf("/"));

    string_maxHumidity=string_serial_buffer.substring(string_serial_buffer.indexOf("maxHumidity"));
    string_maxHumidity=string_maxHumidity.substring(string_maxHumidity.indexOf(":")+1,string_maxHumidity.indexOf("/"));

    string_minPressure=string_serial_buffer.substring(string_serial_buffer.indexOf("minPressure"));
    string_minPressure=string_minPressure.substring(string_minPressure.indexOf(":")+1,string_minPressure.indexOf("/"));

    string_maxPressure=string_serial_buffer.substring(string_serial_buffer.indexOf("maxPressure"));
    string_maxPressure=string_maxPressure.substring(string_maxPressure.indexOf(":")+1,string_maxPressure.indexOf("/"));

    string_allowMagneticField=string_serial_buffer.substring(string_serial_buffer.indexOf("allowMagneticFeild"));
    string_allowMagneticField=string_allowMagneticField.substring(string_allowMagneticField.indexOf(":")+1,string_allowMagneticField.indexOf("/"));

    sring_allowOrientationChange=string_serial_buffer.substring(string_serial_buffer.indexOf("allowOrientationChange"));
    sring_allowOrientationChange=sring_allowOrientationChange.substring(sring_allowOrientationChange.indexOf(":")+1,sring_allowOrientationChange.indexOf("/"));

    
    bool tempMagneticField=false, tempOrientation=false;
    if(string_allowMagneticField.toInt()>0) tempMagneticField = true;
    else tempMagneticField = false;
    if(sring_allowOrientationChange.toInt()>0) tempOrientation=true;
    else tempOrientation=false;
    
    currThreshold.update(string_minTemperature.toDouble(),string_maxTemperature.toDouble(),string_minHumidity.toDouble(),string_maxHumidity.toDouble(),
                      string_minPressure.toDouble(), string_maxPressure.toDouble(), tempMagneticField, tempOrientation);
    

    //Serial.print("NEW THRESHOLD DETECTED: "+ string_minTemperature+" "+string_maxTemperature+" "+string_minHumidity+" "+string_maxHumidity+" "+string_minPressure+" "+
    //string_maxPressure+" "+string_allowMagneticField+" "+sring_allowOrientationChange+'\n');
    //return;
  }
}

void send_JSON_data(SensorData sensorData){
  sendCommandToA9G("AT+MQTTPUB=\"IEDA_test\",\""+sensorData.to_json()+"\",0,0,0",3,"OK");         
}

void turn_off_A9G(){
  Serial2.println("AT+RST=2");
}



#endif