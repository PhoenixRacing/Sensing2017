#include <Adafruit_MAX31865.h>

#define DEBUG

#include <Wire.h>
#include <mcp_can.h>
#include <SPI.h>
#include <Adafruit_MLX90614.h>

#define TACH_NODE 3
#define SPEEDO_RTD_NODE 2
#define IR_NODE 90

#define SPEEDO_POS 0
#define TACH_POS 1
#define CVT_POS 2
#define GEARBOX_POS 3

#define PAYLOAD_SIZE 2 // how many bytes to expect for each data point from each I2C slave node
#define DATA_LEN 4
const int refreshRate = 500;
MCP_CAN CAN0(10);     // Set CS to pin 10

Adafruit_MLX90614 mlx = Adafruit_MLX90614(); //for the IR temp sensor

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
  mlx.begin();
}

unsigned int realData[] = {0, 0, 0, 0}; //{tach,sped,cvt,gb}

void loop() {

  Wire.requestFrom(TACH_NODE, PAYLOAD_SIZE);//update tach
  if (Wire.available()) { // if data size is avaliable from node
    realData[TACH_POS] = receiveData();
//    unsigned int* newData = receiveData(1);
//    realData[TACH_POS] = newData[0];
    #ifdef DEBUG
      Serial.print("Tach:\t");
      Serial.println(realData[TACH_POS]);
    #endif
  }

  Wire.requestFrom(SPEEDO_RTD_NODE, PAYLOAD_SIZE*2);//update speedo
  if (Wire.available()) { // if data size is avaliable from node
    realData[GEARBOX_POS] = receiveData();
    realData[SPEEDO_POS] = 2576;
//    unsigned int* newData = receiveData(2);
//    realData[GEARBOX_POS] = newData[1];
//    realData[SPEEDO_POS] = newData[0];

    #ifdef DEBUG
      Serial.print("Speedo:\t");
      Serial.println(realData[SPEEDO_POS]);
      Serial.print("Gearbx:\t");
      Serial.println(realData[GEARBOX_POS]);
    #endif
  }

  ////// IR sensor sending
  realData[CVT_POS] = round(mlx.readObjectTempC());
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

unsigned int receiveData() {
  byte payload[PAYLOAD_SIZE];
  for (byte i = 0; i < PAYLOAD_SIZE; i ++) {
    payload[i] = Wire.read();
  }
  unsigned int data = *((unsigned int*)payload);//important conversion from byte array back to unsigned int
  return data;
}

//unsigned int* receiveData(int payloads) {
//
//  unsigned int* dataPointer;
//
//  byte* payload[PAYLOAD_SIZE*payloads];
//  for (byte i = 0; i < PAYLOAD_SIZE*payloads; i ++) {
//    payload[i] = Wire.read();
//  }
//  byte* temp1[PAYLOAD_SIZE];
//  temp1[0] = payload[0];
//  temp1[1] = payload[1];
//  Serial.print((byte)temp1[0]);
//  Serial.print("|");
//  Serial.println((byte)temp1[1]);
//  byte* temp2[PAYLOAD_SIZE];
//  temp2[0] = payload[2];
//  temp2[1] = payload[3];
//  Serial.print((byte)temp2[0]);
//  Serial.print("|");
//  Serial.println((byte)temp2[1]);
//  //memcpy(&temp2,(byte*)payload+PAYLOAD_SIZE,PAYLOAD_SIZE);
//  dataPointer[0] = *((unsigned int*)temp1);
//  dataPointer[1] = *((unsigned int*)temp2);
//  return dataPointer;
//
//  for(int i = 0; i < payloads; i ++){
//    byte payload[PAYLOAD_SIZE];
//    for (byte j = 0; j < PAYLOAD_SIZE; j ++) {
//      payload[j] = Wire.read();
//      //Serial.print((byte)payload[j]);
//      //Serial.print("|");
//    }
//    dataPointer[i] = *((unsigned int*)payload);//important conversion from byte array back to unsigned int
//  }
//  return dataPointer;
//}
