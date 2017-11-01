#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define PAYLOAD_SIZE 2 // how many bytes to expect from each I2C salve node
#define NODE_MAX 4 // maximum number of slave nodes (I2C addresses) to probe
#define START_NODE 2 // The starting I2C address of slave nodes
#define NODE_READ_DELAY 1 // Some delay between I2C node reads

Adafruit_7segment tachDisp = Adafruit_7segment();
Adafruit_7segment speedoDisp = Adafruit_7segment();
Adafruit_7segment cvtTempDisp = Adafruit_7segment();
Adafruit_7segment gearBoxTempDisp = Adafruit_7segment();

unsigned int tach = 0;
unsigned int speedo = 0;
unsigned int cvtTemp = 0;
unsigned int gearBoxTemp = 0;
int wheelDia = 22;

void setup() {
  // put your setup code here, to run once:
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  tachDisp.begin(0x70);
  speedoDisp.begin(0x71);
  cvtTempDisp.begin(0x72);
  gearBoxTempDisp.begin(0x73);

  Wire.begin();        // Activate I2C link

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int nodeAddress = START_NODE; nodeAddress <= NODE_MAX; nodeAddress++) { // we are starting from Node address 2
    Wire.requestFrom(nodeAddress, PAYLOAD_SIZE);    // request data from node#
    if(Wire.available() == PAYLOAD_SIZE) {  // if data size is avaliable from nodes
      unsigned int data = receiveData();
      switch(nodeAddress) {
        case 2: //receive data from tach
          Serial.print("tach: ");
          tach = convertToRPM(data);
          Serial.println(tach);
          break;
        case 3: //receive data from speedo
          Serial.print("speedo: ");
          speedo = convertToSpeed(data);
          Serial.println(speedo);
          break;
        case 4: //receive data from cvtTemp
          Serial.print("cvtTemp: ");
          cvtTemp = data;
          Serial.println(cvtTemp);
          break;
        case 5: //receive data from gearBoxTemp
          Serial.print("gearBoxTemp: ");
          gearBoxTemp = data;
          Serial.println(gearBoxTemp);
          break;
      }
      tachDisp.println(tach);
      tachDisp.writeDisplay();
      speedoDisp.println(speedo);
      speedoDisp.writeDisplay();
      cvtTempDisp.println(cvtTemp);
      cvtTempDisp.writeDisplay();
      gearBoxTempDisp.println(gearBoxTemp);
      gearBoxTempDisp.writeDisplay();
    delay(500);
    }
  }
    delay(NODE_READ_DELAY);
}

unsigned int receiveData(){
  byte payload[PAYLOAD_SIZE];
  for(byte i = 0; i < PAYLOAD_SIZE; i ++){
    payload[i] = Wire.read();
  }
  unsigned int data = *((unsigned int*)payload);
  return data;
}  
unsigned int convertToSpeed(unsigned int freq){

  //MPH:
  float circ = wheelDia * 3.1416;
  int speedMPH = (freq * 36 * circ)/633.6;
  return speedMPH;

}

unsigned int convertToRPM(unsigned int freq){

  //RPM:
  unsigned int RPM = freq * 60 * 2;
  return RPM;
  
}

