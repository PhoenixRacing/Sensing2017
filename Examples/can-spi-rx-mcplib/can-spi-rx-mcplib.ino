// CAN Receive Example

#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId = 0x101;
const byte dataLen = 4;
uint8_t rxBuf[dataLen*sizeof(int)];         //raw data from CAN
unsigned int realData[dataLen];             //data from CAN converted back to ints
char msgString[128];                        // Array to store serial string
#define CAN0_INT 2                          // Set INT to pin 2
MCP_CAN CAN0(10);                           // Set CS to pin 10

void setup()
{
  Serial.begin(115200);
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data. //makes the Message Sent successfully on the RX side. 
  pinMode(CAN0_INT, INPUT);                     // Configuring pin for /INT input
 }

void loop()
{
  if(!digitalRead(CAN0_INT))                    // If CAN0_INT pin is low, read receive buffer
  { 
    CAN0.readMsgBuf(&rxId, &dataLen, rxBuf);
    memcpy(realData,rxBuf,4*sizeof(int));
    Serial.print(realData[0]);
    for(byte i = 1; i<dataLen; i++){
      Serial.print(", ");
      Serial.print(realData[i]);
    }
    Serial.println();
  }
}
          
    /*if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits) by taking the bitwise AND of the rxId and 
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), dataLen); // sprintf () is used to store formatted data as a string
      sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, dataLen);

    Serial.print(msgString);
  
    if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);

    } else {                     //we're not remote requesting, we're just sending, so this:
      memcpy(realData,rxBuf,4*sizeof(int));
      //for(byte i = 0; i<len; i++){ //problem is that len = 0, so we never go through this for loop. 
        //sprintf(msgString, " 0x%.2X", rxBuf[i]);

      for(byte i = 0; i<dataLen; i++){ //problem is that len = 0, so we never go through this for loop. 
        //sprintf(msgString, " %d", realData[i]);
        Serial.print(realData[i]);
        Serial.print(", ");
      }
      Serial.println();
    }
        
//    Serial.println();
  }
}
*/
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
