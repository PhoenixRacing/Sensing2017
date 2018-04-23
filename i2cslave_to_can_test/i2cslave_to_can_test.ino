// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.
int potIn = A0;
//int resolution; 
const byte dataLen = 4;

#include <Wire.h>

byte b;

void setup() {
  Serial.begin(9600);
  pinMode(potIn, INPUT);
  Wire.begin(8);                // join i2c bus with address #8
 // Wire.beginTransmission(8);
  Wire.onRequest(requestEvent); // register event
  Serial.println("setup");
}

int potRead;
char buffer[2];


void loop() {
  delay(100);
  //potRead = analogRead(potIn);  
  //b = (byte) potRead; 
  //Serial.print("Pot: ");  
  //Serial.println(b);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  //Wire.write(buffer, 2);

  potRead = analogRead(potIn);
  Serial.println("request");
  //Wire.write(byte(potRead));
  String b;
  char c[5];

  b = (String)potRead;
  b.toCharArray(c, 5);
  Wire.write(c);
  Serial.println(c);
  //}
   
//  I2C_writeAnything(potRead);
  //Wire.write(potRead); // respond with message of 6 bytes
  // as expected by master
  //Serial.println("requested from Master");

}
