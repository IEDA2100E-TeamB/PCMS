#include "sensor_data.hpp"

SensorData::SensorData(double temperature, double humidity, double pressure, double magneticField, double acceleration,
		       double gyroscope, String gpsLocation, String checkTime)
{
	this->temperature = temperature;
	this->humidity = humidity;
	this->pressure = pressure;
	this->magneticField = magneticField;
	this->orientation.acceleration = acceleration;
	this->orientation.gyroscope = gyroscope;
	this->checkTime = checkTime;
}

void SensorData::update(double temperature, double humidity, double pressure, double magneticField, double acceleration,
			double gyroscope, String gpsLocation, String checkTime)
{
	this->temperature = temperature;
	this->humidity = humidity;
	this->pressure = pressure;
	this->magneticField = magneticField;
	this->orientation.acceleration = acceleration;
	this->orientation.gyroscope = gyroscope;
	this->checkTime = checkTime;
}

void SensorData::print(void)
{
	Serial.print("temperature: ");
	Serial.println(this->temperature);
	Serial.print("humidity: ");
	Serial.println(this->humidity);
	Serial.print("pressure: ");
	Serial.println(this->pressure);
	Serial.print("magneticField: ");
	Serial.println(this->magneticField);
	Serial.print("acceleration: ");
	Serial.println(this->orientation.acceleration);
	Serial.print("gyroscope: ");
	Serial.println(this->orientation.gyroscope);
    Serial.print("gpsLocation: ");
    Serial.println(this->gpsLocation);
	Serial.print("checkTime: ");
	Serial.println(this->checkTime);
}

String SensorData::to_json(void)
{
	String json = "{";
	json += "\"temperature\":" + String(this->temperature) + ",";
	json += "\"humidity\":" + String(this->humidity) + ",";
	json += "\"pressure\":" + String(this->pressure) + ",";
	json += "\"magnetic_field\":" + String(this->magneticField) + ",";
	json += "\"orientation\":\"";
	json += this->orientation.acceleration;
	json += ":";
	json += this->orientation.gyroscope;
	json += "\",";
    json += "\"gps_location\":\"" + String(this->gpsLocation) + "\",";
	json += "\"check_time\":\"" + String(this->checkTime) + "\""; 
	json += "}";
	return json;
}