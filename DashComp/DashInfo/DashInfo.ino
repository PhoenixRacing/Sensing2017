#define DEBUG

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
/* Display segment layout:
     8
   -----
 3| 2  |7
  -----
4| 5  |6
 -----  .1

*/

uint8_t O = B00111111;
uint8_t L = B00111000;
uint8_t I = B00000110;
uint8_t n = B01010100;
uint8_t b = B01111100;
uint8_t A = B01110111;
uint8_t J = B00011110;

#define PAYLOAD_SIZE 2 // how many bytes to expect from each I2C salve node
#define NODE_MAX 4 // maximum number of slave nodes (I2C addresses) to probe
#define START_NODE 2 // The starting I2C address of slave nodes
//#define NODE_READ_DELAY 1 // Some delay between I2C node reads

const int refreshTime = 0;

Adafruit_7segment tachDisp = Adafruit_7segment();
Adafruit_7segment speedoDisp = Adafruit_7segment();
Adafruit_7segment cvtTempDisp = Adafruit_7segment();
Adafruit_7segment gearBoxTempDisp = Adafruit_7segment();

unsigned int recentTach;
float recentSpeedo;
float recentCvtTemp;
float recentGearBoxTemp;

const int maxTime = 10000;

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

unsigned int convertToRPM(unsigned int freq){
  //RPM:
  unsigned int RPM = freq*2;
  return RPM;
}

float convertToSpeed(unsigned int freq){
  //MPH:
  float circ = wheelDia * 3.1416;
  //(freq pulses/1 min)(1 rev/spokes pulses)(circ in/1 rev)(1 ft/12 in)(1 mi/5280 ft)(60 min/1 hr)
  float converter = (circ*60)/(spokes*12*5280);
  float speedMPH = round(freq * converter * 100)/100;
  return speedMPH;
}

float convertToTemp(unsigned int temp100){
  return temp100/100;
}



void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Starting Dash Display and Logger...");
#endif
  tachDisp.begin(0x70);
  speedoDisp.begin(0x72);
  cvtTempDisp.begin(0x73);
  gearBoxTempDisp.begin(0x74);

  Wire.begin();        // Activate I2C link

  tachDisp.writeDigitRaw(0,O);
  tachDisp.writeDigitRaw(1,L);
  tachDisp.writeDigitRaw(3,I);
  tachDisp.writeDigitRaw(4,n);
  speedoDisp.writeDigitRaw(0,b);
  speedoDisp.writeDigitRaw(1,A);
  speedoDisp.writeDigitRaw(3,J);
  speedoDisp.writeDigitRaw(4,A);
  cvtTempDisp.println(2017);
  gearBoxTempDisp.println(2018);

  tachDisp.writeDisplay();
  speedoDisp.writeDisplay();
  cvtTempDisp.writeDisplay();
  gearBoxTempDisp.writeDisplay();

  delay(3000);
  tachDisp.println(0);
  speedoDisp.println(0);
  cvtTempDisp.println(0);
  gearBoxTempDisp.println(0);

  tachDisp.writeDisplay();
  speedoDisp.writeDisplay();
  cvtTempDisp.writeDisplay();
  gearBoxTempDisp.writeDisplay();

}

void loop() {
  for (int nodeAddress = START_NODE; nodeAddress <= NODE_MAX; nodeAddress++) { // we are starting from Node address 2
    Wire.requestFrom(nodeAddress, PAYLOAD_SIZE);    // request data from node#
    if(Wire.available() == PAYLOAD_SIZE) {  // if data size is avaliable from nodes
      unsigned int data = receiveData();
      switch(nodeAddress) {
        case 2: //receive data from tach
          recentTach = convertToRPM(data);
          acceptSample(&tach, recentTach);
        #ifdef DEBUG
          Serial.print("tach: ");
          Serial.println(recentTach);
        #endif
          break;
        case 3: //receive data from speedo
          recentSpeedo = convertToSpeed(data);
          acceptSample(&speedo, recentSpeedo);
        #ifdef DEBUG
          Serial.print("speedo: ");
          Serial.println(recentSpeedo);
        #endif
          break;
        case 4: //receive data from cvtTemp
          recentCvtTemp = convertToTemp(data);
          acceptSample(&cvtTemp, recentCvtTemp);
        #ifdef DEBUG
          Serial.print("cvtTemp: ");
          Serial.println(recentCvtTemp);
        #endif
          break;
        case 5: //receive data from gearBoxTemp
          recentGearBoxTemp = convertToTemp(data);
          acceptSample(&gearBoxTemp, recentGearBoxTemp);
        #ifdef DEBUG
          Serial.print("gearBoxTemp: ");
          Serial.println(recentGearBoxTemp);
        #endif
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
        unsigned int logTach = round(getAverage(&tach));
        float logSpeedo = round(getAverage(&speedo)*100)/100;
        float logCvt = round(getAverage(&cvtTemp)*100)/100;
        float logGb = round(getAverage(&gearBoxTemp)*100)/100;
        //get RTC time
        //build log line
        //write to sd card
      #ifdef DEBUG
        Serial.println("Writing line to SD card: ");
      #endif
        lastWriteTime = millis();
        resetAverage(&tach);
        resetAverage(&speedo);
        resetAverage(&cvtTemp);
        resetAverage(&gearBoxTemp);
      }
    delay(refreshTime);
    }
  }
}
