#ifndef SENSOR_DATA
#define SENSOR_DATA

#include <Arduino.h>

class SensorData {
    private:
	double temperature;
	double humidity;
	double pressure;
	bool magneticFeild;
	bool orientation;
	bool opened;
	String gpsLocation;
	String checkTime;

    public:
	SensorData(double temperature, double humidity, double pressure, bool magneticFeild, bool orientation,
		   bool opened, String gpsLocation, String checkTime);
	void update(double temperature, double humidity, double pressure, bool magneticFeild, bool orientation,
		    bool opened, String gpsLocation, String checkTime);
	void print(void);
	String to_json(void);
	double get_temperature(void);
	double get_humidity(void);
	double get_pressure(void);
	bool get_magnetic_feild(void);
	bool get_orientation(void);
	bool get_opened(void);
};

#endif