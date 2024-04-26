#include <Arduino.h>
#include "I2CScanner.h"
#include <Wire.h>

I2CScanner scanner;

void setup() 
{	
	Serial.begin(9600);
	while (!Serial) {};

	scanner.Init();
}

void loop() 
{
	scanner.Scan();
	delay(5000);
}