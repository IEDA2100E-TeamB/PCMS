#include "i2c_bme280.h"

#define BME280_ADDR 0x76
#define SEALEVELPRESSURE_HPA (1013.25)

static Adafruit_BME280 bme280;
static Adafruit_Sensor *bme280T;
static Adafruit_Sensor *bme280H;
static Adafruit_Sensor *bme280P;
static uint32_t prevMillis = 0;
static constexpr uint32_t MEASURE_DELAY = 5000;

void bme280_setup()
{
	if (!bme280.begin(BME280_ADDR, &Wire)) {
		Serial.println("Could not find a valid BME280 sensor, check wiring!");
		// TODO generate software interupt
		while (1)
			;
	}

	// REVIEW additional setups
	// For more details on the following scenario,
	// see chapter 3.5 "Recommended modes of operation" in the datasheet

	bme280T = bme280.getTemperatureSensor();
	bme280H = bme280.getHumiditySensor();
	bme280P = bme280.getPressureSensor();

	bme280T->printSensorDetails();
	bme280H->printSensorDetails();
	bme280P->printSensorDetails();
}

float bme280_getTemperature_Celsius()
{
	// return bme280.readTemperature();

	sensors_event_t eventTemperature;
	bme280T->getEvent(&eventTemperature);
	return eventTemperature.temperature;
}

float bme280_getHumidity()
{
	// return bme280.readHumidity();

	sensors_event_t eventHumidity;
	bme280H->getEvent(&eventHumidity);
	return eventHumidity.relative_humidity;
}

float bme280_getBaroPressure_hPa()
{
	// return bme280.readPressure() / 100.0F;

	sensors_event_t eventBaroPressure;
	bme280P->getEvent(&eventBaroPressure);
	return eventBaroPressure.pressure;
}

float bme280_getAltitude()
{
	return bme280_getAltitude(SEALEVELPRESSURE_HPA);
}

float bme280_getAltitude(float seaLevelPressure)
{
	// return bme280.readAltitude(seaLevelPressure);

	sensors_event_t eventBaroPressure;
	bme280P->getEvent(&eventBaroPressure);
	return 44330.0 * (1.0 - pow(eventBaroPressure.pressure / seaLevelPressure, 0.1903));
}

void bme280_print()
{
	// !!! NodeMCU-32S sometimes cannot init 12c ports. ESP32-DevKitC works fine.
	uint32_t currMillis = millis();
	if (currMillis - prevMillis >= MEASURE_DELAY) {
		// Serial.print("Temperature = ");
		// Serial.print(bme280.readTemperature());
		// Serial.println(" *C");

		// Serial.print("Humidity = ");
		// Serial.print(bme280.readHumidity());
		// Serial.println(" %");

		// Serial.print("Pressure = ");
		// Serial.print(bme280.readPressure() / 100.0F);
		// Serial.println(" hPa");

		// Serial.print("Approx. Altitude = ");
		// Serial.print(bme280.readAltitude(SEALEVELPRESSURE_HPA));
		// Serial.println(" m");

		sensors_event_t eventTemperature;
		sensors_event_t eventHumidity;
		sensors_event_t eventBaroPressure;
		bme280T->getEvent(&eventTemperature);
		bme280H->getEvent(&eventHumidity);
		bme280P->getEvent(&eventBaroPressure);

		Serial.print(F("Temperature (*C): "));
		Serial.print(eventTemperature.temperature);
		Serial.println();

		Serial.print(F("Humidity (%): "));
		Serial.print(eventHumidity.relative_humidity);
		Serial.println();

		Serial.print(F("Pressure (hPa): "));
		Serial.print(eventBaroPressure.pressure);
		Serial.println();

		Serial.println();
		prevMillis = currMillis;
	}
}
