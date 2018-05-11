//cvt temp "censor" data half accomplishes what you want! 
#include <Wire.h> //for i2c pins 

void setup() {
  // put your setup code here, to run once:
  Wire.begin(90);                // factory default is 5A in hex, 90 in decimal
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
}
