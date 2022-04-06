#include <PCMS_GPS_GPRS.hpp>

int countTrueCommand=0;
int countTimeCommand=0;
boolean found = false;
extern String GPS_data;

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
    sendCommandToA9G("AT+GPSRD=2",3,"OK"); //Display location data every 2seconds
}

void get_GPS_data(){
    Serial2.println("AT+LOCATION=2");
    ShowSerialData();
}

void terminate_GPS(){
    Serial2.println("AT+GPSRD=0");
    delay(1000);
    ShowSerialData(); //displays output from A9
    Serial2.println("AT+GPS=0");
    delay(1000);
    ShowSerialData(); //displays output from A9
}


//-------------------------GPRS---------------------------
void connect_mqqt_broker(){
    sendCommandToA9G("AT+CGDCONT=1,\"IP\",\"pccw\"", 3, "OK");    
    sendCommandToA9G("AT+CGACT=1,1", 5, "OK");
    sendCommandToA9G("AT+MQTTCONN=\"broker.mqttdashboard.com\",1883,\"testclient\",120,0", 5, "OK");
}

void send_JSON_data(){
  sendCommandToA9G("AT+MQTTPUB=\"Test1\",\"JSON DATA\",0,0,0",5,"OK");         
}

void terminate_broker_connection(){
    sendCommandToA9G("AT+MQTTDISCONN", 5, "OK");
}




