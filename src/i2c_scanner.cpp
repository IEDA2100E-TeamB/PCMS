// REF: https://playground.arduino.cc/Main/I2cScanner/
#include "i2c_scanner.h"

static uint32_t prevMillis = 0;
static constexpr uint32_t SCAN_INTERVAL = 5000;

// -------- EXAMPLE OF SCANNER SETUP --------
void i2cScannerSetup()
{
	Wire.begin();
	Serial.begin(115200);
	Serial.println("\nI2C Scanner starting...");
}

// -------- EXAMPLE OF SCANNER LOOP --------
void i2cScannerLoop()
{
	uint32_t currMillis = millis();
	if (currMillis - prevMillis >= SCAN_INTERVAL) {
		byte address, error;
		int numDevices;
		Serial.println("Scanning...");
		numDevices = 0;
		for (address = 1; address < 127; address++) {
			Wire.beginTransmission(address);
			error = Wire.endTransmission();
			if (error == 0) {
				Serial.print("I2C device found at address 0x");
				if (address < 16) {
					Serial.print("0");
				}
				Serial.println(address, HEX);
				numDevices++;
			} else if (error == 4) {
				Serial.print("Unknow error at address 0x");
				if (address < 16) {
					Serial.print("0");
				}
				Serial.println(address, HEX);
			}
		}
		if (numDevices == 0) {
			Serial.println("No I2C devices found\n");
		} else {
			Serial.print(numDevices);
			Serial.println(" devices found\n");
		}
		// update time
		prevMillis = currMillis;
	}
}