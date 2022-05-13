#ifndef SENSOR_DATA
#define SENSOR_DATA

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
	String gpsLocation;
	String checkTime;

    public:
	SensorData(double temperature, double humidity, double pressure, double magneticField, double acceleration,
		   double gyroscope, String gpsLocation, String checkTime);
	void update(double temperature, double humidity, double pressure, double magneticField, double acceleration,
		    double gyroscope, String gpsLocation, String checkTime);
	void print(void);
	String toJson(void);
};

#endif