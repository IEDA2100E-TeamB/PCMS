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
		while (1)
			;
	}

	// additional setups
	// For more details on the following scenario,
	// see chapter 3.5 "Recommended modes of operation" in the datasheet

	bmeT->printSensorDetails();
	bmeP->printSensorDetails();
	bmeH->printSensorDetails();
}

float bme280_getTemperature_Celsius()
{
	// return bme.readTemperature();

	sensors_event_t eventTemperature;
	bmeT->getEvent(&eventTemperature);
	return eventTemperature.temperature;
}

float bme280_getHumidity()
{
	// return bme.readHumidity();

	sensors_event_t eventHumidity;
	bmeH->getEvent(&eventHumidity);
	return eventHumidity.relative_humidity;
}

float bme280_getBaroPressure_hPa()
{
	// return bme.readPressure() / 100.0F;

	sensors_event_t eventBaroPressure;
	bmeP->getEvent(&eventBaroPressure);
	return eventBaroPressure.pressure;
}

float bme280_getAltitude(float seaLevelPressure = SEALEVELPRESSURE_HPA)
{
	// return bme.readAltitude(seaLevelPressure);

	// TODO
}

void bme280_print()
{
	// HACK sometimes cannot connect to sensor.
	// hacked by changing library calls
	// consider creating post at https://forums.adafruit.com/viewforum.php?f=19 or https://github.com/adafruit/Adafruit_BME280_Library/issues
	uint32_t currMillis = millis();
	if (currMillis - prevMillis >= MEASURE_DELAY) {
		// Serial.print("Temperature = ");
		// Serial.print(bme.readTemperature());
		// Serial.println(" *C");

		// Serial.print("Humidity = ");
		// Serial.print(bme.readHumidity());
		// Serial.println(" %");

		// Serial.print("Pressure = ");
		// Serial.print(bme.readPressure() / 100.0F);
		// Serial.println(" hPa");

		// Serial.print("Approx. Altitude = ");
		// Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
		// Serial.println(" m");

		sensors_event_t eventTemperature, eventHumidity, eventBaroPressure;
		bmeT->getEvent(&eventTemperature);
		bmeH->getEvent(&eventHumidity);
		bmeP->getEvent(&eventBaroPressure);

		Serial.print(F("Temperature = "));
		Serial.print(eventTemperature.temperature);
		Serial.println(" *C");

		Serial.print(F("Humidity = "));
		Serial.print(eventHumidity.relative_humidity);
		Serial.println(" %");

		Serial.print(F("Pressure = "));
		Serial.print(eventBaroPressure.pressure);
		Serial.println(" hPa");

		Serial.println();
		prevMillis = currMillis;
	}
}
