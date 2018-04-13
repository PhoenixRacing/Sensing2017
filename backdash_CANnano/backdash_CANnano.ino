#include <Wire.h>
#include <Adafruit_MAX31865.h>
#include <mcp_can.h> // library from: https://github.com/coryjfowler/MCP_CAN_lib
#include <SPI.h>

#define PAYLOAD_SIZE 2 // how many bytes to expect from each I2C salve node
#define NODE_MAX 6 // maximum number of slave nodes (I2C addresses) to probe
#define START_NODE 3 // The starting I2C address of slave nodes
#define NODE_READ_DELAY 1000 // Some delay between I2C node reads

#define RREF      430.0 //we have PT100, resistor reference 
#define RNOMINAL  100.0 // The 'nominal' 0-degrees-C resistance of the sensor: 100.0 for PT100, 1000.0 for PT1000

int nodePayload[PAYLOAD_SIZE];
unsigned int realData; 

MCP_CAN CAN0(10);     // Set CS to pin 10
const byte dataLen = 4;

Adafruit_MAX31865 max = Adafruit_MAX31865(5, 6, 7, 8); //SPI: CS, DI, DO, CLK
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 max = Adafruit_MAX31865(10);                     //feel like this shouldn't be commented out- how is this working?

void setup()
{
  Serial.begin(115200);
  Serial.println("MASTER READER NODE");
  Wire.begin();        // Activate I2C link

  Serial.println("Adafruit MAX31865 PT100 Sensor Test!");
  max.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary //begin CAN

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");
  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted 
}

void loop()
{
    for (int nodeAddress = START_NODE; nodeAddress <= NODE_MAX; nodeAddress++) { // we are starting from Node address 2
    Wire.requestFrom(nodeAddress, PAYLOAD_SIZE);    // request data from node#
    if(Wire.available() == PAYLOAD_SIZE) {  // if data size is avaliable from nodes
      for (int i = 0; i < PAYLOAD_SIZE; i++) nodePayload[i] = Wire.read();  // get nodes data
      for (int j = 0; j < PAYLOAD_SIZE; j++) Serial.println(nodePayload[j]);   // print nodes data   
      //the data we got from the i2c is nodePayload
      for (int k = 0; k < PAYLOAD_SIZE; k++) realData = nodePayload[k];   //pass to i2c     
      }
    }
    delay(NODE_READ_DELAY);
  Serial.print(realData);

  uint16_t rtd = max.readRTD();
  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("Ratio = "); Serial.println(ratio,8);
  Serial.print("Resistance = "); Serial.println(RREF*ratio,8);
  Serial.print("Temperature = "); Serial.println(max.temperature(RNOMINAL, RREF));
  unsigned int Resistance = RREF*ratio;  //changed from floats because of the warning below
  unsigned int temp = max.temperature(RNOMINAL, RREF);
  // can we send as floats instead? 
   //realData[dataLen]={rtd, Resistance, temp}; //from can /// warning: narrowing conversion of '(((double)ratio) * 4.3e+2)' from 'double' to 'unsigned int' inside { } [-Wnarrowing]

  // send data:  (ID = 0x101, Standard CAN Frame, Data length in bytes, 'data' = array of data bytes to send)
  byte sndStat = CAN0.sendMsgBuf(0x101, 0, dataLen*sizeof(int), (uint8_t*)realData);
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  delay(100);   // send data per 100ms

  // Check and print any faults
  //rtd specific - perhaps make the fourth field in the send array the error # (aka 1 = high threshold, 2 = low threshold, etc)
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
  Serial.println();
  delay(1000); 
}

