#include <Adafruit_MAX31865.h>

#define DEBUG

#include <Wire.h>
#include <mcp_can.h>
#include <SPI.h>

Adafruit_MAX31865 max = Adafruit_MAX31865(8, 11, 12, 13); //SPI: CS, DI, DO, CLK

#define TACH_NODE 2
#define SPEEDO_NODE 3

#define PAYLOAD_SIZE 2 // how many bytes to expect from each I2C slave node
#define NODE_MAX 3 // The highest I2C slave node address to probe
#define START_NODE 2 // The lowest I2C slave node address to probe
#define RREF      430.0 //we have PT100, resistor reference 
#define RNOMINAL  100.0 // The 'nominal' 0-degrees-C resistance of the sensor: 100.0 for PT100, 1000.0 for PT1000


#define DATA_LEN 4

MCP_CAN CAN0(10);     // Set CS to pin 10


void setup() {
  // set to 2WIRE or 4WIRE as necessary //begin CAN

  
#ifdef DEBUG
  Serial.begin(9600);
#endif

#ifndef DEBUG
  CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ);
#endif

#ifdef DEBUG
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
  Serial.println("MCP2515 Initialized Successfully!");
  }
  else {
    Serial.println("Error Initializing MCP2515...");
  }
#endif

  CAN0.setMode(MCP_NORMAL);
  

  Wire.begin();
  max.begin(MAX31865_3WIRE);
}

unsigned int realData[] = {0, 0, 0, 0}; //{tach,sped,cvt,gb}

void loop() {

  uint16_t rtd = max.readRTD();
  Serial.println(int(rtd));
  //Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("Ratio = "); Serial.println(ratio,8);
  Serial.print("Resistance = "); Serial.println(RREF*ratio,8);
  Serial.print("Temperature = "); Serial.println(max.temperature(RNOMINAL, RREF));
  unsigned int Resistance = RREF*ratio;  //changed from floats because of the warning below
  unsigned int temp = max.temperature(RNOMINAL, RREF);

  realData[2] = temp +1; 
  Serial.println(temp);
//  uint8_t fault = max.readFault();
//  checkFaults(fault); 
  
  Wire.requestFrom(TACH_NODE, PAYLOAD_SIZE);//update tach
  if (Wire.available()) { // if data size is avaliable from node
    realData[0] = receiveData();
    #ifdef DEBUG
      Serial.print("tach:\t");
      Serial.println(realData[0]);
    #endif
  }
  
  Wire.requestFrom(SPEEDO_NODE, PAYLOAD_SIZE);//update speedo
  if (Wire.available()) { // if data size is avaliable from node
    realData[1] = receiveData();
    #ifdef DEBUG
      Serial.print("speedo:\t");
      Serial.println(realData[1]);
    #endif
  }
  delay(1000);
  //update CVT Temp here:
  //realData[2] = someStuff

  //update GB Temp here:
  //realData[3] = someOtherStuff

  byte sndStat = CAN0.sendMsgBuf(0x101, 0, DATA_LEN*sizeof(int), (uint8_t*)realData); //this sends the whole realData array
  #ifdef DEBUG
    if(sndStat == CAN_OK){
      Serial.println("Message Sent Successfully!");
    } else {
      Serial.println("Error Sending Message...");
    }
  #endif
  
}

unsigned int receiveData() {
  byte payload[PAYLOAD_SIZE];
  for (byte i = 0; i < PAYLOAD_SIZE; i ++) {
    payload[i] = Wire.read();
  }
  unsigned int data = *((unsigned int*)payload);//important conversion from byte array back to unsigned int
  return data;
}

void checkFaults(uint8_t fault){
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
