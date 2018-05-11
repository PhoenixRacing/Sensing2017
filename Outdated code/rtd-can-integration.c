//This is for integration of the back section.
#include <Adafruit_MAX31865.h>
#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);     // Set CS to pin 10
const byte dataLen = 4;

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 max = Adafruit_MAX31865(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 max = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit MAX31865 PT100 Sensor Test!");

  max.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary

// Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
else Serial.println("Error Initializing MCP2515...");

CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

unsigned int realData[dataLen]={rtd, ratio, temp}; //from can

void loop() {
  uint16_t rtd = max.readRTD();

  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("Ratio = "); Serial.println(ratio,8);
  Resistance = RREF*ratio;
  Serial.print("Resistance = "); Serial.println(Resistance,8);
  temp = max.temperature(RNOMINAL, RREF)
  Serial.print("Temperature = "); Serial.println(temp);

  // from CAN:
  // send data:  (ID = 0x101, Standard CAN Frame, Data length in bytes, 'data' = array of data bytes to send)
    byte sndStat = CAN0.sendMsgBuf(0x101, 0, dataLen*sizeof(int), (uint8_t*)realData);
    if(sndStat == CAN_OK){
      Serial.println("Message Sent Successfully!");
    } else {
      Serial.println("Error Sending Message...");
    }
    delay(100);   // send data per 100ms

  // Check and print any faults
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

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
