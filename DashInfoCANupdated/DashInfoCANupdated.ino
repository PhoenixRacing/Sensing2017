/*
 *  - Check for data from CAN --> for the time being just if(True) {
 *  --> update averages --> acceptSample(&tach, analogRead(1)) (inside if statement)
 *  - write to displays
 *  - check if it's been long enough since SD write
 *  --> write to SD --> read RTC
 *  - clear averages
 *  
 *               AT REAR | AT DASH | DISPLAY
 * Wheel Speed | *100    | /100    | 0-40mph
 * Tach        | *1      | *1      | 1000-4000
 * GB Temp     | *100    | /100    | 10-120 C
 * CVT Temp    | *100    | /100    | 10-120 C
 */

#define DEBUG

/*ERROR CODES:
E 01: RTC failed initialization
E 02: RTC time has been lost
E 03: SD failed initialization
E 04: File creation failed
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>
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
uint8_t E = B01111001;
uint8_t r = B01010000;

RTC_DS3231 rtc;
File logFile;
char fileName[13];
boolean logFlag = false;

#define BUTTON_PIN 2 //logger button pin 2

const int refreshTime = 100;

typedef struct {
  float sum;
  int count;
} average_data;

average_data tach;
average_data speedo;
average_data cvtTemp;
average_data gearBoxTemp;

unsigned int recentData[4];

void acceptSample(average_data *avg, float data) {
  avg -> sum += data;
  avg -> count++;
}

float getAverage(average_data *avg) {
    float sum = avg -> sum;
    int n = avg -> count;
    return (sum/n);
}

void resetAverage(average_data *avg) {
  avg -> sum = 0;
  avg -> count = 0;
}

Adafruit_7segment tachDisp = Adafruit_7segment();
Adafruit_7segment speedoDisp = Adafruit_7segment();
Adafruit_7segment cvtTempDisp = Adafruit_7segment();
Adafruit_7segment gearBoxTempDisp = Adafruit_7segment();

void initializeDisplays(){
  tachDisp.begin(0x70);
  speedoDisp.begin(0x72);
  cvtTempDisp.begin(0x73);
  gearBoxTempDisp.begin(0x74);
  tachDisp.setBrightness(15);
  speedoDisp.setBrightness(15);
  cvtTempDisp.setBrightness(15);
  gearBoxTempDisp.setBrightness(15);
}

void writeDisplays(){
  tachDisp.writeDisplay();
  speedoDisp.writeDisplay();
  cvtTempDisp.writeDisplay();
  gearBoxTempDisp.writeDisplay();
}

void displayStartup(){
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
  writeDisplays();
}

void displayZero(){
  tachDisp.println(0);
  speedoDisp.println(0);
  cvtTempDisp.println(0);
  gearBoxTempDisp.println(0);
  writeDisplays();
}

void displayClear(){
  tachDisp.println();
  speedoDisp.println();
  cvtTempDisp.println();
  gearBoxTempDisp.println();
  writeDisplays();
}

void displayError(int code){
  gearBoxTempDisp.writeDigitRaw(0,E);
  gearBoxTempDisp.writeDigitRaw(1,r);
  gearBoxTempDisp.writeDigitNum(3,int(code/10));
  gearBoxTempDisp.writeDigitNum(4,code%10);
  gearBoxTempDisp.drawColon(1);
  writeDisplays();
}

//unsigned int recentTach;
//float recentSpeedo;
//float recentCvtTemp;
//float recentGearBoxTemp;

const int maxTime = 5000;

unsigned long lastWriteTime = 0;

//unsigned int receiveData(){
//  byte payload[PAYLOAD_SIZE];
//  for(byte i = 0; i < PAYLOAD_SIZE; i ++){
//    payload[i] = Wire.read();
//  }
//  unsigned int data = *((unsigned int*)payload);
//  return data;
//}

const int wheelDia = 22;
const int spokes = 6;

unsigned int convertToRPM(unsigned int freq){
  //RPM:
  unsigned int RPM = freq*2;
  return RPM;
}

void writeLine(unsigned int tachData, unsigned int speedData, float cvtData, float gbData, boolean logger){
  DateTime logTime = rtc.now();
  char line[36];
  char MM[4];
  char SS[4];
  char TACH[6];
  char SPED[6];
  char CVTTE[7];
  char GBTEM[7];
  char F[2];

  if(logger) {
    F[0] = "1";
  }
  else {
    F[0] ="0";
  }
    
  sprintf(line, "%02d:", logTime.hour());
  sprintf(MM, "%02d:", logTime.minute());
  sprintf(SS, "%02d,", logTime.second());
  sprintf(TACH, "%04d,", tachData);
  //Serial.println(TACH);
  //sprintf included with arduino does not handle floats, so this:
  sprintf(SPED, "%02d.%01d,", (speedData));//, (round(getAverage(4)*10)%10)); //int(getAverage(recentData[1])), (round(getAverage(recentData[1])*10)%10));
  sprintf(CVTTE, "%03d.%01d,", (cvtData));//, (round(getAverage(4)*10)%10)); //int(getAverage(recentData[2])), (round(getAverage(recentData[2])*10)%10));
  sprintf(GBTEM, "%04d.%01d,", (gbData));//, (round(getAverage(4)*10)%10)); //int(getAverage(recentData[3])), (round(getAverage(recentData[3])*10)%10));

  strcat(line, MM);
  strcat(line, SS);
  //Serial.println(line);
  //Serial.println(TACH);
  strcat(line, TACH);
  //Serial.println(line);
  strcat(line, SPED);
  strcat(line, CVTTE);
  strcat(line, GBTEM);
  //strcat(line, F);

  Serial.println(line);

  logFile = SD.open(fileName, FILE_WRITE);
  if(logFile){
    logFile.println(line);
    logFile.close();
  }
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Starting Dash Display and Logger...");
#endif

  initializeDisplays();

  Wire.begin();        // Activate I2C link

  displayStartup();
  delay(3000);
  displayZero();
  pinMode(BUTTON_PIN,INPUT_PULLUP);

  if(!rtc.begin()){
    displayError(1);
    #ifdef DEBUG
      Serial.println("RTC failed initialization");
    #endif
    delay(5000);
  }

  if (rtc.lostPower()) {
    displayError(2);
    #ifdef DEBUG
      Serial.println("RTC time has been lost");
    #endif
    delay(5000);
  }

  if (!SD.begin(4)){
    displayError(3);
    #ifdef DEBUG
      Serial.println("SD failed initialization");
    #endif
    delay(5000);
  }

  DateTime now = rtc.now();
  char MO[3];
  char DD[3];
  char HH[3];
  char MI[3];
  sprintf(MO, "%02d", now.month());
  sprintf(DD, "%02d", now.day());
  sprintf(HH, "%02d", now.hour());
  sprintf(MI, "%02d", now.minute());
  strcat(fileName, MO);
  strcat(fileName, DD);
  strcat(fileName, HH);
  strcat(fileName, MI);
  strcat(fileName,".CSV");
  #ifdef DEBUG
    Serial.println(fileName);
  #endif

  logFile = SD.open(fileName, FILE_WRITE);
  if(!logFile){
    displayError(4);
    #ifdef DEBUG
      Serial.println("File creation failed");
    #endif
    delay(5000);
  }
  logFile.close();
}

void loop() {
  
  if (!digitalRead(BUTTON_PIN)) {
    logFlag = true;
  }

  if(true){
    recentData[0] = 567;
    recentData[1] = 234;
    recentData[2] = 567;
    recentData[3] = 132;
    
    acceptSample(&tach, recentData[0]);
    acceptSample(&speedo, recentData[1]);
    acceptSample(&cvtTemp, recentData[2]);
    acceptSample(&gearBoxTemp, recentData[3]);
  }

  tachDisp.println(int(getAverage(&tach)));
  speedoDisp.println(int((getAverage(&speedo))/100));
  cvtTempDisp.println(((getAverage(&cvtTemp))/100),1);
  gearBoxTempDisp.println(((getAverage(&gearBoxTemp))/100),1);

  writeDisplays();

  if (millis() - lastWriteTime > maxTime) {
    unsigned int logTach = (getAverage(&tach));
    unsigned int logSpeedo = (getAverage(&speedo))/100;
    float logCvt = (getAverage(&cvtTemp))/100;
    float logGb = (getAverage(&gearBoxTemp))/100;
    writeLine(logTach, logSpeedo, logCvt, logGb, logFlag);
    Serial.println(logTach);
    Serial.println(logSpeedo);
    Serial.println(logCvt);
    Serial.println(logGb);
    logFlag = false;
  #ifdef DEBUG
    Serial.println("Writing line to SD card");
  #endif
    lastWriteTime = millis();
    resetAverage(&tach);
    resetAverage(&speedo);
    resetAverage(&cvtTemp);
    resetAverage(&gearBoxTemp);
  }
  (refreshTime);
}
