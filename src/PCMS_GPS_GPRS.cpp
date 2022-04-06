#include <PCMS_GPS_GPRS.hpp>

String HOST = "cn.bing.com";
String PATH = "/";
String PORT = "80";

int countTrueCommand=0;
int countTimeCommand=0;
boolean found = false;

StaticJsonDocument<200> root;
//JsonObject& root = jsonBuffer.to<JsonObject>();

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
    //delay(50);
  }
}


void start_GPS(){
    Serial2.println("AT+GPS=0"); //turns on GPS
    delay(1000);
    ShowSerialData(); //displays output from A9G
    Serial2.println("AT+GPSRD=2"); //retrieve GPS info every 5 seconds
    delay(1000);
    ShowSerialData(); //displays output from A9
}

void sendData(String postRequest) {
  Serial.println(postRequest);
  Serial2.print(postRequest);
  delay(60000);
  ShowSerialData();
  countTrueCommand++;
  
}

void terminate_GPS(){
    Serial2.println("AT+GPSRD=0");
    delay(1000);
    ShowSerialData(); //displays output from A9
    Serial2.println("AT+GPS=0");
    delay(1000);
    ShowSerialData(); //displays output from A9
}

void start_GPRS(){
    sendCommandToA9G("AT+CGDCONT=1,\"IP\",\"pccw\"",5,"OK");
    sendCommandToA9G("AT+CIPMUX=1", 5, "OK");
    sendCommandToA9G("AT+CIPSTART=\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
    
    
    
    


   // Serial2.println("AT+CIPSTART=\"TCP\",\"SuperScrapper.hojinyun.repl.co\",80"); //set APN for GPRS
    //delay(1000);
   // ShowSerialData();
}
void send_request_to_server(){
  Serial2.println("AT+CIPSTATUS");
  delay(500);
  ShowSerialData();
  Serial2.println("AT+CIFSR");
  delay(500);
  ShowSerialData();
  root["name"] = "temperature";
  root["data"] =  21.5;
  String data;
  serializeJson(root, data);
  String postRequest = "GET / HTTP/1.1\r\nUser-Agent: curl/7.37.0\r\nHost: cn.bing.com\r\nAccept: */*\r\n";
  /*String postRequest = "POST " + PATH  + " HTTP/1.1\r\n" +
                        "Host: " + HOST + "\r\n" +
                        data + "\r\n" +
                      //"Accept: *" + "/" + "*\r\n" +
                      //"Content-Length: " + data.length() + "\r\n" +
                      "Content-Type: application/json";// +
                      //"Authorization: Bearer " + DEVICE_SECRET_KEY + "\r\n" +*/
  String cipSend = "AT+CIPSEND=0," + String(postRequest.length());
  sendCommandToA9G(cipSend, 4, ">");
  sendData(postRequest);               

}
/*
void send_data(){
    Serial2.print("AT+CIPSEND\r\n");
    delay(500);
    Serial2.print("GET / HTTP/1.1\r\n");
    Serial2.print((char)26);
    delay(1000);
    ShowSerialData();
}*/

void terminate_GPRS(){
    sendCommandToA9G("AT+CIPCLOSE", 5, "OK");


    Serial2.println("^FTPCLOSE"); //disconnect from server
    delay(1000);
    ShowSerialData();
    Serial2.println("AT+RST=2"); //terminate the whole module
    delay(1000);
    ShowSerialData();
}
