/* 
 * Temperature sensor
 * Reads from TMP36 sensor
 * Displays on 16x2 display
 * Writes to serial
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


//TMP36 Pin Variables
int sensorPin = 0;	//the analog pin the TMP36's Vout (sense) pin is connected to
					//the resolution is 10 mV / degree centigrade with a
					//500 mV offset to allow for negative temperatures

// set aref_voltage to calibrate analog input
#define aref_voltage 3.3

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
	// If you want to set the aref to something other than 5v
	analogReference(EXTERNAL);
	
	Serial.begin(9600);  //Start the serial connection with the computer
	
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);

	lcd.setCursor(1,0);
	lcd.print(" temperature");
}

void loop() {
	//getting the voltage reading from the temperature sensor
	int reading = analogRead(sensorPin);  
 
	// converting that reading to voltage, for 3.3v arduino use 3.3
	float voltage = reading * aref_voltage;
	voltage /= 1024.0; 
 
	// print out the voltage
	Serial.print(voltage); Serial.println(" volts");
 
	// now print out the temperature
	//converting from 10 mv per degree wit 500 mV offset
	//to degrees ((voltage - 500mV) times 100)
	float temperatureC = (voltage - 0.5) * 100 ;  
	Serial.print(temperatureC); Serial.println(" C");
 
	// now convert to Fahrenheit
	float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
	Serial.print(temperatureF); Serial.println(" F");

	lcd.setCursor(0, 1);
	lcd.print(temperatureC);
	lcd.print("C  ");
	lcd.setCursor(9, 1);
	lcd.print(temperatureF);
	lcd.print("F      ");
	
	delay(500);
}