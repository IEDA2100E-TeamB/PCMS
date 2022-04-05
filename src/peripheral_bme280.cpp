#include "peripheral_bme280.h"

// #define BME280_ADDR 0x76
#define SEALEVELPRESSURE_HPA (1013.25)

static Adafruit_BME280 bme;
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
}

float bme280_getTemperature_Celsius()
{
	return bme.readTemperature();
}

float bme280_getHumidity()
{
	return bme.readHumidity();
}

float bme280_getBaroPressure_hPa()
{
	return bme.readPressure() / 100.0F;
}

float bme280_getAltitude(float seaLevelPressure = SEALEVELPRESSURE_HPA)
{
	return bme.readAltitude(seaLevelPressure);
}

void bme280_print()
{
	// BUG sometimes cannot connect to sensor
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

		Serial.println();
		prevMillis = currMillis;
	}
}
