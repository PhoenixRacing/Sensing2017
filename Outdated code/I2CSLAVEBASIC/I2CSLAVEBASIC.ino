#include <Wire.h>
#include <Adafruit_MAX31865.h>

#define RREF  430.0 
#define RNOMINAL  100.0 
#define NODE_ADDRESS 2 // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 2 // Number of bytes  expected to be received by the master I2C node

unsigned int data; //store recent data globally so it can be sent whenever master node requests it
Adafruit_MAX31865 max = Adafruit_MAX31865(8, 11, 12, 13);


void requestEvent(){ //This function is called like an interrupt whenever master node calls requestFrom(NODE_ADDRESS)
  byte* payload = (byte*) & data; //important conversion from unsigned int to byte array
  Wire.write(payload, PAYLOAD_SIZE);
}

void setup() {
  Serial.begin(9600);
  Wire.begin(NODE_ADDRESS);  // Activate I2C network
  max.begin(MAX31865_3WIRE);
  Wire.onRequest(requestEvent); // call requestEvent() whenever master node asks for data
}

void loop() {
   data = max.temperature(100,RREF); // all that happens in loop() is updating the globals where the data is stored. There is no send() function
  Serial.print(data);
uint16_t  rtd = max.readRTD();
  uint8_t fault = max.readFault();
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    max.clearFault();
  }
}
