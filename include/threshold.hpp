#ifndef THRESHOLD
#define THRESHOLD

#include "sensor_data.hpp"

class Threshold {
    private:
	double minTemperature;
	double maxTemperature;
	double minHumidity;
	double maxHumidity;
	double minPressure;
	double maxPressure;
	bool allowMagneticFeild;
	bool allowOrientationChange;

    public:
	Threshold(double minTemp, double maxTemp, double minHumi, double maxHumi, double minPres, double maxPres, bool allowMag, bool allowOriChange);
	void update(double minTemp, double maxTemp, double minHumi, double maxHumi, double minPres, double maxPres, bool allowMag, bool allowOriChange);
    bool check(SensorData *);
};

#endif