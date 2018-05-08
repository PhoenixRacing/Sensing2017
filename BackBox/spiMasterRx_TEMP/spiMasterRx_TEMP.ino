#include <Adafruit_MAX31865.h>

#define DEBUG

#include <Wire.h>
#include <mcp_can.h>
#include <SPI.h>

#define TACH_NODE 3
#define SPEEDO_RTD_NODE 2

#define SPEEDO_POS 0
#define TACH_POS 1
#define CVT_POS 2
#define GEARBOX_POS 3

#define PAYLOAD_SIZE 2 // how many bytes to expect for each data point from each I2C slave node


#define DATA_LEN 4

MCP_CAN CAN0(10);     // Set CS to pin 10


void setup() {
  
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println("Hello World!");
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
}

unsigned int realData[] = {0, 0, 0, 0}; //{tach,sped,cvt,gb}

void loop() {
  
  Wire.requestFrom(TACH_NODE, PAYLOAD_SIZE);//update tach
  if (Wire.available()) { // if data size is avaliable from node
    receiveData(1);
//    unsigned int* newData = receiveData(1);
//    realData[TACH_POS] = newData[0];
    #ifdef DEBUG
      Serial.print("Tach:\t");
      Serial.println(realData[TACH_POS]);
    #endif
  }
  
  Wire.requestFrom(SPEEDO_RTD_NODE, PAYLOAD_SIZE*2);//update speedo
  if (Wire.available()) { // if data size is avaliable from node
    receiveData(2);
    
    #ifdef DEBUG
      Serial.print("Speedo:\t");
      Serial.println(realData[SPEEDO_POS]);
      Serial.print("Gearbx:\t");
      Serial.println(realData[GEARBOX_POS]);
    #endif
  }
  
  //update CVT Temp here:
  realData[CVT_POS] = 1;
  #ifdef DEBUG
    Serial.print("CVT:\t");
    Serial.println(realData[CVT_POS]);
  #endif

  byte sndStat = CAN0.sendMsgBuf(0x101, 0, DATA_LEN*sizeof(int), (uint8_t*)realData); //this sends the whole realData array
  #ifdef DEBUG
    if(sndStat == CAN_OK){
      Serial.println("Message Sent Successfully!");
    } else {
      Serial.println("Error Sending Message...");
    }
  #endif
  delay(500);
}

//unsigned int receiveData() {
//  byte payload[PAYLOAD_SIZE];
//  for (byte i = 0; i < PAYLOAD_SIZE; i ++) {
//    payload[i] = Wire.read();
//  }
//  unsigned int data = *((unsigned int*)payload);//important conversion from byte array back to unsigned int
//  return data;
//}

void receiveData(int payloads) {
  
  byte payload[PAYLOAD_SIZE*payloads];
  for (byte i = 0; i < PAYLOAD_SIZE*payloads; i ++) {
    payload[i] = Wire.read();
  }
  
  if(payloads == 1){
    realData[TACH_POS] = *((unsigned int*)payload);
    return;
  }
  
  byte payload1[PAYLOAD_SIZE];
  payload1[0] = payload[0];
  payload1[1] = payload[1];
  realData[SPEEDO_POS] = *((unsigned int*)payload1);

  byte payload2[PAYLOAD_SIZE];
  payload2[0] = payload[2];
  payload2[1] = payload[3];
  realData[GEARBOX_POS] = *((unsigned int*)payload2);
}
