#include "peripheral_bme280.h"

// #define BME280_ADDR 0x76
#define SEALEVELPRESSURE_HPA (1013.25)

static Adafruit_BME280 bme;
static Adafruit_Sensor *bmeT = bme.getTemperatureSensor();
static Adafruit_Sensor *bmeH = bme.getHumiditySensor();
static Adafruit_Sensor *bmeP = bme.getPressureSensor();
static uint32_t prevMillis = 0;
static constexpr uint32_t MEASURE_DELAY = 5000;

void bme280_setup()
{
	if (!bme.begin(BME280_ADDRESS_ALTERNATE, &Wire)) {
		Serial.println("Could not find a valid BME280 sensor, check wiring!");
		// TODO generate software interupt
		while (1)
			;
	}

	// REVIEW additional setups
	// For more details on the following scenario,
	// see chapter 3.5 "Recommended modes of operation" in the datasheet

	bmeT->printSensorDetails();
	bmeH->printSensorDetails();
	bmeP->printSensorDetails();
}

float bme280_getTemperature_Celsius()
{
	return bme.readTemperature();

	// sensors_event_t eventTemperature;
	// bmeT->getEvent(&eventTemperature);
	// return eventTemperature.temperature;
}

float bme280_getHumidity()
{
	return bme.readHumidity();

	// sensors_event_t eventHumidity;
	// bmeH->getEvent(&eventHumidity);
	// return eventHumidity.relative_humidity;
}

float bme280_getBaroPressure_hPa()
{
	return bme.readPressure() / 100.0F;

	// sensors_event_t eventBaroPressure;
	// bmeP->getEvent(&eventBaroPressure);
	// return eventBaroPressure.pressure;
}

float bme280_getAltitude()
{
	return bme280_getAltitude(SEALEVELPRESSURE_HPA);
}

float bme280_getAltitude(float seaLevelPressure)
{
	return bme.readAltitude(seaLevelPressure);

	// sensors_event_t eventBaroPressure;
	// bmeP->getEvent(&eventBaroPressure);
	// return 44330.0 * (1.0 - pow(eventBaroPressure.pressure / seaLevelPressure, 0.1903));
}

void bme280_print()
{
	// !!! NodeMCU-32S sometimes cannot init 12c ports. ESP32-DevKitC works fine.
	uint32_t currMillis = millis();
	if (currMillis - prevMillis >= MEASURE_DELAY) {
		Serial.print("Temperature = ");
		Serial.print(bme.readTemperature());
		Serial.println(" *C");

		Serial.print("Humidity = ");
		Serial.print(bme.readHumidity());
		Serial.println(" %");

		Serial.print("Pressure = ");
		Serial.print(bme.readPressure() / 100.0F);
		Serial.println(" hPa");

		Serial.print("Approx. Altitude = ");
		Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
		Serial.println(" m");

		// sensors_event_t eventTemperature, eventHumidity, eventBaroPressure;
		// bmeT->getEvent(&eventTemperature);
		// bmeH->getEvent(&eventHumidity);
		// bmeP->getEvent(&eventBaroPressure);

		// Serial.print(F("Temperature = "));
		// Serial.print(eventTemperature.temperature);
		// Serial.println(" *C");

		// Serial.print(F("Humidity = "));
		// Serial.print(eventHumidity.relative_humidity);
		// Serial.println(" %");

		// Serial.print(F("Pressure = "));
		// Serial.print(eventBaroPressure.pressure);
		// Serial.println(" hPa");

		Serial.println();
		prevMillis = currMillis;
	}
}
