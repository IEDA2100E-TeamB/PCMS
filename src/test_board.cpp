#include "test_board.hpp"

// variables for ledBlinkWithoutDelay()
int ledState = LOW; // ledState used to set the LED
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
uint32_t previousMillis = 0; // will store last time LED was updated
constexpr long ledBlinkInterval = 1000; // interval at which to blink (milliseconds)

// variables for ledFade()
int ledBrightness = 0; // how bright the LED is
int ledFadeAmount = 5; // how many points to fade the LED by

// variables for serialEvent)
String inputString = ""; // a String to hold incoming data
bool stringComplete = false; // whether the string is complete

// EXAMPLE OF TESTS
// void setup()
// {
// 	// put your setup code here, to run once:

// 	Serial.begin(9600);
// 	// while (!Serial) {
// 	// 	; // wait for serial port to connect. Needed for native USB port only
// 	// }
// 	Serial.println("serial setup done!");

// 	pinMode(LED_BUILTIN, OUTPUT);

// 	inputString.reserve(200); // reserve 200 bytes for the inputString:
// }

// void loop()
// {
// 	// put your main code here, to run repeatedly:

// 	// ledBlink();
// 	// ledBlinkWithoutDelay();
// 	ledFade();
// 	// ledDimmer();
// 	// printASCII();
// 	// print the string when a newline arrives:
// 	if (stringComplete) {
// 		Serial.println(inputString);
// 		// clear the string:
// 		inputString = "";
// 		stringComplete = false;
// 	}
// }

void ledBlink(void)
{
	// blink for 10 seconds
	// digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
	delay(1000); // wait for a second
	// digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
	delay(1000); // wait for a second
}

void ledBlinkWithoutDelay(void)
{
	// check to see if it's time to blink the LED; that is, if the difference
	// between the current time and last time you blinked the LED is bigger than
	// the interval at which you want to blink the LED.
	uint32_t currentMillis = millis();

	if (currentMillis - previousMillis >= ledBlinkInterval) {
		// save the last time you blinked the LED
		previousMillis = currentMillis;

		// if the LED is off turn it on and vice-versa:
		if (ledState == LOW) {
			ledState = HIGH;
		} else {
			ledState = LOW;
		}

		// set the LED with the ledState of the variable:
		// digitalWrite(LED_BUILTIN, ledState);
	}
}

void ledFade(void)
{
	// set the brightness of pin 9:
	// analogWrite(LED_BUILTIN, ledBrightness);

	// change the brightness for next time through the loop:
	ledBrightness = ledBrightness + ledFadeAmount;

	// reverse the direction of the fading at the ends of the fade:
	if (ledBrightness <= 0 || ledBrightness >= 255) {
		ledFadeAmount = -ledFadeAmount;
	}

	// wait for 20 milliseconds to see the dimming effect
	delay(20);
}

void ledDimmer(void)
{
	byte brightness;

	// check if data has been sent from the computer:
	if (Serial.available()) {
		// read the most recent byte (which will be from 0 to 255):
		brightness = Serial.parseInt();
		Serial.readString(); // catch '\r' and '\n'
		// Serial.println(brightness); // for debugging
		// set the brightness of the LED:
		if (brightness != '\r' && brightness != '\n') {
			// analogWrite(LED_BUILTIN, brightness);
		}
	}
}

void printASCII(void)
{
	// first visible ASCIIcharacter '!' is number 33:
	// you can also write ASCII characters in single quotes.
	// for example, '!' is the same as 33, so you could also use this:
	// int thisByte = '!';

	for (int thisByte = 33; thisByte < 127; thisByte++) {
		// prints value unaltered, i.e. the raw binary version of the byte.
		// The Serial Monitor interprets all bytes as ASCII, so 33, the first number,
		// will show up as '!'
		Serial.write(thisByte);

		Serial.print(", dec: ");
		// prints value as string as an ASCII-encoded decimal (base 10).
		// Decimal is the default format for Serial.print() and Serial.println(),
		// so no modifier is needed:
		Serial.print(thisByte);
		// But you can declare the modifier for decimal if you want to.
		// this also works if you uncomment it:

		// Serial.print(thisByte, DEC);

		Serial.print(", hex: ");
		// prints value as string in hexadecimal (base 16):
		Serial.print(thisByte, HEX);

		Serial.print(", oct: ");
		// prints value as string in octal (base 8);
		Serial.print(thisByte, OCT);

		Serial.print(", bin: ");
		// prints value as string in binary (base 2) also prints ending line break:
		Serial.println(thisByte, BIN);

		// if printed last visible character '~' or 126, stop:
		// if (thisByte == 126) { // you could also use if (thisByte == '~') {
		// 	// This loop loops forever and does nothing
		// 	while (true) {
		// 		continue;
		// 	}
		// }
		// go on to the next character
	}
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent(void)
{
	while (Serial.available()) {
		// get the new byte:
		char inChar = (char)Serial.read();
		// add it to the inputString:
		inputString += inChar;
		// if the incoming character is a newline, set a flag so the main loop can
		// do something about it:
		if (inChar == '\n') {
			stringComplete = true;
		}
	}
}
