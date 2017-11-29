#include "max6675.h"
 
MAX6675 thermocouple(8, 9, 10);
// Max6675 module: SO on pin #8, SS on pin #9, CSK on pin #10 of Arduino UNO
 
void setup()
{
 // thermocouple.setOffset(0);
  // set offset for temperature measurement.
  Serial.begin(9600);
}
 
void loop()
{
  Serial.print(thermocouple.readCelsius(), 2);
  Serial.print(" C / ");
  Serial.print(thermocouple.readFahrenheit(), 2);
  Serial.print(" F / ");
  //Serial.print(thermocouple.readKelvin(), 2);
  //Serial.print(" Kn");
  Serial.println();
  delay(1000);
}
