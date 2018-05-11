#include <Adafruit_MAX31865.h>
#include <Wire.h>
// Use software SPI: CS, DI, DO, CLK

#define DEBUG

#define RREF  430.0 
#define RNOMINAL  100.0 
#define NODE_ADDRESS 2 // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 4 // Number of bytes  expected to be received by the master I2C node

unsigned int tempdata; //[] = {0,0}; //store recent data globally so it can be sent whenever master node requests it
unsigned int speeddata;
Adafruit_MAX31865 max = Adafruit_MAX31865(8, 11, 12, 13);

void setup() {
#ifdef DEBUG
Serial.begin(115200);
Serial.println("Starting Wheel Speed and Gearbox Temperature Node in Debugging Mode");
#endif
max.begin(MAX31865_3WIRE);
Wire.begin(NODE_ADDRESS);  // Activate I2C network
Wire.onRequest(requestEvent); // call requestEvent() whenever master node asks for data
}

void loop() {

  updateTemp();
  //actually update speed here
  delay(100);
}

void requestEvent(){ //This function is called like an interrupt whenever master node calls requestFrom(NODE_ADDRESS)
   byte payload[4];
   payload[0] = tempdata;
   payload[1] = tempdata >>8;
   payload[2] = speeddata; 
   payload[3] = speeddata >> 8;
   //byte* payload = (byte*) & data[1]; //important conversion from unsigned int to byte array
   Wire.write(payload, PAYLOAD_SIZE);
//   #ifdef DEBUG
//   Serial.print((byte)payload[0]);
//   Serial.print("|");
//   Serial.println((byte)payload[1]);
//   Serial.println("requested");
//  #endif 
}

//void requestEvent(){ //This function is called like an interrupt whenever master node calls requestFrom(NODE_ADDRESS)
//  //send speed
//  byte* payload1 = (byte*) & data[0];
//  Serial.print((byte)payload1[0]);
//  Serial.print("|");
//  Serial.println((byte)payload1[1]);
//   
//  byte* payload2 = (byte*) & data[1];
//  Serial.print((byte)payload2[0]);
//  Serial.print("|");
//  Serial.println((byte)payload2[1]);
//  
//  byte* payload[PAYLOAD_SIZE*2];
//  payload[0] = payload1[0];
//  payload[1] = payload1[1];
//  payload[2] = payload2[0];
//  payload[3] = payload2[1];
//  
//  //memcpy(payload, payload1, PAYLOAD_SIZE);
//  //memcpy(payload+PAYLOAD_SIZE, payload2, PAYLOAD_SIZE);
//  
//  Serial.print((byte)payload[0]);
//  Serial.print("|");
//  Serial.print((byte)payload[1]);
//  Serial.print("|");
//  Serial.print((byte)payload[2]);
//  Serial.print("|");
//  Serial.println((byte)payload[3]);
//  
//  Wire.write((byte*)payload, PAYLOAD_SIZE*2);
//  
//  #ifdef DEBUG
//  Serial.println("requested");
//  #endif
//}

void updateTemp(){
  uint16_t  rtd = max.readRTD();
  float ratio = rtd;
  ratio /= 32768;
  float temp = max.temperature(100, RREF);
  tempdata = temp ; //max.temperature(100,RREF);
  #ifdef DEBUG
  //Serial.print("temp: ");
  //Serial.println(data[1]);
  //checkRTDFault();
  #endif 
}

void checkRTDFault(){
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


