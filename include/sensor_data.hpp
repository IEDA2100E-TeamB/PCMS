#ifndef SENSOR_DATA_HPP
#define SENSOR_DATA_HPP

#include <Arduino.h>

struct Orientation {
	double acceleration;
	double gyroscope;
};

class SensorData {
    private:
	double temperature;
	double humidity;
	double pressure;
	double magneticField;
	Orientation orientation;
	String checkTime;

    public:
	SensorData(double temperature, double humidity, double pressure, double magneticField, double acceleration,
		   double gyroscope, String checkTime);
	void update(double temperature, double humidity, double pressure, double magneticField, double acceleration,
		    double gyroscope, String checkTime);
	void print(void);
	String toJson(void);
};

#endif