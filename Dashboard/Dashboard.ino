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
 * GB Temp     | *1      | *1      | 10-120 C
 * CVT Temp    | *1      | *1      | 10-120 C
 */

//#define DEBUG

/*ERROR CODES:
E 01: RTC failed initialization
E 02: RTC time has been lost
E 03: SD failed initialization
E 04: CAN failed initialization
E 05: File creation failed
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>
#include <mcp_can.h>
/* Display segment layout:

     8
   -----
 3| 2  |7
   -----
 4| 5  |6
   -----  .1

*/

#define LETTER_O B00111111
#define LETTER_L B00111000
#define LETTER_I B00000110
#define LETTER_n B01010100
#define LETTER_b B01111100
#define LETTER_A B01110111
#define LETTER_J B00011110
#define LETTER_E B01111001
#define LETTER_r B01010000

RTC_DS3231 rtc;
File logFile;
char fileName[13];
boolean logFlag = false;


#define SPEEDO_POS 0
#define TACH_POS 1
#define CVT_POS 2
#define GEARBOX_POS 3

#define BUTTON_PIN 2 //logger button pin 2

#define REFRESH_TIME 100

#define ERROR_DISPLAY_TIME 500

//long unsigned int rxId = 0x101;
#define DATA_LEN 4
uint8_t rxBuf[DATA_LEN*sizeof(int)];         //raw data from CAN
unsigned int recentData[DATA_LEN];             //data from CAN converted back to ints
//#define CAN0_INT 2                          // Set INT to pin 2
MCP_CAN CAN0(10);                           // Set CS to pin 10


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
  tachDisp.begin(0x73);
  speedoDisp.begin(0x70);
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
  speedoDisp.writeDigitRaw(0,LETTER_O);
  speedoDisp.writeDigitRaw(1,LETTER_L);
  speedoDisp.writeDigitRaw(3,LETTER_I);
  speedoDisp.writeDigitRaw(4,LETTER_n);
  tachDisp.writeDigitRaw(0,LETTER_b);
  tachDisp.writeDigitRaw(1,LETTER_A);
  tachDisp.writeDigitRaw(3,LETTER_J);
  tachDisp.writeDigitRaw(4,LETTER_A);
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
  gearBoxTempDisp.writeDigitRaw(0,LETTER_E);
  gearBoxTempDisp.writeDigitRaw(1,LETTER_r);
  gearBoxTempDisp.writeDigitNum(3,int(code/10));
  gearBoxTempDisp.writeDigitNum(4,code%10);
  gearBoxTempDisp.drawColon(1);
  writeDisplays();
}

#define WRITE_INTERVAL 5000

unsigned long lastWriteTime = 0;

void writeLine(unsigned int tachData, float speedData, unsigned int cvtData, unsigned int gbData, boolean logger){
  DateTime logTime = rtc.now();
  char line[27];
  char MM[4];
  char SS[4];
  char SPED[6];
  char TACH[6];
  char CVT[5];
  char GBT[5];
  char F[3];

  if(logger) {
    F[0] = '1';
  }
  else {
    F[0] = '0';
  }
  F[1] = ',';
    
  sprintf(line,"%02d:", logTime.hour());
  sprintf(MM, "%02d:", logTime.minute());
  sprintf(SS, "%02d,", logTime.second());
  //sprintf included with arduino does not handle floats, so this:
  sprintf(SPED, "%02d.%01d,", int(speedData), (round(speedData*10)%10));
  sprintf(TACH, "%04d,", tachData);
  sprintf(CVT, "%03d,", round(cvtData));
  sprintf(GBT, "%03d,", round(gbData));

  strcat(line, MM);
  strcat(line, SS);
  strcat(line, SPED);
  strcat(line, TACH);
  strcat(line, CVT);
  strcat(line, GBT);
  strcat(line, F);

  #ifdef DEBUG
    Serial.println(line);
  #endif

  logFile = SD.open(fileName, FILE_WRITE);
  if(logFile){
    logFile.println(line);
    logFile.close();
  }
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Starting Dash Display and Logger in Debug Mode...");
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
    delay(ERROR_DISPLAY_TIME);
  }

  if (rtc.lostPower()) {
    displayError(2);
    #ifdef DEBUG
      Serial.println("RTC time has been lost");
    #endif
    delay(ERROR_DISPLAY_TIME);
  }

  if (!SD.begin(4)){
    displayError(3);
    #ifdef DEBUG
      Serial.println("SD failed initialization");
    #endif
    delay(ERROR_DISPLAY_TIME);
  }


  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(!CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK){
    displayError(4);
    #ifdef DEBUG
      Serial.println("CAN failed initialization");
    #endif
    delay(ERROR_DISPLAY_TIME);
  }


  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data. //makes the Message Sent successfully on the RX side. 
  //pinMode(CAN0_INT, INPUT);                     // Configuring pin for /INT input

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
    displayError(5);
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

  CAN0.readMsgBuf(0x101, DATA_LEN, rxBuf);
  memcpy(recentData,rxBuf,DATA_LEN*sizeof(int));

  acceptSample(&tach, recentData[0]);
  acceptSample(&speedo, recentData[1]);
  acceptSample(&cvtTemp, recentData[2]);
  acceptSample(&gearBoxTemp, recentData[3]);
  //Serial.println(realData[0]);

  speedoDisp.printFloat((float)recentData[SPEEDO_POS]/100,1);
  tachDisp.println(recentData[TACH_POS]);
  cvtTempDisp.println(recentData[CVT_POS]);
  gearBoxTempDisp.println(recentData[GEARBOX_POS]);

  writeDisplays();

  if (millis() - lastWriteTime > WRITE_INTERVAL) {
    unsigned int logTach = (getAverage(&tach));
    float logSpeedo = (getAverage(&speedo))/100;
    unsigned int logCvt = (getAverage(&cvtTemp));
    unsigned int logGb = (getAverage(&gearBoxTemp));
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
}
