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

//unsigned int tach = 0;
//unsigned int speedo = 0;
//unsigned int cvtTemp = 0;
//unsigned int gearBoxTemp = 0;

//unsigned int samples = 5;

//unsigned int tachCounter = 0;
//unsigned int speedoCounter = 0;
//unsigned int cvtTempCounter = 0;
//unsigned int gearBoxTempCounter = 0;

unsigned int recentTach;
unsigned int recentSpeedo;
unsigned int recentCvtTemp;
unsigned int recentGearBoxTemp;

const int maxTime = 30000;

unsigned long lastWriteTime = 0;

typedef struct {
  float sum;
  int count;
} average_data;

average_data tach;
average_data speedo;
average_data cvtTemp;
average_data gearBoxTemp;

void acceptSample(average_data *avg, float data) {
  avg -> sum += data;
  avg -> count++;
}

//acceptSample(&tach, tach_value);

float getAverage(average_data *avg) {

    float sum = avg -> sum;
    int n = avg -> count;
    return (sum/n);

}

void resetAverage(average_data *avg) {
  avg -> sum = 0;
  avg -> count = 0;
}

unsigned int receiveData(){
  byte payload[PAYLOAD_SIZE];
  for(byte i = 0; i < PAYLOAD_SIZE; i ++){
    payload[i] = Wire.read();
  }
  unsigned int data = *((unsigned int*)payload);
  return data;
}  

int wheelDia = 22;
int spokes = 6;

unsigned int convertToSpeed(unsigned int freq){
  //MPH:
  float circ = wheelDia * 3.1416;
  //(freq pulses/1 min)(1 rev/spokes pulses)(circ in/1 rev)(1 ft/12 in)(1 mi/5280 ft)(60 min/1 hr)
  float converter = (circ*60)/(spokes*12*5280);
  float speedMPH = round(freq * converter * 100)/100;
  return speedMPH;

}

/*unsigned int convertToRPM(unsigned int freq){
  //RPM:
  unsigned int RPM = freq * 60 * 2;
  return RPM;
}*/

void setup() {
  // put your setup code here, to run once:
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  tachDisp.begin(0x70);
  speedoDisp.begin(0x72);
  cvtTempDisp.begin(0x73);
  gearBoxTempDisp.begin(0x74);

  Wire.begin();        // Activate I2C link

}

void loop() {
  for (int nodeAddress = START_NODE; nodeAddress <= NODE_MAX; nodeAddress++) { // we are starting from Node address 2
    Wire.requestFrom(nodeAddress, PAYLOAD_SIZE);    // request data from node#
    if(Wire.available() == PAYLOAD_SIZE) {  // if data size is avaliable from nodes
      unsigned int data = receiveData();
      switch(nodeAddress) {
        case 2: //receive data from tach
          Serial.print("tach: ");
          recentTach = data;
          acceptSample(&tach, recentTach);
          Serial.println(recentTach);
          break;
        case 3: //receive data from speedo
          Serial.print("speedo: ");
          recentSpeedo = convertToSpeed(data);
          acceptSample(&speedo, recentSpeedo);
          Serial.println(recentSpeedo);
          break;
        case 4: //receive data from cvtTemp
          Serial.print("cvtTemp: ");
          recentCvtTemp = data;
          acceptSample(&cvtTemp, data);
          Serial.println(recentCvtTemp);
          break;
        case 5: //receive data from gearBoxTemp
          Serial.print("gearBoxTemp: ");
          recentGearBoxTemp = data;
          acceptSample(&gearBoxTemp, data);
          Serial.println(recentGearBoxTemp);
          break;
      }
      tachDisp.println(recentTach);
      tachDisp.writeDisplay();
      speedoDisp.println(recentSpeedo);
      speedoDisp.writeDisplay();
      cvtTempDisp.println(recentCvtTemp);
      cvtTempDisp.writeDisplay();
      gearBoxTempDisp.println(recentGearBoxTemp);
      gearBoxTempDisp.writeDisplay();

      if (millis() - lastWriteTime > maxTime) {
        getAverage(&tach);
        //write to sd card
        lastWriteTime = millis();
      }
    delay(500);
    }
  }
}
//    delay(NODE_READ_DELAY);
//    
//    int rollingAvgTach(){
//      int data = analogRead(0);
//      
//      tempRolling[samples - 1] = data; // the last element is the new value
//  
//      for(int i = 0; i < samples - 1; i ++){ // copy the last elements of the old array into the beginning of the new array
//        tempRolling[i] = rolling[i+1];
//      }
//  
//      for(int i = 0; i < samples; i ++){ // overwrite the old array with the new one
//       rolling[i] = tempRolling[i];
//      }
//      int sum = 0;
//      for(int i = 0; i < samples; i ++){ // sum the elements
//       sum += rolling[i];
//      }
//      int avg = sum/samples;
//  
//      printArray(rolling, samples);
//      Serial.print("Rolling Average: ");
//      Serial.println(avg);
//      Serial.println("*****");
//      delay(refreshRate);
//    }
//}


