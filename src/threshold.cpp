#include "threshold.hpp"

const double comparrationInterval = 0.001;

Threshold::Threshold(double minTemp, double maxTemp, double minHumi, double maxHumi, double minPres, double maxPres,
		     bool allowMag, bool allowOriChange)
{
	this->minTemperature = minTemp;
	this->maxTemperature = maxTemp;
	this->minHumidity = minHumi;
	this->maxHumidity = maxHumi;
	this->minPressure = minPres;
	this->maxPressure = maxPres;
	this->allowMagneticFeild = allowMag;
	this->allowOrientationChange = allowOriChange;
}

void Threshold::update(double minTemp, double maxTemp, double minHumi, double maxHumi, double minPres, double maxPres,
		       bool allowMag, bool allowOriChange)
{
	this->minTemperature = minTemp;
	this->maxTemperature = maxTemp;
	this->minHumidity = minHumi;
	this->maxHumidity = maxHumi;
	this->minPressure = minPres;
	this->maxPressure = maxPres;
	this->allowMagneticFeild = allowMag;
	this->allowOrientationChange = allowOriChange;
}

bool Threshold::check_passed(SensorData *sensorData)
{
	if (sensorData->get_temperature() - this->maxTemperature > comparrationInterval) {
		return false;
	}
	if (this->minTemperature - sensorData->get_temperature() > comparrationInterval) {
		return false;
	}
	if (sensorData->get_humidity() - this->maxHumidity > comparrationInterval) {
		return false;
	}
	if (this->minHumidity - sensorData->get_humidity() > comparrationInterval) {
		return false;
	}
	if (sensorData->get_pressure() - this->maxPressure > comparrationInterval) {
		return false;
	}
	if (this->minPressure - sensorData->get_pressure() > comparrationInterval) {
		return false;
	}
	if (sensorData->get_magnetic_feild() != this->allowMagneticFeild) {
		return false;
	}
	if (sensorData->get_orientation() != this->allowOrientationChange) {
		return false;
	}
	if (sensorData->get_opened()) {
		return false;
	}
	return true;
}
