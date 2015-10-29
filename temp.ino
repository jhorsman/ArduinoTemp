/* 
 * Temperature sensor
 *
 * Reads from TMP36 sensor
 * Displays on 16x2 display
 * Temperature unit Celtius/Fahrenheit can be toggled with a button
 * Writes to serial
 *
 * TMP36 Temperature sensor
 * the analog pin the TMP36's Vout (sense) pin is connected to an 
 * analog input.
 * The resolution is 10 mV / degree centigrade with a
 * 500 mV offset to allow for negative temperatures
 * 
 * 16x2 LCD display using LiquidCrystal library
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * +5 and ground via 0-10K resistor to VO pin (pin 3)
 */


//TMP36 pin
const int sensorPin = 0;	
					
//button pin
const int buttonPin = 7;
					
//set aref_voltage to calibrate analog input
#define aref_voltage 3.3

//include the library code:
#include <LiquidCrystal.h>

//initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//default temperature unit (C or F) 
String tempUnit = "C";

int buttonState ;
int lastButtonState = LOW;
int lastDebounceTime = 0;

// button debounce time; increase if the output flickers
const long debounceDelay = 50;	

void setup() {
	//set the aref to the onboard 3.3 voltage
	analogReference(EXTERNAL);

	//set the button pin
    pinMode(buttonPin, INPUT);
	
	Serial.begin(9600);  //Start the serial connection with the computer
	
	//set up the LCD's number of columns and rows:
	lcd.begin(16, 2);

	lcd.setCursor(1,0);
	lcd.print(" temperature");
}

void loop() {
	int buttonReading = digitalRead(buttonPin);
	if(buttonReading != lastButtonState) {
		lastDebounceTime = millis();
	}

	if(millis() - lastDebounceTime > debounceDelay) {
		if(buttonReading != buttonState) {
			buttonState = buttonReading;
			if(buttonState == HIGH) {
				if (tempUnit == "C") {
					tempUnit = "F";
				} else if (tempUnit == "F") {
					tempUnit = "C";
				}		
			}
		}
	}
	lastButtonState = buttonReading;
	
	//getting the voltage reading from the temperature sensor
	int analogReading = analogRead(sensorPin);  
 
	// converting that reading to voltage, for 3.3v arduino use 3.3
	float voltage = analogReading * aref_voltage;
	voltage /= 1024.0; 
 
	// now print out the temperature
	//converting from 10 mv per degree wit 500 mV offset
	//to degrees ((voltage - 500mV) times 100)
	float temperatureC = (voltage - 0.5) * 100 ;  
 
	// now convert to Fahrenheit
	float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

	String displayTemperature;
	if(tempUnit == "C")
	{
		displayTemperature = String(temperatureC) + " C";
		Serial.println(String(temperatureC) + " C");

	} else {
		displayTemperature = String(temperatureF) + " F";
		Serial.println(String(temperatureF) + " F");
	}
	lcd.setCursor(0, 1);
	lcd.print(displayTemperature + "     ");
	
	delay(50);
}