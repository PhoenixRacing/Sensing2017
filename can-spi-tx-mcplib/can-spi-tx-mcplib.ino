// CAN Send Example
//

const byte dataLen = 4;

#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);     // Set CS to pin 10

void setup()
{
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

unsigned int realData[dataLen]={10,35,27,1022};


void loop()
{
  // send data:  (ID = 0x101, Standard CAN Frame, Data length in bytes, 'data' = array of data bytes to send)
  byte sndStat = CAN0.sendMsgBuf(0x101, 0, dataLen*sizeof(int), (uint8_t*)realData);
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  delay(100);   // send data per 100ms
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
