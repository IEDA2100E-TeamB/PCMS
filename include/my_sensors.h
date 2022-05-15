#ifndef MY_SENSORS_H
#define MY_SENSORS_H

#include <Arduino.h>
#include "main.h"
#include "sensor_data.hpp"
#include "i2c_bme280.h"
#include "i2c_mpu6050.h"
#include "adc_light.h"
#include "gpio_hall.h"
#include "gpio_active_buzzer.h"

void sensors_getData(SensorData *dataBlock);

#endif
