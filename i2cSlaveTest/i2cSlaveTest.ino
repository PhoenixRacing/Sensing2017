const int out = 13;
const int highTime = 15;

#include <Wire.h>

#define NODE_ADDRESS 3  // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 2 // Number of bytes  expected to be received by the master I2C node

byte nodePayload[PAYLOAD_SIZE];

void setup(){
  Serial.begin(9600);
  pinMode(out, OUTPUT);

  Serial.begin(9600);
  Serial.println("SLAVE SENDER NODE");
  Serial.print("Node address: ");
  Serial.println(NODE_ADDRESS);
  Serial.print("Payload size: ");
  Serial.println(PAYLOAD_SIZE);
  Serial.println("***********************");

  Wire.begin(NODE_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // Request attention of master node
}

void loop(){
  int val = analogRead(0);
  int freq = map(val, 0, 1023, 5, 50);
  Serial.println(freq);
  digitalWrite(out, HIGH);
  delay(highTime);
  digitalWrite(out, LOW);
  int delayTime = 1000/freq - highTime;
  delay(delayTime);

  delay(100);
  nodePayload[0] = NODE_ADDRESS; // I am sending Node address back.  Replace with any other data
  nodePayload[1] = analogRead(A0)/4; // Read A0 and fit into 1 byte. Replace this line with your sensor value
  //Serial.readBytes(nodePayload(PAYLOAD_SIZE, [1]);
}

void requestEvent()
{
  Wire.write(nodePayload,PAYLOAD_SIZE);
  Serial.print("Sensor value: ");  // for debugging purposes.
  Serial.println(nodePayload[1]); // for debugging purposes.
}
