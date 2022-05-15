#ifndef PERIPHERAL_BME280_H
#define PERIPHERAL_BME280_H

bool bme280_setup();
float bme280_getTemperature_Celsius();
float bme280_getHumidity();
float bme280_getBaroPressure_hPa();
float bme280_getAltitude();
float bme280_getAltitude(float seaLevelPressure);
void bme280_print();

#endif
