// Program: I2C master reader template for multi-node Arduino I2C network
// Programmer: Hazim Bitar (techbitar.com)
// Date: March 30, 2014
// This example code is in the public domain.

#include <Wire.h>

#define PAYLOAD_SIZE 2 // how many bytes to expect from each I2C salve node
#define NODE_MAX 6 // maximum number of slave nodes (I2C addresses) to probe
#define START_NODE 2 // The starting I2C address of slave nodes
#define NODE_READ_DELAY 1000 // Some delay between I2C node reads

int nodePayload[PAYLOAD_SIZE];

void setup()
{
  Serial.begin(9600);  
  Serial.println("MASTER READER NODE");
  Serial.print("Maximum Slave Nodes: ");
  Serial.println(NODE_MAX);
  Serial.print("Payload size: ");
  Serial.println(PAYLOAD_SIZE);
  Serial.println("***********************");
  
  Wire.begin();        // Activate I2C link
}

void loop()
{
  for (int nodeAddress = START_NODE; nodeAddress <= NODE_MAX; nodeAddress++) { // we are starting from Node address 2
    Wire.requestFrom(nodeAddress, PAYLOAD_SIZE);    // request data from node#
    if(Wire.available() == PAYLOAD_SIZE) {  // if data size is avaliable from nodes
      for (int i = 0; i < PAYLOAD_SIZE; i++) nodePayload[i] = Wire.read();  // get nodes data
      for (int j = 0; j < PAYLOAD_SIZE; j++) Serial.println(nodePayload[j]);   // print nodes data   
      Serial.println("*************************");      
      }
    }
    delay(NODE_READ_DELAY);
}
