#include "sensor_data.hpp"

SensorData::SensorData()
{
	temperature = 0;
	humidity = 0;
	pressure = 0;
	magneticFeild = false;
	orientation = false;
	opened = false;
	gpsLocation = "";
	checkTime = "";
}


SensorData::SensorData(double temperature, double humidity, double pressure, bool magneticFeild, bool orientation,
		       bool opened, String gpsLocation, String checkTime)
{
	this->temperature = temperature;
	this->humidity = humidity;
	this->pressure = pressure;
	this->magneticFeild = magneticFeild;
	this->orientation = orientation;
	this->opened = opened;
	this->gpsLocation = gpsLocation;
	this->checkTime = checkTime;
}

void SensorData::update(double temperature, double humidity, double pressure, bool magneticFeild, bool orientation,
			bool opened, String gpsLocation, String checkTime)
{
	this->temperature = temperature;
	this->humidity = humidity;
	this->pressure = pressure;
	this->magneticFeild = magneticFeild;
	this->orientation = orientation;
	this->opened = opened;
	this->gpsLocation = gpsLocation;
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
	Serial.print("magnetic_feild: ");
	Serial.println(this->magneticFeild);
	Serial.print("orientation: ");
	Serial.println(this->orientation);
	Serial.print("opened: ");
	Serial.println(this->opened);
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
	json += "\"magneticFeild\":" + String(this->magneticFeild) + ",";
	json += "\"orientation\":" + String(this->orientation) + ",";
	json += "\"opened\":" + String(this->opened) + ",";
	//json += "\"gps_location\":\"" + String(this->gpsLocation) + "\",";
	json += "\"check_time\":\"" + String(this->checkTime) + "\"";
	//json += "}";
	return json;
}

double SensorData::get_temperature(void)
{
	return this->temperature;
}

double SensorData::get_humidity(void)
{
	return this->humidity;
}

double SensorData::get_pressure(void)
{
	return this->pressure;
}

bool SensorData::get_magnetic_feild(void)
{
	return this->magneticFeild;
}

bool SensorData::get_orientation(void)
{
	return this->orientation;
}

bool SensorData::get_opened(void)
{
	return this->opened;
}