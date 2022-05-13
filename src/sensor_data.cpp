#include "sensor_data.hpp"

SensorData::SensorData(double temperature, double humidity, double pressure, double magneticField, double acceleration,
		       double gyroscope, String checkTime)
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
           double gyroscope, String checkTime)
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
    Serial.print("checkTime: ");
    Serial.println(this->checkTime);
}

String SensorData::toJson(void)
{
    String json = "{";
    json += "\"temperature\":\"";
    json += this->temperature;
    json += "\",";
    json += "\"humidity\":\"";
    json += this->humidity;
    json += "\",";
    json += "\"pressure\":\"";
    json += this->pressure;
    json += "\",";
    json += "\"magneticField\":\"";
    json += this->magneticField;
    json += "\",";
    json += "\"orientation\":\"";
    json += this->orientation.acceleration;
    json += ":";
    json += this->orientation.gyroscope;
    json += "\",";
    json += "\"checkTime\":\"";
    json += "\"";
    json += this->checkTime;
    json += "\"";
    json += "}";
    Serial.println(json);
    return json;
}