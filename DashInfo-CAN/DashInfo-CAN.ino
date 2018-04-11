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

#define PAYLOAD_SIZE 2 // how many bytes to expect from each I2C salve node
#define NODE_MAX 4 // maximum number of slave nodes (I2C addresses) to probe
#define START_NODE 2 // The starting I2C address of slave nodes
//#define NODE_READ_DELAY 1 // Some delay between I2C node reads

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
  speedoDisp.begin(0x73);
  cvtTempDisp.begin(0x74);
  gearBoxTempDisp.begin(0x72);
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

unsigned int receiveData(){
  byte payload[PAYLOAD_SIZE];
  for(byte i = 0; i < PAYLOAD_SIZE; i ++){
    payload[i] = Wire.read();
  }
  unsigned int data = *((unsigned int*)payload);
  return data;
}

const int wheelDia = 22;
const int spokes = 6;

unsigned int convertToRPM(unsigned int freq){
  //RPM:
  unsigned int RPM = freq*2;
  return RPM;
}



void writeLine(unsigned int tachData, float speedData, float cvtData, float gbData, boolean logger){
  DateTime logTime = rtc.now();
  char line[33];
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
  sprintf(TACH, "%04d,", getAverage(recentData[0]));
  //sprintf included with arduino does not handle floats, so this:
  sprintf(SPED, "%02d.%01d,", int(getAverage(recentData[1])), (round(getAverage(recentData[1])*10)%10));
  sprintf(CVTTE, "%03d.%01d,", int(getAverage(recentData[2])), (round(getAverage(recentData[2])*10)%10));
  sprintf(GBTEM, "%03d.%01d,", int(getAverage(recentData[3])), (round(getAverage(recentData[3])*10)%10));

  strcat(line, MM);
  strcat(line, SS);
  strcat(line, TACH);
  strcat(line, SPED);
  strcat(line, CVTTE);
  strcat(line, GBTEM);
  strcat(line, F);

  Serial.println(line);

  logFile = SD.open(fileName, FILE_WRITE);
  if(logFile){
    logFile.println(line);
    logFile.close();
  }
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
  
//  recentTach = analogRead(0);
//  recentSpeedo = analogRead(1)/100;
//  recentCvtTemp = analogRead(2)/10;
//  recentGearBoxTemp = analogRead(3)/10;
    

  if (!digitalRead(BUTTON_PIN)) {
    logFlag = true;
  }
/*
  for(int i = 0; i < 4; i++){
    recentData[i]=analogRead(0);
  }*/
  recentData[0] = 1234;
  recentData[1] = 123;
  recentData[2] = 234;
  recentData[3] = 345;

  
  acceptSample(&tach, recentData[0]);
  acceptSample(&speedo, recentData[1]);
  acceptSample(&cvtTemp, recentData[2]);
  acceptSample(&gearBoxTemp, recentData[3]);

  tachDisp.println(recentData[0]);
  speedoDisp.println(recentData[1]/100);
  cvtTempDisp.println(recentData[2]/100);
  gearBoxTempDisp.println(recentData[3]/100);

  writeDisplays();

  if (millis() - lastWriteTime > maxTime) {
    unsigned int logTach = round(getAverage(&tach));
    float logSpeedo = round(getAverage(&speedo)*100)/100;
    float logCvt = round(getAverage(&cvtTemp)*100)/100;
    float logGb = round(getAverage(&gearBoxTemp)*100)/100;
    writeLine(logTach, logSpeedo, logCvt, logGb, logFlag);
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
  delay(refreshTime);
}
