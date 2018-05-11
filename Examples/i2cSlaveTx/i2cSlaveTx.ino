#include <Wire.h>

#define NODE_ADDRESS 2 // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 2 // Number of bytes  expected to be received by the master I2C node

unsigned int data; //store recent data globally so it can be sent whenever master node requests it

void setup() {
  Serial.begin(9600);

  Wire.begin(NODE_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // call requestEvent() whenever master node asks for data
}

void loop() {
  data = analogRead(0); // all that happens in loop() is updating the globals where the data is stored. There is no send() function
}

void requestEvent(){ //This function is called like an interrupt whenever master node calls requestFrom(NODE_ADDRESS)
  byte* payload = (byte*) & data; //important conversion from unsigned int to byte array
  Wire.write(payload, PAYLOAD_SIZE);
}
