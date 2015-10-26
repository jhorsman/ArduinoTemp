// Temperature sensor
// Reads from TMP36 sensor
// Writes to serial


//TMP36 Pin Variables
int sensorPin = 0;	//the analog pin the TMP36's Vout (sense) pin is connected to
					//the resolution is 10 mV / degree centigrade with a
					//500 mV offset to allow for negative temperatures

#define aref_voltage 3.3

void setup() {
	// If you want to set the aref to something other than 5v
	analogReference(EXTERNAL);
	
	Serial.begin(9600);  //Start the serial connection with the computer
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

	delay(500);
}